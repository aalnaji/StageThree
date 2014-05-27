#include "ball.h"


Ball::Ball(BallConfigItem * config)
    : radius(config->getRadius())
    , velocity(config->getXVelocity(), config->getYVelocity())
    , color(config->getColor())
{
    setPos(mapToScene(config->getXCoordinate(), config->getYCoordinate()));
}

Ball::~Ball()
{
}

/*
 * Re-implemetation of QGraphics::advance, this function determines how to animate the next frame.
 * Below I check the window bounds with diameter rather than radius is because I set QRect boundingRect
 * to coordinates on the top left corner instead of the center.
 */
void Ball::advance(int phase)
{
    if (!phase) {
      return;
    }

    float futureXPos = pos().x() + velocity.x();
    float futureYPos= pos().y() + velocity.y();
    float diameter = radius * 2;

    // Bounce off walls...
    if (futureYPos <= 0) {
        velocity.setY(velocity.y() * -1);
        setPos(futureXPos, -1 * futureYPos);
    } else if (futureXPos <= 0) {
        velocity.setX(velocity.x() * -1);
        setPos(-1 * futureXPos, futureYPos);
    } else if (futureYPos >= scene()->height() - diameter) {
        velocity.setY(velocity.y() * -1);
        setPos(futureXPos, 2 * scene()->height() - futureYPos - 2 * diameter);
    } else if (futureXPos >= scene()->width() - diameter) {
        velocity.setX(velocity.x() * -1);
        setPos(2 * scene()->width() - futureXPos - 2 * diameter, futureYPos);
    } else {
        setPos(futureXPos, futureYPos);
    }

    // Bounce of other items.
    QList<QGraphicsItem *> collidingItems = this->collidingItems();

    // For each colliding item, check what type it is and resolve the collision.
    for (QList<QGraphicsItem *>::iterator iter = collidingItems.begin(); iter != collidingItems.end(); ++iter) {
        QGraphicsItem *item = *iter;

        if (Ball *b = dynamic_cast<Ball *>(item)) {
            // We have a ball...

            QVector2D delta(getCenter() - b->getCenter());
            float length = delta.length();

            if (length > radius + b->radius) {
                // Not actually colliding yet...
                continue;
            }

            // minimum translation distance (mtd) to push balls apart after intersecting
            QVector2D mtd = delta * (((radius + b->radius) - length) / length);

            // Push balls apart
            setPos(pos() + (mtd.toPointF() * 0.5));
            b->setPos(b->pos() - (mtd.toPointF() * 0.5));

            // Get unit vector.
            delta = delta / delta.length();

            QVector2D vel = velocity - b->velocity;
            float vn = QVector2D::dotProduct(vel, delta);

            // If balls are moving away from each other already.
            if (vn > 0.0) {
                continue;
            }

            // Get scale of reflected velocity.
            double ball1dot = QVector2D::dotProduct(velocity, delta);
            double ball2dot = QVector2D::dotProduct(b->velocity, delta);

            // Apply the new velocities to their balls.
            velocity += (ball2dot - ball1dot) * delta;
            b->velocity += (ball1dot - ball2dot) * delta;

        } else if (Block *b = dynamic_cast<Block *>(item)) {
            // We have a block...

            float bX = b->pos().x();
            float bY = b->pos().y();
            QPointF centre = getCenter();

            /*
             * 3 cases:
             * 1) The ball centre is between the left and right sides, so it's colliding with the top or bottom.
             * 2) The ball centre is between the top and bottom sides, so it's colliding with the left or right.
             * 3) The ball is colliding with a corner.
             */

            // If the ball centre is directly over an edge then it's an edge collision...
            if (centre.x() > bX
                 && centre.x() < bX + b->getWidth()) {
                // Only need to look at top and bottom collisions...

                float ballTopEdge = pos().y();
                float ballBottomEdge = pos().y() + radius * 2;

                float blockTopEdge = bY;
                float blockBottomEdge = bY + b->getHeight();

                if (blockTopEdge < ballTopEdge
                        && ballTopEdge < blockBottomEdge) {
                    // block being hit from the south...
                    velocity.setY(velocity.y() * -1);
                    setPos(pos().x(), pos().y() + (blockBottomEdge - ballTopEdge));
                    b->decrementLives();

                } else if (blockBottomEdge > ballBottomEdge
                           && ballBottomEdge > blockTopEdge) {
                    // block being hit from the north...
                    velocity.setY(velocity.y() * -1);
                    setPos(pos().x(), pos().y() - (ballBottomEdge - blockTopEdge));
                    b->decrementLives();
                }

            } else if (centre.y() > bY
                 && centre.y() < bY + b->getHeight()) {
                // Only need to look at left and right collisions...
                float ballLeftEdge = pos().x();
                float ballRightEdge = pos().x() + radius * 2;
                float blockLeftEdge = bX;
                float blockRightEdge = bX + b->getWidth();

                if (blockLeftEdge < ballLeftEdge
                        && ballLeftEdge < blockRightEdge) {
                    // block being hit from the east...
                    velocity.setX(velocity.x() * -1);
                    setPos(pos().x() + (blockRightEdge - ballLeftEdge), pos().y());
                    b->decrementLives();

                } else if (blockRightEdge > ballRightEdge
                           && ballRightEdge > blockLeftEdge) {
                    // block being hit from the west...
                    velocity.setX(velocity.x() * -1);
                    setPos(pos().x() - (ballRightEdge - blockLeftEdge), pos().y());
                    b->decrementLives();

                }

            } else {
                // It's a collision on the corners of the block...
                // Get the distance to the 4 corner points and find the closet.
                QPointF northEastCorner(b->pos());
                QPointF northWestCorner(b->pos().x() + b->getWidth(), b->pos().y());
                QPointF southEastCorner(b->pos().x(), b->pos().y() + b->getHeight());
                QPointF southWestCorner(b->pos().x() + b->getWidth(), b->pos().y() + b->getHeight());

                QVector2D northEastVect(centre - northEastCorner);
                QVector2D northWestVect(centre - northWestCorner);
                QVector2D southEastVect(centre - southEastCorner);
                QVector2D southWestVect(centre - southWestCorner);

                float NE = northEastVect.length();
                float NW = northWestVect.length();
                float SE = southEastVect.length();
                float SW = southWestVect.length();

                if (NE < NW && NE < SE && NE < SW) {
                    resolveCornerCollision(northEastVect, b);
                } else if (NW < NE && NW < SE && NW < SW) {
                    resolveCornerCollision(northWestVect, b);
                } else if (SE < NE && SE < NW && SE < SW) {
                    resolveCornerCollision(southEastVect, b);
                } else { // SW must be min.
                    resolveCornerCollision(southWestVect, b);
                }

            }
        }

        std::cout.flush();

    }
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QRectF rec = boundingRect();
    QBrush brush(color);
    painter->setBrush(brush);
    painter->setPen(color);
    painter->drawEllipse(rec);
}

QRectF Ball::boundingRect() const
{
    return QRectF(0, 0, radius*2, radius*2);
}

QPointF Ball::getPosition() const
{
    return pos();
}

QPointF Ball::getCenter() const
{
    QPointF center(pos().x() + radius, pos().y() + radius);
    return center;
}

int Ball::getRadius() const
{
    return radius;
}

void Ball::setVelocity(QVector2D newVelocity)
{
    velocity = newVelocity;
}


void Ball::resolveCornerCollision(QVector2D &distVect, Block *block)
{
    float length = distVect.length();

    if (length > radius) {
        // Not actually colliding yet...
        return;
    }

    // minimum translation distance (mtd) to push balls apart after intersecting
    QVector2D mtd = distVect * ((radius - length) / length);

    // Push balls apart
    setPos(pos() + mtd.toPointF());

    // Get unit vector.
    distVect = distVect / distVect.length();

    // Get scale of reflected velocity.
    double ballDot = QVector2D::dotProduct(velocity, distVect);

    // If balls are moving away from each other already.
    if (ballDot > 0.0) {
        return;
    }

    // Apply the new velocities to their balls.
    velocity += (-2 * ballDot) * distVect;
    block->decrementLives();
}

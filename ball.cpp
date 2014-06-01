#include <iostream>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPainter>

#include "ball.h"
#include "ballconfigitem.h"
#include "paddle.h"
#include "block.h"
#include "config.h"
#include "chainofresponsibility.h"
#include "Events.h"

Ball::Ball(BallConfigItem * config)
    : QGraphicsEllipseItem(0, 0,config->getRadius()* 2.0, config->getRadius()* 2.0)
	, radius(config->getRadius())
    , velocity(config->getVelocity())
    , color(config->getColor())
{
	setBrush(QBrush(color));
	setPos(config->getCoordinates());
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

	QPointF futurePos(pos()+ velocity.toPointF());

    // Bounce off walls...
    if (futurePos.y() <= 0)
		velocity.setY(-velocity.y()); // left
    else if (futurePos.x() <= 0)
		velocity.setX(-velocity.x()); // top
	else if (futurePos.y() >= scene()->height()- 2.0* radius) {
		velocity.setY(-velocity.y()); // right
		BallLostEvent ballost;
		ChainOfResponsibility::get().handleEvent(&ballost);
	} else if (futurePos.x() >= scene()->width()- 2.0* radius)
		velocity.setX(-velocity.x()); // bottom



	moveBy(velocity.x(), velocity.y());

    // Bounce of other items.
    QList<QGraphicsItem *> collidingItems(this->collidingItems());

    // For each colliding item, check what type it is and resolve the collision.
    for (QList<QGraphicsItem *>::iterator iter(collidingItems.begin()); iter != collidingItems.end(); ++iter) {
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

        } else if (dynamic_cast<QGraphicsRectItem *>(item)) {
			// We have an item that is square in shape,i.e, either the paddle or a block
			QRectF box(static_cast<QGraphicsRectItem *>(item)->rect());

            float bX(item->pos().x());
            float bY(item->pos().y());
            QPointF centre(getCenter());

            /*
             * 3 cases:
             * 1) The ball centre is between the left and right sides, so it's colliding with the top or bottom.
             * 2) The ball centre is between the top and bottom sides, so it's colliding with the left or right.
             * 3) The ball is colliding with a corner.
             */

            // If the ball centre is directly over an edge then it's an edge collision...
            if (centre.x() > bX
                 && centre.x() < bX + box.width()) {
                // Only need to look at top and bottom collisions...

                float ballTopEdge = pos().y();
                float ballBottomEdge = ballTopEdge + radius * 2.0;

                float blockTopEdge = bY;
                float blockBottomEdge = bY + box.height();
                if (blockTopEdge < ballTopEdge
                        && ballTopEdge < blockBottomEdge) {
                    // block being hit from the south...
                    velocity.setY(-velocity.y());
                    //setPos(pos().x(), pos().y() + (blockBottomEdge - ballTopEdge));
					moveBy(0.0 , blockBottomEdge - ballTopEdge);
                    if(dynamic_cast<Block *>(item))
						static_cast<Block *>(item)->decrementLives();

                } else if (blockBottomEdge > ballBottomEdge
                           && ballBottomEdge > blockTopEdge) {
                    // block being hit from the north...
                    velocity.setY(-velocity.y());
                    //setPos(pos().x(), pos().y() - (ballBottomEdge - blockTopEdge));
					moveBy(0.0, blockTopEdge- ballBottomEdge);
					if(dynamic_cast<Block *>(item))
						static_cast<Block *>(item)->decrementLives();
                }

            } else if (centre.y() > bY
                 && centre.y() < bY + box.height()) {
                // Only need to look at left and right collisions...
                float ballLeftEdge = pos().x();
                float ballRightEdge = pos().x() + radius * 2;
                float blockLeftEdge = bX;
                float blockRightEdge = bX + box.width();

                if (blockLeftEdge < ballLeftEdge
                        && ballLeftEdge < blockRightEdge) {
                    // block being hit from the east...
                    velocity.setX(-velocity.x());
                    setPos(pos().x() + (blockRightEdge - ballLeftEdge), pos().y());
					if(dynamic_cast<Block *>(item))
						static_cast<Block *>(item)->decrementLives();

                } else if (blockRightEdge > ballRightEdge
                           && ballRightEdge > blockLeftEdge) {
                    // block being hit from the west...
                    velocity.setX(-velocity.x());
                    setPos(pos().x() - (ballRightEdge - blockLeftEdge), pos().y());
					if(dynamic_cast<Block *>(item))
						static_cast<Block *>(item)->decrementLives();

                }

            } else {
                // It's a collision on the corners of the block...
                // Get the distance to the 4 corner points and find the closet.
                QPointF northEastCorner(box.topRight());
                QPointF northWestCorner(box.topLeft());
                QPointF southEastCorner(box.bottomRight());
                QPointF southWestCorner(box.bottomLeft());

                QVector2D northEastVect(centre - northEastCorner);
                QVector2D northWestVect(centre - northWestCorner);
                QVector2D southEastVect(centre - southEastCorner);
                QVector2D southWestVect(centre - southWestCorner);

                float NE = northEastVect.length();
                float NW = northWestVect.length();
                float SE = southEastVect.length();
                float SW = southWestVect.length();

                if (NE < NW && NE < SE && NE < SW) {
                    if(resolveCornerCollision(northEastVect)&& dynamic_cast<Block *>(item))
						static_cast<Block *>(item)->decrementLives();
                } else if (NW < NE && NW < SE && NW < SW) {
                    if(resolveCornerCollision(northWestVect)&& dynamic_cast<Block *>(item))
							static_cast<Block *>(item)->decrementLives();
                } else if (SE < NE && SE < NW && SE < SW) {
                    if(resolveCornerCollision(southEastVect)&& dynamic_cast<Block *>(item))
						static_cast<Block *>(item)->decrementLives();
                } else { // SW must be min.
                    if(resolveCornerCollision(southWestVect)&& dynamic_cast<Block *>(item))
							static_cast<Block *>(item)->decrementLives();
                }

            }
        }
    }
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

void Ball::setVelocity(QVector2D const &newVelocity)
{
    velocity = newVelocity;
}


bool Ball::resolveCornerCollision(QVector2D &distVect)
{
    float length = distVect.length();

    if (length > radius) {
        // Not actually colliding yet...
        return false;
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
        return false;
    }

    // Apply the new velocities to this ball
    velocity += (-2 * ballDot) * distVect;

	return true;
}

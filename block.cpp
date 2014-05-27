#include "block.h"

Block::Block(BlockConfigItem * config)
    : width(config->getWidth())
    , height(config->getHeight())
    , currentLives(config->getLives())
    , initialLives(config->getLives())
    , color(config->getColor())
    , hueVal(color.hueF())
    , satVal(color.saturationF())
    , ligVal(color.lightnessF())
{
    setPos(mapToScene(config->getXCoordinate(),
                      config->getYCoordinate()));
}

Block::~Block()
{
}

/*
 * Re-implemetation of QGraphics::advance, this function determines how to animate the next frame.
 * Below I check the window bounds with diameter rather than radius is because I set QRect boundingRect
 * to coordinates on the top left corner instead of the center.
 */
void Block::advance(int phase)
{
    if (!phase) {
        update();
    }

    // Check if there are any overlapping blocks...
    QList<QGraphicsItem *> ci = collidingItems();

    for (QList<QGraphicsItem *>::iterator iter = ci.begin(); iter != ci.end(); ++iter) {
        QGraphicsItem *item = *iter;
        if (Block *b = dynamic_cast<Block *>(item)) {
            if (b->zValue() > zValue()) {
                scene()->removeItem(b);
                delete b;
            }
        }
    }

    // Delete if all lives have been lost.
    if (currentLives <= 0) {
        scene()->removeItem(this);
        delete this;
    }

    // Cycle through all the hue colours over the course of all the lives.
    float newHueVal = hueVal - currentLives / (double) initialLives;
    if (newHueVal < 0) {
        newHueVal += 1;
    }
    color.setHslF(newHueVal, satVal, ligVal);
}

void Block::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QRectF rec = boundingRect();
    QBrush brush(color);
    painter->setBrush(brush);
    painter->drawRect(rec);
}

QRectF Block::boundingRect() const
{
    return QRectF(0, 0, width, height);
}

QPointF Block::getPosition() const
{
    return pos();
}

int Block::getWidth() const
{
    return width;
}

int Block::getHeight() const
{
    return height;
}

int Block::getLives() const
{
    return currentLives;
}

void Block::decrementLives()
{
    currentLives--;
}

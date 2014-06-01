#include "block.h"
#include "blockconfigitem.h"
#include <QPainter>
#include <QGraphicsScene>
#include "score.h"
#include "chainofresponsibility.h"
#include "Events.h"

Block::Block(BlockConfigItem * config)
    : QGraphicsRectItem(config->getRect())
    , currentLives(config->getLives())
    , initialLives(config->getLives())
    , color(config->getColor())
    , hueVal(color.hueF())
    , satVal(color.saturationF())
    , ligVal(color.lightnessF())
{
	setPos(config->getCoordinates());
	setBrush(QBrush(color));
}

/*
 * Re-implemetation of QGraphics::advance, this function determines how to animate the next frame.
 * Below I check the window bounds with diameter rather than radius is because I set QRect boundingRect
 * to coordinates on the top left corner instead of the center.
 */
void Block::advance(int phase)
{
    if (!phase) {
        return;
    }

    // Check if there are any overlapping blocks...
/*    QList<QGraphicsItem *> ci(collidingItems());

    for (QList<QGraphicsItem *>::iterator iter(ci.begin()); iter != ci.end(); ++iter) {
        QGraphicsItem *item = *iter;
        if (Block *b = dynamic_cast<Block *>(item)) {
            if (b->zValue() > zValue()) {
                scene()->removeItem(b);
                delete b;
            }
        }
    }*/

    // Delete if all lives have been lost.
    if (currentLives <= 0) {
        scene()->removeItem(this);
		/* Killing the block adds 10 points. */
		Score::get().add(10);
		BlockDeletedEvent bde;
		ChainOfResponsibility::get().handleEvent(&bde);
        delete this;
		return;
    }

    // Cycle through all the hue colours over the course of all the lives.
    float newHueVal = hueVal - currentLives / (double) initialLives;
    if (newHueVal < 0) {
        newHueVal += 1;
    }
    color.setHslF(newHueVal, satVal, ligVal);
	setBrush(QBrush(color));
}

QPointF Block::getPosition() const
{
    return pos();
}

int Block::getLives() const
{
    return currentLives;
}

void Block::decrementLives()
{
    currentLives--;
	/* A single hit adds one point. */
	Score::get().add(1);
}

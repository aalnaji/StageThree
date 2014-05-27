#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QPoint>
#include <QColor>
#include "config.h"

/* Add forward declaration to minimize compile time. */
class BlockConfigItem;
class QPainter;

/**
 * @brief The Block class
 */
class Block : public QGraphicsRectItem
{
public:
    Block(BlockConfigItem * config);

    /* The QGraphicsScene searches for the QGraphicsItem::advance and paint
     * in order for us to animate the ball
     */
    void advance(int phase);

    QPointF getPosition() const;
    int getLives() const;
    void decrementLives();

private:
    int currentLives;
    int initialLives;
    QColor color;
    float hueVal;
    float satVal;
    float ligVal;
};

#endif // BLOCK_H

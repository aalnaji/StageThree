#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPoint>
#include <QPainter>
#include <QColor>
#include "config.h"

/**
 * @brief The Block class
 */
class Block : public QGraphicsItem
{
public:
    Block(BlockConfigItem * config);

    virtual ~Block();

    /* The QGraphicsScene searches for the QGraphicsItem::advance and paint
     * in order for us to animate the ball
     */
    void advance(int phase);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    /* Fames around the item (ball). This function returns QRectF(0, 0, radius*2, radius*2)
     * meaning the origin of the ball/item has moved from the center to the top
     * left corner of the frame
     */
    QRectF boundingRect() const;

    QPointF getPosition() const;
    int getWidth() const;
    int getHeight() const;
    int getLives() const;
    void decrementLives();

private:
    int width;
    int height;
    int currentLives;
    int initialLives;
    QColor color;
    float hueVal;
    float satVal;
    float ligVal;
};

#endif // BLOCK_H

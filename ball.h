#ifndef BALL_H
#define BALL_H

#include <iostream>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPoint>
#include <QPainter>
#include <QColor>
#include <QVector2D>
#include "config.h"

#include "block.h"

/**
 * @brief The Ball class
 */
class Ball : public QGraphicsItem
{
public:
    Ball(BallConfigItem * config);

    virtual ~Ball();

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
    QPointF getCenter() const;
    int getRadius() const;
    QVector2D getVelocity() const;
    void setVelocity(QVector2D newVelocity);

private:
    void resolveCornerCollision(QVector2D &distVect, Block *block);

    int radius;
    QVector2D velocity;
    QColor color;
};

#endif // BALL_H

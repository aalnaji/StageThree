#ifndef BALL_H
#define BALL_H

#include <QGraphicsEllipseItem>
#include <QColor>
#include <QVector2D>
#include <QPoint>

// Forward declaration. The implementation is only needed in the cpp.
class BallConfigItem;

/**
 * @brief The Ball class
 */
class Ball : public QGraphicsEllipseItem
{
public:
    Ball(BallConfigItem * config);

    /* The QGraphicsScene searches for the QGraphicsItem::advance and paint
     * in order for us to animate the ball
     */
    void advance(int phase);

    QPointF getCenter() const;
    int getRadius() const;
	inline QVector2D getVelocity() const { return velocity; };
    void setVelocity(const QVector2D &newVelocity);

private:
    bool resolveCornerCollision(QVector2D &distVect);

    int radius;
    QVector2D velocity;
    QColor color;
};

#endif // BALL_H

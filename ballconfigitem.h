#ifndef BALLCONFIGITEM_H
#define BALLCONFIGITEM_H

#include <QColor>
#include <QRect>
#include <QPointF>
#include <QVector2D>

#include "configitem.h"

/** The config item for a ball. Reworked to interface better with
 * a QGraphicsItem. */
class BallConfigItem : public ConfigItem
{
public:
    BallConfigItem();

    bool validate(int height, int width) const;

    Item getItemType() const;

    void addParameter(std::string name, double value);

	/** Setters and getters for the coordinates. */
	inline QPointF getCoordinates() const { return coordinate; };
	inline void setCoordinate(QPointF const &ncoor) { coordinate= ncoor; };
    void setXCoordinate(int);
    void setYCoordinate(int);

	inline int getRadius() const { return radius; };
    void setRadius(int);

	/** Methods to care about the velocity. */
	QVector2D getVelocity() const { return velocity; };
    void setVelocity(float, float);
    void setXVelocity(float);
    void setYVelocity(float);

    QColor getColor() const;
    void setHue(float);

private:
    QPointF coordinate;
    int radius;
	QVector2D velocity;
    QColor color;
};

#endif // BALLCONFIGITEM_H

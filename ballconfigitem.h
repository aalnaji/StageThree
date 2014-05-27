#ifndef BALLCONFIGITEM_H
#define BALLCONFIGITEM_H

#include <QColor>
#include <iostream>
#include <QRect>

#include "configitem.h"
#include "item.h"
#include "defaults.h"

class BallConfigItem : public ConfigItem
{
public:
    BallConfigItem();

    ~BallConfigItem();

    bool validate(int height, int width) const;

    Item getItemType() const;

    void addParameter(std::string name, double value);

    int getXCoordinate() const;
    void setXCoordinate(int);

    int getYCoordinate() const;
    void setYCoordinate(int);

    int getRadius() const;
    void setRadius(int);

    float getXVelocity() const;
    void setXVelocity(float);

    float getYVelocity() const;
    void setYVelocity(float);

    QColor getColor() const;
    void setHue(float);

private:
    int xCoordinate;
    int yCoordinate;
    int radius;
    float xVelocity;
    float yVelocity;
    QColor color;
};

#endif // BALLCONFIGITEM_H

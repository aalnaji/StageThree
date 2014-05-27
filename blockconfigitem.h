#ifndef BLOCKCONFIGITEM_H
#define BLOCKCONFIGITEM_H

#include <QColor>
#include <iostream>
#include <QRect>

#include "configitem.h"
#include "item.h"
#include "defaults.h"

class BlockConfigItem : public ConfigItem
{
public:
    BlockConfigItem();

    ~BlockConfigItem();

    bool validate(int height, int width) const;

    Item getItemType() const;

    void addParameter(std::string name, double value);

    int getXCoordinate() const;
    void setXCoordinate(int);

    int getYCoordinate() const;
    void setYCoordinate(int);

    int getWidth() const;
    void setWidth(int);

    int getHeight() const;
    void setHeight(int);

    int getLives() const;
    void setLives(int);

    QColor getColor() const;
    void setHue(float);

private:
    int xCoordinate;
    int yCoordinate;
    int width;
    int height;
    int lives;
    QColor color;
};

#endif // BLOCKCONFIGITEM_H

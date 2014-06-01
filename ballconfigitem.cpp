#include <iostream>

#include "ballconfigitem.h"
#include "defaults.h"

BallConfigItem::BallConfigItem()
    : ConfigItem()
    , coordinate(Defaults::BALL_X_COORDINATE, Defaults::BALL_Y_COORDINATE)
    , radius(Defaults::BALL_RADIUS)
    , velocity(Defaults::BALL_X_VELOCITY, Defaults::BALL_Y_VELOCITY)
    , color(Defaults::BALL_COLOR) {}

bool BallConfigItem::validate(int height, int width) const
{
    // Check if in the bounds of the scene.
    QRect wind(0, 0, width, height);
    QRect bal(coordinate.x(), coordinate.y(), radius * 2, radius * 2);

    // Checks if the ball is entirely within the window.
    return wind.contains(bal, true);
}

Item BallConfigItem::getItemType() const
{
    return BALL;
}

void BallConfigItem::addParameter(std::string name, double value)
{
    if (name == "xCoordinate") {
        setXCoordinate(value);
    } else if (name == "yCoordinate") {
        setYCoordinate(value);
    } else if (name == "radius") {
        setRadius(value);
    } else if (name == "xVelocity") {
        setXVelocity(value);
    } else if (name == "yVelocity") {
        setYVelocity(value);
    } else if (name == "colorHue") {
        if (value < 0 || value > 1) {
            std::cout << "Hue value out of bounds [0,1] when creating a ball." << std::endl;
            exit(0);
        }
        setHue(value);
    } else {
        // Unrecognised parameter.
        std::cout << "Unrecognised parameter when creating a ball: " + name << std::endl;
        exit(0);
    }
}

void BallConfigItem::setXCoordinate(int xCoordinate)
{
    this->coordinate.setX(xCoordinate);
}

void BallConfigItem::setYCoordinate(int yCoordinate)
{
    this->coordinate.setY(yCoordinate);
}

void BallConfigItem::setRadius(int radius)
{
    this->radius = radius;
}

void BallConfigItem::setXVelocity(float xVelocity)
{
    this->velocity.setX(xVelocity);
}

void BallConfigItem::setYVelocity(float yVelocity)
{
    this->velocity.setY(yVelocity);
}

QColor BallConfigItem::getColor() const
{
    return color;
}

void BallConfigItem::setHue(float colorHue)
{
    color.setHslF(colorHue, color.saturationF(), color.lightnessF());
}

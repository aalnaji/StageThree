#include "ballconfigitem.h"

BallConfigItem::BallConfigItem()
    : ConfigItem()
    , xCoordinate(Defaults::BALL_X_COORDINATE)
    , yCoordinate(Defaults::BALL_Y_COORDINATE)
    , radius(Defaults::BALL_RADIUS)
    , xVelocity(Defaults::BALL_X_VELOCITY)
    , yVelocity(Defaults::BALL_Y_VELOCITY)
    , color(Defaults::BALL_COLOR) {}

BallConfigItem::~BallConfigItem() {}

bool BallConfigItem::validate(int height, int width) const
{
    // Check if in the bounds of the scene.
    QRect wind(0, 0, width, height);
    QRect bal(xCoordinate, yCoordinate, radius * 2, radius * 2);

    // Checks if the block is entirely within the window.
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

int BallConfigItem::getXCoordinate() const
{
    return xCoordinate;
}

void BallConfigItem::setXCoordinate(int xCoordinate)
{
    this->xCoordinate = xCoordinate;
}

int BallConfigItem::getYCoordinate() const
{
    return yCoordinate;
}

void BallConfigItem::setYCoordinate(int yCoordinate)
{
    this->yCoordinate = yCoordinate;
}

int BallConfigItem::getRadius() const
{
    return radius;
}

void BallConfigItem::setRadius(int radius)
{
    this->radius = radius;
}

float BallConfigItem::getXVelocity() const
{
    return xVelocity;
}

void BallConfigItem::setXVelocity(float xVelocity)
{
    this->xVelocity = xVelocity;
}

float BallConfigItem::getYVelocity() const
{
    return yVelocity;
}

void BallConfigItem::setYVelocity(float yVelocity)
{
    this->yVelocity = yVelocity;
}

QColor BallConfigItem::getColor() const
{
    return color;
}

void BallConfigItem::setHue(float colorHue)
{
    color.setHslF(colorHue, color.saturationF(), color.lightnessF());
}

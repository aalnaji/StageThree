#include <iostream>

#include "paddleconfigitem.h"
#include "item.h"
#include "defaults.h"

PaddleConfigItem::PaddleConfigItem()
	: ConfigItem()
	, coordinates(Defaults::PADDLE_X_COORDINATE, Defaults::PADDLE_Y_COORDINATE)
    , theRectangle(0,0, Defaults::PADDLE_WIDTH, Defaults::PADDLE_HEIGHT)
    , color(Defaults::PADDLE_COLOR)
	, lives(Defaults::PADDLE_LIVES)
{
}

bool PaddleConfigItem::validate(int height, int width) const
{
    // Check if in the bounds of the scene.
    QRect wind(0, 0, width, height);
	QRect pad(theRectangle);
	pad.moveTo(coordinates);
    // Checks if the block is entirely within the window.
    return wind.contains(pad, true);
}

Item PaddleConfigItem::getItemType() const
{
    return PADDLE;
}

void PaddleConfigItem::addParameter(std::string name, double value)
{
    if (name == "xCoordinate") {
        setXCoordinate(value);
    } else if (name == "yCoordinate") {
        setYCoordinate(value);
    } else if (name == "paddleWidth") {
        setWidth(value);
    } else if (name == "paddleHeight") {
        setHeight(value);
    } else if (name == "colorHue") {
        setHue(value);
	} else if (name == "lives") {
		setLives(value);
    } else {
        // Unrecognised parameter.
        std::cout << "Unrecognised parameter when creating a paddle: " + name << std::endl;
        exit(0);
    }
}

int PaddleConfigItem::getXCoordinate() const
{
    return coordinates.x();
}

void PaddleConfigItem::setXCoordinate(int xCoordinate)
{
    coordinates.setX(xCoordinate);
}

int PaddleConfigItem::getYCoordinate() const
{
    return coordinates.y();
}

void PaddleConfigItem::setYCoordinate(int yCoordinate)
{
    coordinates.setY(yCoordinate);
}

float PaddleConfigItem::getWidth() const
{
    return theRectangle.width();
}

void PaddleConfigItem::setWidth(float width)
{
    theRectangle.setWidth(width);
}

float PaddleConfigItem::getHeight() const
{
    return theRectangle.height();
}

void PaddleConfigItem::setHeight(float height)
{
    theRectangle.setHeight(height);
}

QColor PaddleConfigItem::getColor() const
{
    return color;
}

void PaddleConfigItem::setHue(float colorHue)
{
	color.setHslF(colorHue, color.saturationF(), color.lightnessF());
}

/** Get and set the initial number of lives of this paddle. */
unsigned int PaddleConfigItem::getLives() const
{
	return lives;
}
void PaddleConfigItem::setLives(unsigned int lives) {
	this->lives= lives;
}

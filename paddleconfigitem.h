#ifndef PADDLECONFIGITEM_H
#define PADDLECONFIGITEM_H

#include <QColor>
#include <QRect>

#include "configitem.h"

/** Store the configuration options for a paddle.
 * This class essentially is a copy from the BlockConfigItem
 * with some internal changes.
 * @brief Store and propagate the paddle's configuration. */
class PaddleConfigItem : public ConfigItem
{
public:
	/** Set defaults for attributes. */
	PaddleConfigItem();
	/** Check that the paddle is in the visible area of the window. */
    bool validate(int height, int width) const;
	/** Identify us as a paddle. */
    Item getItemType() const;
	/** For easy creation of a graphics item, create a rect here. */
	QRect const getRect() const { return theRectangle; };
	/** Give the initial position of this paddle. */
	QPoint const getPos() const { return coordinates; };
	/** In the configuration file after a PADDLE section a parameter was found.
	 * Check if it is suitable for the paddle. */
    void addParameter(std::string name, double value);
	/** Get the x coordinate. */
    int getXCoordinate() const;
	/** Set the x coordinate. */
    void setXCoordinate(int);
	/** Get the y coordinate. */
    int getYCoordinate() const;
	/** Set the y coordinate. */
    void setYCoordinate(int);
	/** Get the width of the paddle. */
    float getWidth() const;
	/** Set the width of the paddle. */
    void setWidth(float);
	/** Get the height of the paddle. */
    float getHeight() const;
	/** Set the height of the paddle. */
    void setHeight(float);
	/** Get the color of the paddle. */
    QColor getColor() const;
	/** Set the color hue of the paddle. */
	void setHue(float);
	/** Get the initial number of lives of this paddle. */
	unsigned int getLives() const;
	/** Set the initial number of lives of this paddle. */
	void setLives(unsigned int lives);
private:
	/** The paddle position. */
	QPoint coordinates;
	/** The paddle width and height. */
    QRect theRectangle;
	/** The color of the paddle. */
    QColor color;
	/** The number of lives the paddle is configured to be created with. */
	unsigned int lives;
};

#endif // PADDLECONFIGITEM_H

#ifndef PADDLECONFIGITEM_H
#define PADDLECONFIGITEM_H

#include <QColor>
#include <QRect>

#include "configitem.h"

/** Store the configuration options for a paddle.
 * This class essentially is a copy from the BlockConfigItem
 * with some internal changes. */
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
	QRect const getRect() const { return QRect(0, 0, theRectangle.width(), theRectangle.height()); };
	/** Give the initial position of this paddle. */
	QPointF const getPos() const { return theRectangle.topLeft(); };
	/** In the configuration file after a PADDLE section a parameter was found.
	 * Check if it is suitable for the paddle. */
    void addParameter(std::string name, double value);
	/** Getters and setters. */
    int getXCoordinate() const;
    void setXCoordinate(int);

    int getYCoordinate() const;
    void setYCoordinate(int);

    float getWidth() const;
    void setWidth(float);

    float getHeight() const;
    void setHeight(float);

    QColor getColor() const;
	void setHue(float);

	/** Get and set the initial number of lives of this paddle. */
	unsigned int getLives() const;
	void setLives(unsigned int lives);
private:
	/** The paddle position and its width/height in one structure. */
    QRect theRectangle;
	/** The color of the paddle. */
    QColor color;
	/** The number of lives the paddle is configured to be created with. */
	unsigned int lives;
};

#endif // PADDLECONFIGITEM_H

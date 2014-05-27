#include "blockconfigitem.h"

BlockConfigItem::BlockConfigItem()
    : ConfigItem()
	, theRectangle(Defaults::BLOCK_X_COORDINATE, Defaults::BLOCK_Y_COORDINATE,
			Defaults::BLOCK_WIDTH, Defaults::BLOCK_HEIGHT)
    , lives(Defaults::BLOCK_LIVES)
    , color(Defaults::BLOCK_COLOR) {}

BlockConfigItem::~BlockConfigItem() {}

bool BlockConfigItem::validate(int width, int height) const
{
    // Check if in the bounds of the scene.
    QRect wind(0,0,width, height);

    // Checks if the block is entirely within the window.
    return wind.contains(theRectangle, true);
}

Item BlockConfigItem::getItemType() const
{
    return BLOCK;
}

void BlockConfigItem::addParameter(std::string name, double value)
{
    if (name == "blockXCoordinate") {
        setXCoordinate(value);
    } else if (name == "blockYCoordinate") {
        setYCoordinate(value);
    } else if (name == "blockWidth") {
        setWidth(value);
    } else if (name == "blockHeight") {
        setHeight(value);
    } else if (name == "blockLives") {
        setLives(value);
    } else if (name == "colorHue") {
        if (value < 0 || value > 1) {
            std::cout << "Hue value out of bounds [0,1] when creating a block." << std::endl;
            exit(0);
        }
        setHue(value);
    } else {
        // Unrecognised parameter.
        std::cout << "Unrecognised parameter when creating a block: " + name << std::endl;
        exit(0);
    }
}

void BlockConfigItem::setXCoordinate(int xCoordinate)
{
    theRectangle.setX(xCoordinate);
}

void BlockConfigItem::setYCoordinate(int yCoordinate)
{
    theRectangle.setY(yCoordinate);
}

int BlockConfigItem::getWidth() const
{
    return theRectangle.width();
}

void BlockConfigItem::setWidth(int width)
{
    theRectangle.setWidth(width);
}

int BlockConfigItem::getHeight() const
{
    return theRectangle.height();
}

void BlockConfigItem::setHeight(int height)
{
    theRectangle.setHeight(height);
}

int BlockConfigItem::getLives() const
{
    return lives;
}

void BlockConfigItem::setLives(int lives)
{
    this->lives = lives;
}

QColor BlockConfigItem::getColor() const
{
    return color;
}

void BlockConfigItem::setHue(float colorHue)
{
    color.setHslF(colorHue, color.saturationF(), color.lightnessF());
}

#include "blockconfigitem.h"

BlockConfigItem::BlockConfigItem()
    : ConfigItem()
    , xCoordinate(Defaults::BLOCK_X_COORDINATE)
    , yCoordinate(Defaults::BLOCK_Y_COORDINATE)
    , width(Defaults::BLOCK_WIDTH)
    , height(Defaults::BLOCK_HEIGHT)
    , lives(Defaults::BLOCK_LIVES)
    , color(Defaults::BLOCK_COLOR) {}

BlockConfigItem::~BlockConfigItem() {}

bool BlockConfigItem::validate(int width, int height) const
{
    // Check if in the bounds of the scene.
    QRect wind(0,0,width, height);
    QRect blok(xCoordinate, yCoordinate, this->width, this->height);

    // Checks if the block is entirely within the window.
    return wind.contains(blok, true);
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

int BlockConfigItem::getXCoordinate() const
{
    return xCoordinate;
}

void BlockConfigItem::setXCoordinate(int xCoordinate)
{
    this->xCoordinate = xCoordinate;
}

int BlockConfigItem::getYCoordinate() const
{
    return yCoordinate;
}

void BlockConfigItem::setYCoordinate(int yCoordinate)
{
    this->yCoordinate = yCoordinate;
}

int BlockConfigItem::getWidth() const
{
    return width;
}

void BlockConfigItem::setWidth(int width)
{
    this->width = width;
}

int BlockConfigItem::getHeight() const
{
    return height;
}

void BlockConfigItem::setHeight(int height)
{
    this->height = height;
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

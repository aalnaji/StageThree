#include "itemfactory.h"

QGraphicsItem* ItemFactory::make(ConfigItem *config)
{
    switch (config->getItemType()) {
    case BALL:
        return new Ball((BallConfigItem *)config);
        break;
    case BLOCK:
        return new Block((BlockConfigItem *)config);
        break;
    default:
        return NULL;
    }
}

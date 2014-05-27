#include "itemfactory.h"
#include "paddleconfigitem.h"
#include "paddle.h"

QGraphicsItem* ItemFactory::make(ConfigItem *config)
{
    switch (config->getItemType()) {
    case BALL:
        return new Ball((BallConfigItem *)config);
        break;
    case BLOCK:
        return new Block((BlockConfigItem *)config);
        break;
	case PADDLE:
		return new Paddle((PaddleConfigItem *)config);
    default:
        return NULL;
    }
}

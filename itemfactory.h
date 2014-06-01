#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include <iostream>
#include "ball.h"
#include "configitem.h"
#include "block.h"
#include "item.h"

class ItemFactory
{
public:
    static QGraphicsItem* make(ConfigItem *config);
};

#endif // ITEMFACTORY_H

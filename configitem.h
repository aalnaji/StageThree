#ifndef CONFIGITEM_H
#define CONFIGITEM_H

#include "item.h"
#include <string>

class ConfigItem
{
public:

    /**
     * @brief validate
     */
    virtual bool validate(int height, int width) const = 0;

    virtual Item getItemType() const = 0;

    virtual void addParameter(std::string name, double value) = 0;

};

#endif // CONFIGITEM_H

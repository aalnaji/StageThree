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

	/** Add virtual destructor, to make sure all derived classes' objects
	 * are destroyed correctly. */
	virtual ~ConfigItem() {};
};

#endif // CONFIGITEM_H

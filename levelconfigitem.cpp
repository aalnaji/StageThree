#include <iostream>
#include <cstdlib>
#include "levelconfigitem.h"
#include "defaults.h"

/** Set default values. */
LevelConfigItem::LevelConfigItem()
	: levelNum(Defaults::LEVEL_NUM)
	, ballVelFactor(Defaults::LEVEL_BALL_VELOCITY_FACTOR)
{
}

/** On level destruction free the configured items. */
LevelConfigItem::~LevelConfigItem()
{
	for(std::vector<ConfigItem *>::const_iterator iter(configItems.begin()),
			iterEnd(configItems.end()); iter!= iterEnd; ++iter)
		delete *iter;
}

/**
 * Validate that this collection of configured items is in the scene.
 */
bool LevelConfigItem::validate(int height, int width) const
{
	bool res(true);
	for(std::vector<ConfigItem *>::const_iterator iter(configItems.begin()),
			iterEnd(configItems.end()); res&& iter!= iterEnd; ++iter)
		res= (*iter)->validate(height, width);

	return res;
}

/** Set this items type to Level. */
Item LevelConfigItem::getItemType() const
{
	return LEVEL;
}

/** Add parameters known to the level. */
void LevelConfigItem::addParameter(std::string name, double value)
{
	if (name == "level") {
        setLevelNum(value);
    } else if (name == "ballVelocityFactor") {
        setBallVelocityFactor(value);
    } else {
        // Unrecognised parameter.
        std::cout << "Unrecognised parameter when creating a level: " + name << std::endl;
        exit(0);
    }
}

/** Add a config item to this levels set. */
ConfigItem *LevelConfigItem::add(ConfigItem *newItem)
{
	configItems.push_back(newItem);
	return newItem;
}

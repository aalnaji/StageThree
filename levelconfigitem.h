#ifndef LEVELCONFIGITEM_H
#define LEVELCONFIGITEM_H

#include "configitem.h"
#include <vector>

/**
 * Store the configuration file data of a level. Besides the configured blocks
 * the number of the level is stored and the update intervall. A smaller update
 * intervall make the ball faster, while leaving the paddle at the same reaction speed. :)
 * @brief Store config-file data of a level
 */
class LevelConfigItem : public ConfigItem
{
public:
	/** Set default values. */
	LevelConfigItem();
	/** On level destruction free the configured items. */
	~LevelConfigItem();
	/**
     * Validate that this collection of configured items is in the scene.
     */
    bool validate(int height, int width) const;
	/** Set this items type to Level. */
    Item getItemType() const;
	/** Add parameters known to the level. */
    void addParameter(std::string name, double value);
	/** Add a config item to this levels set. */
	ConfigItem *add(ConfigItem *newItem);
	/** Set the number of this level. */
	inline void setLevelNum(int const nLevelNum) { levelNum= nLevelNum; };
	/** Get the number of this level. */
	inline int getLevelNum() const { return levelNum; };
	/** Set the update delay for this level. */
	inline void setUpdateDelay(const int nUpdateWait) { updateWait= nUpdateWait; };
	/** Get the update delay for this level. */
	inline int getUpdateDelay() const { return updateWait; };
	/** Get the i-th item. */
	inline ConfigItem *operator[] (int i) { return configItems[i]; };
	/** Return the number of elements in this level. */
	inline size_t size() const { return configItems.size(); };
private:
	/** The list of items of this level. */
	std::vector<ConfigItem *> configItems;
	/** The number of this level. */
	int levelNum;
	/** The speed of the ball in this level, by giving the update delay. */
	int updateWait;
};

#endif // LEVELCONFIGITEM_H

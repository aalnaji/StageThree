#ifndef LEVEL_H
#define LEVEL_H

#include "AbstractResponsibility.h"

// Forward declaration
class LevelConfigItem;
/**
 * This class stores the information of the currently running level.
 * It also stores a counter of how many blocks are present in the level
 * and emits a level cleared event when all blocks are destroyed.
 * @brief Implement levels and switching to next one.
 */
class Level: public AbstractResponsibility
{
public:
	/** Create the level from the config item. */
	Level(LevelConfigItem const *);
	/** Remove me from the chain of responsibilitiy. */
	~Level();
	/** Handle events of block deleted. */
	void handleEvent(Event *);
	/** Get the number of this level. */
	inline int getLevelNum() const { return num; }
	/** Get the factor the ball is speed up in this level. */
	inline int getBallVelocityFactor() const { return ballVelocityFactor; };
private:
	/** The number of blocks in the level. */
	int numBlock;
	/** The ball speed up factor. */
	int ballVelocityFactor;
	/** The number of the level. */
	int num;
};

#endif // LEVEL_H

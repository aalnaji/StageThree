#include "level.h"
#include "levelconfigitem.h"
#include "Events.h"
#include "chainofresponsibility.h"

/** Create the level from the config item. */
Level::Level(const LevelConfigItem *config)
	: numBlock(config->size())
	, waitUpdate(config->getUpdateDelay())
	, num(config->getLevelNum())
{
	ChainOfResponsibility::get().add(this);
}

/** Remove me from the chain of responsibilitiy. */
Level::~Level()
{
	ChainOfResponsibility::get().remove(this);
}

/** Handle events of block deleted. */
void Level::handleEvent(Event *ev)
{
	if(dynamic_cast<BlockDeletedEvent *>(ev)) {
		--numBlock;
		if(!numBlock) {
			LevelClearedEvent event;
			ChainOfResponsibility::get().handleEvent(&event);
		}
	} else
		AbstractResponsibility::handleEvent(ev);
}

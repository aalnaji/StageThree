#ifndef EVENTS_H
#define EVENTS_H

/** @brief The base structure for all events. */
class Event {
public:
	/** Ensure the class polymorphic, so that dynamic_cast is possible. */
	virtual ~Event() {};
};

/** @brief Transport key stroke events. */
class KeyEvent: public Event {
public:
	/** Store the keycode to transport. */
	int keycode;
};

/** @brief The ball was lost at the bottom. */
class BallLostEvent: public Event {
};

/** @brief Triggered when the lives reaches zero. */
class OutOfLivesEvent: public Event {
};

/** @brief Triggered when a block is removed from the scene. */
class BlockDeletedEvent: public Event {
};

/** @brief Triggered when all blocks are removed from a scene. */
class LevelClearedEvent: public Event {
};

#endif // EVENTS_H

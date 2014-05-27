#ifndef EVENTS_H
#define EVENTS_H

/** The base structure for all events. */
class Event {
public:
	/** Ensure the class polymorphic, so that dynamic_cast is possible. */
	virtual ~Event() {};
};

/** Transport key stroke events. */
class KeyEvent: public Event {
public:
	int keycode;
};

/** The ball was lost at the bottom. */
class BallLostEvent: public Event {
};

#endif // EVENTS_H

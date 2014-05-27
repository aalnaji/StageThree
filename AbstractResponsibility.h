#ifndef ABSTRACTRESPONSIBILITY_H
#define ABSTRACTRESPONSIBILITY_H

/** The base class of all events. */
class Event;

class AbstractResponsibility
{
public:
	/** Ensure that the next pointer is initialized (to null) */
	AbstractResponsibility();
	/** Add the given link to the chain, by putting us in front of it. */
	void add2Chain(AbstractResponsibility *n);
	/** Virtual function to handle any kind of event. Call the
		super-method to iterate through the chain. */
	virtual void handleEvent(Event *);
private:
	/** The pointer to the next item in the chain of responsibility. */
	AbstractResponsibility *next;
};
#endif // ABSTRACTRESPONSIBILITY_H

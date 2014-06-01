#ifndef ABSTRACTRESPONSIBILITY_H
#define ABSTRACTRESPONSIBILITY_H

// Forward declaration of additionally needed classes.
class Event;
class ChainOfResponsibility;

/** All objects that want to participate in the chain of responsibilities have to
 * be derived from these class and implement the handleEvent() method. handleEvent()
 * gets the event to handle and when the object decides to consume the event it just
 * has to quit handleEvent(), if it does no consume event, then the base class'
 * handleEvent() has to be called to enable propagation along the chain.
 * This class in combination with ChainOfResponsibility implements the
 * behavioural design pattern Chain Of Responsibility (p. 223 in GoF-book).
 * @brief Chain of responsibility participants base class
 */
class AbstractResponsibility
{
public:
	/** Ensure that the next pointer is initialized (to null) */
	AbstractResponsibility();
	/** To prevent future compiler warnings, install a virtual destructor. */
	virtual ~AbstractResponsibility() {};
	/** Add the given link to the chain, by putting us in front of it. */
	void add2Chain(AbstractResponsibility *n);
	/** Virtual function to handle any kind of event. Call the
		super-method to iterate through the chain. */
	virtual void handleEvent(Event *);
protected:
	/** The pointer to the next item in the chain of responsibility. */
	AbstractResponsibility *next;
	/** Make the Chain a friend to allow removal from the chain. */
	friend class ChainOfResponsibility;
};
#endif // ABSTRACTRESPONSIBILITY_H

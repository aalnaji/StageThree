#ifndef CHAINOFRESPONSIBILITY_H
#define CHAINOFRESPONSIBILITY_H

// Forward declaration of members of the chain
class AbstractResponsibility;
class Event;

/** The central place of the only chain of responsibility in this programm. */
class ChainOfResponsibility
{
public:
	/** Add a member to the chain. */
	void add(AbstractResponsibility *);
	/** Get the only instance of the chain of responbility. */
	static ChainOfResponsibility &get();
	/** Propagate an event through the chain of responsibility. */
	void handleEvent(Event *);
private:
	/** Construct the chain, by setting the first point to null. */
	ChainOfResponsibility();
	/** The first member of the chain. */
	AbstractResponsibility *first;
};

#endif // CHAINOFRESPONSIBILITY_H

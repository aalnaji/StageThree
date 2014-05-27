#include "chainofresponsibility.h"
#include "AbstractResponsibility.h"

/** Construct the chain, by setting the first point to null. */
ChainOfResponsibility::ChainOfResponsibility()
	: first(0)
{
}

/** Add a member to the chain. */
void ChainOfResponsibility::add(AbstractResponsibility *n)
{
	n->add2Chain(first);
	first= n;
}

/** Propagate an event through the chain of responsibility. */
void ChainOfResponsibility::handleEvent(Event *event)
{
	first->handleEvent(event);
}

/** Get the only instance of the chain of responbility. */
ChainOfResponsibility &ChainOfResponsibility::get()
{
	static ChainOfResponsibility instance;
	return instance;
}

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

/** Remove the member given. */
void ChainOfResponsibility::remove(AbstractResponsibility *item)
{
	if(first== item)
		first= item->next;
	else {
		AbstractResponsibility *prev, *next(first->next);
		prev= first;
		while(next&& item!=next) {
			prev= next;
			next= next->next;
		}
		if(next&& item== next)
			prev->next= item->next;
	}

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

/** Needed for testing only. */
void ChainOfResponsibility::reset() {
	first= 0;
}

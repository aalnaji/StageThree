#include "AbstractResponsibility.h"

/** Ensure that the next pointer is initialized (to null) */
AbstractResponsibility::AbstractResponsibility(): next(0)
{
}

/** Add the given link to the chain, by putting us in front of it. */
void AbstractResponsibility::add2Chain(AbstractResponsibility *n) {
	next= n;
}

/** Virtual function to handle any kind of event. Call the
	super-method to iterate through the chain. */
void AbstractResponsibility::handleEvent(Event *event) {
	if(next)
		next->handleEvent(event);
}

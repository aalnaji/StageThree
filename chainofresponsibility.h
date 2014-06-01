#ifndef CHAINOFRESPONSIBILITY_H
#define CHAINOFRESPONSIBILITY_H

// Forward declaration of members of the chain
class AbstractResponsibility;
struct Event;
class TestSuite;

/**
 * The central place of the only chain of responsibility in this programm.
 * This class is implemented as Singleton (p. 127 GoF-book). Adding and
 * removing of participants of the chain of responsibility as well as
 * pushing an event into the chain is simplified by this class.
 * @brief Traverse chain of responsibility and manage it.
 */
class ChainOfResponsibility
{
public:
	/** Add a member to the chain. */
	void add(AbstractResponsibility *);
	/** Remove the member given. */
	void remove(AbstractResponsibility *);
	/** Get the only instance of the chain of responbility. */
	static ChainOfResponsibility &get();
	/** Propagate an event through the chain of responsibility. */
	void handleEvent(Event *);
protected:
	/** Needed for testing only. */
	void reset();
	friend class TestSuite;
private:
	/** Construct the chain, by setting the first point to null. */
	ChainOfResponsibility();
	/** The first member of the chain. */
	AbstractResponsibility *first;
	/** Prevent copying. */
	ChainOfResponsibility(ChainOfResponsibility const &);
	/** Prevent assignment. */
	void operator=(ChainOfResponsibility const &);
};

#endif // CHAINOFRESPONSIBILITY_H

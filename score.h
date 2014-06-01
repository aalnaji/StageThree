#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsSimpleTextItem>

/**
 * Implements a counter of points. The class is implemented as a Singleton.
 * Special care had to be taken to taken on object destruction, because the
 * scene take ownership of its items and deletes them on destruction.
 *@brief Store the score in a game.
 */
class Score: public QGraphicsSimpleTextItem
{
public:
	/** Clear the score. */
	void reset();
	/** Add the given value to the score. */
	void add(int n);
	/** Get the score. */
	int getScore() const { return score; };
	/** Get the only instance of the score. */
	static Score &get();
	/** Avoid deleting a score object. The singleton is stored in the scene,
	 * which takes ownership and deletes the item on destruction.
	 * Overwriting the delete-operator prevents this. */
	void operator delete(void *) {};
private:
	/** Create a score object. The object is responsible for displaying its contents. */
	Score();
	/** Update the string. */
	void updateScore();
	/** Store the score of the current player. */
	int score;
	Score(Score const&);
	void operator=(Score const&);
};

#endif // SCORE_H

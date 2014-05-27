#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsSimpleTextItem>

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

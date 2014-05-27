#include <QGraphicsScene>
#include <QBrush>
#include <QColor>
#include <iostream>

#include "score.h"

/** Create a score object. The object is responsible for displaying its contents. */
Score::Score()
	: score(0)
{
	setBrush(QBrush(QColor("yellow")));
	setZValue(10);
	setFont(QFont("sans", 15, 2));
}

/** Clear the score. */
void Score::reset() {
	score= 0;
	updateScore();
}

/** Add the given value to the score. */
void Score::add(int n) {
	score+= n;
	updateScore();
}

/** Get the only instance of the score. */
Score &Score::get()
{
	/* Singleton implementation. Has to be done using a pointer here
		because the scene takes ownership of the QGraphicsSimpleTextItem and
		deletes it later. */
	static Score *instance(0);
	if(! instance)
		instance= new Score();
	return *instance;
}

/** Update the string. */
void Score::updateScore() {
	QString scoreString(QString("%1").arg(score, 10, 10, QChar('0')));
	setText(scoreString);
	std::cout<< scoreString.toStdString()<< std::endl;
}

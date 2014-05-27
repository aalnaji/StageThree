#ifndef PADDLE_H
#define PADDLE_H

#include <QGraphicsItem>
#include "AbstractResponsibility.h"

/* Add forward declaration to minimize compile time. */
class PaddleConfigItem;
class QPainter;

class Paddle : public QGraphicsRectItem, public AbstractResponsibility
{
public:
	/** Create a new paddle to let the ball bounce of. */
	Paddle(PaddleConfigItem *);
	/** Implement handling of K and L keys here. K moves the paddle left
	 * and L right. */
	void handleEvent(Event *event);
protected:
	/** When the item is added to the scene then a ItemSceneChanged notify is send.
		On such an event add the livesDisplay to the scene. */
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);
private:
    /** The number of lives this paddle has. */
	unsigned int lives;
	/** Decrement the number of lives and react, if it is zero. */
	void decLives();
	/** Print my number of lives on the screen. */
	QGraphicsSimpleTextItem *livesDisplay;
};

#endif // PADDLE_H

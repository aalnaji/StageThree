#ifndef PADDLE_H
#define PADDLE_H

#include <QGraphicsItem>
#include "AbstractResponsibility.h"

/* Add forward declaration to minimize compile time. */
class PaddleConfigItem;
class QPainter;

/**
 * The paddle is used to let the ball bounce of. Furthermore
 * does it store the number of its lives and is also responsible for displaying
 * them. The paddle observes the chain of responsibility to look for BallLostEvents,
 * certain key stroke events and may trigger the OutOfLives event, when all lives
 * are void. When a OutOfLives event is seen, but lives are still present, then
 * the game ends because all blocks have been destroyed and no more levels are
 * present. The paddle then adds 100 points for every live left.
 * @brief Implement the paddle a the bottom of the screen
 */
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

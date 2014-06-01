#include "paddle.h"
#include "paddleconfigitem.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QKeyEvent>
#include "Events.h"
#include "chainofresponsibility.h"
#include "defaults.h"
#include "score.h"

/** Create a new paddle to let the ball bounce of. */
Paddle::Paddle(PaddleConfigItem *config)
	: QGraphicsRectItem(config->getRect())
	, lives(config->getLives())
	, livesDisplay(new QGraphicsSimpleTextItem(QString("Lives: %1").arg(config->getLives())))
{
	setPos(config->getPos());
	setBrush(QBrush(config->getColor()));
	livesDisplay->setFont(Defaults::DEFAULT_FONT);
	livesDisplay->setBrush(QBrush(Defaults::DEFAULT_FONT_COLOR));
	livesDisplay->setZValue(10);
	livesDisplay->setPos(5,5);
}

/** Implement handling of K and L keys here. K moves the paddle left
 * and L right. */
void Paddle::handleEvent(Event *event) {
	const qreal delta= 20.0;

	KeyEvent *ke;
	if((ke= dynamic_cast<KeyEvent *>(event))) {
		QPointF p(pos());
		if(ke->keycode == Qt::Key_K) {
			// Prevent moves when dead, but consume keys
			if(!lives)
				return;
			if(p.x()- delta> 0.0)
				moveBy(-delta, 0.0);
			else
				setPos(0.0, p.y());
		} else if(ke->keycode == Qt::Key_L) {
			// Prevent moves when dead, but consume keys
			if(!lives)
				return;
			if(p.x()+ rect().width()+ delta< scene()->width())
				moveBy(delta, 0.0);
			else
				setPos(scene()->width()- rect().width(), p.y());
		} else
			/* The paddle does not know further keys to react on. Hand them on. */
			AbstractResponsibility::handleEvent(event);
	} else if(dynamic_cast<BallLostEvent *>(event)) {
		decLives();
	} else if(dynamic_cast<OutOfLivesEvent *>(event)&& lives) {
		/* All block destroyed. For each remaining live add 100 points. */
		Score::get().add(lives* 100);
	} else
		/* This event is not for use, hand it down the chain. */
		AbstractResponsibility::handleEvent(event);
}

/** When the item is added to the scene then a ItemSceneChanged notify is send. */
QVariant Paddle::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
	if(change== QGraphicsItem::ItemSceneChange && !livesDisplay->scene()) {
		value.value<QGraphicsScene *>()->addItem(livesDisplay);
	}
	return value;
}

/** Decrement the number of lives and react, if it is zero. */
void Paddle::decLives()
{
	/* Prevent decrement below zero. */
	if(!lives)
		return;

	--lives;
	livesDisplay->setText(QString("Lives: %1").arg(lives));
	if(!lives)
	{
		OutOfLivesEvent oolEvent;
		ChainOfResponsibility::get().handleEvent(&oolEvent);
	}
}

#include <QGraphicsItem>

#include "dialog.h"
#include "ui_dialog.h"
#include "blockconfigitem.h"
#include "ballconfigitem.h"
#include "paddleconfigitem.h"
#include "itemfactory.h"
#include "score.h"
#include "chainofresponsibility.h"
#include "Events.h"
#include "levelconfigitem.h"
#include "level.h"

Dialog::Dialog(Config *nConfig,
               QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
	, helpManager(this)
	, scoreBoardManager(this)
	, gameOver(false)
	, config(nConfig)
	, level(0)
	, levelText(new QGraphicsSimpleTextItem())
{
    ui->setupUi(this);
    this->resize(config->getWidth(), config->getHeight());
    this->setFixedSize(this->size());

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, config->getWidth(), config->getHeight());
    scene->setBackgroundBrush(Defaults::BOX_COLOR);

	/* Create connection of the timer's timeout with the scences advance slot. */
    QObject::connect(&timer, SIGNAL(timeout()), scene, SLOT(advance()));

    view = new QGraphicsView(this);
    view->setScene(scene);
    view->setRenderHint(QPainter::Antialiasing);

	/* Add this object to the chain for key handling, too. */
	ChainOfResponsibility::get().add(this);

	/* Reseting the score, will render the string, which is then used for positioning. */
	Score::get().reset();
	/* Tell the score item where to display itself. Add 5 points distance to the border. */
	Score::get().setPos(scene->width()- Score::get().boundingRect().width()- 5.0, 5.0);
	scene->addItem(&Score::get());

	/* Add the usual items to the scene. */
	AbstractResponsibility *respChainItem;
	QGraphicsItem *madeItem;
    for (size_t i = 0; i < config->size(); i++) {
		if((madeItem= ItemFactory::make((*config)[i]))){
			scene->addItem(madeItem);
			if((respChainItem= dynamic_cast<AbstractResponsibility *>(madeItem))) {
				/* When no keypress handlers are on the chain, then a null is inserted. */
				ChainOfResponsibility::get().add(respChainItem);
			}
		}
    }

	/* Configure stable parts of the text giving the level number, just once. */
	levelText->setBrush(QBrush(Defaults::DEFAULT_FONT_COLOR));
	levelText->setFont(Defaults::DEFAULT_FONT);
	scene->addItem(levelText);
	/* Add the first level to the scene. */
	addLevel(config, 1);
}

/** Destroy the object, freeing all memory. */
Dialog::~Dialog()
{
    delete ui;
    delete view;
    //when deleting scene, scene also deletes all other items associated with the scene (i.e the ball)
    delete scene;
}

/** Add the desired level's items to the scene.
 *@returns true, when the level was found, false else. */
bool Dialog::addLevel(Config *config, int levelNum)
{
	/* Look up the i-th level config. */
	LevelConfigItem *theLevel;
	QGraphicsItem *madeItem;
	for (size_t i = 0; i < config->size(); i++) {
		if((*config)[i]->getItemType()== LEVEL&&
				(theLevel= static_cast<LevelConfigItem *>((*config)[i]))->getLevelNum()== levelNum) {
			delete level;
			level= new Level(theLevel);
			levelText->setText(QString("Level: %1").arg(level->getLevelNum()));
			levelText->setPos((scene->width()- levelText->boundingRect().width())/ 2, 5);
			for(size_t j= 0; j< theLevel->size(); ++j) {
				madeItem= ItemFactory::make((*theLevel)[j]);
				scene->addItem(madeItem);
			}
			return true;
		}
	}
	return false;
}

void Dialog::nextFrame()
{
    update();
}

/**
 * @brief Dialog::mousePressEvent stores the
 * @param event
 */
void Dialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        BlockConfigItem *newConfig = new BlockConfigItem();

        newConfig->setXCoordinate(event->x() - (newConfig->getWidth() / 2.0));
        newConfig->setYCoordinate(event->y() - (newConfig->getHeight() / 2.0));

        QGraphicsItem *block = ItemFactory::make(newConfig);
        scene->addItem(block);
    } else if (event->button() == Qt::RightButton) {
        BallConfigItem *newConfig = new BallConfigItem();

        newConfig->setXCoordinate(event->x() - (newConfig->getRadius()));
        newConfig->setYCoordinate(event->y() - (newConfig->getRadius()));

        QGraphicsItem *ball = ItemFactory::make(newConfig);
        scene->addItem(ball);
    }
}

/** Start the chain of responsibility for key presses by overloading the
 * method. */
void Dialog::keyPressEvent(QKeyEvent *event)
{
	KeyEvent ke;
	ke.keycode= event->key();
	ChainOfResponsibility::get().handleEvent(&ke);
}

/** Handle the key presses for the dialog window, i.e., act on Q to quit. */
void Dialog::handleEvent(Event *event)
{
	KeyEvent *ke;
	if(((ke= dynamic_cast<KeyEvent *>(event)))&& ke->keycode== Qt::Key_Q)
		this->close();
	else if (dynamic_cast<OutOfLivesEvent *>(event)) {
		stopTimer();
		gameOver= true;
		QGraphicsSimpleTextItem *goText(new QGraphicsSimpleTextItem(QString("Game over !!!")));
		goText->setFont(QFont("sans", 20, 2));
		goText->setBrush(QColor("red"));
		goText->setPos(scene->sceneRect().center()- goText->boundingRect().center());
		scene->addItem(goText);
		/* The score board manager also depends on the event, therefore propagate it. */
		AbstractResponsibility::handleEvent(event);
	} else if (dynamic_cast<LevelClearedEvent *>(event)) {
		if(addLevel(config, level->getLevelNum()+ 1)) {
			Ball *currBall;
			for(QList<QGraphicsItem *>::iterator iter(scene->items().begin()), iterEnd(scene->items().end());
					iter!= iterEnd; ++iter){
				/* Find all balls and update their velocity. */
				if((currBall= dynamic_cast<Ball *>(*iter))) {
					currBall->setVelocity(currBall->getVelocity()* level->getBallVelocityFactor());
				}
			}
		} else {
			stopTimer();
			gameOver= true;
			QGraphicsSimpleTextItem *goText(new QGraphicsSimpleTextItem(QString("Game over !!!")));
			goText->setFont(QFont("sans", 20, 4));
			goText->setBrush(QColor("green"));
			goText->setPos(scene->sceneRect().center()- goText->boundingRect().center());
			scene->addItem(goText);
			/* For each remaining live add 100 points. */

			/* The score board manager depends on the out of lives event, which is not quite
			 * correct here. */
			OutOfLivesEvent oole;
			AbstractResponsibility::handleEvent(&oole);
		}
	} else
		AbstractResponsibility::handleEvent(event);
}

/** (Re-)Start the timer. */
void Dialog::startTimer()
{
	if(!gameOver)
		timer.start(1000/ 120);
}

/** Stop the timer. */
void Dialog::stopTimer()
{
	timer.stop();
}

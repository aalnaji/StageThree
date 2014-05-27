#include "dialog.h"
#include "ui_dialog.h"
#include "blockconfigitem.h"
#include "ballconfigitem.h"
#include "paddleconfigitem.h"
#include "itemfactory.h"
#include "score.h"
#include "chainofresponsibility.h"
#include "Events.h"

Dialog::Dialog(Config *config,
               QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
    , config(config)
{
    ui->setupUi(this);
    this->resize(config->getWidth(), config->getHeight());
    this->setFixedSize(this->size());

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, config->getWidth(), config->getHeight());
    scene->setBackgroundBrush(Defaults::BOX_COLOR);

    view = new QGraphicsView(this);
    view->setScene(scene);
    view->setRenderHint(QPainter::Antialiasing);

	AbstractResponsibility *respChainItem;
    for (size_t i = 0; i < config->size(); i++) {
        QGraphicsItem *madeItem(ItemFactory::make((*config)[i]));
        scene->addItem(madeItem);
		if((respChainItem= dynamic_cast<AbstractResponsibility *>(madeItem))) {
			/* When no keypress handlers are on the chain, then a null is inserted. */
			ChainOfResponsibility::get().add(respChainItem);
		}
    }
	/* Add this object to the chain for key handling, too. */
	ChainOfResponsibility::get().add(this);

	/* Reseting the score, will render the string, which is then used for positioning. */
	Score::get().reset();
	/* Tell the score item where to display itself. Add 5 points distance to the border. */
	Score::get().setPos(scene->width()- Score::get().boundingRect().width()- 5.0, 5.0);
	scene->addItem(&Score::get());
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
  //      block->setZValue(zCount++);
        scene->addItem(block);
    } else if (event->button() == Qt::RightButton) {
        BallConfigItem *newConfig = new BallConfigItem();

        newConfig->setXCoordinate(event->x() - (newConfig->getRadius()));
        newConfig->setYCoordinate(event->y() - (newConfig->getRadius()));

        QGraphicsItem *ball = ItemFactory::make(newConfig);
    //    ball->setZValue(zCount++);
        scene->addItem(ball);
    }
}

/** Start the chain of responsibility for key presses by overloading the
 * method. */
void Dialog::keyPressEvent(QKeyEvent *event) {
	KeyEvent ke;
	ke.keycode= event->key();
	ChainOfResponsibility::get().handleEvent(&ke);
}

void Dialog::handleKeyPress(Event *event) {
	KeyEvent *ke;
	if(((ke= dynamic_cast<KeyEvent *>(event)))&& ke->keycode== Qt::Key_Q)
		this->close();
	else
		AbstractResponsibility::handleEvent(event);
}

Dialog::~Dialog()
{
    delete ui;
    delete view;
    //when deleting scene, scene also deletes all other items associated with the scene (i.e the ball)
    delete scene;
}

QGraphicsScene * Dialog::getScene()
{
    return scene;
}

#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(Config *config,
               QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
    , config(config)
    , zCount(0)
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

    for (size_t i = 0; i < config->size(); i++) {
        QGraphicsItem *madeItem = ItemFactory::make((*config)[i]);
        madeItem->setZValue(zCount++);
        scene->addItem(madeItem);
    }
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
        block->setZValue(zCount++);
        scene->addItem(block);
    } else if (event->button() == Qt::RightButton) {
        BallConfigItem *newConfig = new BallConfigItem();

        newConfig->setXCoordinate(event->x() - (newConfig->getRadius()));
        newConfig->setYCoordinate(event->y() - (newConfig->getRadius()));

        QGraphicsItem *ball = ItemFactory::make(newConfig);
        ball->setZValue(zCount++);
        scene->addItem(ball);
    }
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

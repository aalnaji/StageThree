#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>

#include "config.h"
#include "ball.h"
#include "itemfactory.h"
#include "item.h"

namespace Ui
{
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(Config *config,
                    QWidget *parent = 0);

    ~Dialog();

    QGraphicsScene * getScene();

    void mousePressEvent(QMouseEvent *event);


public slots:
    void nextFrame();

private:
    Ui::Dialog *ui;
    QGraphicsView *view;
    QGraphicsScene *scene;
    Config *config;

    int zCount;
};

#endif // DIALOG_H

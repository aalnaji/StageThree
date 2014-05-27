#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QKeyEvent>

#include "config.h"
#include "AbstractResponsibility.h"

namespace Ui
{
    class Dialog;
}

class Paddle;

class Dialog : public QDialog, public AbstractResponsibility
{
    Q_OBJECT

public:
    explicit Dialog(Config *config,
                    QWidget *parent = 0);

    ~Dialog();

    QGraphicsScene * getScene();

    void mousePressEvent(QMouseEvent *event);
	/** Start the chain of responsibility for key presses by overloading the
	 * method. */
	void keyPressEvent(QKeyEvent *);

	/** Handle the key presses for the dialog window, i.e., act on Q to quit. */
	void handleKeyPress(Event *);
public slots:
    void nextFrame();

private:
    Ui::Dialog *ui;
    QGraphicsView *view;
    QGraphicsScene *scene;
    Config *config;
};

#endif // DIALOG_H

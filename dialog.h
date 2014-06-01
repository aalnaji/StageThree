#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimer>

#include "config.h"
#include "AbstractResponsibility.h"
#include "helpdialogmanager.h"
#include "scoreboardmanager.h"

namespace Ui
{
    class Dialog;
}

// Forward declaration
class Level;

class Dialog : public QDialog, public AbstractResponsibility
{
    Q_OBJECT

public:
    explicit Dialog(Config *config,
                    QWidget *parent = 0);
	/** Destroy the object, freeing all memory. */
    ~Dialog();
	/** Handle mouse clicks. */
    void mousePressEvent(QMouseEvent *event);
	/** Start the chain of responsibility for key presses by overloading the
	 * method. */
	void keyPressEvent(QKeyEvent *);
	/** Handle the key presses for the dialog window, i.e., act on Q to quit. */
	void handleEvent(Event *);
	/** (Re-)Start the timer. */
	void startTimer();
	/** Stop the timer. */
	void stopTimer();
public slots:
    void nextFrame();

private:
	/** Add the desired level's items to the scene. */
	bool addLevel(Config *config, int i);
	Ui::Dialog *ui;
    QGraphicsView *view;
    QGraphicsScene *scene;
	/** The manager to open a help dialog on request. */
	HelpDialogManager helpManager;
	/** Had to move the timer here, to be able to stop it, when another
	 * window is opened. */
	QTimer timer;
	/** The score board manager. */
	ScoreBoardManager scoreBoardManager;
	/** Remember, when the game is over. */
	bool gameOver;
	/** The configuration is needed to create further levels. */
	Config *config;
	/** The current level. */
	Level *level;
	/** The text giving the level. */
	QGraphicsSimpleTextItem *levelText;
};

#endif // DIALOG_H

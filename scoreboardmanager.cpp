#include <QString>

#include "scoreboardmanager.h"

#include "helpdialogmanager.h"
#include "ui_scoreboard.h"
#include "chainofresponsibility.h"
#include "Events.h"
#include "dialog.h"
#include "QDataStream"
#include "score.h"

/** Hook ourself into the chain of responsibility, to
 * watch out for s key presses or OutOfLivesEvents. */
ScoreBoardManager::ScoreBoardManager(Dialog *par)
	: parent(par)
{
	ChainOfResponsibility::get().add(this);
}

/** Handle presses of s key and OutOfLiveEvents. */
void ScoreBoardManager::handleEvent(Event *key)
{
	KeyEvent *ke;
	if((ke= dynamic_cast<KeyEvent *>(key))&&
			ke->keycode== Qt::Key_S) {
		/* Just show the score board. */
		parent->stopTimer();
		QDialog window(parent);
		Ui::highScores scoreBoard;
		scoreBoard.setupUi(&window);
		fillBoard(scoreBoard.highScoreTable);
		window.exec();
		parent->startTimer();
	} else if(dynamic_cast<OutOfLivesEvent *>(key)) {
		/* Show the score board and if a score worth entering was reached,
		 * enable entering. */
		QDialog window(parent);
		Ui::highScores scoreBoard;
		scoreBoard.setupUi(&window);
		fillBoard(scoreBoard.highScoreTable);
		// Get the new score and check if it is to be inserted into the score board
		int newScore(Score::get().getScore());
		// Remember that the score board changed to save it.
		bool changed(false);
		int i(0);
		for(QString temp; i< 10&& scoreBoard.highScoreTable->item(i, SCORECOLUMN)&&
			 !(temp= scoreBoard.highScoreTable->item(i, SCORECOLUMN)->text()).isEmpty()&&
			  temp.toInt()> newScore; ++i)
			/* intentionally do nothing */ ;
		if(i< 10) {
			/* New high score to enter. */
			/* Now shift the items 10 to i down one item. */
			for(int j= 10; i< j; --j) {
				scoreBoard.highScoreTable->setItem(j, SCORECOLUMN,
												   scoreBoard.highScoreTable->takeItem(j- 1, SCORECOLUMN));
				scoreBoard.highScoreTable->setItem(j, NAMECOLUMN,
												   scoreBoard.highScoreTable->takeItem(j- 1, NAMECOLUMN));
			}
			scoreBoard.highScoreTable->setItem(i, SCORECOLUMN, new QTableWidgetItem(QString("%1").arg(newScore)));
			scoreBoard.highScoreTable->setItem(i, NAMECOLUMN, new QTableWidgetItem(QString("Enter your name")));
			changed= true;
			/* Start the editor for that item. */
			scoreBoard.highScoreTable->editItem(scoreBoard.highScoreTable->item(i, NAMECOLUMN));
		}
		window.exec();
		/* User closed the window, we assume he stored his name. */
		if(changed) {
			QFile file(Defaults::HIGHSCORE_PATH);
			if(!file.open(QIODevice::WriteOnly))
				return;
			QDataStream res(&file);
			for(i= 0; i< 10&& scoreBoard.highScoreTable->item(i, SCORECOLUMN)&&
					scoreBoard.highScoreTable->item(i, NAMECOLUMN); ++i) {
				scoreBoard.highScoreTable->item(i, SCORECOLUMN)->write(res);
				scoreBoard.highScoreTable->item(i, NAMECOLUMN)->write(res);
			}
		}
	} else
		AbstractResponsibility::handleEvent(key);
}

/** Fill the score board from a resource file. */
void ScoreBoardManager::fillBoard(QTableWidget *list)
{
	QFile file(Defaults::HIGHSCORE_PATH);
	if(!file.open(QIODevice::ReadOnly))
		return;
	QDataStream res(&file);
	QTableWidgetItem *itemName, *itemScore;
	int row(0);
	while(!file.atEnd()) {
		itemScore= new QTableWidgetItem();
		itemScore->read(res);
		itemName= new QTableWidgetItem();
		itemName->read(res);
		list->setItem(row, SCORECOLUMN, itemScore);
		list->setItem(row, NAMECOLUMN, itemName);
		++row;
	}
}

#ifndef SCOREBOARDMANAGER_H
#define SCOREBOARDMANAGER_H

#include "AbstractResponsibility.h"

// Forward declaration.
class Dialog;
class QTableWidget;

/** Manage a score board, i.e., on pressing s the score board window is
 * opened, on game over the score board with the ability to enter ones
 * name is to be displayed.
 * @brief Manage displaying the score board and name entry.
 */
class ScoreBoardManager: public AbstractResponsibility
{
public:
	/** Hook ourself into the chain of responsibility, to
	 * watch out for s key presses or OutOfLivesEvents. */
	ScoreBoardManager(Dialog *par);
	/** Handle presses of s key and OutOfLiveEvents. */
	void handleEvent(Event *);
private:
	/** Parent dialog. This needs to be locked, while we display the score board
	 * and the time needs to be stopped. */
	Dialog *parent;
	/** The column used for the score. */
	static const int SCORECOLUMN= 0;
	/** The column used for the name. */
	static const int NAMECOLUMN= 1;
	/** Fill the score board from a resource file. */
	void fillBoard(QTableWidget *list);
};
#endif // SCOREBOARDMANAGER_H

#ifndef HELPDIALOGMANAGER_H
#define HELPDIALOGMANAGER_H

#include "AbstractResponsibility.h"

// Forward declaration.
class Dialog;

/** Manage opening a help dialog.
 * The manager waits for key presses of h and ? to display a help window.
 * @brief Display a window with a help text.
 */
class HelpDialogManager: public AbstractResponsibility
{
public:
	/** Hook ourself into the chain of responsibility, to
	 * watch out for help key presses. */
	HelpDialogManager(Dialog *par);
	/** Handle presses of h and ? keys. */
	void handleEvent(Event *);
private:
	/** Parent dialog. This needs to be locked, while we display help
	 * and the time needs to be stopped. */
	Dialog *parent;
};

#endif // HELPDIALOGMANAGER_H

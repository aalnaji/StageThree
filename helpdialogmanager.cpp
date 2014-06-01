#include "helpdialogmanager.h"
#include "ui_helpdialog.h"
#include "chainofresponsibility.h"
#include "Events.h"
#include "dialog.h"

/** Hook ourself into the chain of responsibility, to
 * watch out for help key presses. */
HelpDialogManager::HelpDialogManager(Dialog *par)
	: parent(par)
{
	ChainOfResponsibility::get().add(this);
}

/** Handle presses of h and ? keys. */
void HelpDialogManager::handleEvent(Event *key)
{
	KeyEvent *ke;
	if((ke= dynamic_cast<KeyEvent *>(key))&&
			(ke->keycode== Qt::Key_H|| ke->keycode== Qt::Key_Question))
	{
		parent->stopTimer();
		QDialog window(parent);
		Ui::helpDialog hDialog;
		hDialog.setupUi(&window);
		window.exec();
		parent->startTimer();
	} else
		AbstractResponsibility::handleEvent(key);
}

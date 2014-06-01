#include "dialog.h"
#include "config.h"
#include <QTimer>
#include <QApplication>

int main(int argc, char *argv[])
{
    Config config;
    QApplication a(argc, argv);
    Dialog w(&config);

    w.show();
	w.startTimer();

	return a.exec();
}

#include "dialog.h"
#include "config.h"
#include <QTimer>
#include <QApplication>

int main(int argc, char *argv[])
{
    Config *config = new Config();
    QApplication a(argc, argv);
    Dialog w(config);

    w.show();

    QTimer timer;
    QObject::connect(&timer, SIGNAL(timeout()), w.getScene(), SLOT(advance()));
    timer.start(1000 / 120);

    delete config;
    return a.exec();
}

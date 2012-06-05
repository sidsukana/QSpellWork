#include "Updater.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Updater updater;
    updater.start();

    return a.quit();
}

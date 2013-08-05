#include "SWMainForm.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    SWMainForm *form = new SWMainForm;

    form->setWindowTitle(QString("Qt SpellWork %0 (%1) for WoW %2 (%3)")
        .arg(QSW_VERSION)
        .arg(QSW_BUILD)
        .arg(CLIENT_VERSION)
        .arg(CLIENT_BUILD));

    form->show();

    return app.exec();
}

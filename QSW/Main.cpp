#include "SWMainForm.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    SWMainForm form;

    form.setWindowTitle(QString("Qt SpellWork for WoW %0 (%1) build %2")
        .arg(CLIENT_VERSION)
        .arg(CLIENT_BUILD)
        .arg(QSW_BUILD));

    form.show();

    return app.exec();
}
#include "SWMainForm.h"
#include <QtGui/QApplication>
#include <QtGui/QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    SWMainForm form;

    form.setWindowTitle(QString("Qt SpellWork for WoW %0 (%1) build %2")
        .arg(CLIENT_VERSION)
        .arg(CLIENT_BUILD)
        .arg(QSW_BUILD));

    // Set position to center about desktop widget
    QRect frameRect = form.frameGeometry();
    frameRect.moveCenter(QDesktopWidget().availableGeometry().center());
    form.move(frameRect.topLeft());

    form.show();

    return app.exec();
}

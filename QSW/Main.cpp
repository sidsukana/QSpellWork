#include <QApplication>
#include <QDesktopWidget>
#include <QDir>
#include <QMessageBox>

#include "MainForm.h"
#include "SettingsForm.h"
#include "qsw.h"
#include "mpq/MPQ.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainForm form;

    form.setWindowTitle(QString("Qt SpellWork %0")
        .arg(QSW::VERSION));
    
    // Set position to center about desktop widget
    QRect frameRect = form.frameGeometry();
    frameRect.moveCenter(QDesktopWidget().availableGeometry().center());
    form.move(frameRect.topLeft());

    form.show();

    for (quint8 i = 0; i < 3; ++i) {
        QObject::connect(&app, SIGNAL(aboutToQuit()), form.getBrowser(i), SLOT(deleteLater()));
    }

    return app.exec();
}

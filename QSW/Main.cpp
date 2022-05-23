#include <QApplication>
#include <QScreen>
#include <QDir>
#include <QMessageBox>

#include "MainForm.h"
#include "SettingsForm.h"
#include "qsw.h"
#include "mpq/MPQ.h"

int main(int argc, char *argv[])
{
    bool overridenLastActivePlugin = false;
    QString activePlugin = "";
    for (int i = 0; i < argc; ++i)
    {
        if (strcmp(argv[i], "--plugin") == 0)
        {
            if (i + 1 < argc)
            {
                activePlugin = argv[i + 1];
                overridenLastActivePlugin = true;
            }
        }
    }

    QApplication app(argc, argv);

    MainForm form;
    form.loadSettings(overridenLastActivePlugin, activePlugin);

    QString pluginTitle = "";
    if (activePlugin == "wotlk-cmangos")
        pluginTitle = "WOTLK";
    else if (activePlugin == "tbc-cmangos")
        pluginTitle = "TBC";
    else if (activePlugin == "pre-tbc-cmangos")
        pluginTitle = "Classic";

    form.setWindowTitle(QString("QSW %0 %1")
        .arg(QSW::VERSION).arg(pluginTitle));
    
    // Set position to center about desktop widget
    QRect frameRect = form.frameGeometry();
    QScreen *screen = QGuiApplication::primaryScreen();
    frameRect.moveCenter(screen->geometry().center());
    form.move(frameRect.topLeft());

    form.show();

    for (quint8 i = 0; i < 3; ++i) {
        QObject::connect(&app, SIGNAL(aboutToQuit()), form.getBrowser(i), SLOT(deleteLater()));
    }

    return app.exec();
}

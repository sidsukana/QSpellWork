#include <QApplication>
#include <QDesktopWidget>
#include <QDir>
#include <QMessageBox>

#include "SWMainForm.h"
#include "SWSettingsForm.h"
#include "SWDefines.h"
#include "mpq/MPQ.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MPQ::gameDir() = QDir::fromNativeSeparators(QSW::settings().value("Directories/WoW1", "").toString());

    bool hasGameDir = false;
    if (!QSW::checkDir(MPQ::gameDir()))
    {
        while (!hasGameDir)
        {
            SWSettingsForm settingsForm;
            if (settingsForm.exec() == QDialog::Accepted)
            {
                if (!QSW::checkDir(MPQ::gameDir()))
                    QSW::settings().setValue("Directories/WoW1", "");
                else hasGameDir = true;
            }
            else break;
        }
    }
    else hasGameDir = true;

    if (!hasGameDir)
        return 0;

    SWMainForm form;

    form.setWindowTitle(QString("Qt SpellWork for WoW %0 (%1) build %2")
        .arg(QSW::CLIENT_VERSION)
        .arg(QSW::CLIENT_BUILD)
        .arg(QSW::QSW_BUILD));
    
    // Set position to center about desktop widget
    QRect frameRect = form.frameGeometry();
    frameRect.moveCenter(QDesktopWidget().availableGeometry().center());
    form.move(frameRect.topLeft());

    form.show();

    return app.exec();
}
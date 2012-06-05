#include "Updater.h"

#include <QtGui/QApplication>
#include <QtCore/QDir>
#include <QtCore/QProcess>
#include <QtCore/QThread>

Updater::Updater(QObject* parent)
    : QObject(parent)
{

}

Updater::~Updater()
{

}

void Updater::start()
{
    QStringList fileList = QApplication::arguments();
    fileList.pop_front();
    if (fileList.isEmpty())
        return;

    QDir path;
    path.setCurrent(QApplication::applicationDirPath());

    if (path.exists("Temp"))
    {
        for (QStringList::const_iterator itr = fileList.begin(); itr != fileList.end(); ++itr)
        {
            while (!path.remove((*itr))) {}
            while (!path.rename("Temp/" + (*itr), (*itr))) {}
            path.cleanPath("Temp");
        }
        path.rmdir("Temp");
    }

    QProcess::startDetached("QSW.exe");
    QApplication::quit();
}

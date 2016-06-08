#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QIcon>

#include "Defines.h"

bool QSW::checkDir(const QString &dir)
{
    if (dir.isEmpty())
    {
        QMessageBox messageBox(QMessageBox::Warning, "Warning!", "Please set game directory!");
        messageBox.setWindowIcon(QIcon(":/qsw/resources/mangos.ico"));
        messageBox.exec();
        return false;
    }

    const QString mpqs[] = {
        "patch-2.MPQ",
        "patch.MPQ",
        "dbc.MPQ",
        "model.MPQ",
        "interface.MPQ",
        "texture.MPQ",
        ""
    };

    const QString *mpq = mpqs;
    QStringList nonExisted;

    while (!mpq->isEmpty())
    {
        QString path = dir + "Data/" + *mpq;

        if (!QFile::exists(path))
            nonExisted << *mpq;

        ++mpq;
    }

    if (!nonExisted.isEmpty())
    {
        QString message;
        message.append("MPQ files: \n\n");
        QStringList::iterator itr = nonExisted.begin();
        while (itr != nonExisted.end())
        {
            message.append(QString("%0\n").arg(*itr));
            ++itr;
        }
        message.append("\n not found!");
        QMessageBox messageBox(QMessageBox::Warning, "Warning!", message);
        messageBox.setWindowIcon(QIcon(":/qsw/resources/mangos.ico"));
        messageBox.exec();
        return false;
    }

    return true;
}

QSettings& QSW::settings()
{
    static QSettings m_settings("QSW.ini", QSettings::IniFormat);
    m_settings.sync();
    return m_settings;
}

quint8 QSW::Locale = 0;
QString QSW::VERSION = "2.0.0";

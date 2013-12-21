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
QString QSW::CLIENT_VERSION = "1.12.x";
QString QSW::QSW_BUILD = "112";
QString QSW::CLIENT_BUILD = "5875, 6005";

QString ProcFlagDesc[] =
{
    // 00 0x00000001
    "00 Killed by aggressor that receive experience or honor",
    // 01 0x00000002
    "01 Kill that yields experience or honor",
    // 02 0x00000004
    "02 Successful melee attack",
    // 03 0x00000008
    "03 Taken damage from melee strike hit",
    // 04 0x00000010
    "04 Successful attack by Spell that use melee weapon",
    // 05 0x00000020
    "05 Taken damage by Spell that use melee weapon",
    // 06 0x00000040
    "06 Successful Ranged attack (and wand spell cast)",
    // 07 0x00000080
    "07 Taken damage from ranged attack",
    // 08 0x00000100
    "08 Successful Ranged attack by Spell that use ranged weapon",
    // 09 0x00000200
    "09 Taken damage by Spell that use ranged weapon",
    // 10 0x00000400
    "10 Successful spell hit",
    // 11 0x00000800
    "11 Taken spell hit",
    // 12 0x00001000
    "12 Successful spell cast",
    // 13 0x00002000
    "13 Taken spell hit",
    // 14 0x00004000
    "14 Successful cast positive spell",
    // 15 0x00008000
    "15 Taken positive spell hit",
    // 16 0x00010000
    "16 Successful damage from harmful spell cast",
    // 17 0x00020000
    "17 Taken spell damage",
    // 18 0x00040000
    "18 Deal periodic damage",
    // 19 0x00080000
    "19 Taken periodic damage",
    // 20 0x00100000
    "20 Taken any damage",
    // 21 0x00200000
    "21 On trap activation"
};
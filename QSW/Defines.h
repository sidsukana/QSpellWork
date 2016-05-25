#ifndef SWDEFINES_H
#define SWDEFINES_H

#include <QString>
#include <QMetaType>
#include <QSettings>

namespace QSW
{
    bool checkDir(const QString &dir);
    QSettings& settings();

    extern quint8 Locale;
    extern QString CLIENT_VERSION;
    extern QString QSW_BUILD;
    extern QString CLIENT_BUILD;

    enum Pages
    {
        PAGE_MAIN       = 0,
        PAGE_CLEFT      = 1,
        PAGE_CRIGHT     = 2,
        PAGE_MAX        = 3
    };
}

extern QString ProcFlagDesc[];

#define MAX_PROC 32 


#endif // SWDEFINES_H

#ifndef SWDEFINES_H
#define SWDEFINES_H

#include <QString>
#include <QMetaType>
#include <QSettings>

namespace QSW
{
    QSettings& settings();

    extern QString VERSION;

    enum Pages
    {
        PAGE_MAIN       = 0,
        PAGE_CLEFT      = 1,
        PAGE_CRIGHT     = 2,
        PAGE_MAX        = 3
    };
}

#endif // SWDEFINES_H

#ifndef MPQ_H
#define MPQ_H

#include <QString>
#include <QByteArray>

#include "mpq_global.h"

namespace MPQ
{
    MPQSHARED_EXPORT QString & gameDir();
    MPQSHARED_EXPORT QByteArray readFile(const QString &fileName);
}

#endif

#ifndef MPQ_H
#define MPQ_H

#include <QString>
#include <QByteArray>

#include "StormLib/include/StormLib.h"

#ifdef MPQ_LIBRARY
#  define MPQ_EXPORT Q_DECL_EXPORT
#else
#  define MPQ_EXPORT Q_DECL_IMPORT
#endif

namespace MPQ
{
    MPQ_EXPORT QString & gameDir();
    MPQ_EXPORT QByteArray readFile(const QString &fileName);
}

#endif

#ifndef SHARED_H
#define SHARED_H

#include <QMap>
#include <QHash>

#include "blp/BLP.h"
#include "dbc/DBC.h"

typedef QMap<qint64, QString> Enumerator;
typedef QHash<QString, Enumerator> EnumHash;
typedef QMapIterator<qint64, QString> EnumIterator;

namespace QSW {

    Q_DECL_EXPORT EnumHash loadEnumFile(QString fileName);
}

#endif // SHARED_H

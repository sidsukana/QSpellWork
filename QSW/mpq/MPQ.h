#ifndef MPQ_H
#define MPQ_H

#include <QString>
#include <QByteArray>

namespace MPQ
{
    Q_DECL_EXPORT QString& mpqDir();
    Q_DECL_EXPORT QStringList& mpqFiles();
    QByteArray readFile(const QString &fileName);
}

#endif

#ifndef MPQ_H
#define MPQ_H

#include <QString>
#include <QByteArray>

namespace MPQ
{
    QString& mpqDir();
    QString& localeDir();
    QStringList& mpqFiles();
    QByteArray readFile(const QString &fileName);
}

#endif

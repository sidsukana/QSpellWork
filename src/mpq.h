#pragma once

#include <QPair>
#include <QString>
#include <QByteArray>

typedef QPair<QString, QStringList> MPQPair;
typedef QList<MPQPair> MPQList;

namespace MPQ
{
    QString& mpqDir();
    QString& localeDir();
    MPQList& mpqFiles();
    void setMpqFiles(const MPQList &files);
    QByteArray readFile(const QString &fileName);
}

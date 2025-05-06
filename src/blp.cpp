#include <QDir>

#include "blp.h"
#include "mpq.h"

QImage BLP::fromMPQ(const QString &fileName)
{
    if (MPQ::mpqDir().isEmpty()) {
        return QImage();
    }

    QByteArray data = MPQ::readFile(QDir::toNativeSeparators(fileName));
    if (data.isEmpty()) {
        return QImage();
    }

    return QImage::fromData(data);
}

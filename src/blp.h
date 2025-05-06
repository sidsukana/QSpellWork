#pragma once

#include <QImage>
#include "qsw_export.h"

#define BLP_MAGIC "BLP2"

struct BLPHeader
{
    char magic[4];
    quint32 type;
    quint8 compression;
    quint8 alphaDepth;
    quint8 alphaType;
    quint8 hasMips;
    quint32 width;
    quint32 height;
    quint32 mipmapOffset[16];
    quint32 mipmapLength[16];
};

namespace BLP
{
QSW_EXPORT QImage fromMPQ(const QString &fileName);
}

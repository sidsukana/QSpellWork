#include <QDebug>
#include <QDir>

#include "DBC/BLP.h"
#include "SWDefines.h"
#include "squish.h"
#include "mpq/MPQ.h"

QImage BLP::getImage(const QString &fileName)
{
    QString fn = QDir::fromNativeSeparators(fileName);
    m_data = MPQ::readFile(fn);

    if (m_data.size() == 0) {
        qCritical("Cannot load texture '%s'", qPrintable(fileName));
    }

    m_header = reinterpret_cast<BLPHeader *>(m_data.data());

    if (qstrncmp(m_header->magic, BLP_MAGIC, 4) != 0) {
        qCritical("File '%s' is not a valid BLP file!", qPrintable(fileName));
    }

    if (m_header->type != 1) {
        qCritical("File '%s' has unsupported BLP type!", qPrintable(fileName));
    }

    quint8* imageData = reinterpret_cast<quint8 *>(m_data.data() + m_header->mipmapOffset[0]);
    quint8* uncompressed = new quint8[m_header->width * m_header->height * 4];

    quint8 dxtVer;
    switch (m_header->alphaType)
    {
        case 0: dxtVer = squish::kDxt1; break;
        case 1: dxtVer = squish::kDxt3; break;
        case 7: dxtVer = squish::kDxt5; break;
        default: dxtVer = squish::kDxt1; break;
    }

    squish::DecompressImage(uncompressed, m_header->width, m_header->height, imageData, dxtVer);

    QImage image(uncompressed, m_header->width, m_header->height, QImage::Format_ARGB32);
    return image.rgbSwapped();
}
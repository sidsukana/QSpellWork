#include <QDebug>
#include <QDir>
#include <QStringList>

#include "texture.h"
#include "mpq/MPQ.h"

#ifndef GL_COMPRESSED_RGB_S3TC_DXT1_EXT
#  define GL_COMPRESSED_RGB_S3TC_DXT1_EXT   0x83F0
#  define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT  0x83F1
#  define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT  0x83F2
#  define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT  0x83F3
#endif

#ifndef GL_BGRA
#  define GL_BGRA                           0x80E1
#endif

#ifndef GL_TEXTURE_MAX_LEVEL
#  define GL_TEXTURE_MAX_LEVEL              0x813D
#endif

Texture::Texture() : m_dirty(false), m_texture(0)
{
}

bool Texture::load(const QString &fileName)
{
    m_data = MPQ::readFile(fileName);

    if (m_data.size() == 0) {
        qCritical("Cannot load texture '%s'", qPrintable(fileName));
        return false;
    }

    m_header = reinterpret_cast<BLPHeader *>(m_data.data());

    if (qstrncmp(m_header->magic, BLP_MAGIC, 4) != 0) {
        qCritical("File '%s' is not a valid BLP file!", qPrintable(fileName));
        return false;
    }

    if (m_header->type != 1) {
        qCritical("File '%s' has unsupported BLP type!", qPrintable(fileName));
        return false;
    }

    m_palette = reinterpret_cast<quint32 *>(m_data.data() + sizeof(BLPHeader));

    m_dirty = true;

    return true;
}

quint32 * Texture::readPalettedTexture(quint32 width, quint32 height, const char *data)
{
    quint32 *texture = new quint32[width * height * sizeof(quint32)];

    quint32 pixelCount = width * height;

    const quint8 *indices = reinterpret_cast<const quint8 *>(data);
    const quint8 *alphas = reinterpret_cast<const quint8 *>(data + pixelCount * sizeof(quint8));

    for (quint32 i = 0; i < pixelCount; i++) {
        texture[i] = m_palette[indices[i]];

        quint8 alpha = 0xff;

        switch (m_header->alphaDepth) {
            case 1:
                if ((alphas[i >> 3] & (1 << (i % 8))) == 0)
                    alpha = 0x00;
                break;
            case 8:
                alpha = alphas[i];
                break;
        }

        texture[i] |= alpha << 24;
    }

    return texture;
}

void Texture::create()
{
    if (!m_texture)
        glGenTextures(1, &m_texture);

    initializeOpenGLFunctions();

    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    quint32 width = m_header->width;
    quint32 height = m_header->height;

    GLenum internalFormat;

    switch (m_header->alphaDepth) {
        case 0:
            internalFormat = GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
            break;
        case 1:
            internalFormat = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
            break;
        default:
            internalFormat = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
            break;
    }

    int i;

    for (i = 0; i < 16; i++) {
        if (!m_header->mipmapLength[i])
            break;

        if (m_header->compression == 1) {
            quint32 *data = readPalettedTexture(width, height, m_data.data() + m_header->mipmapOffset[i]);

            glTexImage2D(GL_TEXTURE_2D, i, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);

            delete[] data;
        } else {
            glCompressedTexImage2D(GL_TEXTURE_2D, i, internalFormat, width, height, 0, m_header->mipmapLength[i], m_data.data() + m_header->mipmapOffset[i]);
        }

        if (glGetError() == GL_INVALID_VALUE) {
            qDebug() << "Texture loading failed";
            qDebug() << "\tcompression" << m_header->compression;
            qDebug() << "\talpha depth" << m_header->alphaDepth;
            qDebug() << "\talpha type" << m_header->alphaType;
            qDebug() << "\tmipmap level" << i;

            break;
        }

        width >>= 1;

        if (width == 0)
            width = 1;

        height >>= 1;

        if (height == 0)
            height = 1;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, i ? i - 1 : 0);

    m_dirty = false;
}

void Texture::bind()
{
    if (m_dirty)
        create();

    glBindTexture(GL_TEXTURE_2D, m_texture);
}

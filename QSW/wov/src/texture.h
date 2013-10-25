#ifndef TEXTURE_H
#define TEXTURE_H

#include <QGLFunctions>

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

class Texture : public QGLFunctions
{
public:
    Texture();

    bool load(const QString &fileName);
    void bind();

private:
    void create();

    quint32 * readPalettedTexture(quint32 width, quint32 height, const char *data);

    QByteArray m_data;
    BLPHeader *m_header;
    quint32 *m_palette;

    bool m_dirty;

    GLuint m_texture;
};

#endif

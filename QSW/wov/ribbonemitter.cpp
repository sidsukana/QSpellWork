#include "ribbonemitter.h"

RibbonEmitter::RibbonEmitter(const M2RibbonEmitter &emitter, const quint32 *sequences, const QByteArray &data)
    : m_bone(emitter.bone),
      m_position(emitter.position[0], emitter.position[1], emitter.position[2]),
      m_color(emitter.color, sequences, data),
      m_opacity(emitter.opacity, sequences, data),
      m_above(emitter.above, sequences, data),
      m_below(emitter.below, sequences, data),
      m_segments(emitter.segments),
      m_length(emitter.length),
      m_angle(emitter.angle),
      m_vertices(0),
      m_vertexBuffer(0),
      m_initialized(false)
{
    const qint32 *textures = reinterpret_cast<const qint32 *>(data.data() + emitter.texturesOffset);
    for (quint32 i = 0; i < emitter.texturesCount; i++)
        m_textures << textures[i];
}

void RibbonEmitter::update(quint32 animation, quint32 time, QMatrix4x4 boneMatrix)
{
    Ribbon ribbon;
    ribbon.position = boneMatrix * m_position;
    ribbon.up = (boneMatrix * QVector4D(0.0f, 0.0f, 1.0f, 0.0f)).toVector3D();

    if (m_ribbons.isEmpty())
        m_ribbons << ribbon << ribbon;
    else
        m_ribbons[0] = ribbon;

    float length = (m_ribbons[0].position - m_ribbons[1].position).length();

    if (length >= m_length / m_segments) {
        m_ribbons.prepend(ribbon);

        if (m_ribbons.size() - 1 > m_segments)
            m_ribbons.removeLast();
    }

    float above = m_above.getValue(animation, time);
    float below = m_below.getValue(animation, time);
    QVector3D color = m_color.getValue(animation, time);
    float opacity = m_opacity.getValue(animation, time) / 32767.0f;

    if (m_vertices)
        delete[] m_vertices;

    m_vertices = new ParticleVertex[2 * m_ribbons.size()];

    for (int i = 0; i < m_ribbons.size(); i++) {
        QVector3D position = m_ribbons[i].position;
        QVector3D up = m_ribbons[i].up;

        m_vertices[2 * i + 0].setPosition(position + above * up);
        m_vertices[2 * i + 1].setPosition(position - below * up);

        m_vertices[2 * i + 0].setColor(QVector4D(color, opacity));
        m_vertices[2 * i + 1].setColor(QVector4D(color, opacity));

        m_vertices[2 * i + 0].setTexcoord(QVector2D(float(i) / float(m_ribbons.size() - 1), 0.0f));
        m_vertices[2 * i + 1].setTexcoord(QVector2D(float(i) / float(m_ribbons.size() - 1), 1.0f));
    }
}

void RibbonEmitter::initialize()
{
    initializeOpenGLFunctions();

    m_vertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vertexBuffer->create();
    m_vertexBuffer->setUsagePattern(QOpenGLBuffer::StreamDraw);

    m_initialized = true;
}

void RibbonEmitter::render(QOpenGLShaderProgram *program, MVP viewProjection)
{
    if (!m_initialized)
        initialize();

    if (!m_vertices)
        return;

    program->setUniformValue("mvpMatrix", viewProjection.getMVPMatrix());

    m_vertexBuffer->bind();
    m_vertexBuffer->allocate(m_vertices, 2 * m_ribbons.size() * sizeof(ParticleVertex));

    program->enableAttributeArray("position");
    program->setAttributeBuffer("position", GL_FLOAT, 0, 3, sizeof(ParticleVertex));

    program->enableAttributeArray("color");
    program->setAttributeBuffer("color", GL_FLOAT, 3 * sizeof(float), 4, sizeof(ParticleVertex));

    program->enableAttributeArray("texcoord");
    program->setAttributeBuffer("texcoord", GL_FLOAT, 7 * sizeof(float), 2, sizeof(ParticleVertex));

    glDisable(GL_CULL_FACE);
    glDepthMask(GL_FALSE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 2 * m_ribbons.size());

    program->disableAttributeArray("position");
    program->disableAttributeArray("color");
    program->disableAttributeArray("texcoord");

    glDepthMask(GL_TRUE);

    glDisable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_vertexBuffer->release();
}

qint32 RibbonEmitter::getBoneId() const
{
    return m_bone;
}

qint32 RibbonEmitter::getTextureId() const
{
    if (m_textures.empty())
        return -1;

    return m_textures[0];
}


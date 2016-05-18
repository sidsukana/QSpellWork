#define _USE_MATH_DEFINES
#include <cmath>

#include "particleemitter.h"

float rand(float min, float max)
{
    return min + (max - min) * (float(rand()) / RAND_MAX);
}

template <typename T>
T getValueAtLife(float life, float midpoint, T a, T b, T c)
{
    float t;
    T min, max;

    if (life <= midpoint) {
        t = life / midpoint;
        min = a;
        max = b;
    } else {
        t = (life - midpoint) / (1.0f - midpoint);
        min = b;
        max = c;
    }

    return min * (1.0f - t) + max * t;
}

ParticleEmitter::ParticleEmitter(const M2ParticleEmitter &emitter, const quint32 *sequences, const QByteArray &data)
    : m_flags(emitter.flags),
      m_position(emitter.position[0], emitter.position[1], emitter.position[2]),
      m_bone(emitter.bone),
      m_texture(emitter.texture),
      m_blending(emitter.blending),
      m_emitterType(emitter.emitterType),
      m_particleType(emitter.particleType),
      m_rows(emitter.rows),
      m_cols(emitter.cols),
      m_speed(emitter.speed, sequences, data),
      m_speedVariation(emitter.speedVariation, sequences, data),
      m_verticalRange(emitter.verticalRange, sequences, data),
      m_horizontalRange(emitter.horizontalRange, sequences, data),
      m_gravity(emitter.gravity, sequences, data),
      m_lifespan(emitter.lifespan, sequences, data),
      m_emissionRate(emitter.emissionRate, sequences, data),
      m_emissionLength(emitter.emissionLength, sequences, data),
      m_emissionWidth(emitter.emissionWidth, sequences, data),
      m_enabled(emitter.enabled, sequences, data),
      m_midpoint(emitter.midpoint),
      m_slowdown(emitter.slowdown),
      m_rotation(emitter.rotation),
      m_initialized(false),
      m_vertexBuffer(0), m_indexBuffer(0)
{
    if (m_rows == 0)
        m_rows = 1;

    if (m_cols == 0)
        m_cols = 1;

    for (int i = 0; i < 3; i++) {
        m_sizes[i] = emitter.sizes[i];

        quint32 color = emitter.colors[i];

        float alpha = ((color >> 24) & 0xff) / 255.0f;
        float red   = ((color >> 16) & 0xff) / 255.0f;
        float green = ((color >>  8) & 0xff) / 255.0f;
        float blue  = ((color >>  0) & 0xff) / 255.0f;

        m_colors[i] = QVector4D(red, green, blue, alpha);
    }
}

QMatrix4x4 getParticleMatrix(float v, float h, float l, float w)
{
    QMatrix4x4 matrix;

    matrix.scale(w, w, l);

    matrix.rotate(0.5f * rand(-v, v) * 180.0f / M_PI, 1.0f, 0.0f, 0.0f);
    matrix.rotate(0.5f * rand(-h, h) * 180.0f / M_PI, 0.0f, 0.0f, 1.0f);

    return matrix;
}

void ParticleEmitter::update(quint32 animation, quint32 time, float timeDelta, QMatrix4x4 boneMatrix)
{
    float rate = m_emissionRate.getValue(animation, time);

    bool enabled = m_enabled.getValue(animation, time);
    if (!enabled)
        rate = 0.0f;

    double count;
    m_remainingCount = modf(rate * timeDelta + m_remainingCount, &count);

    float verticalRange = m_verticalRange.getValue(animation, time);
    float horizontalRange = m_horizontalRange.getValue(animation, time);

    float length = m_emissionLength.getValue(animation, time);
    float width = m_emissionWidth.getValue(animation, time);

    for (int i = 0; i < int(count); i++) {
        Particle particle;

        QVector3D direction(0.0f, 0.0f, 1.0f);

        if (m_emitterType == 2) {
            if (horizontalRange == 0)
                horizontalRange = float(M_PI);

            QMatrix4x4 m = getParticleMatrix(verticalRange * 2, horizontalRange * 2, length, width);

            direction = (boneMatrix * m * QVector4D(0.0f, 1.0f, 0.0f, 0.0f) * rand(0.0f, 1.0f)).toVector3D();

            particle.position = boneMatrix * m_position + direction;

            if (m_flags & 0x100)
                direction = QVector3D(0.0f, 0.0f, 1.0f);
            else
                direction.normalize();
        } else {
            //QMatrix4x4 m = getParticleMatrix(verticalRange, verticalRange, 1.0f, 1.0f);

            particle.position = boneMatrix * (m_position + QVector3D(0.5f * rand(-length, length), 0.5f * rand(-width, width), 0.0f));

            direction = (boneMatrix * QVector4D(0.0f, 0.0f, 1.0f, 0.0f)).toVector3D();
        }

        particle.origin = particle.position;

        float speed = m_speed.getValue(animation, time);
        float speedVariation = m_speedVariation.getValue(animation, time);
        particle.speed = direction * speed * (1.0f + rand(-speedVariation, speedVariation));

        float gravity = m_gravity.getValue(animation, time);
        particle.acceleration = QVector3D(0.0f, 0.0f, -1.0f) * gravity;

        particle.tileU = rand() % m_rows;
        particle.tileV = rand() % m_cols;

        particle.life = 0.0f;
        particle.lifespan = m_lifespan.getValue(animation, time);

        m_particles << particle;
    }

    for (int i = 0; i < m_particles.size();) {
        Particle &particle = m_particles[i];

        particle.speed += particle.acceleration * timeDelta;
        particle.position += particle.speed * timeDelta;
        particle.life += timeDelta;

        if (particle.life >= particle.lifespan)
            m_particles.removeAt(i);
        else
            i++;
    }
}

void ParticleEmitter::initialize()
{
    initializeOpenGLFunctions();

    m_vertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vertexBuffer->create();
    m_vertexBuffer->setUsagePattern(QOpenGLBuffer::StreamDraw);

    m_indexBuffer = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    m_indexBuffer->create();
    m_indexBuffer->setUsagePattern(QOpenGLBuffer::StreamDraw);

    m_initialized = true;
}

void ParticleEmitter::render(QOpenGLShaderProgram *program, MVP viewProjection)
{
    if (!m_initialized)
        initialize();

    program->setUniformValue("mvpMatrix", viewProjection.getMVPMatrix());

    QMatrix4x4 billboard = viewProjection.getBillboardMatrix();

    ParticleVertex *vertices = new ParticleVertex[4 * m_particles.size()];
    quint16 *indices = new quint16[6 * m_particles.size()];

    for (int i = 0; i < m_particles.size(); i++) {
        indices[6 * i + 0] = 4 * i + 0;
        indices[6 * i + 1] = 4 * i + 1;
        indices[6 * i + 2] = 4 * i + 2;
        indices[6 * i + 3] = 4 * i + 2;
        indices[6 * i + 4] = 4 * i + 3;
        indices[6 * i + 5] = 4 * i + 0;

        QVector3D origin = m_particles[i].origin;
        QVector3D position = m_particles[i].position;

        float life = m_particles[i].life / m_particles[i].lifespan;
        float size = getValueAtLife(life, m_midpoint, m_sizes[0], m_sizes[1], m_sizes[2]);

        QVector4D color = getValueAtLife(life, m_midpoint, m_colors[0], m_colors[1], m_colors[2]);

        int tileU = m_particles[i].tileU;
        int tileV = m_particles[i].tileV;

        if (m_particleType == 1) {
            vertices[4 * i + 0].setPosition(origin   + billboard * QVector3D(-1.0f,-0.0f, 0.0f) * size);
            vertices[4 * i + 1].setPosition(origin   + billboard * QVector3D( 1.0f, 0.0f, 0.0f) * size);
            vertices[4 * i + 2].setPosition(position + billboard * QVector3D( 1.0f, 0.0f, 0.0f) * size);
            vertices[4 * i + 3].setPosition(position + billboard * QVector3D(-1.0f,-0.0f, 0.0f) * size);
        } else {
            vertices[4 * i + 0].setPosition(position + billboard * QVector3D(-1.0f, -1.0f, 0.0f) * size);
            vertices[4 * i + 1].setPosition(position + billboard * QVector3D( 1.0f, -1.0f, 0.0f) * size);
            vertices[4 * i + 2].setPosition(position + billboard * QVector3D( 1.0f,  1.0f, 0.0f) * size);
            vertices[4 * i + 3].setPosition(position + billboard * QVector3D(-1.0f,  1.0f, 0.0f) * size);
        }

        vertices[4 * i + 0].setColor(color);
        vertices[4 * i + 1].setColor(color);
        vertices[4 * i + 2].setColor(color);
        vertices[4 * i + 3].setColor(color);

        vertices[4 * i + 0].setTexcoord(QVector2D(float(tileU) / m_rows, float(tileV) / m_cols));
        vertices[4 * i + 1].setTexcoord(QVector2D(float(tileU + 1) / m_rows, float(tileV) / m_cols));
        vertices[4 * i + 2].setTexcoord(QVector2D(float(tileU + 1) / m_rows, float(tileV + 1) / m_cols));
        vertices[4 * i + 3].setTexcoord(QVector2D(float(tileU) / m_rows, float(tileV + 1) / m_cols));
    }

    m_vertexBuffer->bind();
    m_vertexBuffer->allocate(vertices, 4 * m_particles.size() * sizeof(ParticleVertex));

    program->enableAttributeArray("position");
    program->setAttributeBuffer("position", GL_FLOAT, 0, 3, sizeof(ParticleVertex));

    program->enableAttributeArray("color");
    program->setAttributeBuffer("color", GL_FLOAT, 3 * sizeof(float), 4, sizeof(ParticleVertex));

    program->enableAttributeArray("texcoord");
    program->setAttributeBuffer("texcoord", GL_FLOAT, 7 * sizeof(float), 2, sizeof(ParticleVertex));

    m_indexBuffer->bind();
    m_indexBuffer->allocate(indices, 6 * m_particles.size() * sizeof(quint16));

    glDisable(GL_CULL_FACE);
    glDepthMask(GL_FALSE);

    switch (m_blending) {
        case 0:
            glDisable(GL_BLEND);
            glDisable(GL_ALPHA_TEST);
            break;
        case 1:
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_COLOR, GL_ONE);
            glDisable(GL_ALPHA_TEST);
            break;
        case 2:
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glDisable(GL_ALPHA_TEST);
            break;
        case 3:
            glDisable(GL_BLEND);
            glEnable(GL_ALPHA_TEST);
            break;
        case 4:
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            glDisable(GL_ALPHA_TEST);
            break;
    }

    glDrawElements(GL_TRIANGLES, 6 * m_particles.size(), GL_UNSIGNED_SHORT, 0);

    program->disableAttributeArray("position");
    program->disableAttributeArray("color");
    program->disableAttributeArray("texcoord");

    glDepthMask(GL_TRUE);

    m_vertexBuffer->release();
    m_indexBuffer->release();
}

qint16 ParticleEmitter::getBoneId()
{
    return m_bone;
}

qint16 ParticleEmitter::getTextureId()
{
    return m_texture;
}

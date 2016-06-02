#ifndef PARTICLE_EMITTER_H
#define PARTICLE_EMITTER_H

#include <QObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>

#include "m2structures.h"
#include "animatedvalue.h"
#include "mvp.h"

struct Particle
{
    QVector3D origin;
    QVector3D position;
    QVector3D speed;
    QVector3D acceleration;

    int tileU, tileV;

    float life;
    float lifespan;
};

struct ParticleVertex
{
    void setPosition(QVector3D position)
    {
        m_position[0] = position.x();
        m_position[1] = position.y();
        m_position[2] = position.z();
    }

    void setColor(QVector4D color)
    {
        m_color[0] = color.x();
        m_color[1] = color.y();
        m_color[2] = color.z();
        m_color[3] = color.w();
    }

    void setTexcoord(QVector2D texcoord)
    {
        m_texcoord[0] = texcoord.x();
        m_texcoord[1] = texcoord.y();
    }

    float m_position[3];
    float m_color[4];
    float m_texcoord[2];
};

class ParticleEmitter : public QObject
{
    Q_OBJECT
public:
    ParticleEmitter(const M2ParticleEmitter &emitter, const quint32 *sequences, const QByteArray &data);

    void update(quint32 animation, quint32 time, float timeDelta, QMatrix4x4 boneMatrix);
    void render(QOpenGLShaderProgram *program, MVP viewProjection);

    qint16 getBoneId();
    qint16 getTextureId();

private:
    void initialize();

    qint32 m_flags;
    QVector3D m_position;
    qint16 m_bone;
    qint16 m_texture;
    qint16 m_blending;
    qint16 m_emitterType;
    qint16 m_particleType;
    qint16 m_rows;
    qint16 m_cols;

    AnimatedValue<float> m_speed;
    AnimatedValue<float> m_speedVariation;
    AnimatedValue<float> m_verticalRange;
    AnimatedValue<float> m_horizontalRange;
    AnimatedValue<float> m_gravity;
    AnimatedValue<float> m_lifespan;
    AnimatedValue<float> m_emissionRate;
    AnimatedValue<float> m_emissionLength;
    AnimatedValue<float> m_emissionWidth;
    AnimatedValue<quint8> m_enabled;

    float m_midpoint;
    QVector4D m_colors[3];
    float m_sizes[3];
    qint16 m_tiles[10];
    float m_scales[3];
    float m_slowdown;
    float m_rotation;

    QList<Particle> m_particles;
    float m_remainingCount;

    bool m_initialized;

    QOpenGLBuffer *m_vertexBuffer;
    QOpenGLBuffer *m_indexBuffer;

    QOpenGLContext* m_context;
    QOpenGLFunctions* m_funcs;
};

#endif

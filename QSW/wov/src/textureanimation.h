#ifndef TEXTURE_ANIMATION_H
#define TEXTURE_ANIMATION_H

#include <QMatrix4x4>

#include "m2structures.h"
#include "animatedvalue.h"

class TextureAnimation
{
public:
    TextureAnimation(const M2TextureAnimation &animation, const quint32 *sequences, const QByteArray &data);

    QMatrix4x4 getMatrix(quint32 animation, quint32 time);

private:
    AnimatedValue<QVector3D> m_translation;
    AnimatedValue<QVector3D> m_rotation;
    AnimatedValue<QVector3D> m_scaling;
};

#endif

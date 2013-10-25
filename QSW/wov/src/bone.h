#ifndef BONE_H
#define BONE_H

#include <QMatrix4x4>

#include "m2structures.h"
#include "animatedvalue.h"
#include "mvp.h"

class Bone
{
public:
    Bone(const M2Bone &bone, const quint32 *sequences, const QByteArray &data);

    QMatrix4x4 getMatrix(quint32 animation, quint32 time, MVP mvp);
    const QVector3D & getPivot() const;
    bool isBillboarded() const;

    Bone *parent;

private:
    quint32 m_flags;

    AnimatedValue<QVector3D> m_translation;
    AnimatedValue<QQuaternion> m_rotation;
    AnimatedValue<QVector3D> m_scaling;

    QVector3D m_pivot;
};

#endif

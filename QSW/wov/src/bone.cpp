#include "bone.h"

Bone::Bone(const M2Bone &bone, const quint32 *sequences, const QByteArray &data)
    : parent(0),
      m_flags(bone.flags),
      m_translation(bone.translation, sequences, data),
      m_rotation(bone.rotation, sequences, data),
      m_scaling(bone.scaling, sequences, data),
      m_pivot(bone.pivot)
{
}

QMatrix4x4 Bone::getMatrix(quint32 animation, quint32 time, MVP mvp)
{
    QMatrix4x4 matrix;
    matrix.translate(m_pivot);

    if (m_translation.isValid())
        matrix.translate(m_translation.getValue(animation, time));

    if (m_rotation.isValid())
        matrix.rotate(m_rotation.getValue(animation, time));

    if (m_scaling.isValid())
        matrix.scale(m_scaling.getValue(animation, time));

    if (isBillboarded()) {
        QMatrix4x4 billboard = mvp.getBillboardMatrix();

        billboard.rotate(-90, 0.0f, 1.0f, 0.0f);
        billboard.rotate(-90, 1.0f, 0.0f, 0.0f);

        matrix *= billboard;
    }

    matrix.translate(-1.0 * m_pivot);

    if (parent)
        matrix = parent->getMatrix(animation, time, mvp) * matrix;

    return matrix;
}

const QVector3D & Bone::getPivot() const
{
    return m_pivot;
}

bool Bone::isBillboarded() const
{
    return m_flags & 0x8;
}

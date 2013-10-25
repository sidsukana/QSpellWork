#include "textureanimation.h"

TextureAnimation::TextureAnimation(const M2TextureAnimation &animation, const quint32 *sequences, const QByteArray &data)
    : m_translation(animation.translation, sequences, data),
      m_rotation(animation.rotation, sequences, data),
      m_scaling(animation.scaling, sequences, data)
{
}

QMatrix4x4 TextureAnimation::getMatrix(quint32 animation, quint32 time)
{
    QMatrix4x4 matrix;

    if (m_translation.isValid())
        matrix.translate(m_translation.getValue(animation, time));

    return matrix;
}

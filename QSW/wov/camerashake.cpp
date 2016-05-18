#define _USE_MATH_DEFINES
#include <cmath>

#include <QDateTime>

#include "camerashake.h"

CameraShake::CameraShake(quint32 id)
{
    m_shake = CameraShakesDBC::getRecord(id, true);
    m_duration = m_shake->duration;
}

bool CameraShake::update(int timeDelta)
{
    if (m_duration <= timeDelta / 1000.0f)
        return false;

    m_duration -= timeDelta / 1000.0f;

    return true;
}

QVector3D CameraShake::getShake()
{
    float amplitude = m_shake->amplitude / 36.0f;
    float frequency = 2 * M_PI * m_shake->frequency;
    float time = QDateTime::currentMSecsSinceEpoch() / 1000.0f;

    float shake = amplitude * sin(frequency * time);

    switch (m_shake->axis) {
        case 0:
            return QVector3D(0.0f, 0.0f, shake);
        case 1:
            return QVector3D(shake, 0.0f, 0.0f);
        case 2:
            return QVector3D(0.0f, shake, 0.0f);
        default:
            return QVector3D();
    }
}

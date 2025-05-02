#ifndef CAMERA_SHAKE_H
#define CAMERA_SHAKE_H

#include <QVector3D>

#include "wovdbc.h"

class CameraShake
{
public:
    explicit CameraShake(quint32 id);

    bool update(int timeDelta);
    QVector3D getShake();

private:
    const CameraShakesDBC::entry* m_shake;

    float m_duration;
};

#endif

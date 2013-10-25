#include "mvp.h"

QMatrix4x4 MVP::getMVPMatrix() const
{
    return projection * view * model;
}

QMatrix3x3 MVP::getNormalMatrix() const
{
    return (view * model).normalMatrix();
}

QMatrix4x4 MVP::getBillboardMatrix() const
{
    QMatrix4x4 billboard = (view * model).inverted();

    billboard(0, 3) = 0.0f;
    billboard(1, 3) = 0.0f;
    billboard(2, 3) = 0.0f;
    billboard(3, 0) = 0.0f;
    billboard(3, 1) = 0.0f;
    billboard(3, 2) = 0.0f;

    return billboard;
}

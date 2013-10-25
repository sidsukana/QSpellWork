#ifndef MVP_H
#define MVP_H

#include <QMatrix4x4>

class MVP
{
public:
    QMatrix4x4 getMVPMatrix() const;
    QMatrix3x3 getNormalMatrix() const;
    QMatrix4x4 getBillboardMatrix() const;

    QMatrix4x4 projection;
    QMatrix4x4 view;
    QMatrix4x4 model;
};

#endif

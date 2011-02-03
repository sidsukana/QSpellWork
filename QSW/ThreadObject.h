#ifndef THREADOBJ_H
#define THREADOBJ_H

#include <QtCore/QThread>
#include "SpellWork.h"

class ObjThread: public QThread
{
    friend class SpellWork;
public:
    
    ObjThread(quint8 id = 0, SpellWork *obj = NULL);
    ~ObjThread();

    virtual void run();
    quint8 GetId() { return t_id; }
private:
    quint8 t_id;

    SpellWork *_iFace;
};

#endif
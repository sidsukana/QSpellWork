#ifndef THREADOBJ_H
#define THREADOBJ_H

#include <iostream>
#include "SpellWork.h"

class ObjThread: public QThread
{
    friend class SpellWork;
public:
    
    ObjThread(uint8 id = 0, SpellWork *obj = NULL);
    ~ObjThread();

    virtual void run();
    uint8 GetId() { return t_id; }
private:
    uint8 t_id;

    SpellWork *_iFace;
};

#endif
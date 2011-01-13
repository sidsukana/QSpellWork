#ifndef THREADOBJ_H
#define THREADOBJ_H

#include <iostream>
#include "SpellWork.h"

class ObjThread: public QThread
{
    friend class SpellWork;
public:
    
    ObjThread(int id = 0, SpellWork *obj = NULL);
    ~ObjThread();

    virtual void run();
    int GetId() { return t_id; }
private:
    int t_id;

    SpellWork *_iFace;
};

#endif
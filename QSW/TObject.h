#ifndef THREADOBJ_H
#define THREADOBJ_H

#include <QtCore/QThread>
#include "SWObject.h"
#include "SWSearch.h"

class SWObject;
class SWSearch;
class TObject: public QThread
{
public:
    
    TObject(quint8 id, SWObject* sw);
    ~TObject();

    virtual void run();
    quint8 getId() { return m_id; }
private:

    quint8 m_id;
    SWObject* m_sw;
};

#endif

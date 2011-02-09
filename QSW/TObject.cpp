#include "TObject.h"
#include "Defines.h"

TObject::TObject(quint8 id, SWObject *sw)
    : m_id(id), m_sw(sw)
{
    moveToThread(this);
}

TObject::~TObject()
{
}

void TObject::run()
{
    switch (m_id)
    {
        case THREAD_SEARCH:
        {
            SWSearch *search = new SWSearch(m_sw);
            search->Search();
        }
        break;
    }
}

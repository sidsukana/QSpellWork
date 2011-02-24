#ifndef SWSEARCH_H
#define SWSEARCH_H

#include "SWObject.h"
#include "DBC/DBCStores.h"

class SWObject;
class SWForm;
class SWSearch
{
    public:
        SWSearch(SWObject *sw = NULL);
        ~SWSearch();

        void Search();
        bool HasValue(quint8 index, QString str, SpellEntry const *m_spellInfo, quint8 state);

    private:
        SWObject *m_sw;
};

#endif // SWSEARCH_H

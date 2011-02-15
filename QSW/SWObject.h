#ifndef SWOBJECT_H
#define SWOBJECT_H

#include <QtCore/QMetaEnum>
#include <QtCore/QMutex>

#include "SWForm.h"
#include "SWEvent.h"
#include "TObject.h"
#include "DBC/DBCStores.h"
#include "SWDefines.h"

class SWForm;
class TObject;
class SWObject
{
    public:
        SWObject(SWForm *form = NULL);
        ~SWObject();

        void ShowInfo(SpellEntry const* spellInfo);

        void AppendSkillLine(SpellEntry const* spellInfo);
        void AppendCastTimeLine(SpellEntry const* spellInfo);
        void AppendDurationLine(SpellEntry const* spellInfo);
        void AppendRangeInfo(SpellEntry const* spellInfo);
        void AppendSpellEffectInfo(SpellEntry const* spellInfo);
        void AppendAuraInfo(SpellEntry const* spellInfo, quint8 index);
        void AppendRadiusInfo(SpellEntry const* spellInfo, quint8 index);
        void AppendTriggerInfo(SpellEntry const* spellInfo, quint8 index);
        void AppendProcInfo(SpellEntry const *spellInfo);

        QString CompareAttributes(SpellEntry const* spellInfo, AttrType attr, quint8 index = 0);
        QString GetDescription(QString str, SpellEntry const *spellInfo);

        void ThreadBegin(quint8 id);
        void ThreadSet(quint8 id) { ThreadSemaphore[id] = true; }
        void ThreadUnset(quint8 id) { ThreadSemaphore[id] = false; }
        bool ThreadExist(quint8 id) { return ThreadSemaphore[id]; }

        void SetMetaEnum(char* e)
        {
            e_idx = mo.indexOfEnumerator(e);
            me = mo.enumerator(e_idx);
        }

        QMetaEnum GetMetaEnum() { return me; }
        SWForm* GetForm() { return m_form; }
        bool IsRegExp() const { return useRegExp; }
        bool IsFilter() const { return useFilter; }
        void SetRegExp(bool on) { useRegExp = on; }
        void SetFilter(bool on) { useFilter = on; }

        QMetaEnum me;

    private:
        SWForm *m_form;

        bool useRegExp;
        bool useFilter;

        QMetaObject mo;
        quint8 e_idx;
        bool ThreadSemaphore[MAX_THREAD];
};

#endif // SWOBJECT_H

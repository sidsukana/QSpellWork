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

        void ShowInfo(SpellEntry const* spellInfo, quint8 num = 0);
        void Compare();

        void AppendSkillLine(SpellEntry const* spellInfo, quint8 num);
        void AppendCastTimeLine(SpellEntry const* spellInfo, quint8 num);
        void AppendDurationLine(SpellEntry const* spellInfo, quint8 num);
        void AppendRangeInfo(SpellEntry const* spellInfo, quint8 num);
        void AppendSpellEffectInfo(SpellEntry const* spellInfo, quint8 num);
        void AppendAuraInfo(SpellEntry const* spellInfo, quint8 index, quint8 num);
        void AppendRadiusInfo(SpellEntry const* spellInfo, quint8 index, quint8 num);
        void AppendTriggerInfo(SpellEntry const* spellInfo, quint8 index, quint8 num);
        void AppendProcInfo(SpellEntry const *spellInfo, quint8 num);

        QString ContainAttributes(SpellEntry const* spellInfo, AttrType attr, quint8 index = 0);
        QString GetDescription(QString str, SpellEntry const *spellInfo);

        void ThreadBegin(quint8 id);
        void ThreadSet(quint8 id) { ThreadSemaphore[id] = true; }
        void ThreadUnset(quint8 id) { ThreadSemaphore[id] = false; }
        bool ThreadExist(quint8 id) { return ThreadSemaphore[id]; }

        void SetMetaEnum(const char* e)
        {
            e_idx = mo.indexOfEnumerator(e);
            me = mo.enumerator(e_idx);
        }

        QMetaEnum GetMetaEnum() { return me; }
        SWForm* GetForm() { return m_form; }
        bool IsRegExp() const { return useRegExp; }
        quint8 GetType() const { return m_type; }
        void SetRegExp(bool on) { useRegExp = on; }
        void SetType(quint8 type) { m_type = type; }

        void SetLocale(quint8 locale) { m_locale = locale; }
        quint8 GetLocale() const { return m_locale; }

        QMetaEnum me;

    private:
        SWForm *m_form;

        bool useRegExp;
        quint8 m_type;
        quint8 m_locale;

        QMetaObject mo;
        quint8 e_idx;
        bool ThreadSemaphore[MAX_THREAD];
};

#endif // SWOBJECT_H

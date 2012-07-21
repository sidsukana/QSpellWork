#ifndef SWOBJECT_H
#define SWOBJECT_H

#include <QtCore/QMetaEnum>

#include "SWMainForm.h"
#include "SWEvent.h"
#include "DBC/DBCStores.h"
#include "SWDefines.h"

class SWMainForm;

class SWObject
{
    public:
        SWObject(SWMainForm *form);
        ~SWObject();

        void showInfo(SpellEntry const* spellInfo, quint8 num = 1);
        quint32 getParentSpellId(quint32 triggerId);
        void compare();
        void search();

        void appendSkillInfo(SpellEntry const* spellInfo, quint8 num);
        void appendCastTimeInfo(SpellEntry const* spellInfo, quint8 num);
        void appendDurationInfo(SpellEntry const* spellInfo, quint8 num);
        void appendRangeInfo(SpellEntry const* spellInfo, quint8 num);
        void appendSpellEffectInfo(SpellEntry const* spellInfo, quint8 num);
        void appendAuraInfo(SpellEntry const* spellInfo, quint8 index, quint8 num);
        void appendRadiusInfo(SpellEntry const* spellInfo, quint8 index, quint8 num);
        void appendTriggerInfo(SpellEntry const* spellInfo, quint8 index, quint8 num);
        void appendProcInfo(SpellEntry const *spellInfo, quint8 num);

        QString containAttributes(SpellEntry const* spellInfo, AttrType attr, quint8 index = 0);
        QString getDescription(QString str, SpellEntry const *spellInfo);
        QString getSpellIconName(quint32 iconId);

        QMetaEnum getMetaEnum() { return m_metaEnum; }
        void setMetaEnum(const char* enumName);

        bool isRegExp() const { return m_regExp; }
        void setRegExp(bool on) { m_regExp = on; }

        quint8 getType() const { return m_type; }
        void setType(quint8 type) { m_type = type; }

        SWMainForm* getForm() { return m_form; }

    private:
        SWMainForm *m_form;

        bool m_regExp;
        QString html;
        quint8 m_type;

        QMetaEnum m_metaEnum;
};

namespace Converter
{
    quint64 getULongLong(QString value);
    qint64  getLongLong(QString value);
    quint32 getULong(QString value);
    qint32  getLong(QString value);
};

#endif // SWOBJECT_H

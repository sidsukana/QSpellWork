#ifndef SWOBJECT_H
#define SWOBJECT_H

#include <QMetaEnum>

#include "SWMainForm.h"
#include "SWEnums.h"
#include "SWEvent.h"
#include "dbc/DBCStructure.h"
#include "blp/BLP.h"

enum MaskType
{
    TYPE_ATTR,
    TYPE_ATTR_EX1,
    TYPE_ATTR_EX2,
    TYPE_ATTR_EX3,
    TYPE_ATTR_EX4,
    TYPE_TARGETS,
    TYPE_CREATURE,
    TYPE_FORMS,
    TYPE_FORMS_NOT,
    TYPE_ITEM_WEAPON,
    TYPE_ITEM_ARMOR,
    TYPE_ITEM_MISC,
    TYPE_ITEM_INVENTORY,
    MAX_ATTR_TYPE
};

class SWMainForm;
class SWObject
{
    public:
        SWObject(SWMainForm *form);
        ~SWObject();

        void showInfo(Spell::entry const* spellInfo, quint8 num = 1);
        quint32 getParentSpellId(quint32 triggerId);
        void compare();
        void search();

        void appendSkillInfo(Spell::entry const* spellInfo, quint8 num);
        void appendCastTimeInfo(Spell::entry const* spellInfo, quint8 num);
        void appendDurationInfo(Spell::entry const* spellInfo, quint8 num);
        void appendRangeInfo(Spell::entry const* spellInfo, quint8 num);
        void appendSpellEffectInfo(Spell::entry const* spellInfo, quint8 num);
        void appendAuraInfo(Spell::entry const* spellInfo, quint8 index, quint8 num);
        void appendRadiusInfo(Spell::entry const* spellInfo, quint8 index, quint8 num);
        void appendTriggerInfo(Spell::entry const* spellInfo, quint8 index, quint8 num);
        void appendProcInfo(Spell::entry const *spellInfo, quint8 num);

        QString containAttributes(Spell::entry const* spellInfo, MaskType type, quint8 index = 0);
        QString getDescription(QString str, Spell::entry const *spellInfo);
        QString getSpellIconName(quint32 iconId);
        QImage getSpellIcon(quint32 iconId);

        QMetaEnum getMetaEnum() { return m_metaEnum; }
        void setMetaEnum(const char* enumName);

        quint8 getType() const { return m_type; }
        void setType(quint8 type) { m_type = type; }

        SWMainForm* getForm() { return m_form; }

    private:
        SWMainForm *m_form;
        SWEnums* m_enums;

        QMetaEnum m_metaEnum;
        QString html;

        bool m_regExp;
        quint8 m_type;
};

namespace Converter
{
    quint64 getULongLong(QString value);
    qint64  getLongLong(QString value);
    quint32 getULong(QString value);
    qint32  getLong(QString value);
};

#endif // SWOBJECT_H
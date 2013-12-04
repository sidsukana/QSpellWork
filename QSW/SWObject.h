#ifndef SWOBJECT_H
#define SWOBJECT_H

#include <QMetaEnum>
#include <QScriptEngine>
#include <QScriptValue>
#include <QScriptValueList>

#include "MainForm.h"
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

class MainForm;
class SWObject : public QObject
{
    Q_OBJECT

    public:
        SWObject(MainForm *form);
        ~SWObject() {}

        void showInfo(const Spell::entry* spellInfo, quint8 num = 1);
        quint32 getParentSpellId(quint32 triggerId);
        void compare();
        QList<QEvent*> search();

        void appendSkillInfo(const Spell::entry* spellInfo, quint8 num);
        void appendCastTimeInfo(const Spell::entry* spellInfo, quint8 num);
        void appendDurationInfo(const Spell::entry* spellInfo, quint8 num);
        void appendRangeInfo(const Spell::entry* spellInfo, quint8 num);
        void appendSpellEffectInfo(const Spell::entry* spellInfo, quint8 num);
        void appendAuraInfo(const Spell::entry* spellInfo, quint8 index, quint8 num);
        void appendRadiusInfo(const Spell::entry* spellInfo, quint8 index, quint8 num);
        void appendTriggerInfo(const Spell::entry* spellInfo, quint8 index, quint8 num);
        void appendProcInfo(const Spell::entry *spellInfo, quint8 num);

        QString containAttributes(const Spell::entry* spellInfo, MaskType type, quint8 index = 0);
        QString getDescription(QString str, const Spell::entry* spellInfo);
        QString getSpellIconName(quint32 iconId);
        QImage getSpellIcon(quint32 iconId);

        QMetaEnum getMetaEnum() { return m_metaEnum; }
        void setMetaEnum(const char* enumName);

        quint8 getType() const { return m_type; }
        void setType(quint8 type) { m_type = type; }

        MainForm* getForm() { return m_form; }

    private:
        MainForm *m_form;
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
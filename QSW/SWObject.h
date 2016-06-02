#ifndef SWOBJECT_H
#define SWOBJECT_H

#include <QMetaEnum>
#include <QJSEngine>
#include <QJSValue>
#include <QJSValueList>

#include "MainForm.h"
#include "SWEnums.h"
#include "SWEvent.h"
#include "Defines.h"
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

        void showInfo(const Spell::entry* spellInfo, QSW::Pages pageId = QSW::PAGE_MAIN);
        QVariantList getParentSpells(quint32 triggerId);
        void compare();
        QList<QEvent*> search();

        QString containAttributes(const Spell::entry* spellInfo, MaskType type);
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

        bool m_regExp;
        quint8 m_type;

        QByteArray m_templateHtml;
        QByteArray m_styleCss;
};

namespace Converter
{
    quint64 getULongLong(QString value);
    qint64  getLongLong(QString value);
    quint32 getULong(QString value);
    qint32  getLong(QString value);
}

#endif // SWOBJECT_H

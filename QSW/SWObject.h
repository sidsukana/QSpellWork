#ifndef SWOBJECT_H
#define SWOBJECT_H

#include <QtCore/QMetaEnum>
#include <QtCore/QAbstractTableModel>
#include <QtGui/QSortFilterProxyModel>

#include "SWForm.h"
#include "SWEvent.h"
#include "TObject.h"
#include "DBC/DBCStores.h"
#include "SWDefines.h"

class SWForm;
class TObject;

class SpellListSortedModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    SpellListSortedModel(QObject *parent = 0);

    bool lessThan(const QModelIndex &left, const QModelIndex &right) const;
};

class SpellListModel : public QAbstractTableModel
{
    Q_OBJECT
    
    public:
        SpellListModel(QObject *parent = 0);

        int rowCount(const QModelIndex &parent) const;
        int columnCount(const QModelIndex &parent) const;
        QVariant data(const QModelIndex &index, int role) const;
        QVariant headerData(int section, Qt::Orientation orientation, int role) const;
        Qt::ItemFlags flags(const QModelIndex &index) const;
        void appendRecord(QStringList strl) { m_spellList << strl; }
        QList<QStringList> getSpellList() { return m_spellList; }
        void clear();

    private:
        QList<QStringList> m_spellList;
};

class SWObject
{
    public:
        SWObject(SWForm *form);
        ~SWObject();

        void showInfo(SpellEntry const* spellInfo, quint8 num = 0);
        quint32 getParentSpellId(quint32 triggerId);
        void compare();

        void appendSkillLine(SpellEntry const* spellInfo, quint8 num);
        void appendCastTimeLine(SpellEntry const* spellInfo, quint8 num);
        void appendDurationLine(SpellEntry const* spellInfo, quint8 num);
        void appendRangeInfo(SpellEntry const* spellInfo, quint8 num);
        void appendSpellEffectInfo(SpellEntry const* spellInfo, quint8 num);
        void appendAuraInfo(SpellEntry const* spellInfo, quint8 index, quint8 num);
        void appendRadiusInfo(SpellEntry const* spellInfo, quint8 index, quint8 num);
        void appendTriggerInfo(SpellEntry const* spellInfo, quint8 index, quint8 num);
        void appendProcInfo(SpellEntry const *spellInfo, quint8 num);

        QString containAttributes(SpellEntry const* spellInfo, AttrType attr, quint8 index = 0);
        QString getDescription(QString str, SpellEntry const *spellInfo);
        QString getSpellIconName(quint32 iconId);

        void threadBegin(quint8 id);
        void threadSet(quint8 id) { threadSemaphore[id] = true; }
        void threadUnset(quint8 id) { threadSemaphore[id] = false; }
        bool threadExist(quint8 id) { return threadSemaphore[id]; }

        QMetaEnum getMetaEnum() { return m_metaEnum; }
        void setMetaEnum(const char* enumName);

        bool isRegExp() const { return m_regExp; }
        void setRegExp(bool on) { m_regExp = on; }

        quint8 getType() const { return m_type; }
        void setType(quint8 type) { m_type = type; }

        SWForm* getForm() { return m_form; }

    private:
        SWForm *m_form;

        bool m_regExp;
        QString html;
        quint8 m_type;

        QMetaEnum m_metaEnum;
        bool threadSemaphore[MAX_THREAD];
};

#endif // SWOBJECT_H

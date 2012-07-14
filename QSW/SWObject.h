#ifndef SWOBJECT_H
#define SWOBJECT_H

#include <QtCore/QMetaEnum>
#include <QtCore/QBuffer>
#include <QtCore/QAbstractTableModel>
#include <QtGui/QSortFilterProxyModel>

#include "SWMainForm.h"
#include "SWEvent.h"
#include "DBC/DBCStores.h"
#include "SWDefines.h"

class SWMainForm;

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


Q_DECLARE_METATYPE(SpellListModel*);

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



class DNDModel : public QAbstractItemModel
{
    Q_OBJECT

    signals:
        void signalDataDropped(const QString &curData, const QString &newData);

    public:
        DNDModel(QObject *parent = 0);

        int rowCount(const QModelIndex &parent) const;
        int columnCount(const QModelIndex &parent) const;
        QVariant data(const QModelIndex &index, int role) const;
        QVariant headerData(int section, Qt::Orientation orientation, int role) const;
        Qt::ItemFlags flags(const QModelIndex &index) const;
        void append(QString str) { m_valueHash[str] = m_valueCount++; m_valueList << str;}
        void clear();
        QModelIndex index(int row, int column, const QModelIndex &parent /* = QModelIndex */) const;
        QModelIndex parent(const QModelIndex & index) const;

        void setViewerName(QString str) { m_viewerName = str; }
        QString getViewerName() const { return m_viewerName; }
        quint32 getDataRow(const QString &data) const { return m_valueHash[data]; }

        bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

        Qt::DropActions supportedDropActions() const
        {
            return Qt::CopyAction | Qt::MoveAction;
        }

        QStringList mimeTypes() const
        {
            QStringList types;
            types << "application/vnd.text.list";
            return types;
        }

        QMimeData *mimeData(const QModelIndexList &indexes) const
        {
            QMimeData *mimeData = new QMimeData();
            QByteArray encodedData;

            QDataStream stream(&encodedData, QIODevice::WriteOnly);

            foreach (QModelIndex index, indexes)
            {
                if (index.isValid())
                {
                    QString text = data(index, Qt::DisplayRole).toString();
                    stream << m_viewerName << text << ";";
                }
            }

            mimeData->setData("application/vnd.text.list", encodedData);
            return mimeData;
        }

        bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
        {
            if (action == Qt::IgnoreAction)
                return true;

            if (!data->hasFormat("application/vnd.text.list"))
                return false;

            if (column > 0)
                return false;

            int beginRow;

            if (row != -1)
                beginRow = row;
            else if (parent.isValid())
                beginRow = parent.row();
            else
                beginRow = rowCount(QModelIndex());

            QByteArray encodedData = data->data("application/vnd.text.list");
            QDataStream stream(&encodedData, QIODevice::ReadOnly);

            QString viewer, text;

            stream >> viewer >> text;

            QString curdata = this->data(index(beginRow, 0, QModelIndex()), Qt::DisplayRole).toString();

            if (viewer != m_viewerName)
            {
                emit signalDataDropped(curdata, text);
            }

            return true;
        }

    private:
        QHash<QString, quint32> m_valueHash;
        QStringList m_valueList;
        QString m_viewerName;
        quint32 m_valueCount;
};

#endif // SWOBJECT_H

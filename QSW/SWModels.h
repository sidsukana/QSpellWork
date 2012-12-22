#ifndef SW_MODELS_H
#define SW_MODELS_H

#include <QtCore/QStringList>
#include <QtCore/QAbstractTableModel>
#include <QtCore/QSortFilterProxyModel>
#include <QtWidgets/QItemDelegate>

#include "SWMainForm.h"

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

class RelationDelegate : public QItemDelegate
{
    public:
        RelationDelegate(QObject* parent = NULL) : QItemDelegate(parent) {}
        QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
        void setEditorData(QWidget *editor, const QModelIndex &index) const;
        void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
};

class SpellDelegate : public QItemDelegate
{
    public:
        SpellDelegate(QObject* parent = NULL) : QItemDelegate(parent)
        {
            m_form = qobject_cast<SWMainForm*>(parent);
        }
        QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
        void setEditorData(QWidget *editor, const QModelIndex &index) const;
        void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    private:
        SWMainForm* m_form;
};

class RelationItem
{
    public:
        RelationItem();
        QString dbcField;
        QString sqlField;
        QString index;
};

typedef QList<RelationItem*> RelationList;

class RelationModel : public QAbstractTableModel
{
    Q_OBJECT

    public:
        RelationModel(QObject* parent = NULL);

        int rowCount(const QModelIndex &parent) const;
        int columnCount(const QModelIndex &parent) const;
        QVariant data(const QModelIndex &index, int role) const;
        bool setData(const QModelIndex &index, const QVariant &value, int role);
        QVariant headerData(int section, Qt::Orientation orientation, int role) const;
        Qt::ItemFlags flags(const QModelIndex &index) const;
        void appendRelation(RelationItem* relation) { m_relations << relation; }
        void appendDbcField(QString field) { m_dbcFields << field; }
        void clear();
        void autoRelate();
        void resetRelate();

        RelationList getRelations() const { return m_relations; }

    private:
        RelationList m_relations;
        QStringList m_dbcFields;
        QStringList m_indexes;
};

#endif
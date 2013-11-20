#ifndef SW_MODELS_H
#define SW_MODELS_H

#include <QStringList>
#include <QAbstractTableModel>
#include <QSortFilterProxyModel>

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

#endif
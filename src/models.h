#ifndef MODELS_H
#define MODELS_H

#include <QStringList>
#include <QAbstractTableModel>
#include <QSortFilterProxyModel>

class SpellListSortedModel : public QSortFilterProxyModel
{
    Q_OBJECT

    public:
        SpellListSortedModel(QObject *parent = nullptr);

        bool lessThan(const QModelIndex &left, const QModelIndex &right) const;
};

class SpellListModel : public QAbstractTableModel
{
    Q_OBJECT

    public:
        SpellListModel(QObject *parent = nullptr);

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

typedef QPair<qint32, QString> ComboBoxPair;
typedef QHash<qint32, ComboBoxPair> ComboBoxHash;

class ComboBoxModel : public QAbstractItemModel
{
    Q_OBJECT

    public:
        ComboBoxModel(QObject *parent = nullptr);

        QModelIndex parent(const QModelIndex &index) const;
        QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
        int rowCount(const QModelIndex &parent) const;
        int columnCount(const QModelIndex &parent) const;
        QVariant data(const QModelIndex &index, int role) const;
        QVariant headerData(int section, Qt::Orientation orientation, int role) const;
        Qt::ItemFlags flags(const QModelIndex &index) const;
        void setItems(ComboBoxHash items);
        ComboBoxHash getItems() { return m_items; }
        void clear();

    private:
        ComboBoxHash m_items;
};

Q_DECLARE_METATYPE(SpellListModel*)

#endif

#include <QFontComboBox>
#include <QLineEdit>
#include <QMetaEnum>

#include "models.h"
#include "Alphanum.h"

SpellListSortedModel::SpellListSortedModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

bool SpellListSortedModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    QVariant leftData = sourceModel()->data(left);
    QVariant rightData = sourceModel()->data(right);

    if (compare(leftData.toString(), rightData.toString()) < 0)
        return true;

    return false;
}

SpellListModel::SpellListModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    m_spellList.clear();
}

void SpellListModel::clear()
{
    beginResetModel();
    m_spellList.clear();
    endResetModel();
}

int SpellListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_spellList.size();
}

int SpellListModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}

QVariant SpellListModel::data(const QModelIndex &index, int role) const
{
    if (m_spellList.isEmpty())
        return QVariant();

    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_spellList.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole)
        return m_spellList.at(index.row()).at(index.column());

    return QVariant();
}

QVariant SpellListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
    {
        switch (section)
        {
        case 0: return QString("ID");
        case 1: return QString("Name");
        }
    }

    return QVariant();
}

Qt::ItemFlags SpellListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index);
}

ComboBoxModel::ComboBoxModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    m_items.clear();
}

void ComboBoxModel::clear()
{
    beginResetModel();
    m_items.clear();
    endResetModel();
}

QModelIndex ComboBoxModel::parent(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return QModelIndex();
}

QModelIndex ComboBoxModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(column);
    Q_UNUSED(parent);
    return createIndex(row, 0);
}

int ComboBoxModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_items.size();
}

int ComboBoxModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant ComboBoxModel::data(const QModelIndex &index, int role) const
{
    if (m_items.isEmpty())
        return QVariant();

    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_items.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole)
        return m_items[index.row()].second;

    if (role == Qt::UserRole)
        return m_items[index.row()].first;

    return QVariant();
}

void ComboBoxModel::setItems(ComboBoxHash items)
{
    m_items = items;
    emit dataChanged(createIndex(0, 0), createIndex(items.size(), 0));
}

QVariant ComboBoxModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section);
    Q_UNUSED(orientation);
    Q_UNUSED(role);
    return QVariant();
}

Qt::ItemFlags ComboBoxModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index);
}

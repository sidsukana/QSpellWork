#include "SWModels.h"
#include "Alphanum.h"

#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QLineEdit>

#include <QtCore/QMetaEnum>

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

// Relation Model

RelationItem::RelationItem()
{
    dbcField = "";
    sqlField = "";
    index = "";
}

QWidget *RelationDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    switch (index.column())
    {
        case 1:
        case 2:
        {
            QFontComboBox* box = new QFontComboBox(parent);
            box->clear();
            box->addItems(index.model()->data(index, Qt::EditRole).toStringList());
            return box;
        }
        default:
        {
            QLineEdit* editor = new QLineEdit(parent);
            QString currentText = index.model()->data(index, Qt::DisplayRole).toString();
            editor->setText(currentText);
            return editor;
        }
    }
}

void RelationDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::DisplayRole).toString();

    QFontComboBox *box = static_cast<QFontComboBox*>(editor);
    box->setItemText(box->currentIndex(), value);
}

void RelationDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    switch (index.column())
    {
        case 1:
        case 2:
        {
            if (QFontComboBox* box = qobject_cast<QFontComboBox*>(editor))
                model->setData(index, box->itemText(box->currentIndex()));
            break;
        }
        default: break;
    }
}

QWidget *SpellDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    RelationList relationList = ((RelationModel*)m_form->fieldsView->model())->getRelations();
    if (RelationItem* item = relationList.at(index.column()))
    {
        QStringList keys;
        QMetaEnum metaEnum;

        if (item->dbcField == "Effect")
            metaEnum = Enums::staticMetaObject.enumerator(Enums::staticMetaObject.indexOfEnumerator("Effects"));
        else if (item->dbcField == "EffectApplyAuraName")
            metaEnum = Enums::staticMetaObject.enumerator(Enums::staticMetaObject.indexOfEnumerator("AuraType"));

        if (metaEnum.isValid())
        {
            quint32 count = metaEnum.keyCount();
            for (quint32 i = 0; i < count; ++i)
                keys << metaEnum.key(i);

            QFontComboBox* box = new QFontComboBox(parent);
            box->clear();
            box->addItems(keys);
            return box;
        }
    }

    QLineEdit* editor = new QLineEdit(parent);
    QString currentText = index.model()->data(index, Qt::DisplayRole).toString();
    editor->setText(currentText);
    return editor;
}

void SpellDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString name = editor->metaObject()->className();
    if (name == "QFontComboBox")
    {
        QFontComboBox *box = static_cast<QFontComboBox*>(editor);
        box->setCurrentIndex(index.model()->data(index, Qt::DisplayRole).toUInt());
        return;
    }

    QLineEdit* lineEdit = static_cast<QLineEdit*>(editor);
    lineEdit->setText(index.model()->data(index, Qt::DisplayRole).toString());
}

void SpellDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QString name = editor->metaObject()->className();
    if (name == "QFontComboBox")
    {
        RelationList relationList = ((RelationModel*)m_form->fieldsView->model())->getRelations();
        if (RelationItem* item = relationList.at(index.column()))
        {
            QFontComboBox* box = qobject_cast<QFontComboBox*>(editor);
            if (!box->currentText().toInt())
            {
                QMetaEnum metaEnum;

                if (item->dbcField == "Effect")
                    metaEnum = Enums::staticMetaObject.enumerator(Enums::staticMetaObject.indexOfEnumerator("Effects"));
                else if (item->dbcField == "EffectApplyAuraName")
                    metaEnum = Enums::staticMetaObject.enumerator(Enums::staticMetaObject.indexOfEnumerator("AuraType"));

                if (metaEnum.isValid())
                    model->setData(index, metaEnum.keyToValue(qPrintable(box->currentText())));
                else
                    model->setData(index, box->currentText().toInt());
            }
            else
                model->setData(index, box->currentText().toInt());

            return;
        }
    }

    QLineEdit* lineEdit = static_cast<QLineEdit*>(editor);
    model->setData(index, lineEdit->text());
}

RelationModel::RelationModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    m_relations.clear();
    m_indexes.clear();
    m_indexes << "";
    for (quint8 i = 0; i < 10; ++i)
        m_indexes << QString::number(i);
}

void RelationModel::clear()
{
    beginResetModel();
    m_relations.clear();
    m_indexes.clear();
    endResetModel();
}

int RelationModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_relations.size();
}

int RelationModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 3;
}

QVariant RelationModel::data(const QModelIndex &index, int role) const
{
    if (m_relations.isEmpty())
        return QVariant();

    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_relations.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        switch (index.column())
        {
            case 0: return m_relations.at(index.row())->sqlField;
            case 1: return m_relations.at(index.row())->dbcField;
            case 2: return m_relations.at(index.row())->index;
        }
    }
    else if (role == Qt::EditRole)
    {
        if (index.column() == 1)
            return m_dbcFields;
        else if (index.column() == 2)
            return m_indexes;
    }

    return QVariant();
}

bool RelationModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        if (index.column() == 1)
            m_relations.at(index.row())->dbcField = value.toString();
        else if (index.column() == 2)
            m_relations.at(index.row())->index = value.toString();

        return true;
    }
    return false;
}

QVariant RelationModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
    {
        switch (section)
        {
            case 0: return QString("SQL Fields");
            case 1: return QString("DBC Fields");
            case 2: return QString("Array Index");
        }
    }
    else if (orientation == Qt::Vertical)
        return section + 1;

    return QVariant();
}

Qt::ItemFlags RelationModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    switch (index.column())
    {
        case 1:
        case 2:
            return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
        default: return QAbstractTableModel::flags(index);
    }

    return QAbstractTableModel::flags(index);
}

void RelationModel::autoRelate()
{
    for (RelationList::iterator itr = m_relations.begin(); itr != m_relations.end(); ++itr)
        for (QStringList::iterator itr2 = m_dbcFields.begin(); itr2 != m_dbcFields.end(); ++itr2)
            if ((*itr2).contains((*itr)->sqlField, Qt::CaseInsensitive))
                (*itr)->dbcField = (*itr)->sqlField;
}

void RelationModel::resetRelate()
{
    for (RelationList::iterator itr = m_relations.begin(); itr != m_relations.end(); ++itr)\
    {
        (*itr)->dbcField = "";
        (*itr)->index = "";
    }
}
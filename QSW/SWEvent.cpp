#include "SWEvent.h"

SendSpell::SendSpell(SpellEntry const* obj)
    : QEvent(QEvent::Type(SendSpell::TypeId)), m_obj(obj)
{
}

SendSpell::~SendSpell()
{
}

SendCompareSpell::SendCompareSpell(SpellEntry const* obj, quint8 num)
    : QEvent(QEvent::Type(SendCompareSpell::TypeId)), m_obj(obj), m_num(num)
{
}

SendCompareSpell::~SendCompareSpell()
{
}

SendModel::SendModel(SpellListModel* obj)
    : QEvent(QEvent::Type(SendModel::TypeId)), m_obj(obj)
{
}

SendModel::~SendModel()
{
}






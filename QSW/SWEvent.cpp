#include "SWEvent.h"

SendSpell::SendSpell(SWForm *form, SpellEntry const* obj)
    : QEvent(QEvent::Type(SendSpell::TypeId)), m_obj(obj), m_form(form)
{
}

SendSpell::~SendSpell()
{
}

SendModel::SendModel(SWForm *form, QStandardItemModel* obj)
    : QEvent(QEvent::Type(SendModel::TypeId)), m_obj(obj), m_form(form)
{
}

SendModel::~SendModel()
{
}




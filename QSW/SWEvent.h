#ifndef EVENT_H
#define EVENT_H

#include <QtCore/QEvent>
#include <SWForm.h>
#include "QtGui/QStandardItemModel"
#include "DBC/DBCStores.h"

class SWForm;

class SendSpell : public QEvent
{
    public:
        enum { TypeId = QEvent::User + 1 };
        SendSpell(SWForm *form, SpellEntry const* obj);
        ~SendSpell();

        SpellEntry const* GetObject() { return m_obj; }

    private:
        SWForm *m_form;
        SpellEntry const* m_obj;
};

class SendModel : public QEvent
{
    public:
        enum { TypeId = QEvent::User + 2 };
        SendModel(SWForm *form, QStandardItemModel* obj);
        ~SendModel();

        QStandardItemModel* GetObject() { return m_obj; }

    private:
        SWForm *m_form;
        QStandardItemModel* m_obj;
};

#endif // EVENTMGR_H

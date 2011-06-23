#ifndef EVENT_H
#define EVENT_H

#include <QtCore/QEvent>
#include "SWForm.h"
#include "DBC/DBCStores.h"

class SWForm;
class SpellListModel;

class SendSpell : public QEvent
{
    public:
        enum { TypeId = QEvent::User + 1 };
        SendSpell(SpellEntry const* obj);
        ~SendSpell();

        SpellEntry const* getObject() { return m_obj; }

    private:
        SpellEntry const* m_obj;
};

class SendModel : public QEvent
{
    public:
        enum { TypeId = QEvent::User + 2 };
        SendModel(SpellListModel* obj);
        ~SendModel();

        SpellListModel* getObject() { return m_obj; }

    private:
        SpellListModel* m_obj;
};

class SendCompareSpell : public QEvent
{
    public:
        enum { TypeId = QEvent::User + 3 };
        SendCompareSpell(SpellEntry const* obj, quint8 num);
        ~SendCompareSpell();

        SpellEntry const* getObject() { return m_obj; }
        quint8 getNum() { return m_num; }

    private:
        SpellEntry const* m_obj;
        quint8 m_num;
};

#endif // EVENTMGR_H

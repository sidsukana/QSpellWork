/*
 * Copyright (C) 2010 Anathema Engine project <http://valkyrie-wow.ru/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 */

#include "EventProcessor.h"

EventProcessor::EventProcessor()
{
    m_time = 0;
    m_aborting = false;
}

EventProcessor::~EventProcessor()
{
    KillAllEvents(true);
}

void EventProcessor::Update(quint32 p_time)
{
    // update time
    m_time += p_time;

    // main event loop
    EventList::iterator i;
    while (((i = m_events.begin()) != m_events.end()) && i->first <= m_time)
    {
        // get and remove event from queue
        BasicEvent* Event = i->second;
        m_events.erase(i);

        if (!Event->to_Abort)
        {
            if (Event->Execute(m_time, p_time))
            {
                // completely destroy event if it is not re-added
                delete Event;
            }
        }
        else
        {
            Event->Abort(m_time);
            delete Event;
        }
    }
}

void EventProcessor::KillAllEvents(bool force)
{
    // prevent event insertions
    m_aborting = true;

    // first, abort all existing events
    for (EventList::iterator i = m_events.begin(); i != m_events.end();)
    {
        EventList::iterator i_old = i;
        ++i;

        i_old->second->to_Abort = true;
        i_old->second->Abort(m_time);
        if (force || i_old->second->IsDeletable())
        {
            delete i_old->second;

            if (!force)                                      // need per-element cleanup
                m_events.erase (i_old);
        }
    }

    // fast clear event list (in force case)
    if (force)
        m_events.clear();
}

void EventProcessor::AddEvent(BasicEvent* Event, quint64 e_time, bool set_addtime)
{
    if (set_addtime)
        Event->m_addTime = m_time;

    Event->m_execTime = e_time;
    m_events.insert(std::pair<quint64, BasicEvent*>(e_time, Event));
}

quint64 EventProcessor::CalculateTime(quint64 t_offset)
{
    return m_time + t_offset;
}

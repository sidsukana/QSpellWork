/*
 * Copyright (C) 2010 Anathema Engine project <http://valkyrie-wow.ru/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 */

#ifndef __EVENTPROCESSOR_H
#define __EVENTPROCESSOR_H

#include "Platform/Define.h"
#include <QtCore/QtGlobal>

#include <map>

// Note. All times are in milliseconds here.

class BasicEvent
{
    public:

        BasicEvent()
            : to_Abort(false)
        {
        }

        virtual ~BasicEvent()                               // override destructor to perform some actions on event removal
        {
        };

        // this method executes when the event is triggered
        // return false if event does not want to be deleted
        // e_time is execution time, p_time is update interval
        virtual bool Execute(quint64 /*e_time*/, quint32 /*p_time*/) { return true; }

        virtual bool IsDeletable() const { return true; }   // this event can be safely deleted

        virtual void Abort(quint64 /*e_time*/) {}            // this method executes when the event is aborted

        bool to_Abort;                                      // set by externals when the event is aborted, aborted events don't execute
        // and get Abort call when deleted

        // these can be used for time offset control
        quint64 m_addTime;                                   // time when the event was added to queue, filled by event handler
        quint64 m_execTime;                                  // planned time of next execution, filled by event handler
};

typedef std::multimap<quint64, BasicEvent*> EventList;

class EventProcessor
{
    public:

        EventProcessor();
        ~EventProcessor();

        void Update(quint32 p_time);
        void KillAllEvents(bool force);
        void AddEvent(BasicEvent* Event, quint64 e_time, bool set_addtime = true);
        quint64 CalculateTime(quint64 t_offset);

    protected:

        quint64 m_time;
        EventList m_events;
        bool m_aborting;
};

#endif

/*
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 */

#ifndef QSW_OBJECTLIFETIME_H
#define QSW_OBJECTLIFETIME_H

#include <stdexcept>
#include "Platform/Define.h"

typedef void (* Destroyer)(void);

namespace QSW
{
    void QSW_DLL_SPEC at_exit(void (*func)());

    template<class T>
    class QSW_DLL_DECL ObjectLifeTime
    {
        public:

            static void ScheduleCall(void (*destroyer)())
            {
                at_exit(destroyer);
            }

            DECLSPEC_NORETURN static void OnDeadReference() ATTR_NORETURN;
    };

    template <class T>
    void ObjectLifeTime<T>::OnDeadReference()           // We don't handle Dead Reference for now
    {
        throw std::runtime_error("Dead Reference");
    }
}

#endif

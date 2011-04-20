/*
 * Copyright (C) 2010 QSW Engine project <http://valkyrie-wow.ru/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 */

#ifndef QSW_SINGLETONIMPL_H
#define QSW_SINGLETONIMPL_H

#include "Policies/Singleton.h"

// avoid the using namespace here cuz
// its a .h file afterall

template
<
typename T,
class ThreadingModel,
class CreatePolicy,
class LifeTimePolicy
>
T& QSW::Singleton<T, ThreadingModel, CreatePolicy, LifeTimePolicy>::Instance()
{
    if (!si_instance)
    {
        // double-checked Locking pattern
        Guard();

        if (!si_instance)
        {
            if (si_destroyed)
            {
                si_destroyed = false;
                LifeTimePolicy::OnDeadReference();
            }

            si_instance = CreatePolicy::Create();
            LifeTimePolicy::ScheduleCall(&DestroySingleton);
        }
    }

    return *si_instance;
}

template
<
typename T,
class ThreadingModel,
class CreatePolicy,
class LifeTimePolicy
>
void QSW::Singleton<T, ThreadingModel, CreatePolicy, LifeTimePolicy>::DestroySingleton()
{
    CreatePolicy::Destroy(si_instance);
    si_instance = NULL;
    si_destroyed = true;
}

#define INSTANTIATE_SINGLETON_1(TYPE) \
    template class QSW_DLL_DECL QSW::Singleton<TYPE, QSW::SingleThreaded<TYPE>, QSW::OperatorNew<TYPE>, QSW::ObjectLifeTime<TYPE> >; \
    template<> TYPE* QSW::Singleton<TYPE, QSW::SingleThreaded<TYPE>, QSW::OperatorNew<TYPE>, QSW::ObjectLifeTime<TYPE> >::si_instance = 0; \
    template<> bool QSW::Singleton<TYPE, QSW::SingleThreaded<TYPE>, QSW::OperatorNew<TYPE>, QSW::ObjectLifeTime<TYPE> >::si_destroyed = false

#define INSTANTIATE_SINGLETON_2(TYPE, THREADINGMODEL) \
    template class QSW_DLL_DECL QSW::Singleton<TYPE, THREADINGMODEL, QSW::OperatorNew<TYPE>, QSW::ObjectLifeTime<TYPE> >; \
    template<> TYPE* QSW::Singleton<TYPE, THREADINGMODEL, QSW::OperatorNew<TYPE>, QSW::ObjectLifeTime<TYPE> >::si_instance = 0; \
    template<> bool QSW::Singleton<TYPE, THREADINGMODEL, QSW::OperatorNew<TYPE>, QSW::ObjectLifeTime<TYPE> >::si_destroyed = false

#define INSTANTIATE_SINGLETON_3(TYPE, THREADINGMODEL, CREATIONPOLICY ) \
    template class QSW_DLL_DECL QSW::Singleton<TYPE, THREADINGMODEL, CREATIONPOLICY, QSW::ObjectLifeTime<TYPE> >; \
    template<> TYPE* QSW::Singleton<TYPE, THREADINGMODEL, CREATIONPOLICY, QSW::ObjectLifeTime<TYPE> >::si_instance = 0; \
    template<> bool QSW::Singleton<TYPE, THREADINGMODEL, CREATIONPOLICY, QSW::ObjectLifeType<TYPE> >::si_destroyed = false

#define INSTANTIATE_SINGLETON_4(TYPE, THREADINGMODEL, CREATIONPOLICY, OBJECTLIFETIME) \
    template class QSW_DLL_DECL QSW::Singleton<TYPE, THREADINGMODEL, CREATIONPOLICY, OBJECTLIFETIME >; \
    template<> TYPE* QSW::Singleton<TYPE, THREADINGMODEL, CREATIONPOLICY, OBJECTLIFETIME >::si_instance = 0; \
    template<> bool QSW::Singleton<TYPE, THREADINGMODEL, CREATIONPOLICY, OBJECTLIFETIME >::si_destroyed = false

#endif

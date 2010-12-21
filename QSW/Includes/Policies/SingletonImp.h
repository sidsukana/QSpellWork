/*
 * Copyright (C) 2010 Anathema Engine project <http://valkyrie-wow.ru/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 */

#ifndef ANATHEMA_SINGLETONIMPL_H
#define ANATHEMA_SINGLETONIMPL_H

#include "Singleton.h"

// avoid the using namespace here cuz
// its a .h file afterall

template
<
typename T,
class ThreadingModel,
class CreatePolicy,
class LifeTimePolicy
>
T& ANATHEMA::Singleton<T, ThreadingModel, CreatePolicy, LifeTimePolicy>::Instance()
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
void ANATHEMA::Singleton<T, ThreadingModel, CreatePolicy, LifeTimePolicy>::DestroySingleton()
{
    CreatePolicy::Destroy(si_instance);
    si_instance = NULL;
    si_destroyed = true;
}

#define INSTANTIATE_SINGLETON_1(TYPE) \
    template class ANATHEMA_DLL_DECL ANATHEMA::Singleton<TYPE, ANATHEMA::SingleThreaded<TYPE>, ANATHEMA::OperatorNew<TYPE>, ANATHEMA::ObjectLifeTime<TYPE> >; \
    template<> TYPE* ANATHEMA::Singleton<TYPE, ANATHEMA::SingleThreaded<TYPE>, ANATHEMA::OperatorNew<TYPE>, ANATHEMA::ObjectLifeTime<TYPE> >::si_instance = 0; \
    template<> bool ANATHEMA::Singleton<TYPE, ANATHEMA::SingleThreaded<TYPE>, ANATHEMA::OperatorNew<TYPE>, ANATHEMA::ObjectLifeTime<TYPE> >::si_destroyed = false

#define INSTANTIATE_SINGLETON_2(TYPE, THREADINGMODEL) \
    template class ANATHEMA_DLL_DECL ANATHEMA::Singleton<TYPE, THREADINGMODEL, ANATHEMA::OperatorNew<TYPE>, ANATHEMA::ObjectLifeTime<TYPE> >; \
    template<> TYPE* ANATHEMA::Singleton<TYPE, THREADINGMODEL, ANATHEMA::OperatorNew<TYPE>, ANATHEMA::ObjectLifeTime<TYPE> >::si_instance = 0; \
    template<> bool ANATHEMA::Singleton<TYPE, THREADINGMODEL, ANATHEMA::OperatorNew<TYPE>, ANATHEMA::ObjectLifeTime<TYPE> >::si_destroyed = false

#define INSTANTIATE_SINGLETON_3(TYPE, THREADINGMODEL, CREATIONPOLICY ) \
    template class ANATHEMA_DLL_DECL ANATHEMA::Singleton<TYPE, THREADINGMODEL, CREATIONPOLICY, ANATHEMA::ObjectLifeTime<TYPE> >; \
    template<> TYPE* ANATHEMA::Singleton<TYPE, THREADINGMODEL, CREATIONPOLICY, ANATHEMA::ObjectLifeTime<TYPE> >::si_instance = 0; \
    template<> bool ANATHEMA::Singleton<TYPE, THREADINGMODEL, CREATIONPOLICY, ANATHEMA::ObjectLifeType<TYPE> >::si_destroyed = false

#define INSTANTIATE_SINGLETON_4(TYPE, THREADINGMODEL, CREATIONPOLICY, OBJECTLIFETIME) \
    template class ANATHEMA_DLL_DECL ANATHEMA::Singleton<TYPE, THREADINGMODEL, CREATIONPOLICY, OBJECTLIFETIME >; \
    template<> TYPE* ANATHEMA::Singleton<TYPE, THREADINGMODEL, CREATIONPOLICY, OBJECTLIFETIME >::si_instance = 0; \
    template<> bool ANATHEMA::Singleton<TYPE, THREADINGMODEL, CREATIONPOLICY, OBJECTLIFETIME >::si_destroyed = false

#endif

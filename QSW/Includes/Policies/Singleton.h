/*
 * Copyright (C) 2010 Anathema Engine project <http://valkyrie-wow.ru/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 */

#ifndef ANATHEMA_SINGLETON_H
#define ANATHEMA_SINGLETON_H

/**
 * @brief class Singleton
 */

#include "CreationPolicy.h"
#include "ThreadingModel.h"
#include "ObjectLifeTime.h"

namespace ANATHEMA
{
    template
    <
    typename T,
    class ThreadingModel = ANATHEMA::SingleThreaded<T>,
    class CreatePolicy = ANATHEMA::OperatorNew<T>,
    class LifeTimePolicy = ANATHEMA::ObjectLifeTime<T>
    >
    class ANATHEMA_DLL_DECL Singleton
    {
        public:

            static T& Instance();

        protected:

            Singleton()
            {
            }

        private:

            // Prohibited actions...this does not prevent hijacking.
            Singleton(const Singleton&);
            Singleton& operator=(const Singleton&);

            // Singleton Helpers
            static void DestroySingleton();

            // data structure
            typedef typename ThreadingModel::Lock Guard;
            static T *si_instance;
            static bool si_destroyed;
    };
}

#endif

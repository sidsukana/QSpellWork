/*
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 */

#ifndef QSW_THREADINGMODEL_H
#define QSW_THREADINGMODEL_H

/**
 * @class ThreadingModel<T>
 *
 */

#include "Platform/Define.h"

namespace QSW
{
    template<typename MUTEX>
    class QSW_DLL_DECL GeneralLock
    {
        public:

            GeneralLock(MUTEX &m)
                : i_mutex(m)
            {
                i_mutex.acquire();
            }

            ~GeneralLock()
            {
                i_mutex.release();
            }

        private:

            GeneralLock(const GeneralLock &);
            GeneralLock& operator=(const GeneralLock &);
            MUTEX &i_mutex;
    };

    template<class T>
    class QSW_DLL_DECL SingleThreaded
    {
        public:

            struct Lock                                     // empty object
            {
                Lock()
                {
                }
                Lock(const T&)
                {
                }

                Lock(const SingleThreaded<T>&)              // for single threaded we ignore this
                {
                }
            };
    };

    template<class T, class MUTEX>
    class QSW_DLL_DECL ObjectLevelLockable
    {
        public:

            ObjectLevelLockable()
                : i_mtx()
            {
            }

            friend class Lock;

            class Lock
            {
                public:

                    Lock(ObjectLevelLockable<T, MUTEX> &host)
                        : i_lock(host.i_mtx)
                    {
                    }

                private:

                    GeneralLock<MUTEX> i_lock;
            };

        private:

            // prevent the compiler creating a copy construct
            ObjectLevelLockable(const ObjectLevelLockable<T, MUTEX>&);
            ObjectLevelLockable<T, MUTEX>& operator=(const ObjectLevelLockable<T, MUTEX>&);

            MUTEX i_mtx;
    };

    template<class T, class MUTEX>
    class QSW_DLL_DECL ClassLevelLockable
    {
        public:

            ClassLevelLockable()
            {
            }

            friend class Lock;

            class Lock
            {
                public:

                    Lock(T& /*host*/)
                    {
                        ClassLevelLockable<T, MUTEX>::si_mtx.acquire();
                    }

                    Lock(ClassLevelLockable<T, MUTEX> &)
                    {
                        ClassLevelLockable<T, MUTEX>::si_mtx.acquire();
                    }

                    Lock()
                    {
                        ClassLevelLockable<T, MUTEX>::si_mtx.acquire();
                    }

                    ~Lock()
                    {
                        ClassLevelLockable<T, MUTEX>::si_mtx.release();
                    }
            };

        private:

            static MUTEX si_mtx;
    };

}

template<class T, class MUTEX> MUTEX QSW::ClassLevelLockable<T, MUTEX>::si_mtx;

#define INSTANTIATE_CLASS_MUTEX(CTYPE, MUTEX) \
    template class QSW_DLL_DECL QSW::ClassLevelLockable<CTYPE, MUTEX>

#endif

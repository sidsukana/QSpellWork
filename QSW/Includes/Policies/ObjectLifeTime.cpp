/*
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 */

#include <cstdlib>
#include "ObjectLifeTime.h"

namespace ANATHEMA
{
    extern "C" void external_wrapper(void *p)
    {
        std::atexit((void (*)())p);
    }

    void QSW_DLL_SPEC at_exit(void (*func)())
    {
        external_wrapper((void*)func);
    }
}

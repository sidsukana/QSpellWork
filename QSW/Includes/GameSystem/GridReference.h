/*
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 */

#ifndef _GRIDREFERENCE_H
#define _GRIDREFERENCE_H

#include "Utilities/LinkedReference/Reference.h"

template<class OBJECT> class GridRefManager;

template<class OBJECT>
class QSW_DLL_SPEC GridReference : public Reference<GridRefManager<OBJECT>, OBJECT>
{
    protected:

        void targetObjectBuildLink()
        {
            // called from link()
            this->getTarget()->insertFirst(this);
            this->getTarget()->incSize();
        }

        void targetObjectDestroyLink()
        {
            // called from unlink()
            if (this->isValid())
                this->getTarget()->decSize();
        }

        void sourceObjectDestroyLink()
        {
            // called from invalidate()
            this->getTarget()->decSize();
        }

    public:

        GridReference()
            : Reference<GridRefManager<OBJECT>, OBJECT>()
        {
        }

        ~GridReference()
        {
            this->unlink();
        }

        GridReference *next()
        {
            return (GridReference*)Reference<GridRefManager<OBJECT>, OBJECT>::next();
        }
};

#endif

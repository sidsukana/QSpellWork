/*
 * Copyright (C) 2010 Anathema Engine project <http://valkyrie-wow.ru/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 */

#ifndef _REFMANAGER_H
#define _REFMANAGER_H

//=====================================================

#include "Utilities/LinkedList.h"
#include "Utilities/LinkedReference/Reference.h"

template <class TO, class FROM>
class RefManager : public LinkedListHead
{
    public:

        typedef LinkedListHead::Iterator<Reference<TO, FROM> > iterator;
        RefManager() {}
        virtual ~RefManager() { clearReferences(); }

        Reference<TO, FROM>*       getFirst()       { return ((Reference<TO, FROM>      *) LinkedListHead::getFirst()); }
        Reference<TO, FROM> const* getFirst() const { return ((Reference<TO, FROM> const*) LinkedListHead::getFirst()); }
        Reference<TO, FROM>*       getLast()       { return ((Reference<TO, FROM>      *) LinkedListHead::getLast()); }
        Reference<TO, FROM> const* getLast() const { return ((Reference<TO, FROM> const*) LinkedListHead::getLast()); }

        iterator begin() { return iterator(getFirst()); }
        iterator end() { return iterator(NULL); }
        iterator rbegin() { return iterator(getLast()); }
        iterator rend() { return iterator(NULL); }

        void clearReferences()
        {
            LinkedListElement* ref;
            while ((ref = getFirst()) != NULL)
            {
                ((Reference<TO, FROM>*) ref)->invalidate();
                ref->delink();                              // the delink might be already done by invalidate(), but doing it here again does not hurt and insures an empty list
            }
        }
};

//=====================================================

#endif

/*
 * Copyright (C) 2010 Anathema Engine project <http://valkyrie-wow.ru/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 */

#ifndef ANATHEMA_TYPECONTAINER_H
#define ANATHEMA_TYPECONTAINER_H

/*
 * Here, you'll find a series of containers that allow you to hold multiple
 * types of object at the same time.
 */

#include <cassert>
#include <map>
#include <vector>
#include "Platform/Define.h"
#include "Utilities/TypeList.h"
#include "Utilities/UnorderedMapSet.h"
#include "GameSystem/GridRefManager.h"

template<class OBJECT, class KEY_TYPE>
struct ContainerUnorderedMap
{
    UNORDERED_MAP<KEY_TYPE, OBJECT*> _element;
};

template<class KEY_TYPE>
struct ContainerUnorderedMap<TypeNull, KEY_TYPE>
{
};

template<class H, class T, class KEY_TYPE>
struct ContainerUnorderedMap< TypeList<H, T>, KEY_TYPE >
{
    ContainerUnorderedMap<H, KEY_TYPE> _elements;
    ContainerUnorderedMap<T, KEY_TYPE> _TailElements;
};

template<class OBJECT_TYPES, class KEY_TYPE = OBJECT_HANDLE>
class TypeUnorderedMapContainer
{
    public:

        template<class SPECIFIC_TYPE>
        bool insert(KEY_TYPE handle, SPECIFIC_TYPE* obj)
        {
            return TypeUnorderedMapContainer::insert(i_elements, handle, obj);
        }

        template<class SPECIFIC_TYPE>
        bool erase(KEY_TYPE handle, SPECIFIC_TYPE* /*obj*/)
        {
            return TypeUnorderedMapContainer::erase(i_elements, handle, (SPECIFIC_TYPE*)NULL);
        }

        template<class SPECIFIC_TYPE>
        SPECIFIC_TYPE* find(KEY_TYPE hdl, SPECIFIC_TYPE* /*obj*/)
        {
            return TypeUnorderedMapContainer::find(i_elements, hdl, (SPECIFIC_TYPE*)NULL);
        }

    private:

        ContainerUnorderedMap<OBJECT_TYPES, KEY_TYPE> i_elements;

        // Helpers
        // Insert helpers
        template<class SPECIFIC_TYPE>
        static bool insert(ContainerUnorderedMap<SPECIFIC_TYPE, KEY_TYPE>& elements, KEY_TYPE handle, SPECIFIC_TYPE* obj)
        {
            typename UNORDERED_MAP<KEY_TYPE, SPECIFIC_TYPE*>::iterator i = elements._element.find(handle);
            if (i == elements._element.end())
            {
                elements._element[handle] = obj;
                return true;
            }
            else
            {
                assert(i->second == obj && "Object with certain key already in but objects are different!");
                return false;
            }
        }

        template<class SPECIFIC_TYPE>
        static bool insert(ContainerUnorderedMap<TypeNull, KEY_TYPE>& /*elements*/, KEY_TYPE /*handle*/, SPECIFIC_TYPE* /*obj*/)
        {
            return false;
        }

        template<class SPECIFIC_TYPE, class T>
        static bool insert(ContainerUnorderedMap<T, KEY_TYPE>& /*elements*/, KEY_TYPE /*handle*/, SPECIFIC_TYPE* /*obj*/)
        {
            return false;
        }

        template<class SPECIFIC_TYPE, class H, class T>
        static bool insert(ContainerUnorderedMap< TypeList<H, T>, KEY_TYPE >& elements, KEY_TYPE handle, SPECIFIC_TYPE* obj)
        {
            bool ret = TypeUnorderedMapContainer::insert(elements._elements, handle, obj);
            return ret ? ret : TypeUnorderedMapContainer::insert(elements._TailElements, handle, obj);
        }

        // Find helpers
        template<class SPECIFIC_TYPE>
        static SPECIFIC_TYPE* find(ContainerUnorderedMap<SPECIFIC_TYPE, KEY_TYPE>& elements, KEY_TYPE hdl, SPECIFIC_TYPE* /*obj*/)
        {
            typename UNORDERED_MAP<KEY_TYPE, SPECIFIC_TYPE*>::iterator i = elements._element.find(hdl);
            if (i == elements._element.end())
                return NULL;
            else
                return i->second;
        }

        template<class SPECIFIC_TYPE>
        static SPECIFIC_TYPE* find(ContainerUnorderedMap<TypeNull, KEY_TYPE>& /*elements*/, KEY_TYPE /*hdl*/, SPECIFIC_TYPE* /*obj*/)
        {
            return NULL;
        }

        template<class SPECIFIC_TYPE, class T>
        static SPECIFIC_TYPE* find(ContainerUnorderedMap<T, KEY_TYPE>& /*elements*/, KEY_TYPE /*hdl*/, SPECIFIC_TYPE* /*obj*/)
        {
            return NULL;
        }

        template<class SPECIFIC_TYPE, class H, class T>
        static SPECIFIC_TYPE* find(ContainerUnorderedMap< TypeList<H, T>, KEY_TYPE >& elements, KEY_TYPE hdl, SPECIFIC_TYPE* /*obj*/)
        {
            SPECIFIC_TYPE* ret = TypeUnorderedMapContainer::find(elements._elements, hdl, (SPECIFIC_TYPE*)NULL);
            return ret ? ret : TypeUnorderedMapContainer::find(elements._TailElements, hdl, (SPECIFIC_TYPE*)NULL);
        }

        // Erase helpers
        template<class SPECIFIC_TYPE>
        static bool erase(ContainerUnorderedMap<SPECIFIC_TYPE, KEY_TYPE>& elements, KEY_TYPE handle, SPECIFIC_TYPE* /*obj*/)
        {
            elements._element.erase(handle);

            return true;
        }

        template<class SPECIFIC_TYPE>
        static bool erase(ContainerUnorderedMap<TypeNull, KEY_TYPE>& /*elements*/, KEY_TYPE /*handle*/, SPECIFIC_TYPE* /*obj*/)
        {
            return false;
        }

        template<class SPECIFIC_TYPE, class T>
        static bool erase(ContainerUnorderedMap<T, KEY_TYPE>& /*elements*/, KEY_TYPE /*handle*/, SPECIFIC_TYPE* /*obj*/)
        {
            return false;
        }

        template<class SPECIFIC_TYPE, class H, class T>
        static bool erase(ContainerUnorderedMap< TypeList<H, T>, KEY_TYPE >& elements, KEY_TYPE handle, SPECIFIC_TYPE* /*obj*/)
        {
            bool ret = TypeUnorderedMapContainer::erase(elements._elements, handle, (SPECIFIC_TYPE*)NULL);
            return ret ? ret : TypeUnorderedMapContainer::erase(elements._TailElements, handle, (SPECIFIC_TYPE*)NULL);
        }
};

/*
 * @class ContainerMapList is a mulit-type container for map elements
 * By itself its meaningless but collaborate along with TypeContainers,
 * it become the most powerfully container in the whole system.
 */
template<class OBJECT>
struct ContainerMapList
{
    GridRefManager<OBJECT> _element;
};

template<>
struct ContainerMapList<TypeNull>                           /* nothing is in type null */
{
};

template<class H, class T>
struct ContainerMapList<TypeList<H, T> >
{
    ContainerMapList<H> _elements;
    ContainerMapList<T> _TailElements;
};

#include "TypeContainerFunctions.h"

/*
 * @class TypeMapContainer contains a fixed number of types and is
 * determined at compile time.  This is probably the most complicated
 * class and do its simplest thing, that is, holds objects
 * of different types.
 */

template<class OBJECT_TYPES>
class ANATHEMA_DLL_DECL TypeMapContainer
{
    public:

        template<class SPECIFIC_TYPE>
        size_t Count() const { return ANATHEMA::Count(i_elements, (SPECIFIC_TYPE*)NULL); }

        /// inserts a specific object into the container
        template<class SPECIFIC_TYPE>
        bool insert(SPECIFIC_TYPE *obj)
        {
            SPECIFIC_TYPE* t = ANATHEMA::Insert(i_elements, obj);
            return (t != NULL);
        }

        ///  Removes the object from the container, and returns the removed object
        template<class SPECIFIC_TYPE>
        bool remove(SPECIFIC_TYPE* obj)
        {
            SPECIFIC_TYPE* t = ANATHEMA::Remove(i_elements, obj);
            return (t != NULL);
        }

        ContainerMapList<OBJECT_TYPES> & GetElements() { return i_elements; }
        const ContainerMapList<OBJECT_TYPES> & GetElements() const { return i_elements;}

    private:

        ContainerMapList<OBJECT_TYPES> i_elements;
};

#endif

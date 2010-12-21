/*
 * Copyright (C) 2010 Anathema Engine project <http://valkyrie-wow.ru/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 */

#ifndef ANATHEMA_GRID_H
#define ANATHEMA_GRID_H

/*
  @class Grid
  Grid is a logical segment of the game world represented inside ANATHEMA.
  Grid is bind at compile time to a particular type of object which
  we call it the object of interested.  There are many types of loader,
  specially, dynamic loader, static loader, or on-demand loader.  There's
  a subtle difference between dynamic loader and on-demand loader but
  this is implementation specific to the loader class.  From the
  Grid's perspective, the loader meets its API requirement is suffice.
*/

#include "Platform/Define.h"
#include "Policies/ThreadingModel.h"
#include "TypeContainer.h"
#include "TypeContainerVisitor.h"

// forward declaration
template<class A, class T, class O> class GridLoader;

template
<
class ACTIVE_OBJECT,
class WORLD_OBJECT_TYPES,
class GRID_OBJECT_TYPES
>
class ANATHEMA_DLL_DECL Grid
{
    // allows the GridLoader to access its internals
    template<class A, class T, class O> friend class GridLoader;

    public:

        /** destructor to clean up its resources. This includes unloading the
        grid if it has not been unload.
        */
        ~Grid() {}

        /** an object of interested enters the grid
         */
        template<class SPECIFIC_OBJECT>
        bool AddWorldObject(SPECIFIC_OBJECT *obj)
        {
            return i_objects.template insert<SPECIFIC_OBJECT>(obj);
        }

        /** an object of interested exits the grid
         */
        template<class SPECIFIC_OBJECT>
        bool RemoveWorldObject(SPECIFIC_OBJECT *obj)
        {
            return i_objects.template remove<SPECIFIC_OBJECT>(obj);
        }

        /** Grid visitor for grid objects
         */
        template<class T>
        void Visit(TypeContainerVisitor<T, TypeMapContainer<GRID_OBJECT_TYPES> > &visitor)
        {
            visitor.Visit(i_container);
        }

        /** Grid visitor for world objects
         */
        template<class T>
        void Visit(TypeContainerVisitor<T, TypeMapContainer<WORLD_OBJECT_TYPES> > &visitor)
        {
            visitor.Visit(i_objects);
        }

        /** Returns the number of object within the grid.
         */
        uint32 ActiveObjectsInGrid() const
        {
            return m_activeGridObjects.size() + i_objects.template Count<ACTIVE_OBJECT>();
        }

        /** Inserts a container type object into the grid.
         */
        template<class SPECIFIC_OBJECT>
        bool AddGridObject(SPECIFIC_OBJECT *obj)
        {
            if (obj->isActiveObject())
                m_activeGridObjects.insert(obj);

            return i_container.template insert<SPECIFIC_OBJECT>(obj);
        }

        /** Removes a containter type object from the grid
         */
        template<class SPECIFIC_OBJECT>
        bool RemoveGridObject(SPECIFIC_OBJECT *obj)
        {
            if (obj->isActiveObject())
                m_activeGridObjects.erase(obj);

            return i_container.template remove<SPECIFIC_OBJECT>(obj);
        }

    private:

        TypeMapContainer<GRID_OBJECT_TYPES> i_container;
        TypeMapContainer<WORLD_OBJECT_TYPES> i_objects;
        typedef std::set<void*> ActiveGridObjects;
        ActiveGridObjects m_activeGridObjects;
};

#endif

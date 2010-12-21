/*
 * Copyright (C) 2010 Anathema Engine project <http://valkyrie-wow.ru/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 */

#ifndef ANATHEMA_GRIDLOADER_H
#define ANATHEMA_GRIDLOADER_H

/**
  @class GridLoader
  The GridLoader is working in conjuction with the Grid and responsible
  for loading and unloading object-types (one or more) when objects
  enters a grid.  Unloading is scheduled and might be canceled if
  an interested object re-enters.  GridLoader does not do the actuall
  loading and unloading but implements as a template pattern that
  delicate its loading and unloading for the actualy loader and unloader.
  GridLoader manages the grid (both local and remote).
 */

#include "Platform/Define.h"
#include "Grid.h"
#include "TypeContainerVisitor.h"

template
<
class ACTIVE_OBJECT,
class WORLD_OBJECT_TYPES,
class GRID_OBJECT_TYPES
>
class ANATHEMA_DLL_DECL GridLoader
{
    public:

        /** Loads the grid
         */
        template<class LOADER>
        void Load(Grid<ACTIVE_OBJECT,WORLD_OBJECT_TYPES, GRID_OBJECT_TYPES> &grid, LOADER &loader)
        {
            loader.Load(grid);
        }

        /** Stop the grid
         */
        template<class STOPER>
        void Stop(Grid<ACTIVE_OBJECT,WORLD_OBJECT_TYPES, GRID_OBJECT_TYPES> &grid, STOPER &stoper)
        {
            stoper.Stop(grid);
        }

        /** Unloads the grid
         */
        template<class UNLOADER>
        void Unload(Grid<ACTIVE_OBJECT,WORLD_OBJECT_TYPES, GRID_OBJECT_TYPES> &grid, UNLOADER &unloader)
        {
            unloader.Unload(grid);
        }
};

#endif

/*
 * Copyright (C) 2010 Anathema Engine project <http://valkyrie-wow.ru/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 */

#ifndef ANATHEMA_TYPECONTAINERVISITOR_H
#define ANATHEMA_TYPECONTAINERVISITOR_H

/*
 * @class TypeContainerVisitor is implemented as a visitor pattern.  It is
 * a visitor to the TypeMapContainer or ContainerMapList.  The visitor has
 * to overload its types as a visit method is called.
 */

#include "Platform/Define.h"
#include "TypeContainer.h"

// forward declaration
template<class T, class Y> class TypeContainerVisitor;

// visitor helper
template<class VISITOR, class TYPE_CONTAINER>
void VisitorHelper(VISITOR &v, TYPE_CONTAINER &c)
{
    v.Visit(c);
}

// terminate condition container map list
template<class VISITOR>
void VisitorHelper(VISITOR &/*v*/, ContainerMapList<TypeNull> &/*c*/)
{
}

template<class VISITOR, class T>
void VisitorHelper(VISITOR &v, ContainerMapList<T> &c)
{
    v.Visit(c._element);
}

// recursion container map list
template<class VISITOR, class H, class T>
void VisitorHelper(VISITOR &v, ContainerMapList<TypeList<H, T> > &c)
{
    VisitorHelper(v, c._elements);
    VisitorHelper(v, c._TailElements);
}

// for TypeMapContainer
template<class VISITOR, class OBJECT_TYPES>
void VisitorHelper(VISITOR &v, TypeMapContainer<OBJECT_TYPES> &c)
{
    VisitorHelper(v, c.GetElements());
}

template<class VISITOR, class TYPE_CONTAINER>
class ANATHEMA_DLL_DECL TypeContainerVisitor
{
    public:

        TypeContainerVisitor(VISITOR &v)
            : i_visitor(v)
        {
        }

        void Visit(TYPE_CONTAINER &c)
        {
            VisitorHelper(i_visitor, c);
        }

        void Visit(const TYPE_CONTAINER &c) const
        {
            VisitorHelper(i_visitor, c);
        }

    private:

        VISITOR &i_visitor;
};

#endif

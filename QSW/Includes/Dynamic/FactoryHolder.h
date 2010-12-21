/*
 * Copyright (C) 2010 Anathema Engine project <http://valkyrie-wow.ru/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 */

#ifndef ANATHEMA_FACTORY_HOLDER
#define ANATHEMA_FACTORY_HOLDER

#include "Platform/Define.h"
#include "Utilities/TypeList.h"
#include "ObjectRegistry.h"
#include "Policies/SingletonImp.h"

/** FactoryHolder holds a factory object of a specific type
 */
template<class T, class Key = std::string>
class ANATHEMA_DLL_DECL FactoryHolder
{
    public:
        typedef ObjectRegistry<FactoryHolder<T, Key >, Key > FactoryHolderRegistry;
        typedef ANATHEMA::Singleton<FactoryHolderRegistry > FactoryHolderRepository;

        FactoryHolder(Key k) : i_key(k) {}
        virtual ~FactoryHolder() {}
        inline Key key() const { return i_key; }

        void RegisterSelf(void) { FactoryHolderRepository::Instance().InsertItem(this, i_key); }
        void DeregisterSelf(void) { FactoryHolderRepository::Instance().RemoveItem(this, false); }

        /// Abstract Factory create method
        virtual T* Create(void *data = NULL) const = 0;
    private:
        Key i_key;
};

/** Permissible is a classic way of letting the object decide
 * whether how good they handle things.  This is not retricted
 * to factory selectors.
 */
template<class T>
class Permissible
{
    public:
        virtual ~Permissible() {}
        virtual int Permit(const T *) const = 0;
};
#endif

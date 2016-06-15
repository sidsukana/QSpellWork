#ifndef SPELLINFO_INTERFACE_H
#define SPELLINFO_INTERFACE_H

#include <QObject>
#include <QVariantHash>

#include "../../shared.h"

class SpellInfoInterface
{
    public:
        virtual ~SpellInfoInterface() {}

        virtual bool init() const = 0;

        virtual void setEnums(EnumHash enums) = 0;

        virtual quint32 getSpellsCount() const = 0;
        virtual QObject* getMetaSpell(quint32 id, bool realId = false) const = 0;
        virtual QVariantHash getValues(quint32 id) const = 0;
        virtual QObjectList getMetaSpells() const = 0;
        virtual EnumHash getEnums() const = 0;
        virtual quint8 getLocale() const = 0;
        virtual QStringList getNames() const = 0;
};

#define SpellInfoInterface_iid "org.qsw.plugins.spellinfo"

Q_DECLARE_INTERFACE(SpellInfoInterface, SpellInfoInterface_iid)

#endif // SPELLINFO_INTERFACE_H

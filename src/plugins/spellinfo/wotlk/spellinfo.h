#pragma once

#include <QObject>
#include <QtPlugin>

#include "../interface.h"

extern EnumHash m_enums;
extern QStringList m_names;
extern QObjectList m_metaSpells;
extern Indexes m_metaSpellIndexes;
extern Indexes m_internalSpells;
extern QStringList m_modifiedStrings;

class SpellInfo : public QObject, SpellInfoInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID SpellInfoInterface_iid FILE "wotlk.json")
    Q_INTERFACES(SpellInfoInterface)

    public:

        bool init();

        void setEnums(EnumHash enums);

        MPQList getMPQFiles() const;
        quint32 getSpellsCount() const;
        QObject* getMetaSpell(quint32 id, bool realId = false) const;
        QVariantHash getValues(quint32 id) const;
        QObjectList getMetaSpells() const;
        EnumHash getEnums() const;
        QStringList getNames() const;
};

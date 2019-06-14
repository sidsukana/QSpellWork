#ifndef SPELLINFO_H
#define SPELLINFO_H

#include <QObject>
#include <QtPlugin>

#include "../interface.h"

extern quint8 m_locale;

extern EnumHash m_enums;
extern QStringList m_names;
extern QObjectList m_metaSpells;
extern Indexes m_metaSpellIndexes;
extern Indexes m_internalSpells;
extern QStringList m_modifiedStrings;

class SpellInfo : public QObject, SpellInfoInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID SpellInfoInterface_iid FILE "cata.json")
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
        quint8 getLocale() const;
        QStringList getNames() const;
};

#endif // SPELLINFO_H

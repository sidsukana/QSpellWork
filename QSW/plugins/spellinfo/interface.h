#pragma once

#include <QObject>
#include <QSqlQuery>
#include <QVariantHash>

#include "../../qsw.h"

class SpellInfoInterface
{
    public:
        virtual ~SpellInfoInterface() {}

        virtual bool init() = 0;

        virtual void setEnums(EnumHash enums) = 0;

        virtual MPQList getMPQFiles() const = 0;
        virtual quint32 getSpellsCount() const = 0;
        virtual QObject* getMetaSpell(quint32 id, bool realId = false) const = 0;
        virtual QVariantHash getValues(quint32 id) const = 0;
        virtual QObjectList getMetaSpells() const = 0;
        virtual EnumHash getEnums() const = 0;
        virtual QStringList getNames() const = 0;

        virtual QStringList getModifiedSqlDataQueries() { return QStringList(); }
        virtual void setModifiedSqlDataResult(quint8 queryIndex, QSqlQuery& query) { Q_UNUSED(queryIndex) Q_UNUSED(query) }

    /*
    signals:
        void progressShow(int maximum);
        void progressStep(int value);
        void progressHide();
     */
};

#define SpellInfoInterface_iid "org.qsw.plugins.spellinfo"

Q_DECLARE_INTERFACE(SpellInfoInterface, SpellInfoInterface_iid)

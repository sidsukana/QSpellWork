#ifndef SWSEARCH_H
#define SWSEARCH_H

#include "SWObject.h"
#include "DBC/DBCStores.h"

class SWObject;
class SWForm;

class SWSearch
{
    public:
        SWSearch(SWObject* sw);
        ~SWSearch();

        void search();
        bool hasValue(QString name, QString value, SpellEntry const* spellInfo);

    private:
        SWObject* m_sw;
        SWForm*   m_form;
};

class MetaSpell : public QObject
{
    Q_OBJECT
    
    public:
        MetaSpell(SpellEntry const* spellInfo);
        ~MetaSpell();

        quint32 getId() { return m_spellInfo->Id; }
        quint32 getSchool() { return m_spellInfo->School; }
        quint32 getCategory() { return m_spellInfo->Category; }
        quint32 getCastUI() { return m_spellInfo->CastUI; }
        quint32 getDispel() { return m_spellInfo->Dispel; }
        quint32 getMechanic() { return m_spellInfo->Mechanic; }
        quint32 getAttributes() { return m_spellInfo->Attributes; }
        quint32 getAttributesEx() { return m_spellInfo->AttributesEx; }
        quint32 getAttributesEx2() { return m_spellInfo->AttributesEx2; }
        quint32 getAttributesEx3() { return m_spellInfo->AttributesEx3; }
        quint32 getAttributesEx4() { return m_spellInfo->AttributesEx4; }
        quint32 getStances() { return m_spellInfo->Stances; }
        quint32 getStancesNot() { return m_spellInfo->StancesNot; }
        quint32 getTargets() { return m_spellInfo->Targets; }
        quint32 getTargetCreatureType() { return m_spellInfo->TargetCreatureType; }
        quint32 getRequiresSpellFocus() { return m_spellInfo->RequiresSpellFocus; }
        quint32 getCasterAuraState() { return m_spellInfo->CasterAuraState; }
        quint32 getTargetAuraState() { return m_spellInfo->TargetAuraState; }
        quint32 getCastingTimeIndex() { return m_spellInfo->CastingTimeIndex; }
        quint32 getRecoveryTime() { return m_spellInfo->RecoveryTime; }
        quint32 getCategoryRecoveryTime() { return m_spellInfo->CategoryRecoveryTime; }
        quint32 getInterruptFlags() { return m_spellInfo->InterruptFlags; }
        quint32 getAuraInterruptFlags() { return m_spellInfo->AuraInterruptFlags; }
        quint32 getChannelInterruptFlags() { return m_spellInfo->ChannelInterruptFlags; }
        quint32 getProcFlags() { return m_spellInfo->ProcFlags; }
        quint32 getProcChance() { return m_spellInfo->ProcChance; }
        quint32 getProcCharges() { return m_spellInfo->ProcCharges; }
        quint32 getMaxLevel() { return m_spellInfo->MaxLevel; }
        quint32 getBaseLevel() { return m_spellInfo->BaseLevel; }
        quint32 getSpellLevel() { return m_spellInfo->SpellLevel; }
        quint32 getDurationIndex() { return m_spellInfo->DurationIndex; }
        qint32  getPowerType() { return m_spellInfo->PowerType; }
        quint32 getManaCost() { return m_spellInfo->ManaCost; }
        quint32 getManaCostPerlevel() { return m_spellInfo->ManaCostPerlevel; }
        quint32 getManaPerSecond() { return m_spellInfo->ManaPerSecond; }
        quint32 getManaPerSecondPerLevel() { return m_spellInfo->ManaPerSecondPerLevel; }
        quint32 getRangeIndex() { return m_spellInfo->RangeIndex; }
        float   getSpeed() { return m_spellInfo->Speed; }
        quint32 getModalNextSpell() { return m_spellInfo->ModalNextSpell; }
        quint32 getStackAmount() { return m_spellInfo->StackAmount; }
        qint32  getEquippedItemClass() { return m_spellInfo->EquippedItemClass; }
        qint32  getEquippedItemSubClassMask() { return m_spellInfo->EquippedItemSubClassMask; }
        qint32  getEquippedItemInventoryTypeMask() { return m_spellInfo->EquippedItemInventoryTypeMask; }
        quint32 getSpellIconID() { return m_spellInfo->SpellIconID; }
        quint32 getActiveIconID() { return m_spellInfo->ActiveIconID; }
        quint32 getSpellPriority() { return m_spellInfo->SpellPriority; }
        quint32 getSpellNameFlag() { return m_spellInfo->SpellNameFlag; }
        quint32 getRankFlags() { return m_spellInfo->RankFlags; }
        quint32 getDescriptionFlags() { return m_spellInfo->DescriptionFlags; }
        quint32 getToolTipFlags() { return m_spellInfo->ToolTipFlags; }
        quint32 getManaCostPercentage() { return m_spellInfo->ManaCostPercentage; }
        quint32 getStartRecoveryCategory() { return m_spellInfo->StartRecoveryCategory; }
        quint32 getStartRecoveryTime() { return m_spellInfo->StartRecoveryTime; }
        quint32 getMaxTargetLevel() { return m_spellInfo->MaxTargetLevel; }
        quint32 getSpellFamilyName() { return m_spellInfo->SpellFamilyName; }
        quint64 getSpellFamilyFlags() { return m_spellInfo->SpellFamilyFlags; }
        quint32 getMaxAffectedTargets() { return m_spellInfo->MaxAffectedTargets; }
        quint32 getDmgClass() { return m_spellInfo->DmgClass; }
        quint32 getPreventionType() { return m_spellInfo->PreventionType; }
        qint32  getStanceBarOrder() { return m_spellInfo->StanceBarOrder; }
        quint32 getMinFactionId() { return m_spellInfo->MinFactionId; }
        quint32 getMinReputation() { return m_spellInfo->MinReputation; }
        quint32 getRequiredAuraVision() { return m_spellInfo->RequiredAuraVision; }

        QString getSpellName() { return QString::fromUtf8(m_spellInfo->SpellName[Locale]); }
        QString getRank() { return QString::fromUtf8(m_spellInfo->Rank[Locale]); }
        QString getDescription() { return QString::fromUtf8(m_spellInfo->Description[Locale]); }
        QString getToolTip() { return QString::fromUtf8(m_spellInfo->ToolTip[Locale]); }

        QVariantList getTotem() { return Totem; }
        QVariantList getReagent() { return Reagent; }
        QVariantList getReagentCount() { return ReagentCount; }
        QVariantList getEffect() { return Effect; }
        QVariantList getEffectDieSides() { return EffectDieSides; }
        QVariantList getEffectBaseDice() { return EffectBaseDice; }
        QVariantList getEffectDicePerLevel() { return EffectDicePerLevel; }
        QVariantList getEffectRealPointsPerLevel() { return EffectRealPointsPerLevel; }
        QVariantList getEffectBasePoints() { return EffectBasePoints; }
        QVariantList getEffectMechanic() { return EffectMechanic; }
        QVariantList getEffectImplicitTargetA() { return EffectImplicitTargetA; }
        QVariantList getEffectImplicitTargetB() { return EffectImplicitTargetB; }
        QVariantList getEffectRadiusIndex() { return EffectRadiusIndex; }
        QVariantList getEffectApplyAuraName() { return EffectApplyAuraName; }
        QVariantList getEffectAmplitude() { return EffectAmplitude; }
        QVariantList getEffectMultipleValue() { return EffectMultipleValue; }
        QVariantList getEffectChainTarget() { return EffectChainTarget; }
        QVariantList getEffectItemType() { return EffectItemType; }
        QVariantList getEffectMiscValue() { return EffectMiscValue; }
        QVariantList getEffectTriggerSpell() { return EffectTriggerSpell; }
        QVariantList getEffectPointsPerComboPoint() { return EffectPointsPerComboPoint; }
        QVariantList getSpellVisual() { return SpellVisual; }
        QVariantList getDmgMultiplier() { return DmgMultiplier; }

    private:
        SpellEntry const* m_spellInfo;

        // Arrays values
        QVariantList Totem;
        QVariantList Reagent;
        QVariantList ReagentCount;
        QVariantList Effect;
        QVariantList EffectDieSides;
        QVariantList EffectBaseDice;
        QVariantList EffectDicePerLevel;
        QVariantList EffectRealPointsPerLevel;
        QVariantList EffectBasePoints;
        QVariantList EffectMechanic;
        QVariantList EffectImplicitTargetA;
        QVariantList EffectImplicitTargetB;
        QVariantList EffectRadiusIndex;
        QVariantList EffectApplyAuraName;
        QVariantList EffectAmplitude;
        QVariantList EffectMultipleValue;
        QVariantList EffectChainTarget;
        QVariantList EffectItemType;
        QVariantList EffectMiscValue;
        QVariantList EffectTriggerSpell;
        QVariantList EffectPointsPerComboPoint;
        QVariantList SpellVisual;
        QVariantList DmgMultiplier;


    Q_PROPERTY(quint32 Id READ getId)
    Q_PROPERTY(quint32 School READ getSchool)
    Q_PROPERTY(quint32 Category READ getCategory)
    Q_PROPERTY(quint32 CastUI READ getCastUI)
    Q_PROPERTY(quint32 Dispel READ getDispel)
    Q_PROPERTY(quint32 Mechanic READ getMechanic)
    Q_PROPERTY(quint32 Attributes READ getAttributes)
    Q_PROPERTY(quint32 AttributesEx READ getAttributesEx)
    Q_PROPERTY(quint32 AttributesEx2 READ getAttributesEx2)
    Q_PROPERTY(quint32 AttributesEx3 READ getAttributesEx3)
    Q_PROPERTY(quint32 AttributesEx4 READ getAttributesEx4)
    Q_PROPERTY(quint32 Stances READ getStances)
    Q_PROPERTY(quint32 StancesNot READ getStancesNot)
    Q_PROPERTY(quint32 Targets READ getTargets)
    Q_PROPERTY(quint32 TargetCreatureType READ getTargetCreatureType)
    Q_PROPERTY(quint32 RequiresSpellFocus READ getRequiresSpellFocus)
    Q_PROPERTY(quint32 CasterAuraState READ getCasterAuraState)
    Q_PROPERTY(quint32 TargetAuraState READ getTargetAuraState)
    Q_PROPERTY(quint32 CastingTimeIndex READ getCastingTimeIndex)
    Q_PROPERTY(quint32 RecoveryTime READ getRecoveryTime)
    Q_PROPERTY(quint32 CategoryRecoveryTime READ getCategoryRecoveryTime)
    Q_PROPERTY(quint32 InterruptFlags READ getInterruptFlags)
    Q_PROPERTY(quint32 AuraInterruptFlags READ getAuraInterruptFlags)
    Q_PROPERTY(quint32 ChannelInterruptFlags READ getChannelInterruptFlags)
    Q_PROPERTY(quint32 ProcFlags READ getProcFlags)
    Q_PROPERTY(quint32 ProcChance READ getProcChance)
    Q_PROPERTY(quint32 ProcCharges READ getProcCharges)
    Q_PROPERTY(quint32 MaxLevel READ getMaxLevel)
    Q_PROPERTY(quint32 BaseLevel READ getBaseLevel)
    Q_PROPERTY(quint32 SpellLevel READ getSpellLevel)
    Q_PROPERTY(quint32 DurationIndex READ getDurationIndex)
    Q_PROPERTY(qint32  PowerType READ getPowerType)
    Q_PROPERTY(quint32 ManaCost READ getManaCost)
    Q_PROPERTY(quint32 ManaCostPerlevel READ getManaCostPerlevel)
    Q_PROPERTY(quint32 ManaPerSecond READ getManaPerSecond)
    Q_PROPERTY(quint32 ManaPerSecondPerLevel READ getManaPerSecondPerLevel)
    Q_PROPERTY(quint32 RangeIndex READ getRangeIndex)
    Q_PROPERTY(float   Speed READ getSpeed)
    Q_PROPERTY(quint32 ModalNextSpell READ getModalNextSpell)
    Q_PROPERTY(quint32 StackAmount READ getStackAmount)
    Q_PROPERTY(QVariant Totem READ getTotem)
    //Q_PROPERTY(QVariantList Reagent READ getReagent)
    //Q_PROPERTY(QVariantList ReagentCount READ getReagentCount)
    Q_PROPERTY(qint32  EquippedItemClass READ getEquippedItemClass)
    Q_PROPERTY(qint32  EquippedItemSubClassMask READ getEquippedItemSubClassMask)
    Q_PROPERTY(qint32  EquippedItemInventoryTypeMask READ getEquippedItemInventoryTypeMask)
    /*Q_PROPERTY(QVariantList Effect READ getEffect)
    Q_PROPERTY(QVariantList EffectDieSides READ getEffectDieSides)
    Q_PROPERTY(QVariantList EffectBaseDice READ getEffectBaseDice)
    Q_PROPERTY(QVariantList EffectDicePerLevel READ getEffectDicePerLevel)
    Q_PROPERTY(QVariantList EffectRealPointsPerLevel READ getEffectRealPointsPerLevel)
    Q_PROPERTY(QVariantList EffectBasePoints READ getEffectBasePoints)
    Q_PROPERTY(QVariantList EffectMechanic READ getEffectMechanic)
    Q_PROPERTY(QVariantList EffectImplicitTargetA READ getEffectImplicitTargetA)
    Q_PROPERTY(QVariantList EffectImplicitTargetB READ getEffectImplicitTargetB)
    Q_PROPERTY(QVariantList EffectRadiusIndex READ getEffectRadiusIndex)
    Q_PROPERTY(QVariantList EffectApplyAuraName READ getEffectApplyAuraName)
    Q_PROPERTY(QVariantList EffectAmplitude READ getEffectAmplitude)
    Q_PROPERTY(QVariantList EffectMultipleValue READ getEffectMultipleValue)
    Q_PROPERTY(QVariantList EffectChainTarget READ getEffectChainTarget)
    Q_PROPERTY(QVariantList EffectItemType READ getEffectItemType)
    Q_PROPERTY(QVariantList EffectMiscValue READ getEffectMiscValue)
    Q_PROPERTY(QVariantList EffectTriggerSpell READ getEffectTriggerSpell)
    Q_PROPERTY(QVariantList EffectPointsPerComboPoint READ getEffectPointsPerComboPoint)
    Q_PROPERTY(QVariantList SpellVisual READ getSpellVisual)*/
    Q_PROPERTY(quint32 SpellIconID READ getSpellIconID)
    Q_PROPERTY(quint32 ActiveIconID READ getActiveIconID)
    Q_PROPERTY(quint32 SpellPriority READ getSpellPriority)
    Q_PROPERTY(QString SpellName READ getSpellName)
    Q_PROPERTY(quint32 SpellNameFlag READ getSpellNameFlag)
    Q_PROPERTY(QString Rank READ getRank)
    Q_PROPERTY(quint32 RankFlags READ getRankFlags)
    Q_PROPERTY(QString Description READ getDescription)
    Q_PROPERTY(quint32 DescriptionFlags READ getDescriptionFlags)
    Q_PROPERTY(QString ToolTip READ getToolTip)
    Q_PROPERTY(quint32 ToolTipFlags READ getToolTipFlags)
    Q_PROPERTY(quint32 ManaCostPercentage READ getManaCostPercentage)
    Q_PROPERTY(quint32 StartRecoveryCategory READ getStartRecoveryCategory)
    Q_PROPERTY(quint32 StartRecoveryTime READ getStartRecoveryTime)
    Q_PROPERTY(quint32 MaxTargetLevel READ getMaxTargetLevel)
    Q_PROPERTY(quint32 SpellFamilyName READ getSpellFamilyName)
    Q_PROPERTY(quint64 SpellFamilyFlags READ getSpellFamilyFlags)
    Q_PROPERTY(quint32 MaxAffectedTargets READ getMaxAffectedTargets)
    Q_PROPERTY(quint32 DmgClass READ getDmgClass)
    Q_PROPERTY(quint32 PreventionType READ getPreventionType)
    Q_PROPERTY(qint32  StanceBarOrder READ getStanceBarOrder)
    //Q_PROPERTY(QVariantList DmgMultiplier READ getDmgMultiplier)
    Q_PROPERTY(quint32 MinFactionId READ getMinFactionId)
    Q_PROPERTY(quint32 MinReputation READ getMinReputation)
    Q_PROPERTY(quint32 RequiredAuraVision READ getRequiredAuraVision)
};

#endif // SWSEARCH_H

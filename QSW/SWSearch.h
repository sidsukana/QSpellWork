#ifndef SWSEARCH_H
#define SWSEARCH_H

#include "SWObject.h"
#include "DBC/DBCStores.h"

class SWObject;
class SWMainForm;

class SWSearch
{
    public:
        SWSearch(SWObject* sw);
        ~SWSearch();

        void search();
        bool hasValue(int index, QString value, SpellEntry const* spellInfo);

    private:
        SWObject* m_sw;
        SWMainForm* m_form;
};

class MetaSpell : public QObject
{
    Q_OBJECT

    public:
        MetaSpell() : m_spellInfo(NULL) {}
        MetaSpell(SpellEntry const* spellInfo) : m_spellInfo(spellInfo) {}
        ~MetaSpell() {}

        Q_INVOKABLE QVariant Id() { return m_spellInfo->Id; }
        Q_INVOKABLE QVariant School() { return m_spellInfo->School; }
        Q_INVOKABLE QVariant Category() { return m_spellInfo->Category; }
        Q_INVOKABLE QVariant CastUI() { return m_spellInfo->CastUI; }
        Q_INVOKABLE QVariant Dispel() { return m_spellInfo->Dispel; }
        Q_INVOKABLE QVariant Mechanic() { return m_spellInfo->Mechanic; }
        Q_INVOKABLE QVariant Attributes() { return m_spellInfo->Attributes; }
        Q_INVOKABLE QVariant AttributesEx1() { return m_spellInfo->AttributesEx1; }
        Q_INVOKABLE QVariant AttributesEx2() { return m_spellInfo->AttributesEx2; }
        Q_INVOKABLE QVariant AttributesEx3() { return m_spellInfo->AttributesEx3; }
        Q_INVOKABLE QVariant AttributesEx4() { return m_spellInfo->AttributesEx4; }
        Q_INVOKABLE QVariant Stances() { return m_spellInfo->Stances; }
        Q_INVOKABLE QVariant StancesNot() { return m_spellInfo->StancesNot; }
        Q_INVOKABLE QVariant Targets() { return m_spellInfo->Targets; }
        Q_INVOKABLE QVariant TargetCreatureType() { return m_spellInfo->TargetCreatureType; }
        Q_INVOKABLE QVariant RequiresSpellFocus() { return m_spellInfo->RequiresSpellFocus; }
        Q_INVOKABLE QVariant CasterAuraState() { return m_spellInfo->CasterAuraState; }
        Q_INVOKABLE QVariant TargetAuraState() { return m_spellInfo->TargetAuraState; }
        Q_INVOKABLE QVariant CastingTimeIndex() { return m_spellInfo->CastingTimeIndex; }
        Q_INVOKABLE QVariant RecoveryTime() { return m_spellInfo->RecoveryTime; }
        Q_INVOKABLE QVariant CategoryRecoveryTime() { return m_spellInfo->CategoryRecoveryTime; }
        Q_INVOKABLE QVariant InterruptFlags() { return m_spellInfo->InterruptFlags; }
        Q_INVOKABLE QVariant AuraInterruptFlags() { return m_spellInfo->AuraInterruptFlags; }
        Q_INVOKABLE QVariant ChannelInterruptFlags() { return m_spellInfo->ChannelInterruptFlags; }
        Q_INVOKABLE QVariant ProcFlags() { return m_spellInfo->ProcFlags; }
        Q_INVOKABLE QVariant ProcChance() { return m_spellInfo->ProcChance; }
        Q_INVOKABLE QVariant ProcCharges() { return m_spellInfo->ProcCharges; }
        Q_INVOKABLE QVariant MaxLevel() { return m_spellInfo->MaxLevel; }
        Q_INVOKABLE QVariant BaseLevel() { return m_spellInfo->BaseLevel; }
        Q_INVOKABLE QVariant SpellLevel() { return m_spellInfo->SpellLevel; }
        Q_INVOKABLE QVariant DurationIndex() { return m_spellInfo->DurationIndex; }
        Q_INVOKABLE QVariant PowerType() { return m_spellInfo->PowerType; }
        Q_INVOKABLE QVariant ManaCost() { return m_spellInfo->ManaCost; }
        Q_INVOKABLE QVariant ManaCostPerlevel() { return m_spellInfo->ManaCostPerlevel; }
        Q_INVOKABLE QVariant ManaPerSecond() { return m_spellInfo->ManaPerSecond; }
        Q_INVOKABLE QVariant ManaPerSecondPerLevel() { return m_spellInfo->ManaPerSecondPerLevel; }
        Q_INVOKABLE QVariant RangeIndex() { return m_spellInfo->RangeIndex; }
        Q_INVOKABLE QVariant Speed() { return m_spellInfo->Speed; }
        Q_INVOKABLE QVariant ModalNextSpell() { return m_spellInfo->ModalNextSpell; }
        Q_INVOKABLE QVariant StackAmount() { return m_spellInfo->StackAmount; }
        Q_INVOKABLE QVariant Totem(quint8 index) { return m_spellInfo->Totem[index]; }
        Q_INVOKABLE QVariant Reagent(quint8 index) { return m_spellInfo->Reagent[index]; }
        Q_INVOKABLE QVariant ReagentCount(quint8 index) { return m_spellInfo->ReagentCount[index]; }
        Q_INVOKABLE QVariant EquippedItemClass() { return m_spellInfo->EquippedItemClass; }
        Q_INVOKABLE QVariant EquippedItemSubClassMask() { return m_spellInfo->EquippedItemSubClassMask; }
        Q_INVOKABLE QVariant EquippedItemInventoryTypeMask() { return m_spellInfo->EquippedItemInventoryTypeMask; }
        Q_INVOKABLE QVariant Effect(quint8 index) { return m_spellInfo->Effect[index]; }
        Q_INVOKABLE QVariant EffectDieSides(quint8 index) { return m_spellInfo->EffectDieSides[index]; }
        Q_INVOKABLE QVariant EffectBaseDice(quint8 index) { return m_spellInfo->EffectBaseDice[index]; }
        Q_INVOKABLE QVariant EffectDicePerLevel(quint8 index) { return m_spellInfo->EffectDicePerLevel[index]; }
        Q_INVOKABLE QVariant EffectRealPointsPerLevel(quint8 index) { return m_spellInfo->EffectRealPointsPerLevel[index]; }
        Q_INVOKABLE QVariant EffectBasePoints(quint8 index) { return m_spellInfo->EffectBasePoints[index]; }
        Q_INVOKABLE QVariant EffectMechanic(quint8 index) { return m_spellInfo->EffectMechanic[index]; }
        Q_INVOKABLE QVariant EffectImplicitTargetA(quint8 index) { return m_spellInfo->EffectImplicitTargetA[index]; }
        Q_INVOKABLE QVariant EffectImplicitTargetB(quint8 index) { return m_spellInfo->EffectImplicitTargetB[index]; }
        Q_INVOKABLE QVariant EffectRadiusIndex(quint8 index) { return m_spellInfo->EffectRadiusIndex[index]; }
        Q_INVOKABLE QVariant EffectApplyAuraName(quint8 index) { return m_spellInfo->EffectApplyAuraName[index]; }
        Q_INVOKABLE QVariant EffectAmplitude(quint8 index) { return m_spellInfo->EffectAmplitude[index]; }
        Q_INVOKABLE QVariant EffectMultipleValue(quint8 index) { return m_spellInfo->EffectMultipleValue[index]; }
        Q_INVOKABLE QVariant EffectChainTarget(quint8 index) { return m_spellInfo->EffectChainTarget[index]; }
        Q_INVOKABLE QVariant EffectItemType(quint8 index) { return m_spellInfo->EffectItemType[index]; }
        Q_INVOKABLE QVariant EffectMiscValue(quint8 index) { return m_spellInfo->EffectMiscValue[index]; }
        Q_INVOKABLE QVariant EffectTriggerSpell(quint8 index) { return m_spellInfo->EffectTriggerSpell[index]; }
        Q_INVOKABLE QVariant EffectPointsPerComboPoint(quint8 index) { return m_spellInfo->EffectPointsPerComboPoint[index]; }
        Q_INVOKABLE QVariant SpellVisual(quint8 index) { return m_spellInfo->SpellVisual[index]; }
        Q_INVOKABLE QVariant SpellIconId() { return m_spellInfo->SpellIconId; }
        Q_INVOKABLE QVariant ActiveIconId() { return m_spellInfo->ActiveIconId; }
        Q_INVOKABLE QVariant SpellPriority() { return m_spellInfo->SpellPriority; }
        Q_INVOKABLE QVariant SpellName() { return QString::fromUtf8(m_spellInfo->SpellName[Locale]); }
        Q_INVOKABLE QVariant Rank() { return QString::fromUtf8(m_spellInfo->Rank[Locale]); }
        Q_INVOKABLE QVariant Description() { return QString::fromUtf8(m_spellInfo->Description[Locale]); }
        Q_INVOKABLE QVariant ToolTip() { return QString::fromUtf8(m_spellInfo->ToolTip[Locale]); }
        Q_INVOKABLE QVariant SpellNameFlag() { return m_spellInfo->SpellNameFlag; }
        Q_INVOKABLE QVariant RankFlags() { return m_spellInfo->RankFlags; }
        Q_INVOKABLE QVariant DescriptionFlags() { return m_spellInfo->DescriptionFlags; }
        Q_INVOKABLE QVariant ToolTipFlags() { return m_spellInfo->ToolTipFlags; }
        Q_INVOKABLE QVariant ManaCostPercentage() { return m_spellInfo->ManaCostPercentage; }
        Q_INVOKABLE QVariant StartRecoveryCategory() { return m_spellInfo->StartRecoveryCategory; }
        Q_INVOKABLE QVariant StartRecoveryTime() { return m_spellInfo->StartRecoveryTime; }
        Q_INVOKABLE QVariant MaxTargetLevel() { return m_spellInfo->MaxTargetLevel; }
        Q_INVOKABLE QVariant SpellFamilyName() { return m_spellInfo->SpellFamilyName; }
        Q_INVOKABLE QVariant SpellFamilyFlags() { return m_spellInfo->SpellFamilyFlags; }
        Q_INVOKABLE QVariant MaxAffectedTargets() { return m_spellInfo->MaxAffectedTargets; }
        Q_INVOKABLE QVariant DamageClass() { return m_spellInfo->DamageClass; }
        Q_INVOKABLE QVariant PreventionType() { return m_spellInfo->PreventionType; }
        Q_INVOKABLE QVariant StanceBarOrder() { return m_spellInfo->StanceBarOrder; }
        Q_INVOKABLE QVariant DamageMultiplier(quint8 index) { return m_spellInfo->DamageMultiplier[index]; }
        Q_INVOKABLE QVariant MinFactionId() { return m_spellInfo->MinFactionId; }
        Q_INVOKABLE QVariant MinReputation() { return m_spellInfo->MinReputation; }
        Q_INVOKABLE QVariant RequiredAuraVision() { return m_spellInfo->RequiredAuraVision; }

        quint8 Totem() { return 2; }
        quint8 Reagent() { return 8; }
        quint8 ReagentCount() { return 8; }
        quint8 Effect() { return 3; }
        quint8 EffectDieSides() { return 3; }
        quint8 EffectBaseDice() { return 3; }
        quint8 EffectDicePerLevel() { return 3; }
        quint8 EffectRealPointsPerLevel() { return 3; }
        quint8 EffectBasePoints() { return 3; }
        quint8 EffectMechanic() { return 3; }
        quint8 EffectImplicitTargetA() { return 3; }
        quint8 EffectImplicitTargetB() { return 3; }
        quint8 EffectRadiusIndex() { return 3; }
        quint8 EffectApplyAuraName() { return 3; }
        quint8 EffectAmplitude() { return 3; }
        quint8 EffectMultipleValue() { return 3; }
        quint8 EffectChainTarget() { return 3; }
        quint8 EffectItemType() { return 3; }
        quint8 EffectMiscValue() { return 3; }
        quint8 EffectTriggerSpell() { return 3; }
        quint8 EffectPointsPerComboPoint() { return 3; }
        quint8 SpellVisual() { return 2; }
        quint8 DamageMultiplier() { return 3; }

    private:
        SpellEntry const* m_spellInfo;

        Q_PROPERTY(quint8 Totem READ Totem)
        Q_PROPERTY(quint8 Reagent READ Reagent)
        Q_PROPERTY(quint8 ReagentCount READ ReagentCount)
        Q_PROPERTY(quint8 Effect READ Effect)
        Q_PROPERTY(quint8 EffectDieSides READ EffectDieSides)
        Q_PROPERTY(quint8 EffectBaseDice READ EffectBaseDice)
        Q_PROPERTY(quint8 EffectDicePerLevel READ EffectDicePerLevel)
        Q_PROPERTY(quint8 EffectRealPointsPerLevel READ EffectRealPointsPerLevel)
        Q_PROPERTY(quint8 EffectBasePoints READ EffectBasePoints)
        Q_PROPERTY(quint8 EffectMechanic READ EffectMechanic)
        Q_PROPERTY(quint8 EffectImplicitTargetA READ EffectImplicitTargetA)
        Q_PROPERTY(quint8 EffectImplicitTargetB READ EffectImplicitTargetB)
        Q_PROPERTY(quint8 EffectRadiusIndex READ EffectRadiusIndex)
        Q_PROPERTY(quint8 EffectApplyAuraName READ EffectApplyAuraName)
        Q_PROPERTY(quint8 EffectAmplitude READ EffectAmplitude)
        Q_PROPERTY(quint8 EffectMultipleValue READ EffectMultipleValue)
        Q_PROPERTY(quint8 EffectChainTarget READ EffectChainTarget)
        Q_PROPERTY(quint8 EffectItemType READ EffectItemType)
        Q_PROPERTY(quint8 EffectMiscValue READ EffectMiscValue)
        Q_PROPERTY(quint8 EffectTriggerSpell READ EffectTriggerSpell)
        Q_PROPERTY(quint8 EffectPointsPerComboPoint READ EffectPointsPerComboPoint)
        Q_PROPERTY(quint8 SpellVisual READ SpellVisual)
        Q_PROPERTY(quint8 DamageMultiplier READ DamageMultiplier)
};

#endif // SWSEARCH_H
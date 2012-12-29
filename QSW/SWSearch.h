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
        Q_INVOKABLE QVariant Category() { return m_spellInfo->Category; }
        Q_INVOKABLE QVariant Dispel() { return m_spellInfo->Dispel; }
        Q_INVOKABLE QVariant Mechanic() { return m_spellInfo->Mechanic; }
        Q_INVOKABLE QVariant Attributes() { return m_spellInfo->Attributes; }
        Q_INVOKABLE QVariant AttributesEx() { return m_spellInfo->AttributesEx; }
        Q_INVOKABLE QVariant AttributesEx2() { return m_spellInfo->AttributesEx2; }
        Q_INVOKABLE QVariant AttributesEx3() { return m_spellInfo->AttributesEx3; }
        Q_INVOKABLE QVariant AttributesEx4() { return m_spellInfo->AttributesEx4; }
        Q_INVOKABLE QVariant AttributesEx5() { return m_spellInfo->AttributesEx5; }
        Q_INVOKABLE QVariant AttributesEx6() { return m_spellInfo->AttributesEx6; }
        Q_INVOKABLE QVariant AttributesEx7() { return m_spellInfo->AttributesEx7; }
        Q_INVOKABLE QVariant Stances(quint8 index) { return m_spellInfo->Stances[index]; }
        Q_INVOKABLE QVariant StancesNot(quint8 index) { return m_spellInfo->StancesNot[index]; }
        Q_INVOKABLE QVariant Targets() { return m_spellInfo->Targets; }
        Q_INVOKABLE QVariant TargetCreatureType() { return m_spellInfo->TargetCreatureType; }
        Q_INVOKABLE QVariant RequiresSpellFocus() { return m_spellInfo->RequiresSpellFocus; }
        Q_INVOKABLE QVariant FacingCasterFlags() { return m_spellInfo->FacingCasterFlags; }
        Q_INVOKABLE QVariant CasterAuraState() { return m_spellInfo->CasterAuraState; }
        Q_INVOKABLE QVariant TargetAuraState() { return m_spellInfo->TargetAuraState; }
        Q_INVOKABLE QVariant CasterAuraStateNot() { return m_spellInfo->CasterAuraStateNot; }
        Q_INVOKABLE QVariant TargetAuraStateNot() { return m_spellInfo->TargetAuraStateNot; }
        Q_INVOKABLE QVariant CasterAuraSpell() { return m_spellInfo->CasterAuraSpell; }
        Q_INVOKABLE QVariant TargetAuraSpell() { return m_spellInfo->TargetAuraSpell; }
        Q_INVOKABLE QVariant ExcludeCasterAuraSpell() { return m_spellInfo->ExcludeCasterAuraSpell; }
        Q_INVOKABLE QVariant ExcludeTargetAuraSpell() { return m_spellInfo->ExcludeTargetAuraSpell; }
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
        Q_INVOKABLE QVariant TotemCategory(quint8 index) { return m_spellInfo->TotemCategory[index]; }
        Q_INVOKABLE QVariant Reagent(quint8 index) { return m_spellInfo->Reagent[index]; }
        Q_INVOKABLE QVariant ReagentCount(quint8 index) { return m_spellInfo->ReagentCount[index]; }
        Q_INVOKABLE QVariant EquippedItemClass() { return m_spellInfo->EquippedItemClass; }
        Q_INVOKABLE QVariant EquippedItemSubClassMask() { return m_spellInfo->EquippedItemSubClassMask; }
        Q_INVOKABLE QVariant EquippedItemInventoryTypeMask() { return m_spellInfo->EquippedItemInventoryTypeMask; }
        Q_INVOKABLE QVariant Effect(quint8 index) { return m_spellInfo->Effect[index]; }
        Q_INVOKABLE QVariant EffectDieSides(quint8 index) { return m_spellInfo->EffectDieSides[index]; }
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
        Q_INVOKABLE QVariant EffectMiscValueB(quint8 index) { return m_spellInfo->EffectMiscValueB[index]; }
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
        Q_INVOKABLE QVariant EffectSpellClassMaskA(quint8 index) { return m_spellInfo->EffectSpellClassMaskA[index]; }
        Q_INVOKABLE QVariant EffectSpellClassMaskB(quint8 index) { return m_spellInfo->EffectSpellClassMaskB[index]; }
        Q_INVOKABLE QVariant EffectSpellClassMaskC(quint8 index) { return m_spellInfo->EffectSpellClassMaskC[index]; }
        Q_INVOKABLE QVariant SpellFamilyFlags(quint8 index) { return m_spellInfo->SpellFamilyFlags[index]; }
        Q_INVOKABLE QVariant MaxAffectedTargets() { return m_spellInfo->MaxAffectedTargets; }
        Q_INVOKABLE QVariant DamageClass() { return m_spellInfo->DamageClass; }
        Q_INVOKABLE QVariant PreventionType() { return m_spellInfo->PreventionType; }
        Q_INVOKABLE QVariant StanceBarOrder() { return m_spellInfo->StanceBarOrder; }
        Q_INVOKABLE QVariant DamageMultiplier(quint8 index) { return m_spellInfo->DamageMultiplier[index]; }
        Q_INVOKABLE QVariant MinFactionId() { return m_spellInfo->MinFactionId; }
        Q_INVOKABLE QVariant MinReputation() { return m_spellInfo->MinReputation; }
        Q_INVOKABLE QVariant RequiredAuraVision() { return m_spellInfo->RequiredAuraVision; }
        Q_INVOKABLE QVariant AreaGroupId() { return m_spellInfo->AreaGroupId; }
        Q_INVOKABLE QVariant SchoolMask() { return m_spellInfo->SchoolMask; }
        Q_INVOKABLE QVariant RuneCostId() { return m_spellInfo->RuneCostId; }
        Q_INVOKABLE QVariant SpellMissileId() { return m_spellInfo->SpellMissileId; }
        Q_INVOKABLE QVariant PowerDisplayId() { return m_spellInfo->PowerDisplayId; }
        Q_INVOKABLE QVariant Unk3(quint8 index) { return m_spellInfo->Unk3[index]; }
        Q_INVOKABLE QVariant SpellDescriptionVariableId() { return m_spellInfo->SpellDescriptionVariableId; }
        Q_INVOKABLE QVariant SpellDifficultyId() { return m_spellInfo->SpellDifficultyId; }

        quint8 Stances() { return 2; }
        quint8 StancesNot() { return 2; }
        quint8 Totem() { return 2; }
        quint8 TotemCategory() { return 2; }
        quint8 Reagent() { return 8; }
        quint8 ReagentCount() { return 8; }
        quint8 Effect() { return 3; }
        quint8 EffectDieSides() { return 3; }
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
        quint8 EffectMiscValueB() { return 3; }
        quint8 EffectTriggerSpell() { return 3; }
        quint8 EffectPointsPerComboPoint() { return 3; }
        quint8 EffectSpellClassMaskA() { return 3; }
        quint8 EffectSpellClassMaskB() { return 3; }
        quint8 EffectSpellClassMaskC() { return 3; }
        quint8 SpellFamilyFlags() { return 3; }
        quint8 SpellVisual() { return 2; }
        quint8 DamageMultiplier() { return 3; }
        quint8 Unk3() { return 3; }

    private:
        SpellEntry const* m_spellInfo;

        Q_PROPERTY(quint8 Stances READ Stances)
        Q_PROPERTY(quint8 StancesNot READ StancesNot)
        Q_PROPERTY(quint8 Totem READ Totem)
        Q_PROPERTY(quint8 TotemCategory READ TotemCategory)
        Q_PROPERTY(quint8 Reagent READ Reagent)
        Q_PROPERTY(quint8 ReagentCount READ ReagentCount)
        Q_PROPERTY(quint8 Effect READ Effect)
        Q_PROPERTY(quint8 EffectDieSides READ EffectDieSides)
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
        Q_PROPERTY(quint8 EffectMiscValueB READ EffectMiscValueB)
        Q_PROPERTY(quint8 EffectTriggerSpell READ EffectTriggerSpell)
        Q_PROPERTY(quint8 EffectPointsPerComboPoint READ EffectPointsPerComboPoint)
        Q_PROPERTY(quint8 EffectSpellClassMaskA READ EffectSpellClassMaskA)
        Q_PROPERTY(quint8 EffectSpellClassMaskB READ EffectSpellClassMaskB)
        Q_PROPERTY(quint8 EffectSpellClassMaskC READ EffectSpellClassMaskC)
        Q_PROPERTY(quint8 SpellFamilyFlags READ SpellFamilyFlags)
        Q_PROPERTY(quint8 SpellVisual READ SpellVisual)
        Q_PROPERTY(quint8 DamageMultiplier READ DamageMultiplier)
        Q_PROPERTY(quint8 Unk3 READ Unk3)
};

#endif // SWSEARCH_H

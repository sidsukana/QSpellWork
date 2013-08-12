#ifndef SWSEARCH_H
#define SWSEARCH_H

#include "SWObject.h"
#include "DBC/DBCStores.h"

#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValue>
#include <QtScript/QScriptValueList>

class SWObject;
class SWMainForm;

class MetaSpell : public QObject
{
    Q_OBJECT
    
    public:
        MetaSpell();
        
        void setSpell(SpellEntry const* spellInfo) { m_spellInfo = spellInfo; }
        
        quint32 Id() { return m_spellInfo->Id; }
        quint32 Category() { return m_spellInfo->Category; }
        quint32 Dispel() { return m_spellInfo->Dispel; }
        quint32 Mechanic() { return m_spellInfo->Mechanic; }
        quint32 Attributes() { return m_spellInfo->Attributes; }
        quint32 AttributesEx1() { return m_spellInfo->AttributesEx1; }
        quint32 AttributesEx2() { return m_spellInfo->AttributesEx2; }
        quint32 AttributesEx3() { return m_spellInfo->AttributesEx3; }
        quint32 AttributesEx4() { return m_spellInfo->AttributesEx4; }
        quint32 AttributesEx5() { return m_spellInfo->AttributesEx5; }
        quint32 AttributesEx6() { return m_spellInfo->AttributesEx6; }
        quint32 AttributesEx7() { return m_spellInfo->AttributesEx7; }
        quint32 Stances(quint8 index) { return m_spellInfo->Stances[index]; }
        quint32 StancesNot(quint8 index) { return m_spellInfo->StancesNot[index]; }
        quint32 Targets() { return m_spellInfo->Targets; }
        quint32 TargetCreatureType() { return m_spellInfo->TargetCreatureType; }
        quint32 RequiresSpellFocus() { return m_spellInfo->RequiresSpellFocus; }
        quint32 FacingCasterFlags() { return m_spellInfo->FacingCasterFlags; }
        quint32 CasterAuraState() { return m_spellInfo->CasterAuraState; }
        quint32 TargetAuraState() { return m_spellInfo->TargetAuraState; }
        quint32 CasterAuraStateNot() { return m_spellInfo->CasterAuraStateNot; }
        quint32 TargetAuraStateNot() { return m_spellInfo->TargetAuraStateNot; }
        quint32 CasterAuraSpell() { return m_spellInfo->CasterAuraSpell; }
        quint32 TargetAuraSpell() { return m_spellInfo->TargetAuraSpell; }
        quint32 ExcludeCasterAuraSpell() { return m_spellInfo->ExcludeCasterAuraSpell; }
        quint32 ExcludeTargetAuraSpell() { return m_spellInfo->ExcludeTargetAuraSpell; }
        quint32 CastingTimeIndex() { return m_spellInfo->CastingTimeIndex; }
        quint32 RecoveryTime() { return m_spellInfo->RecoveryTime; }
        quint32 CategoryRecoveryTime() { return m_spellInfo->CategoryRecoveryTime; }
        quint32 InterruptFlags() { return m_spellInfo->InterruptFlags; }
        quint32 AuraInterruptFlags() { return m_spellInfo->AuraInterruptFlags; }
        quint32 ChannelInterruptFlags() { return m_spellInfo->ChannelInterruptFlags; }
        quint32 ProcFlags() { return m_spellInfo->ProcFlags; }
        quint32 ProcChance() { return m_spellInfo->ProcChance; }
        quint32 ProcCharges() { return m_spellInfo->ProcCharges; }
        quint32 MaxLevel() { return m_spellInfo->MaxLevel; }
        quint32 BaseLevel() { return m_spellInfo->BaseLevel; }
        quint32 SpellLevel() { return m_spellInfo->SpellLevel; }
        quint32 DurationIndex() { return m_spellInfo->DurationIndex; }
        qint32 PowerType() { return m_spellInfo->PowerType; }
        quint32 ManaCost() { return m_spellInfo->ManaCost; }
        quint32 ManaCostPerlevel() { return m_spellInfo->ManaCostPerlevel; }
        quint32 ManaPerSecond() { return m_spellInfo->ManaPerSecond; }
        quint32 ManaPerSecondPerLevel() { return m_spellInfo->ManaPerSecondPerLevel; }
        quint32 RangeIndex() { return m_spellInfo->RangeIndex; }
        float Speed() { return m_spellInfo->Speed; }
        quint32 ModalNextSpell() { return m_spellInfo->ModalNextSpell; }
        quint32 StackAmount() { return m_spellInfo->StackAmount; }
        quint32 Totem(quint8 index) { return m_spellInfo->Totem[index]; }
        qint32 Reagent(quint8 index) { return m_spellInfo->Reagent[index]; }
        quint32 ReagentCount(quint8 index) { return m_spellInfo->ReagentCount[index]; }
        qint32 EquippedItemClass() { return m_spellInfo->EquippedItemClass; }
        qint32 EquippedItemSubClassMask() { return m_spellInfo->EquippedItemSubClassMask; }
        qint32 EquippedItemInventoryTypeMask() { return m_spellInfo->EquippedItemInventoryTypeMask; }
        quint32 Effect(quint8 index) { return m_spellInfo->Effect[index]; }
        qint32 EffectDieSides(quint8 index) { return m_spellInfo->EffectDieSides[index]; }
        float EffectRealPointsPerLevel(quint8 index) { return m_spellInfo->EffectRealPointsPerLevel[index]; }
        qint32 EffectBasePoints(quint8 index) { return m_spellInfo->EffectBasePoints[index]; }
        quint32 EffectMechanic(quint8 index) { return m_spellInfo->EffectMechanic[index]; }
        quint32 EffectImplicitTargetA(quint8 index) { return m_spellInfo->EffectImplicitTargetA[index]; }
        quint32 EffectImplicitTargetB(quint8 index) { return m_spellInfo->EffectImplicitTargetB[index]; }
        quint32 EffectRadiusIndex(quint8 index) { return m_spellInfo->EffectRadiusIndex[index]; }
        quint32 EffectApplyAuraName(quint8 index) { return m_spellInfo->EffectApplyAuraName[index]; }
        quint32 EffectAmplitude(quint8 index) { return m_spellInfo->EffectAmplitude[index]; }
        float EffectMultipleValue(quint8 index) { return m_spellInfo->EffectMultipleValue[index]; }
        quint32 EffectChainTarget(quint8 index) { return m_spellInfo->EffectChainTarget[index]; }
        quint32 EffectItemType(quint8 index) { return m_spellInfo->EffectItemType[index]; }
        qint32 EffectMiscValue(quint8 index) { return m_spellInfo->EffectMiscValue[index]; }
        qint32 EffectMiscValueB(quint8 index) { return m_spellInfo->EffectMiscValueB[index]; }
        quint32 EffectTriggerSpell(quint8 index) { return m_spellInfo->EffectTriggerSpell[index]; }
        float EffectPointsPerComboPoint(quint8 index) { return m_spellInfo->EffectPointsPerComboPoint[index]; }
        quint32 EffectSpellClassMaskA(quint8 index) { return m_spellInfo->EffectSpellClassMaskA[index]; }
        quint32 EffectSpellClassMaskB(quint8 index) { return m_spellInfo->EffectSpellClassMaskB[index]; }
        quint32 EffectSpellClassMaskC(quint8 index) { return m_spellInfo->EffectSpellClassMaskC[index]; }
        quint32 SpellVisual(quint8 index) { return m_spellInfo->SpellVisual[index]; }
        quint32 SpellIconId() { return m_spellInfo->SpellIconId; }
        quint32 ActiveIconId() { return m_spellInfo->ActiveIconId; }
        quint32 SpellPriority() { return m_spellInfo->SpellPriority; }
        QString SpellName() { return QString::fromUtf8(m_spellInfo->SpellName[Locale]); }
        QString Rank() { return QString::fromUtf8(m_spellInfo->Rank[Locale]); }
        QString Description() { return QString::fromUtf8(m_spellInfo->Description[Locale]); }
        QString ToolTip() { return QString::fromUtf8(m_spellInfo->ToolTip[Locale]); }
        quint32 SpellNameFlag() { return m_spellInfo->SpellNameFlag; }
        quint32 RankFlags() { return m_spellInfo->RankFlags; }
        quint32 DescriptionFlags() { return m_spellInfo->DescriptionFlags; }
        quint32 ToolTipFlags() { return m_spellInfo->ToolTipFlags; }
        quint32 ManaCostPercentage() { return m_spellInfo->ManaCostPercentage; }
        quint32 StartRecoveryCategory() { return m_spellInfo->StartRecoveryCategory; }
        quint32 StartRecoveryTime() { return m_spellInfo->StartRecoveryTime; }
        quint32 MaxTargetLevel() { return m_spellInfo->MaxTargetLevel; }
        quint32 SpellFamilyName() { return m_spellInfo->SpellFamilyName; }
        quint32 SpellFamilyFlags(quint8 index) { return m_spellInfo->SpellFamilyFlags[index]; }
        quint32 MaxAffectedTargets() { return m_spellInfo->MaxAffectedTargets; }
        quint32 DamageClass() { return m_spellInfo->DamageClass; }
        quint32 PreventionType() { return m_spellInfo->PreventionType; }
        qint32 StanceBarOrder() { return m_spellInfo->StanceBarOrder; }
        float DamageMultiplier(quint8 index) { return m_spellInfo->DamageMultiplier[index]; }
        quint32 MinFactionId() { return m_spellInfo->MinFactionId; }
        quint32 MinReputation() { return m_spellInfo->MinReputation; }
        quint32 RequiredAuraVision() { return m_spellInfo->RequiredAuraVision; }
        qint32 TotemCategory(quint8 index) { return m_spellInfo->TotemCategory[index]; }
        quint32 AreaGroupId() { return m_spellInfo->AreaGroupId; }
        quint32 SchoolMask() { return m_spellInfo->SchoolMask; }
        quint32 RuneCostId() { return m_spellInfo->RuneCostId; }
        quint32 SpellMissileId() { return m_spellInfo->SpellMissileId; }
        quint32 PowerDisplayId() { return m_spellInfo->PowerDisplayId; }
        float Unk3(quint8 index) { return m_spellInfo->Unk3[index]; }
        quint32 SpellDescriptionVariableId() { return m_spellInfo->SpellDescriptionVariableId; }
        quint32 SpellDifficultyId() { return m_spellInfo->SpellDifficultyId; }

    private:
        SpellEntry const* m_spellInfo;
        
        Q_PROPERTY(quint32 Id READ Id)
        Q_PROPERTY(quint32 Category READ Category)
        Q_PROPERTY(quint32 Dispel READ Dispel)
        Q_PROPERTY(quint32 Mechanic READ Mechanic)
        Q_PROPERTY(quint32 Attributes READ Attributes)
        Q_PROPERTY(quint32 AttributesEx1 READ AttributesEx1)
        Q_PROPERTY(quint32 AttributesEx2 READ AttributesEx2)
        Q_PROPERTY(quint32 AttributesEx3 READ AttributesEx3)
        Q_PROPERTY(quint32 AttributesEx4 READ AttributesEx4)
        Q_PROPERTY(quint32 AttributesEx5 READ AttributesEx5)
        Q_PROPERTY(quint32 AttributesEx6 READ AttributesEx6)
        Q_PROPERTY(quint32 AttributesEx7 READ AttributesEx7)
        Q_PROPERTY(quint32 Targets READ Targets)
        Q_PROPERTY(quint32 TargetCreatureType READ TargetCreatureType)
        Q_PROPERTY(quint32 RequiresSpellFocus READ RequiresSpellFocus)
        Q_PROPERTY(quint32 FacingCasterFlags READ FacingCasterFlags)
        Q_PROPERTY(quint32 CasterAuraState READ CasterAuraState)
        Q_PROPERTY(quint32 TargetAuraState READ TargetAuraState)
        Q_PROPERTY(quint32 CasterAuraStateNot READ CasterAuraStateNot)
        Q_PROPERTY(quint32 TargetAuraStateNot READ TargetAuraStateNot)
        Q_PROPERTY(quint32 CasterAuraSpell READ CasterAuraSpell)
        Q_PROPERTY(quint32 TargetAuraSpell READ TargetAuraSpell)
        Q_PROPERTY(quint32 ExcludeCasterAuraSpell READ ExcludeCasterAuraSpell)
        Q_PROPERTY(quint32 ExcludeTargetAuraSpell READ ExcludeTargetAuraSpell)
        Q_PROPERTY(quint32 CastingTimeIndex READ CastingTimeIndex)
        Q_PROPERTY(quint32 RecoveryTime READ RecoveryTime)
        Q_PROPERTY(quint32 CategoryRecoveryTime READ CategoryRecoveryTime)
        Q_PROPERTY(quint32 InterruptFlags READ InterruptFlags)
        Q_PROPERTY(quint32 AuraInterruptFlags READ AuraInterruptFlags)
        Q_PROPERTY(quint32 ChannelInterruptFlags READ ChannelInterruptFlags)
        Q_PROPERTY(quint32 ProcFlags READ ProcFlags)
        Q_PROPERTY(quint32 ProcChance READ ProcChance)
        Q_PROPERTY(quint32 ProcCharges READ ProcCharges)
        Q_PROPERTY(quint32 MaxLevel READ MaxLevel)
        Q_PROPERTY(quint32 BaseLevel READ BaseLevel)
        Q_PROPERTY(quint32 SpellLevel READ SpellLevel)
        Q_PROPERTY(quint32 DurationIndex READ DurationIndex)
        Q_PROPERTY(qint32 PowerType READ PowerType)
        Q_PROPERTY(quint32 ManaCost READ ManaCost)
        Q_PROPERTY(quint32 ManaCostPerlevel READ ManaCostPerlevel)
        Q_PROPERTY(quint32 ManaPerSecond READ ManaPerSecond)
        Q_PROPERTY(quint32 ManaPerSecondPerLevel READ ManaPerSecondPerLevel)
        Q_PROPERTY(quint32 RangeIndex READ RangeIndex)
        Q_PROPERTY(float Speed READ Speed)
        Q_PROPERTY(quint32 ModalNextSpell READ ModalNextSpell)
        Q_PROPERTY(quint32 StackAmount READ StackAmount)
        Q_PROPERTY(qint32 EquippedItemClass READ EquippedItemClass)
        Q_PROPERTY(qint32 EquippedItemSubClassMask READ EquippedItemSubClassMask)
        Q_PROPERTY(qint32 EquippedItemInventoryTypeMask READ EquippedItemInventoryTypeMask)
        Q_PROPERTY(quint32 SpellIconId READ SpellIconId)
        Q_PROPERTY(quint32 ActiveIconId READ ActiveIconId)
        Q_PROPERTY(quint32 SpellPriority READ SpellPriority)
        Q_PROPERTY(QString SpellName READ SpellName)
        Q_PROPERTY(QString Rank READ Rank)
        Q_PROPERTY(QString Description READ Description)
        Q_PROPERTY(QString ToolTip READ ToolTip)
        Q_PROPERTY(quint32 SpellNameFlag READ SpellNameFlag)
        Q_PROPERTY(quint32 RankFlags READ RankFlags)
        Q_PROPERTY(quint32 DescriptionFlags READ DescriptionFlags)
        Q_PROPERTY(quint32 ToolTipFlags READ ToolTipFlags)
        Q_PROPERTY(quint32 ManaCostPercentage READ ManaCostPercentage)
        Q_PROPERTY(quint32 StartRecoveryCategory READ StartRecoveryCategory)
        Q_PROPERTY(quint32 StartRecoveryTime READ StartRecoveryTime)
        Q_PROPERTY(quint32 MaxTargetLevel READ MaxTargetLevel)
        Q_PROPERTY(quint32 SpellFamilyName READ SpellFamilyName)
        Q_PROPERTY(quint32 MaxAffectedTargets READ MaxAffectedTargets)
        Q_PROPERTY(quint32 DamageClass READ DamageClass)
        Q_PROPERTY(quint32 PreventionType READ PreventionType)
        Q_PROPERTY(qint32 StanceBarOrder READ StanceBarOrder)
        Q_PROPERTY(quint32 MinFactionId READ MinFactionId)
        Q_PROPERTY(quint32 MinReputation READ MinReputation)
        Q_PROPERTY(quint32 RequiredAuraVision READ RequiredAuraVision)
        Q_PROPERTY(quint32 AreaGroupId READ AreaGroupId)
        Q_PROPERTY(quint32 SchoolMask READ SchoolMask)
        Q_PROPERTY(quint32 RuneCostId READ RuneCostId)
        Q_PROPERTY(quint32 SpellMissileId READ SpellMissileId)
        Q_PROPERTY(quint32 PowerDisplayId READ PowerDisplayId)
        Q_PROPERTY(quint32 SpellDescriptionVariableId READ SpellDescriptionVariableId)
        Q_PROPERTY(quint32 SpellDifficultyId READ SpellDifficultyId)
};

class SWSearch : public QObject
{
    public:
        SWSearch(SWObject* sw, QObject* parent = NULL);
        ~SWSearch();

        void search();
        bool hasValue(SpellEntry const* spellInfo);

    private:
        SWObject* m_sw;
        SWMainForm* m_form;
        QScriptEngine* m_scriptEngine;
        QScriptValue m_script;
};

#endif // SWSEARCH_H

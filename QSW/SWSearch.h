#ifndef SWSEARCH_H
#define SWSEARCH_H

#include <QScriptEngine>
#include <QScriptValue>
#include <QScriptValueList>

#include "SWDefines.h"
#include "SWObject.h"
#include "dbc/DBCStructure.h"
 
class SWObject;
class SWMainForm;

class MetaSpell : public QObject
{
    Q_OBJECT

    public:
        MetaSpell();

        void setSpell(Spell::entry const* spellInfo) { m_spellInfo = spellInfo; }

    public slots:
        quint32 Id() { return m_spellInfo->id; }
        quint32 School() { return m_spellInfo->school; }
        quint32 Category() { return m_spellInfo->category; }
        quint32 CastUI() { return m_spellInfo->castUI; }
        quint32 Dispel() { return m_spellInfo->dispel; }
        quint32 Mechanic() { return m_spellInfo->mechanic; }
        quint32 Attributes() { return m_spellInfo->attributes; }
        quint32 AttributesEx1() { return m_spellInfo->attributesEx1; }
        quint32 AttributesEx2() { return m_spellInfo->attributesEx2; }
        quint32 AttributesEx3() { return m_spellInfo->attributesEx3; }
        quint32 AttributesEx4() { return m_spellInfo->attributesEx4; }
        quint32 Stances() { return m_spellInfo->stances; }
        quint32 StancesNot() { return m_spellInfo->stancesNot; }
        quint32 Targets() { return m_spellInfo->targets; }
        quint32 TargetCreatureType() { return m_spellInfo->targetCreatureType; }
        quint32 RequiresSpellFocus() { return m_spellInfo->requiresSpellFocus; }
        quint32 CasterAuraState() { return m_spellInfo->casterAuraState; }
        quint32 TargetAuraState() { return m_spellInfo->targetAuraState; }
        quint32 CastingTimeIndex() { return m_spellInfo->castingTimeIndex; }
        quint32 RecoveryTime() { return m_spellInfo->recoveryTime; }
        quint32 CategoryRecoveryTime() { return m_spellInfo->categoryRecoveryTime; }
        quint32 InterruptFlags() { return m_spellInfo->interruptFlags; }
        quint32 AuraInterruptFlags() { return m_spellInfo->auraInterruptFlags; }
        quint32 ChannelInterruptFlags() { return m_spellInfo->channelInterruptFlags; }
        quint32 ProcFlags() { return m_spellInfo->procFlags; }
        quint32 ProcChance() { return m_spellInfo->procChance; }
        quint32 ProcCharges() { return m_spellInfo->procCharges; }
        quint32 MaxLevel() { return m_spellInfo->maxLevel; }
        quint32 BaseLevel() { return m_spellInfo->baseLevel; }
        quint32 SpellLevel() { return m_spellInfo->spellLevel; }
        quint32 DurationIndex() { return m_spellInfo->durationIndex; }
        qint32 PowerType() { return m_spellInfo->powerType; }
        quint32 ManaCost() { return m_spellInfo->manaCost; }
        quint32 ManaCostPerlevel() { return m_spellInfo->manaCostPerlevel; }
        quint32 ManaPerSecond() { return m_spellInfo->manaPerSecond; }
        quint32 ManaPerSecondPerLevel() { return m_spellInfo->manaPerSecondPerLevel; }
        quint32 RangeIndex() { return m_spellInfo->rangeIndex; }
        float Speed() { return m_spellInfo->speed; }
        quint32 ModalNextSpell() { return m_spellInfo->modalNextSpell; }
        quint32 StackAmount() { return m_spellInfo->stackAmount; }
        quint32 Totem(quint8 index) { return m_spellInfo->totem[index]; }
        qint32 Reagent(quint8 index) { return m_spellInfo->reagent[index]; }
        quint32 ReagentCount(quint8 index) { return m_spellInfo->reagentCount[index]; }
        qint32 EquippedItemClass() { return m_spellInfo->equippedItemClass; }
        qint32 EquippedItemSubClassMask() { return m_spellInfo->equippedItemSubClassMask; }
        qint32 EquippedItemInventoryTypeMask() { return m_spellInfo->equippedItemInventoryTypeMask; }
        quint32 Effect(quint8 index) { return m_spellInfo->effect[index]; }
        quint32 EffectDieSides(quint8 index) { return m_spellInfo->effectDieSides[index]; }
        quint32 EffectBaseDice(quint8 index) { return m_spellInfo->effectBaseDice[index]; }
        float EffectDicePerLevel(quint8 index) { return m_spellInfo->effectDicePerLevel[index]; }
        float EffectRealPointsPerLevel(quint8 index) { return m_spellInfo->effectRealPointsPerLevel[index]; }
        qint32 EffectBasePoints(quint8 index) { return m_spellInfo->effectBasePoints[index]; }
        quint32 EffectMechanic(quint8 index) { return m_spellInfo->effectMechanic[index]; }
        quint32 EffectImplicitTargetA(quint8 index) { return m_spellInfo->effectImplicitTargetA[index]; }
        quint32 EffectImplicitTargetB(quint8 index) { return m_spellInfo->effectImplicitTargetB[index]; }
        quint32 EffectRadiusIndex(quint8 index) { return m_spellInfo->effectRadiusIndex[index]; }
        quint32 EffectApplyAuraName(quint8 index) { return m_spellInfo->effectApplyAuraName[index]; }
        quint32 EffectAmplitude(quint8 index) { return m_spellInfo->effectAmplitude[index]; }
        float EffectMultipleValue(quint8 index) { return m_spellInfo->effectMultipleValue[index]; }
        quint32 EffectChainTarget(quint8 index) { return m_spellInfo->effectChainTarget[index]; }
        quint32 EffectItemType(quint8 index) { return m_spellInfo->effectItemType[index]; }
        qint32 EffectMiscValue(quint8 index) { return m_spellInfo->effectMiscValue[index]; }
        quint32 EffectTriggerSpell(quint8 index) { return m_spellInfo->effectTriggerSpell[index]; }
        float EffectPointsPerComboPoint(quint8 index) { return m_spellInfo->effectPointsPerComboPoint[index]; }
        quint32 SpellVisual(quint8 index) { return m_spellInfo->spellVisual[index]; }
        quint32 SpellIconId() { return m_spellInfo->spellIconId; }
        quint32 ActiveIconId() { return m_spellInfo->activeIconId; }
        quint32 SpellPriority() { return m_spellInfo->spellPriority; }
        QString SpellName() { return QString::fromUtf8(m_spellInfo->spellName[QSW::Locale]); }
        QString Rank() { return QString::fromUtf8(m_spellInfo->rank[QSW::Locale]); }
        QString Description() { return QString::fromUtf8(m_spellInfo->description[QSW::Locale]); }
        QString ToolTip() { return QString::fromUtf8(m_spellInfo->toolTip[QSW::Locale]); }
        quint32 SpellNameFlag() { return m_spellInfo->spellNameFlag; }
        quint32 RankFlags() { return m_spellInfo->rankFlags; }
        quint32 DescriptionFlags() { return m_spellInfo->descriptionFlags; }
        quint32 ToolTipFlags() { return m_spellInfo->toolTipFlags; }
        quint32 ManaCostPercentage() { return m_spellInfo->manaCostPercentage; }
        quint32 StartRecoveryCategory() { return m_spellInfo->startRecoveryCategory; }
        quint32 StartRecoveryTime() { return m_spellInfo->startRecoveryTime; }
        quint32 MaxTargetLevel() { return m_spellInfo->maxTargetLevel; }
        quint32 SpellFamilyName() { return m_spellInfo->spellFamilyName; }
        quint64 SpellFamilyFlags() { return m_spellInfo->spellFamilyFlags; }
        quint32 MaxAffectedTargets() { return m_spellInfo->maxAffectedTargets; }
        quint32 DamageClass() { return m_spellInfo->damageClass; }
        quint32 PreventionType() { return m_spellInfo->preventionType; }
        qint32 StanceBarOrder() { return m_spellInfo->stanceBarOrder; }
        float DamageMultiplier(quint8 index) { return m_spellInfo->damageMultiplier[index]; }
        quint32 MinFactionId() { return m_spellInfo->minFactionId; }
        quint32 MinReputation() { return m_spellInfo->minReputation; }
        quint32 RequiredAuraVision() { return m_spellInfo->requiredAuraVision; }

    private:
        Spell::entry const* m_spellInfo;

        Q_PROPERTY(quint32 Id READ Id)
        Q_PROPERTY(quint32 School READ School)
        Q_PROPERTY(quint32 Category READ Category)
        Q_PROPERTY(quint32 CastUI READ CastUI)
        Q_PROPERTY(quint32 Dispel READ Dispel)
        Q_PROPERTY(quint32 Mechanic READ Mechanic)
        Q_PROPERTY(quint32 Attributes READ Attributes)
        Q_PROPERTY(quint32 AttributesEx1 READ AttributesEx1)
        Q_PROPERTY(quint32 AttributesEx2 READ AttributesEx2)
        Q_PROPERTY(quint32 AttributesEx3 READ AttributesEx3)
        Q_PROPERTY(quint32 AttributesEx4 READ AttributesEx4)
        Q_PROPERTY(quint32 Stances READ Stances)
        Q_PROPERTY(quint32 StancesNot READ StancesNot)
        Q_PROPERTY(quint32 Targets READ Targets)
        Q_PROPERTY(quint32 TargetCreatureType READ TargetCreatureType)
        Q_PROPERTY(quint32 RequiresSpellFocus READ RequiresSpellFocus)
        Q_PROPERTY(quint32 CasterAuraState READ CasterAuraState)
        Q_PROPERTY(quint32 TargetAuraState READ TargetAuraState)
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
        Q_PROPERTY(quint64 SpellFamilyFlags READ SpellFamilyFlags)
        Q_PROPERTY(quint32 MaxAffectedTargets READ MaxAffectedTargets)
        Q_PROPERTY(quint32 DamageClass READ DamageClass)
        Q_PROPERTY(quint32 PreventionType READ PreventionType)
        Q_PROPERTY(qint32 StanceBarOrder READ StanceBarOrder)
        Q_PROPERTY(quint32 MinFactionId READ MinFactionId)
        Q_PROPERTY(quint32 MinReputation READ MinReputation)
        Q_PROPERTY(quint32 RequiredAuraVision READ RequiredAuraVision)
};

class SWSearch : public QObject
{
public:
    SWSearch(SWObject* sw, QObject* parent = NULL);
    ~SWSearch();

    void search();
    bool hasValue(Spell::entry const* spellInfo);

private:
    SWObject* m_sw;
    SWMainForm* m_form;
    QScriptEngine* m_scriptEngine;
    QScriptValue m_script;
};

#endif // SWSEARCH_H
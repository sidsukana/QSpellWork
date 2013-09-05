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

    public slots:
        quint32 Id() { return m_spellInfo->Id; }
        quint32 Category() { return m_spellInfo->getCategory(); }
        quint32 Dispel() { return m_spellInfo->getDispel(); }
        quint32 Mechanic() { return m_spellInfo->getMechanic(); }
        quint32 Attributes() { return m_spellInfo->getAttributes(); }
        quint32 AttributesEx1() { return m_spellInfo->getAttributesEx1(); }
        quint32 AttributesEx2() { return m_spellInfo->getAttributesEx2(); }
        quint32 AttributesEx3() { return m_spellInfo->getAttributesEx3(); }
        quint32 AttributesEx4() { return m_spellInfo->getAttributesEx4(); }
        quint32 AttributesEx5() { return m_spellInfo->getAttributesEx5(); }
        quint32 AttributesEx6() { return m_spellInfo->getAttributesEx6(); }
        quint32 AttributesEx7() { return m_spellInfo->getAttributesEx7(); }
        quint32 AttributesEx8() { return m_spellInfo->getAttributesEx8(); }
        quint32 AttributesEx9() { return m_spellInfo->getAttributesEx9(); }
        quint32 AttributesEx10() { return m_spellInfo->getAttributesEx10(); }
        quint32 AttributesEx11() { return m_spellInfo->getAttributesEx11(); }
        quint32 Stances() { return m_spellInfo->getStances(); }
        quint32 StancesNot() { return m_spellInfo->getStancesNot(); }
        quint32 Targets() { return m_spellInfo->getTargets(); }
        quint32 TargetCreatureType() { return m_spellInfo->getTargetCreatureType(); }
        quint32 RequiresSpellFocus() { return m_spellInfo->getRequiresSpellFocus(); }
        quint32 FacingCasterFlags() { return m_spellInfo->getFacingCasterFlags(); }
        quint32 CasterAuraState() { return m_spellInfo->getCasterAuraState(); }
        quint32 TargetAuraState() { return m_spellInfo->getTargetAuraState(); }
        quint32 CasterAuraStateNot() { return m_spellInfo->getCasterAuraStateNot(); }
        quint32 TargetAuraStateNot() { return m_spellInfo->getTargetAuraStateNot(); }
        quint32 CasterAuraSpell() { return m_spellInfo->getCasterAuraSpell(); }
        quint32 TargetAuraSpell() { return m_spellInfo->getTargetAuraSpell(); }
        quint32 ExcludeCasterAuraSpell() { return m_spellInfo->getExcludeCasterAuraSpell(); }
        quint32 ExcludeTargetAuraSpell() { return m_spellInfo->getExcludeTargetAuraSpell(); }
        quint32 CastingTimeIndex() { return m_spellInfo->getCastingTimeIndex(); }
        quint32 RecoveryTime() { return m_spellInfo->getRecoveryTime(); }
        quint32 CategoryRecoveryTime() { return m_spellInfo->getCategoryRecoveryTime(); }
        quint32 InterruptFlags() { return m_spellInfo->getInterruptFlags(); }
        quint32 AuraInterruptFlags() { return m_spellInfo->getAuraInterruptFlags(); }
        quint32 ChannelInterruptFlags() { return m_spellInfo->getChannelInterruptFlags(); }
        quint32 ProcFlags() { return m_spellInfo->getProcFlags(); }
        quint32 ProcChance() { return m_spellInfo->getProcChance(); }
        quint32 ProcCharges() { return m_spellInfo->getProcCharges(); }
        quint32 MaxLevel() { return m_spellInfo->getMaxLevel(); }
        quint32 BaseLevel() { return m_spellInfo->getBaseLevel(); }
        quint32 SpellLevel() { return m_spellInfo->getSpellLevel(); }
        quint32 DurationIndex() { return m_spellInfo->getDurationIndex(); }
        qint32 PowerType() { return m_spellInfo->getPowerType(); }
        quint32 ManaCost() { return m_spellInfo->getManaCost(); }
        quint32 ManaCostPerLevel() { return m_spellInfo->getManaCostPerLevel(); }
        quint32 ManaPerSecond() { return m_spellInfo->getManaPerSecond(); }
        quint32 RangeIndex() { return m_spellInfo->getRangeIndex(); }
        float Speed() { return m_spellInfo->getSpeed(); }
        quint32 ModalNextSpell() { return m_spellInfo->getModalNextSpell(); }
        quint32 StackAmount() { return m_spellInfo->getStackAmount(); }
        quint32 Totem(quint8 index) { return m_spellInfo->getTotem(index); }
        qint32 TotemCategory(quint8 index) { return m_spellInfo->getTotemCategory(index); }
        qint32 Reagent(quint8 index) { return m_spellInfo->getReagent(index); }
        quint32 ReagentCount(quint8 index) { return m_spellInfo->getReagentCount(index); }
        qint32 EquippedItemClass() { return m_spellInfo->getEquippedItemClass(); }
        qint32 EquippedItemSubClassMask() { return m_spellInfo->getEquippedItemSubClassMask(); }
        qint32 EquippedItemInventoryTypeMask() { return m_spellInfo->getEquippedItemInventoryTypeMask(); }
        quint32 Effect(quint8 index) { return m_spellInfo->getEffect(index); }
        qint32 EffectDieSides(quint8 index) { return m_spellInfo->getEffectDieSides(index); }
        float EffectRealPointsPerLevel(quint8 index) { return m_spellInfo->getEffectRealPointsPerLevel(index); }
        qint32 EffectBasePoints(quint8 index) { return m_spellInfo->getEffectBasePoints(index); }
        quint32 EffectMechanic(quint8 index) { return m_spellInfo->getEffectMechanic(index); }
        quint32 EffectImplicitTargetA(quint8 index) { return m_spellInfo->getEffectImplicitTargetA(index); }
        quint32 EffectImplicitTargetB(quint8 index) { return m_spellInfo->getEffectImplicitTargetB(index); }
        quint32 EffectRadiusIndex(quint8 index) { return m_spellInfo->getEffectRadiusIndex(index); }
        quint32 EffectApplyAuraName(quint8 index) { return m_spellInfo->getEffectApplyAuraName(index); }
        quint32 EffectAmplitude(quint8 index) { return m_spellInfo->getEffectAmplitude(index); }
        quint32 EffectChainTarget(quint8 index) { return m_spellInfo->getEffectChainTarget(index); }
        quint32 EffectItemType(quint8 index) { return m_spellInfo->getEffectItemType(index); }
        qint32 EffectMiscValue(quint8 index) { return m_spellInfo->getEffectMiscValue(index); }
        qint32 EffectMiscValueB(quint8 index) { return m_spellInfo->getEffectMiscValueB(index); }
        quint32 EffectTriggerSpell(quint8 index) { return m_spellInfo->getEffectTriggerSpell(index); }
        float EffectPointsPerComboPoint(quint8 index) { return m_spellInfo->getEffectPointsPerComboPoint(index); }
        float EffectValueMultiplier(quint8 index) { return m_spellInfo->getEffectValueMultiplier(index); }
        quint32 SpellVisual(quint8 index) { return m_spellInfo->getSpellVisual(index); }
        quint32 SpellIconId() { return m_spellInfo->getSpellIconId(); }
        quint32 SpellBuffIconId() { return m_spellInfo->getSpellBuffIconId(); }
        QString SpellName() { return QString::fromUtf8(m_spellInfo->SpellName); }
        QString Rank() { return QString::fromUtf8(m_spellInfo->Rank); }
        QString Description() { return QString::fromUtf8(m_spellInfo->Description); }
        QString ToolTip() { return QString::fromUtf8(m_spellInfo->ToolTip); }
        quint32 ManaCostPercentage() { return m_spellInfo->getManaCostPercentage(); }
        quint32 StartRecoveryCategory() { return m_spellInfo->getStartRecoveryCategory(); }
        quint32 StartRecoveryTime() { return m_spellInfo->getStartRecoveryTime(); }
        quint32 MaxTargetLevel() { return m_spellInfo->getMaxTargetLevel(); }
        quint32 SpellFamilyName() { return m_spellInfo->getSpellFamilyName(); }
        quint32 EffectSpellClassMaskA(quint8 index) { return m_spellInfo->getEffectSpellClassMaskA(index); }
        quint32 EffectSpellClassMaskB(quint8 index) { return m_spellInfo->getEffectSpellClassMaskB(index); }
        quint32 EffectSpellClassMaskC(quint8 index) { return m_spellInfo->getEffectSpellClassMaskC(index); }
        quint32 SpellFamilyFlags(quint8 index) { return m_spellInfo->getSpellFamilyFlags(index); }
        quint32 MaxAffectedTargets() { return m_spellInfo->getMaxAffectedTargets(); }
        quint32 DamageClass() { return m_spellInfo->getDamageClass(); }
        quint32 PreventionType() { return m_spellInfo->getPreventionType(); }
        qint32 StanceBarOrder() { return m_spellInfo->getStanceBarOrder(); }
        float DamageMultiplier(quint8 index) { return m_spellInfo->getEffectDamageMultiplier(index); }
        quint32 MinFactionId() { return m_spellInfo->getMinFactionId(); }
        quint32 MinReputation() { return m_spellInfo->getMinReputation(); }
        quint32 RequiredAuraVision() { return m_spellInfo->getRequiredAuraVision(); }
        quint32 AreaGroupId() { return m_spellInfo->getAreaGroupId(); }
        quint32 SchoolMask() { return m_spellInfo->getSchoolMask(); }
        quint32 RuneCostId() { return m_spellInfo->RuneCostId; }
        quint32 SpellMissileId() { return m_spellInfo->SpellMissileId; }
        quint32 SpellDescriptionVariableId() { return m_spellInfo->SpellDescriptionVariableId; }

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
        Q_PROPERTY(quint32 AttributesEx8 READ AttributesEx8)
        Q_PROPERTY(quint32 AttributesEx9 READ AttributesEx9)
        Q_PROPERTY(quint32 AttributesEx10 READ AttributesEx10)
        Q_PROPERTY(quint32 AttributesEx11 READ AttributesEx11)
        Q_PROPERTY(quint32 Stances READ Stances)
        Q_PROPERTY(quint32 StancesNot READ StancesNot)
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
        Q_PROPERTY(quint32 ManaCostPerLevel READ ManaCostPerLevel)
        Q_PROPERTY(quint32 ManaPerSecond READ ManaPerSecond)
        Q_PROPERTY(quint32 RangeIndex READ RangeIndex)
        Q_PROPERTY(float Speed READ Speed)
        Q_PROPERTY(quint32 ModalNextSpell READ ModalNextSpell)
        Q_PROPERTY(quint32 StackAmount READ StackAmount)
        Q_PROPERTY(qint32 EquippedItemClass READ EquippedItemClass)
        Q_PROPERTY(qint32 EquippedItemSubClassMask READ EquippedItemSubClassMask)
        Q_PROPERTY(qint32 EquippedItemInventoryTypeMask READ EquippedItemInventoryTypeMask)
        Q_PROPERTY(quint32 SpellIconId READ SpellIconId)
        Q_PROPERTY(quint32 SpellBuffIconId READ SpellBuffIconId)
        Q_PROPERTY(QString SpellName READ SpellName)
        Q_PROPERTY(QString Rank READ Rank)
        Q_PROPERTY(QString Description READ Description)
        Q_PROPERTY(QString ToolTip READ ToolTip)
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
        Q_PROPERTY(quint32 SpellDescriptionVariableId READ SpellDescriptionVariableId)
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

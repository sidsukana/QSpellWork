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
        Q_INVOKABLE QVariant Category() { return m_spellInfo->getCategory(); }
        Q_INVOKABLE QVariant Dispel() { return m_spellInfo->getDispel(); }
        Q_INVOKABLE QVariant Mechanic() { return m_spellInfo->getMechanic(); }
        Q_INVOKABLE QVariant Attributes() { return m_spellInfo->getAttributes(); }
        Q_INVOKABLE QVariant AttributesEx1() { return m_spellInfo->getAttributesEx1(); }
        Q_INVOKABLE QVariant AttributesEx2() { return m_spellInfo->getAttributesEx2(); }
        Q_INVOKABLE QVariant AttributesEx3() { return m_spellInfo->getAttributesEx3(); }
        Q_INVOKABLE QVariant AttributesEx4() { return m_spellInfo->getAttributesEx4(); }
        Q_INVOKABLE QVariant AttributesEx5() { return m_spellInfo->getAttributesEx5(); }
        Q_INVOKABLE QVariant AttributesEx6() { return m_spellInfo->getAttributesEx6(); }
        Q_INVOKABLE QVariant AttributesEx7() { return m_spellInfo->getAttributesEx7(); }
        Q_INVOKABLE QVariant AttributesEx8() { return m_spellInfo->getAttributesEx8(); }
        Q_INVOKABLE QVariant AttributesEx9() { return m_spellInfo->getAttributesEx9(); }
        Q_INVOKABLE QVariant AttributesEx10() { return m_spellInfo->getAttributesEx10(); }
        Q_INVOKABLE QVariant AttributesEx11() { return m_spellInfo->getAttributesEx11(); }
        Q_INVOKABLE QVariant Stances() { return m_spellInfo->getStances(); }
        Q_INVOKABLE QVariant StancesNot() { return m_spellInfo->getStancesNot(); }
        Q_INVOKABLE QVariant Targets() { return m_spellInfo->getTargets(); }
        Q_INVOKABLE QVariant TargetCreatureType() { return m_spellInfo->getTargetCreatureType(); }
        Q_INVOKABLE QVariant RequiresSpellFocus() { return m_spellInfo->getRequiresSpellFocus(); }
        Q_INVOKABLE QVariant FacingCasterFlags() { return m_spellInfo->getFacingCasterFlags(); }
        Q_INVOKABLE QVariant CasterAuraState() { return m_spellInfo->getCasterAuraState(); }
        Q_INVOKABLE QVariant TargetAuraState() { return m_spellInfo->getTargetAuraState(); }
        Q_INVOKABLE QVariant CasterAuraStateNot() { return m_spellInfo->getCasterAuraStateNot(); }
        Q_INVOKABLE QVariant TargetAuraStateNot() { return m_spellInfo->getTargetAuraStateNot(); }
        Q_INVOKABLE QVariant CasterAuraSpell() { return m_spellInfo->getCasterAuraSpell(); }
        Q_INVOKABLE QVariant TargetAuraSpell() { return m_spellInfo->getTargetAuraSpell(); }
        Q_INVOKABLE QVariant ExcludeCasterAuraSpell() { return m_spellInfo->getExcludeCasterAuraSpell(); }
        Q_INVOKABLE QVariant ExcludeTargetAuraSpell() { return m_spellInfo->getExcludeTargetAuraSpell(); }
        Q_INVOKABLE QVariant CastingTimeIndex() { return m_spellInfo->getCastingTimeIndex(); }
        Q_INVOKABLE QVariant RecoveryTime() { return m_spellInfo->getRecoveryTime(); }
        Q_INVOKABLE QVariant CategoryRecoveryTime() { return m_spellInfo->getCategoryRecoveryTime(); }
        Q_INVOKABLE QVariant InterruptFlags() { return m_spellInfo->getInterruptFlags(); }
        Q_INVOKABLE QVariant AuraInterruptFlags() { return m_spellInfo->getAuraInterruptFlags(); }
        Q_INVOKABLE QVariant ChannelInterruptFlags() { return m_spellInfo->getChannelInterruptFlags(); }
        Q_INVOKABLE QVariant ProcFlags() { return m_spellInfo->getProcFlags(); }
        Q_INVOKABLE QVariant ProcChance() { return m_spellInfo->getProcChance(); }
        Q_INVOKABLE QVariant ProcCharges() { return m_spellInfo->getProcCharges(); }
        Q_INVOKABLE QVariant MaxLevel() { return m_spellInfo->getMaxLevel(); }
        Q_INVOKABLE QVariant BaseLevel() { return m_spellInfo->getBaseLevel(); }
        Q_INVOKABLE QVariant SpellLevel() { return m_spellInfo->getSpellLevel(); }
        Q_INVOKABLE QVariant DurationIndex() { return m_spellInfo->getDurationIndex(); }
        Q_INVOKABLE QVariant PowerType() { return m_spellInfo->getPowerType(); }
        Q_INVOKABLE QVariant ManaCost() { return m_spellInfo->getManaCost(); }
        Q_INVOKABLE QVariant ManaCostPerlevel() { return m_spellInfo->getManaCostPerLevel(); }
        Q_INVOKABLE QVariant ManaPerSecond() { return m_spellInfo->getManaPerSecond(); }
        Q_INVOKABLE QVariant RangeIndex() { return m_spellInfo->getRangeIndex(); }
        Q_INVOKABLE QVariant Speed() { return m_spellInfo->getSpeed(); }
        Q_INVOKABLE QVariant ModalNextSpell() { return m_spellInfo->getModalNextSpell(); }
        Q_INVOKABLE QVariant StackAmount() { return m_spellInfo->getStackAmount(); }
        Q_INVOKABLE QVariant Totem(quint8 index) { return m_spellInfo->getTotem(index); }
        Q_INVOKABLE QVariant TotemCategory(quint8 index) { return m_spellInfo->getTotemCategory(index); }
        Q_INVOKABLE QVariant Reagent(quint8 index) { return m_spellInfo->getReagent(index); }
        Q_INVOKABLE QVariant ReagentCount(quint8 index) { return m_spellInfo->getReagentCount(index); }
        Q_INVOKABLE QVariant EquippedItemClass() { return m_spellInfo->getEquippedItemClass(); }
        Q_INVOKABLE QVariant EquippedItemSubClassMask() { return m_spellInfo->getEquippedItemSubClassMask(); }
        Q_INVOKABLE QVariant EquippedItemInventoryTypeMask() { return m_spellInfo->getEquippedItemInventoryTypeMask(); }
        Q_INVOKABLE QVariant Effect(quint8 index) { return m_spellInfo->getEffect(index); }
        Q_INVOKABLE QVariant EffectDieSides(quint8 index) { return m_spellInfo->getEffectDieSides(index); }
        Q_INVOKABLE QVariant EffectRealPointsPerLevel(quint8 index) { return m_spellInfo->getEffectRealPointsPerLevel(index); }
        Q_INVOKABLE QVariant EffectBasePoints(quint8 index) { return m_spellInfo->getEffectBasePoints(index); }
        Q_INVOKABLE QVariant EffectMechanic(quint8 index) { return m_spellInfo->getEffectMechanic(index); }
        Q_INVOKABLE QVariant EffectImplicitTargetA(quint8 index) { return m_spellInfo->getEffectImplicitTargetA(index); }
        Q_INVOKABLE QVariant EffectImplicitTargetB(quint8 index) { return m_spellInfo->getEffectImplicitTargetB(index); }
        Q_INVOKABLE QVariant EffectRadiusIndex(quint8 index) { return m_spellInfo->getEffectRadiusIndex(index); }
        Q_INVOKABLE QVariant EffectApplyAuraName(quint8 index) { return m_spellInfo->getEffectApplyAuraName(index); }
        Q_INVOKABLE QVariant EffectAmplitude(quint8 index) { return m_spellInfo->getEffectAmplitude(index); }
        Q_INVOKABLE QVariant EffectChainTarget(quint8 index) { return m_spellInfo->getEffectChainTarget(index); }
        Q_INVOKABLE QVariant EffectItemType(quint8 index) { return m_spellInfo->getEffectItemType(index); }
        Q_INVOKABLE QVariant EffectMiscValue(quint8 index) { return m_spellInfo->getEffectMiscValue(index); }
        Q_INVOKABLE QVariant EffectMiscValueB(quint8 index) { return m_spellInfo->getEffectMiscValueB(index); }
        Q_INVOKABLE QVariant EffectTriggerSpell(quint8 index) { return m_spellInfo->getEffectTriggerSpell(index); }
        Q_INVOKABLE QVariant EffectPointsPerComboPoint(quint8 index) { return m_spellInfo->getEffectPointsPerComboPoint(index); }
        Q_INVOKABLE QVariant EffectValueMultiplier(quint8 index) { return m_spellInfo->getEffectValueMultiplier(index); }
        Q_INVOKABLE QVariant SpellVisual(quint8 index) { return m_spellInfo->getSpellVisual(index); }
        Q_INVOKABLE QVariant SpellIconId() { return m_spellInfo->getSpellIconId(); }
        Q_INVOKABLE QVariant SpellBuffIconId() { return m_spellInfo->getSpellBuffIconId(); }
        Q_INVOKABLE QVariant SpellName() { return QString::fromUtf8(m_spellInfo->SpellName); }
        Q_INVOKABLE QVariant Rank() { return QString::fromUtf8(m_spellInfo->Rank); }
        Q_INVOKABLE QVariant Description() { return QString::fromUtf8(m_spellInfo->Description); }
        Q_INVOKABLE QVariant ToolTip() { return QString::fromUtf8(m_spellInfo->ToolTip); }
        Q_INVOKABLE QVariant ManaCostPercentage() { return m_spellInfo->getManaCostPercentage(); }
        Q_INVOKABLE QVariant StartRecoveryCategory() { return m_spellInfo->getStartRecoveryCategory(); }
        Q_INVOKABLE QVariant StartRecoveryTime() { return m_spellInfo->getStartRecoveryTime(); }
        Q_INVOKABLE QVariant MaxTargetLevel() { return m_spellInfo->getMaxTargetLevel(); }
        Q_INVOKABLE QVariant SpellFamilyName() { return m_spellInfo->getSpellFamilyName(); }
        Q_INVOKABLE QVariant EffectSpellClassMaskA(quint8 index) { return m_spellInfo->getEffectSpellClassMaskA(index); }
        Q_INVOKABLE QVariant EffectSpellClassMaskB(quint8 index) { return m_spellInfo->getEffectSpellClassMaskB(index); }
        Q_INVOKABLE QVariant EffectSpellClassMaskC(quint8 index) { return m_spellInfo->getEffectSpellClassMaskC(index); }
        Q_INVOKABLE QVariant SpellFamilyFlags(quint8 index) { return m_spellInfo->getSpellFamilyFlags(index); }
        Q_INVOKABLE QVariant MaxAffectedTargets() { return m_spellInfo->getMaxAffectedTargets(); }
        Q_INVOKABLE QVariant DamageClass() { return m_spellInfo->getDamageClass(); }
        Q_INVOKABLE QVariant PreventionType() { return m_spellInfo->getPreventionType(); }
        Q_INVOKABLE QVariant StanceBarOrder() { return m_spellInfo->getStanceBarOrder(); }
        Q_INVOKABLE QVariant DamageMultiplier(quint8 index) { return m_spellInfo->getEffectDamageMultiplier(index); }
        Q_INVOKABLE QVariant MinFactionId() { return m_spellInfo->getMinFactionId(); }
        Q_INVOKABLE QVariant MinReputation() { return m_spellInfo->getMinReputation(); }
        Q_INVOKABLE QVariant RequiredAuraVision() { return m_spellInfo->getRequiredAuraVision(); }
        Q_INVOKABLE QVariant AreaGroupId() { return m_spellInfo->getAreaGroupId(); }
        Q_INVOKABLE QVariant SchoolMask() { return m_spellInfo->getSchoolMask(); }
        Q_INVOKABLE QVariant RuneCostId() { return m_spellInfo->RuneCostId; }
        Q_INVOKABLE QVariant SpellMissileId() { return m_spellInfo->SpellMissileId; }
        Q_INVOKABLE QVariant SpellDescriptionVariableId() { return m_spellInfo->SpellDescriptionVariableId; }

        quint8 Totem() { return 2; }
        quint8 TotemCategory() { return 2; }
        quint8 Reagent() { return 8; }
        quint8 ReagentCount() { return 8; }
        quint8 Effect() { return 3; }
        quint8 EffectDieSides() { return 3; }
        quint8 EffectRealPointsPerLevel() { return 3; }
        quint8 EffectBasePoints() { return 3; }
        quint8 EffectMechanic() { return 3; }
        quint8 EffectImplicitTargetA() { return 3; }
        quint8 EffectImplicitTargetB() { return 3; }
        quint8 EffectRadiusIndex() { return 3; }
        quint8 EffectApplyAuraName() { return 3; }
        quint8 EffectAmplitude() { return 3; }
        quint8 EffectChainTarget() { return 3; }
        quint8 EffectItemType() { return 3; }
        quint8 EffectMiscValue() { return 3; }
        quint8 EffectMiscValueB() { return 3; }
        quint8 EffectTriggerSpell() { return 3; }
        quint8 EffectPointsPerComboPoint() { return 3; }
        quint8 EffectValueMultiplier() { return 3; }
        quint8 EffectSpellClassMaskA() { return 3; }
        quint8 EffectSpellClassMaskB() { return 3; }
        quint8 EffectSpellClassMaskC() { return 3; }
        quint8 SpellFamilyFlags() { return 3; }
        quint8 SpellVisual() { return 2; }
        quint8 DamageMultiplier() { return 3; }

    private:
        SpellEntry const* m_spellInfo;

        Q_PROPERTY(quint8 Totem READ Totem)
        Q_PROPERTY(quint8 TotemCategory READ TotemCategory)
        Q_PROPERTY(quint8 Reagent READ Reagent)
        Q_PROPERTY(quint8 ReagentCount READ ReagentCount)
        Q_PROPERTY(quint8 Effect READ Effect)
        Q_PROPERTY(quint8 EffectDieSides READ EffectDieSides)
        Q_PROPERTY(quint8 EffectRealPointsPerLevel READ EffectRealPointsPerLevel)
        Q_PROPERTY(quint8 EffectBasePoints READ EffectBasePoints)
        Q_PROPERTY(quint8 EffectMechanic READ EffectMechanic)
        Q_PROPERTY(quint8 EffectImplicitTargetA READ EffectImplicitTargetA)
        Q_PROPERTY(quint8 EffectImplicitTargetB READ EffectImplicitTargetB)
        Q_PROPERTY(quint8 EffectRadiusIndex READ EffectRadiusIndex)
        Q_PROPERTY(quint8 EffectApplyAuraName READ EffectApplyAuraName)
        Q_PROPERTY(quint8 EffectAmplitude READ EffectAmplitude)
        Q_PROPERTY(quint8 EffectValueMultiplier READ EffectValueMultiplier)
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
};

#endif // SWSEARCH_H

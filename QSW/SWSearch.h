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
    bool hasValue(QString name, QString value, SpellEntry const* spellInfo);

private:
    SWObject* m_sw;
    SWMainForm*   m_form;
};

class MetaSpell : public QObject
{
    Q_OBJECT

public:
    MetaSpell(SpellEntry const* spellInfo);
    ~MetaSpell();

    quint32 getId() { return m_spellInfo->Id; }
    quint32 getCategory() { return m_spellInfo->Category; }
    quint32 getCastUI() { return m_spellInfo->CastUI; }
    quint32 getDispel() { return m_spellInfo->Dispel; }
    quint32 getMechanic() { return m_spellInfo->Mechanic; }
    quint32 getAttributes() { return m_spellInfo->Attributes; }
    quint32 getAttributesEx() { return m_spellInfo->AttributesEx; }
    quint32 getAttributesEx2() { return m_spellInfo->AttributesEx2; }
    quint32 getAttributesEx3() { return m_spellInfo->AttributesEx3; }
    quint32 getAttributesEx4() { return m_spellInfo->AttributesEx4; }
    quint32 getAttributesEx5() { return m_spellInfo->AttributesEx5; }
    quint32 getAttributesEx6() { return m_spellInfo->AttributesEx6; }
    quint32 getStances() { return m_spellInfo->Stances; }
    quint32 getStancesNot() { return m_spellInfo->StancesNot; }
    quint32 getTargets() { return m_spellInfo->Targets; }
    quint32 getTargetCreatureType() { return m_spellInfo->TargetCreatureType; }
    quint32 getRequiresSpellFocus() { return m_spellInfo->RequiresSpellFocus; }
    quint32 getFacingCasterFlags() { return m_spellInfo->FacingCasterFlags; }
    quint32 getCasterAuraState() { return m_spellInfo->CasterAuraState; }
    quint32 getTargetAuraState() { return m_spellInfo->TargetAuraState; }
    quint32 getCasterAuraStateNot() { return m_spellInfo->CasterAuraStateNot; }
    quint32 getTargetAuraStateNot() { return m_spellInfo->TargetAuraStateNot; }
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
    quint32 getSpellIconId() { return m_spellInfo->SpellIconId; }
    quint32 getActiveIconId() { return m_spellInfo->ActiveIconId; }
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
    quint32 getDamageClass() { return m_spellInfo->DamageClass; }
    quint32 getPreventionType() { return m_spellInfo->PreventionType; }
    qint32  getStanceBarOrder() { return m_spellInfo->StanceBarOrder; }
    quint32 getMinFactionId() { return m_spellInfo->MinFactionId; }
    quint32 getMinReputation() { return m_spellInfo->MinReputation; }
    quint32 getRequiredAuraVision() { return m_spellInfo->RequiredAuraVision; }
    quint32 getAreaId() { return m_spellInfo->AreaId; }
    quint32 getSchoolMask() { return m_spellInfo->SchoolMask; }

    QString getSpellName() { return QString::fromUtf8(m_spellInfo->SpellName[Locale]); }
    QString getRank() { return QString::fromUtf8(m_spellInfo->Rank[Locale]); }
    QString getDescription() { return QString::fromUtf8(m_spellInfo->Description[Locale]); }
    QString getToolTip() { return QString::fromUtf8(m_spellInfo->ToolTip[Locale]); }

    QVariant getTotem() { return QVariant::fromValue(m_spellInfo->Totem); }
    QVariant getReagent() { return QVariant::fromValue(m_spellInfo->Reagent); }
    QVariant getReagentCount() { return QVariant::fromValue(m_spellInfo->ReagentCount); }
    QVariant getEffect() { return QVariant::fromValue(m_spellInfo->Effect); }
    QVariant getEffectDieSides() { return QVariant::fromValue(m_spellInfo->EffectDieSides); }
    QVariant getEffectBaseDice() { return QVariant::fromValue(m_spellInfo->EffectBaseDice); }
    QVariant getEffectDicePerLevel() { return QVariant::fromValue(m_spellInfo->EffectDicePerLevel); }
    QVariant getEffectRealPointsPerLevel() { return QVariant::fromValue(m_spellInfo->EffectRealPointsPerLevel); }
    QVariant getEffectBasePoints() { return QVariant::fromValue(m_spellInfo->EffectBasePoints); }
    QVariant getEffectMechanic() { return QVariant::fromValue(m_spellInfo->EffectMechanic); }
    QVariant getEffectImplicitTargetA() { return QVariant::fromValue(m_spellInfo->EffectImplicitTargetA); }
    QVariant getEffectImplicitTargetB() { return QVariant::fromValue(m_spellInfo->EffectImplicitTargetB); }
    QVariant getEffectRadiusIndex() { return QVariant::fromValue(m_spellInfo->EffectRadiusIndex); }
    QVariant getEffectApplyAuraName() { return QVariant::fromValue(m_spellInfo->EffectApplyAuraName); }
    QVariant getEffectAmplitude() { return QVariant::fromValue(m_spellInfo->EffectAmplitude); }
    QVariant getEffectMultipleValue() { return QVariant::fromValue(m_spellInfo->EffectMultipleValue); }
    QVariant getEffectChainTarget() { return QVariant::fromValue(m_spellInfo->EffectChainTarget); }
    QVariant getEffectItemType() { return QVariant::fromValue(m_spellInfo->EffectItemType); }
    QVariant getEffectMiscValue() { return QVariant::fromValue(m_spellInfo->EffectMiscValue); }
    QVariant getEffectMiscValueB() { return QVariant::fromValue(m_spellInfo->EffectMiscValueB); }
    QVariant getEffectTriggerSpell() { return QVariant::fromValue(m_spellInfo->EffectTriggerSpell); }
    QVariant getEffectPointsPerComboPoint() { return QVariant::fromValue(m_spellInfo->EffectPointsPerComboPoint); }
    QVariant getSpellVisual() { return QVariant::fromValue(m_spellInfo->SpellVisual); }
    QVariant getDamageMultiplier() { return QVariant::fromValue(m_spellInfo->DamageMultiplier); }
    QVariant getTotemCategory() { return QVariant::fromValue(m_spellInfo->TotemCategory); }

private:
    SpellEntry const* m_spellInfo;

    Q_PROPERTY(quint32 Id READ getId)
        Q_PROPERTY(quint32 Category READ getCategory)
        Q_PROPERTY(quint32 CastUI READ getCastUI)
        Q_PROPERTY(quint32 Dispel READ getDispel)
        Q_PROPERTY(quint32 Mechanic READ getMechanic)
        Q_PROPERTY(quint32 Attributes READ getAttributes)
        Q_PROPERTY(quint32 AttributesEx READ getAttributesEx)
        Q_PROPERTY(quint32 AttributesEx2 READ getAttributesEx2)
        Q_PROPERTY(quint32 AttributesEx3 READ getAttributesEx3)
        Q_PROPERTY(quint32 AttributesEx4 READ getAttributesEx4)
        Q_PROPERTY(quint32 AttributesEx5 READ getAttributesEx5)
        Q_PROPERTY(quint32 AttributesEx6 READ getAttributesEx6)
        Q_PROPERTY(quint32 Stances READ getStances)
        Q_PROPERTY(quint32 StancesNot READ getStancesNot)
        Q_PROPERTY(quint32 Targets READ getTargets)
        Q_PROPERTY(quint32 TargetCreatureType READ getTargetCreatureType)
        Q_PROPERTY(quint32 RequiresSpellFocus READ getRequiresSpellFocus)
        Q_PROPERTY(quint32 FacingCasterFlags READ getFacingCasterFlags)
        Q_PROPERTY(quint32 CasterAuraStateNot READ getCasterAuraStateNot)
        Q_PROPERTY(quint32 TargetAuraStateNot READ getTargetAuraStateNot)
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
        Q_PROPERTY(QVariant Reagent READ getReagent)
        Q_PROPERTY(QVariant ReagentCount READ getReagentCount)
        Q_PROPERTY(qint32  EquippedItemClass READ getEquippedItemClass)
        Q_PROPERTY(qint32  EquippedItemSubClassMask READ getEquippedItemSubClassMask)
        Q_PROPERTY(qint32  EquippedItemInventoryTypeMask READ getEquippedItemInventoryTypeMask)
        Q_PROPERTY(QVariant Effect READ getEffect)
        Q_PROPERTY(QVariant EffectDieSides READ getEffectDieSides)
        Q_PROPERTY(QVariant EffectBaseDice READ getEffectBaseDice)
        Q_PROPERTY(QVariant EffectDicePerLevel READ getEffectDicePerLevel)
        Q_PROPERTY(QVariant EffectRealPointsPerLevel READ getEffectRealPointsPerLevel)
        Q_PROPERTY(QVariant EffectBasePoints READ getEffectBasePoints)
        Q_PROPERTY(QVariant EffectMechanic READ getEffectMechanic)
        Q_PROPERTY(QVariant EffectImplicitTargetA READ getEffectImplicitTargetA)
        Q_PROPERTY(QVariant EffectImplicitTargetB READ getEffectImplicitTargetB)
        Q_PROPERTY(QVariant EffectRadiusIndex READ getEffectRadiusIndex)
        Q_PROPERTY(QVariant EffectApplyAuraName READ getEffectApplyAuraName)
        Q_PROPERTY(QVariant EffectAmplitude READ getEffectAmplitude)
        Q_PROPERTY(QVariant EffectMultipleValue READ getEffectMultipleValue)
        Q_PROPERTY(QVariant EffectChainTarget READ getEffectChainTarget)
        Q_PROPERTY(QVariant EffectItemType READ getEffectItemType)
        Q_PROPERTY(QVariant EffectMiscValue READ getEffectMiscValue)
        Q_PROPERTY(QVariant EffectMiscValueB READ getEffectMiscValueB)
        Q_PROPERTY(QVariant EffectTriggerSpell READ getEffectTriggerSpell)
        Q_PROPERTY(QVariant EffectPointsPerComboPoint READ getEffectPointsPerComboPoint)
        Q_PROPERTY(QVariant SpellVisual READ getSpellVisual)
        Q_PROPERTY(quint32 SpellIconId READ getSpellIconId)
        Q_PROPERTY(quint32 ActiveIconId READ getActiveIconId)
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
        Q_PROPERTY(quint32 DamageClass READ getDamageClass)
        Q_PROPERTY(quint32 PreventionType READ getPreventionType)
        Q_PROPERTY(qint32  StanceBarOrder READ getStanceBarOrder)
        Q_PROPERTY(QVariant DamageMultiplier READ getDamageMultiplier)
        Q_PROPERTY(quint32 MinFactionId READ getMinFactionId)
        Q_PROPERTY(quint32 MinReputation READ getMinReputation)
        Q_PROPERTY(quint32 RequiredAuraVision READ getRequiredAuraVision)
        Q_PROPERTY(QVariant TotemCategory READ getTotemCategory)
        Q_PROPERTY(quint32 AreaId READ getAreaId)
        Q_PROPERTY(quint32 SchoolMask READ getSchoolMask)
};

#endif // SWSEARCH_H

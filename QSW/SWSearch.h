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
        quint32 getCategory() { return m_spellInfo->getCategory(); }
        quint32 getDispel() { return m_spellInfo->getDispel(); }
        quint32 getMechanic() { return m_spellInfo->getMechanic(); }
        quint32 getAttributes() { return m_spellInfo->Attributes; }
        quint32 getAttributesEx() { return m_spellInfo->AttributesEx; }
        quint32 getAttributesEx2() { return m_spellInfo->AttributesEx2; }
        quint32 getAttributesEx3() { return m_spellInfo->AttributesEx3; }
        quint32 getAttributesEx4() { return m_spellInfo->AttributesEx4; }
        quint32 getAttributesEx5() { return m_spellInfo->AttributesEx5; }
        quint32 getAttributesEx6() { return m_spellInfo->AttributesEx6; }
        quint32 getAttributesEx7() { return m_spellInfo->AttributesEx7; }
        quint32 getAttributesEx8() { return m_spellInfo->AttributesEx8; }
        quint32 getTargets() { return m_spellInfo->getTargets(); }
        quint32 getTargetCreatureType() { return m_spellInfo->getTargetCreatureType(); }
        quint32 getRequiresSpellFocus() { return m_spellInfo->getRequiresSpellFocus(); }
        quint32 getFacingCasterFlags() { return m_spellInfo->getFacingCasterFlags(); }
        quint32 getCasterAuraState() { return m_spellInfo->getCasterAuraState(); }
        quint32 getTargetAuraState() { return m_spellInfo->getTargetAuraState(); }
        quint32 getCasterAuraStateNot() { return m_spellInfo->getCasterAuraStateNot(); }
        quint32 getTargetAuraStateNot() { return m_spellInfo->getTargetAuraStateNot(); }
        quint32 getCasterAuraSpell() { return m_spellInfo->getCasterAuraSpell(); }
        quint32 getTargetAuraSpell() { return m_spellInfo->getTargetAuraSpell(); }
        quint32 getExcludeCasterAuraSpell() { return m_spellInfo->getExcludeCasterAuraSpell(); }
        quint32 getExcludeTargetAuraSpell() { return m_spellInfo->getExcludeTargetAuraSpell(); }
        quint32 getCastingTimeIndex() { return m_spellInfo->CastingTimeIndex; }
        quint32 getRecoveryTime() { return m_spellInfo->getRecoveryTime(); }
        quint32 getCategoryRecoveryTime() { return m_spellInfo->getCategoryRecoveryTime(); }
        quint32 getInterruptFlags() { return m_spellInfo->getInterruptFlags(); }
        quint32 getAuraInterruptFlags() { return m_spellInfo->getAuraInterruptFlags(); }
        quint32 getChannelInterruptFlags() { return m_spellInfo->getChannelInterruptFlags(); }
        quint32 getProcFlags() { return m_spellInfo->getProcFlags(); }
        quint32 getProcChance() { return m_spellInfo->getProcChance(); }
        quint32 getProcCharges() { return m_spellInfo->getProcCharges(); }
        quint32 getMaxLevel() { return m_spellInfo->getMaxLevel(); }
        quint32 getBaseLevel() { return m_spellInfo->getBaseLevel(); }
        quint32 getSpellLevel() { return m_spellInfo->getSpellLevel(); }
        quint32 getDurationIndex() { return m_spellInfo->DurationIndex; }
        qint32  getPowerType() { return m_spellInfo->PowerType; }
        quint32 getManaCost() { return m_spellInfo->getManaCost(); }
        quint32 getManaCostPerlevel() { return m_spellInfo->getManaCostPerLevel(); }
        quint32 getManaPerSecond() { return m_spellInfo->getManaPerSecond(); }
        quint32 getRangeIndex() { return m_spellInfo->RangeIndex; }
        float   getSpeed() { return m_spellInfo->Speed; }
        quint32 getModalNextSpell() { return m_spellInfo->getModalNextSpell(); }
        quint32 getStackAmount() { return m_spellInfo->getStackAmount(); }
        qint32  getEquippedItemClass() { return m_spellInfo->getEquippedItemClass(); }
        qint32  getEquippedItemSubClassMask() { return m_spellInfo->getEquippedItemSubClassMask(); }
        qint32  getEquippedItemInventoryTypeMask() { return m_spellInfo->getEquippedItemInventoryTypeMask(); }
        quint32 getSpellIconId() { return m_spellInfo->SpellIconId; }
        quint32 getActiveIconId() { return m_spellInfo->ActiveIconId; }
        quint32 getManaCostPercentage() { return m_spellInfo->getManaCostPercentage(); }
        quint32 getStartRecoveryCategory() { return m_spellInfo->getStartRecoveryCategory(); }
        quint32 getStartRecoveryTime() { return m_spellInfo->getStartRecoveryTime(); }
        quint32 getMaxTargetLevel() { return m_spellInfo->getMaxTargetLevel(); }
        quint32 getSpellFamilyName() { return m_spellInfo->getSpellFamilyName(); }
        quint32 getMaxAffectedTargets() { return m_spellInfo->getMaxAffectedTargets(); }
        quint32 getDmgClass() { return m_spellInfo->getDmgClass(); }
        quint32 getPreventionType() { return m_spellInfo->getPreventionType(); }
        qint32  getStanceBarOrder() { return m_spellInfo->getStanceBarOrder(); }
        //quint32 getMinFactionId() { return m_spellInfo->GetSpellCastingRequirements()->MinFactionId; }
        //quint32 getMinReputation() { return m_spellInfo->GetSpellCastingRequirements()->MinReputation; }
        //quint32 getRequiredAuraVision() { return m_spellInfo->GetSpellCastingRequirements()->RequiredAuraVision; }
        quint32 getAreaGroupId() { return m_spellInfo->getAreaGroupId(); }
        quint32 getSchoolMask() { return m_spellInfo->SchoolMask; }
        quint32 getRuneCostID() { return m_spellInfo->RuneCostId; }
        quint32 getSpellMissileId() { return m_spellInfo->SpellMissileId; }
        //quint32 getPowerDisplayId() { return m_spellInfo->GetSpellPower()->PowerDisplayId; }
        quint32 getSpellDescriptionVariableId() { return m_spellInfo->SpellDescriptionVariableId; }
        quint32 getSpellDifficultyId() { return m_spellInfo->SpellDifficultyId; }

        QString getSpellName() { return QString::fromUtf8(m_spellInfo->SpellName); }
        QString getRank() { return QString::fromUtf8(m_spellInfo->Rank); }
        QString getDescription() { return QString::fromUtf8(m_spellInfo->Description); }
        QString getToolTip() { return QString::fromUtf8(m_spellInfo->ToolTip); }

        QVariant getStances() { return QVariant::fromValue(m_spellInfo->getStances()); }
        QVariant getStancesNot() { return QVariant::fromValue(m_spellInfo->getStancesNot()); }
        /*QVariant getTotem() { return QVariant::fromValue(m_spellInfo->GetSpellTotems()->Totem); }
        QVariant getTotemCategory() { return QVariant::fromValue(m_spellInfo->GetSpellTotems()->TotemCategory); }
        QVariant getReagent() { return QVariant::fromValue(m_spellInfo->GetSpellReagents()->Reagent); }
        QVariant getReagentCount() { return QVariant::fromValue(m_spellInfo->GetSpellReagents()->ReagentCount); }
        QVariant getEffect() { return QVariant::fromValue(m_spellInfo->GetSpellEffect()->Effect); }
        QVariant getEffectDieSides() { return QVariant::fromValue(m_spellInfo->EffectDieSides); }
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
        QVariant getEffectSpellClassMaskA() { return QVariant::fromValue(m_spellInfo->EffectSpellClassMaskA); }
        QVariant getEffectSpellClassMaskB() { return QVariant::fromValue(m_spellInfo->EffectSpellClassMaskB); }
        QVariant getEffectSpellClassMaskC() { return QVariant::fromValue(m_spellInfo->EffectSpellClassMaskC); }
        QVariant getDmgMultiplier() { return QVariant::fromValue(m_spellInfo->EffectDamageMultiplier); }*/
        QVariant getSpellFamilyFlags() { return QVariant::fromValue(m_spellInfo->getSpellFamilyFlags()); }
        QVariant getSpellVisual() { return QVariant::fromValue(m_spellInfo->SpellVisual); }

    private:
        SpellEntry const* m_spellInfo;

    Q_PROPERTY(quint32 Id READ getId)
    Q_PROPERTY(quint32 Category READ getCategory)
    Q_PROPERTY(quint32 Dispel READ getDispel)
    Q_PROPERTY(quint32 Mechanic READ getMechanic)
    Q_PROPERTY(quint32 Attributes READ getAttributes)
    Q_PROPERTY(quint32 AttributesEx READ getAttributesEx)
    Q_PROPERTY(quint32 AttributesEx2 READ getAttributesEx2)
    Q_PROPERTY(quint32 AttributesEx3 READ getAttributesEx3)
    Q_PROPERTY(quint32 AttributesEx4 READ getAttributesEx4)
    Q_PROPERTY(quint32 AttributesEx5 READ getAttributesEx5)
    Q_PROPERTY(quint32 AttributesEx6 READ getAttributesEx6)
    Q_PROPERTY(quint32 AttributesEx7 READ getAttributesEx7)
    Q_PROPERTY(quint32 AttributesEx8 READ getAttributesEx8)
    Q_PROPERTY(QVariant Stances READ getStances)
    Q_PROPERTY(QVariant StancesNot READ getStancesNot)
    Q_PROPERTY(quint32 Targets READ getTargets)
    Q_PROPERTY(quint32 TargetCreatureType READ getTargetCreatureType)
    Q_PROPERTY(quint32 RequiresSpellFocus READ getRequiresSpellFocus)
    Q_PROPERTY(quint32 FacingCasterFlags READ getFacingCasterFlags)
    Q_PROPERTY(quint32 CasterAuraStateNot READ getCasterAuraStateNot)
    Q_PROPERTY(quint32 TargetAuraStateNot READ getTargetAuraStateNot)
    Q_PROPERTY(quint32 CasterAuraState READ getCasterAuraState)
    Q_PROPERTY(quint32 TargetAuraState READ getTargetAuraState)
    Q_PROPERTY(quint32 CasterAuraSpell READ getCasterAuraSpell)
    Q_PROPERTY(quint32 TargetAuraSpell READ getTargetAuraSpell)
    Q_PROPERTY(quint32 ExcludeCasterAuraSpell READ getExcludeCasterAuraSpell)
    Q_PROPERTY(quint32 ExcludeTargetAuraSpell READ getExcludeTargetAuraSpell)
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
    //Q_PROPERTY(quint32 ManaPerSecondPerLevel READ getManaPerSecondPerLevel)
    Q_PROPERTY(quint32 RangeIndex READ getRangeIndex)
    Q_PROPERTY(float   Speed READ getSpeed)
    Q_PROPERTY(quint32 ModalNextSpell READ getModalNextSpell)
    Q_PROPERTY(quint32 StackAmount READ getStackAmount)
    //Q_PROPERTY(QVariant Totem READ getTotem)
    //Q_PROPERTY(QVariant Reagent READ getReagent)
    //Q_PROPERTY(QVariant ReagentCount READ getReagentCount)
    Q_PROPERTY(qint32  EquippedItemClass READ getEquippedItemClass)
    Q_PROPERTY(qint32  EquippedItemSubClassMask READ getEquippedItemSubClassMask)
    Q_PROPERTY(qint32  EquippedItemInventoryTypeMask READ getEquippedItemInventoryTypeMask)
    /*Q_PROPERTY(QVariant Effect READ getEffect)
    Q_PROPERTY(QVariant EffectDieSides READ getEffectDieSides)
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
    Q_PROPERTY(QVariant EffectSpellClassMaskA READ getEffectSpellClassMaskA)
    Q_PROPERTY(QVariant EffectSpellClassMaskB READ getEffectSpellClassMaskB)
    Q_PROPERTY(QVariant EffectSpellClassMaskC READ getEffectSpellClassMaskC)*/
    Q_PROPERTY(QVariant SpellVisual READ getSpellVisual)
    Q_PROPERTY(quint32 SpellIconId READ getSpellIconId)
    Q_PROPERTY(quint32 ActiveIconId READ getActiveIconId)
    //Q_PROPERTY(quint32 SpellPriority READ getSpellPriority)
    Q_PROPERTY(QString SpellName READ getSpellName)
    //Q_PROPERTY(quint32 SpellNameFlag READ getSpellNameFlag)
    Q_PROPERTY(QString Rank READ getRank)
    //Q_PROPERTY(quint32 RankFlags READ getRankFlags)
    Q_PROPERTY(QString Description READ getDescription)
    //Q_PROPERTY(quint32 DescriptionFlags READ getDescriptionFlags)
    Q_PROPERTY(QString ToolTip READ getToolTip)
    //Q_PROPERTY(quint32 ToolTipFlags READ getToolTipFlags)
    Q_PROPERTY(quint32 ManaCostPercentage READ getManaCostPercentage)
    Q_PROPERTY(quint32 StartRecoveryCategory READ getStartRecoveryCategory)
    Q_PROPERTY(quint32 StartRecoveryTime READ getStartRecoveryTime)
    Q_PROPERTY(quint32 MaxTargetLevel READ getMaxTargetLevel)
    Q_PROPERTY(quint32 SpellFamilyName READ getSpellFamilyName)
    Q_PROPERTY(QVariant SpellFamilyFlags READ getSpellFamilyFlags)
    Q_PROPERTY(quint32 MaxAffectedTargets READ getMaxAffectedTargets)
    Q_PROPERTY(quint32 DmgClass READ getDmgClass)
    Q_PROPERTY(quint32 PreventionType READ getPreventionType)
    Q_PROPERTY(qint32  StanceBarOrder READ getStanceBarOrder)
    //Q_PROPERTY(QVariant DmgMultiplier READ getDmgMultiplier)
    //Q_PROPERTY(quint32 MinFactionId READ getMinFactionId)
    //Q_PROPERTY(quint32 MinReputation READ getMinReputation)
    //Q_PROPERTY(quint32 RequiredAuraVision READ getRequiredAuraVision)
    //Q_PROPERTY(QVariant TotemCategory READ getTotemCategory)
    Q_PROPERTY(quint32 AreaGroupId READ getAreaGroupId)
    Q_PROPERTY(quint32 SchoolMask READ getSchoolMask)
    Q_PROPERTY(quint32 RuneCostId READ getRuneCostID)
    Q_PROPERTY(quint32 SpellMissileId READ getSpellMissileId)
    //Q_PROPERTY(quint32 PowerDisplayId READ getPowerDisplayId)
    Q_PROPERTY(quint32 SpellDescriptionVariableId READ getSpellDescriptionVariableId)
    Q_PROPERTY(quint32 SpellDifficultyId READ getSpellDifficultyId)
};

#endif // SWSEARCH_H

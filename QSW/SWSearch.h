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
        bool hasValue(quint8 index, QString name, QString value, SpellEntry const* spellInfo);

    private:
        SWObject* m_sw;
        SWForm*   m_form;
        quint8    m_locale;
};

class MetaSpell : public QObject
{
    Q_OBJECT
    
    public:
        MetaSpell(quint8 index, SpellEntry const* spellInfo, quint8 locale);
        ~MetaSpell();

        quint32 getId() { return Id; }
        quint32 getSchool() { return School; }
        quint32 getCategory() { return Category; }
        quint32 getCastUI() { return CastUI; }
        quint32 getDispel() { return Dispel; }
        quint32 getMechanic() { return Mechanic; }
        quint32 getAttributes() { return Attributes; }
        quint32 getAttributesEx() { return AttributesEx; }
        quint32 getAttributesEx2() { return AttributesEx2; }
        quint32 getAttributesEx3() { return AttributesEx3; }
        quint32 getAttributesEx4() { return AttributesEx4; }
        quint32 getStances() { return Stances; }
        quint32 getStancesNot() { return StancesNot; }
        quint32 getTargets() { return Targets; }
        quint32 getTargetCreatureType() { return TargetCreatureType; }
        quint32 getRequiresSpellFocus() { return RequiresSpellFocus; }
        quint32 getCasterAuraState() { return CasterAuraState; }
        quint32 getTargetAuraState() { return TargetAuraState; }
        quint32 getCastingTimeIndex() { return CastingTimeIndex; }
        quint32 getRecoveryTime() { return RecoveryTime; }
        quint32 getCategoryRecoveryTime() { return CategoryRecoveryTime; }
        quint32 getInterruptFlags() { return InterruptFlags; }
        quint32 getAuraInterruptFlags() { return AuraInterruptFlags; }
        quint32 getChannelInterruptFlags() { return ChannelInterruptFlags; }
        quint32 getProcFlags() { return ProcFlags; }
        quint32 getProcChance() { return ProcChance; }
        quint32 getProcCharges() { return ProcCharges; }
        quint32 getMaxLevel() { return MaxLevel; }
        quint32 getBaseLevel() { return BaseLevel; }
        quint32 getSpellLevel() { return SpellLevel; }
        quint32 getDurationIndex() { return DurationIndex; }
        qint32  getPowerType() { return PowerType; }
        quint32 getManaCost() { return ManaCost; }
        quint32 getManaCostPerlevel() { return ManaCostPerlevel; }
        quint32 getManaPerSecond() { return ManaPerSecond; }
        quint32 getManaPerSecondPerLevel() { return ManaPerSecondPerLevel; }
        quint32 getRangeIndex() { return RangeIndex; }
        float   getSpeed() { return Speed; }
        quint32 getModalNextSpell() { return ModalNextSpell; }
        quint32 getStackAmount() { return StackAmount; }
        qint32  getEquippedItemClass() { return EquippedItemClass; }
        qint32  getEquippedItemSubClassMask() { return EquippedItemSubClassMask; }
        qint32  getEquippedItemInventoryTypeMask() { return EquippedItemInventoryTypeMask; }
        quint32 getSpellIconID() { return SpellIconID; }
        quint32 getActiveIconID() { return ActiveIconID; }
        quint32 getSpellPriority() { return SpellPriority; }
        quint32 getSpellNameFlag() { return SpellNameFlag; }
        quint32 getRankFlags() { return RankFlags; }
        quint32 getDescriptionFlags() { return DescriptionFlags; }
        quint32 getToolTipFlags() { return ToolTipFlags; }
        quint32 getManaCostPercentage() { return ManaCostPercentage; }
        quint32 getStartRecoveryCategory() { return StartRecoveryCategory; }
        quint32 getStartRecoveryTime() { return StartRecoveryTime; }
        quint32 getMaxTargetLevel() { return MaxTargetLevel; }
        quint32 getSpellFamilyName() { return SpellFamilyName; }
        quint64 getSpellFamilyFlags() { return SpellFamilyFlags; }
        quint32 getMaxAffectedTargets() { return MaxAffectedTargets; }
        quint32 getDmgClass() { return DmgClass; }
        quint32 getPreventionType() { return PreventionType; }
        qint32  getStanceBarOrder() { return StanceBarOrder; }
        quint32 getMinFactionId() { return MinFactionId; }
        quint32 getMinReputation() { return MinReputation; }
        quint32 getRequiredAuraVision() { return RequiredAuraVision; }

        QString getSpellName() { return SpellName; }
        QString getRank() { return Rank; }
        QString getDescription() { return Description; }
        QString getToolTip() { return ToolTip; }

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
        quint32    Id;
        quint32    School;
        quint32    Category;
        quint32    CastUI;
        quint32    Dispel;
        quint32    Mechanic;
        quint32    Attributes;
        quint32    AttributesEx;
        quint32    AttributesEx2;
        quint32    AttributesEx3;
        quint32    AttributesEx4;
        quint32    Stances;
        quint32    StancesNot;
        quint32    Targets;
        quint32    TargetCreatureType;
        quint32    RequiresSpellFocus;
        quint32    CasterAuraState;
        quint32    TargetAuraState;
        quint32    CastingTimeIndex;
        quint32    RecoveryTime;
        quint32    CategoryRecoveryTime;
        quint32    InterruptFlags;
        quint32    AuraInterruptFlags;
        quint32    ChannelInterruptFlags;
        quint32    ProcFlags;
        quint32    ProcChance;
        quint32    ProcCharges;
        quint32    MaxLevel;
        quint32    BaseLevel;
        quint32    SpellLevel;
        quint32    DurationIndex;
        qint32     PowerType;
        quint32    ManaCost;
        quint32    ManaCostPerlevel;
        quint32    ManaPerSecond;
        quint32    ManaPerSecondPerLevel;
        quint32    RangeIndex;
        float      Speed;
        quint32    ModalNextSpell;
        quint32    StackAmount;
        QVariantList Totem;
        QVariantList Reagent;
        QVariantList ReagentCount;
        qint32     EquippedItemClass;
        qint32     EquippedItemSubClassMask;
        qint32     EquippedItemInventoryTypeMask;
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
        quint32    SpellIconID;
        quint32    ActiveIconID;
        quint32    SpellPriority;
        QString    SpellName;
        quint32    SpellNameFlag;
        QString    Rank;
        quint32    RankFlags;
        QString    Description;
        quint32    DescriptionFlags;
        QString    ToolTip;
        quint32    ToolTipFlags;
        quint32    ManaCostPercentage;
        quint32    StartRecoveryCategory;
        quint32    StartRecoveryTime;
        quint32    MaxTargetLevel;
        quint32    SpellFamilyName;
        quint64    SpellFamilyFlags;
        quint32    MaxAffectedTargets;
        quint32    DmgClass;
        quint32    PreventionType;
        qint32     StanceBarOrder;
        QVariantList DmgMultiplier;
        quint32    MinFactionId;
        quint32    MinReputation;
        quint32    RequiredAuraVision;

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
    Q_PROPERTY(QVariantList Totem READ getTotem)
    Q_PROPERTY(QVariantList Reagent READ getReagent)
    Q_PROPERTY(QVariantList ReagentCount READ getReagentCount)
    Q_PROPERTY(qint32  EquippedItemClass READ getEquippedItemClass)
    Q_PROPERTY(qint32  EquippedItemSubClassMask READ getEquippedItemSubClassMask)
    Q_PROPERTY(qint32  EquippedItemInventoryTypeMask READ getEquippedItemInventoryTypeMask)
    Q_PROPERTY(QVariantList Effect READ getEffect)
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
    Q_PROPERTY(QVariantList SpellVisual READ getSpellVisual)
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
    Q_PROPERTY(QVariantList DmgMultiplier READ getDmgMultiplier)
    Q_PROPERTY(quint32 MinFactionId READ getMinFactionId)
    Q_PROPERTY(quint32 MinReputation READ getMinReputation)
    Q_PROPERTY(quint32 RequiredAuraVision READ getRequiredAuraVision)
};

#endif // SWSEARCH_H

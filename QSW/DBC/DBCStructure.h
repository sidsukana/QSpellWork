#ifndef DBCSTRUCTURE_H
#define DBCSTRUCTURE_H

#include "SWDefines.h"
#include "Define.h"

#include <map>
#include <set>
#include <vector>

// GCC have alternative #pragma pack(N) syntax and old gcc version not support pack(push,N), also any gcc version not support it at some platform
#if defined( __GNUC__ )
#pragma pack(1)
#else
#pragma pack(push,1)
#endif

struct SkillLineEntry
{
    quint32    Id;                                              // 0
    qint32     CategoryId;                                      // 1 (index from SkillLineCategory.dbc)
    char*      Name;                                            // 2
    char*      Description;                                     // 3
    quint32    SpellIcon;                                       // 4
    char*      AlternateVerb;                                   // 5
    quint32    CanLink;                                         // 6
    // quint32    Unk7                                          // 7
};

struct SkillLineAbilityEntry
{
    quint32    Id;                                              // 0 INDEX
    quint32    SkillId;                                         // 1
    quint32    SpellId;                                         // 2
    quint32    RaceMask;                                        // 3
    quint32    ClassMask;                                       // 4
    quint32    ReqSkillValue;                                   // 5 for trade skill.not for training.
    quint32    ForwardSpellId;                                  // 6
    quint32    LearnOnGetSkill;                                 // 7 can be 1 or 2 for spells learned on get skill
    quint32    MaxValue;                                        // 8
    quint32    MinValue;                                        // 9
    quint32    CharPoints;                                      // 10
    // quint32    Unk11;                                        // 11
    // quint32    Unk12;                                        // 12
};

struct SpellAuraOptionsEntry
{
    // quint32    Id;                                           // 0       m_ID
    quint32    SpellId;                                         // 1      m_spellId
    // quint32    Unk2;                                         // 2       flags ?
    quint32    StackAmount;                                     // 3       m_cumulativeAura
    quint32    ProcChance;                                      // 4       m_procChance
    quint32    ProcCharges;                                     // 5       m_procCharges
    quint32    ProcFlags;                                       // 6       m_procTypeMask
};

struct SpellAuraRestrictionsEntry
{
    // quint32    Id;                                        // 0       m_ID
    quint32    SpellId;                                      // 1       m_spellId
    // quint32    Unk2;                                      // 2       flags ?
    quint32    CasterAuraState;                              // 3       m_casterAuraState
    quint32    TargetAuraState;                              // 4       m_targetAuraState
    quint32    CasterAuraStateNot;                           // 5       m_excludeCasterAuraState
    quint32    TargetAuraStateNot;                           // 6       m_excludeTargetAuraState
    quint32    CasterAuraSpell;                              // 7       m_casterAuraSpell
    quint32    TargetAuraSpell;                              // 8       m_targetAuraSpell
    quint32    ExcludeCasterAuraSpell;                       // 9       m_excludeCasterAuraSpell
    quint32    ExcludeTargetAuraSpell;                       // 10       m_excludeTargetAuraSpell
};

struct SpellCastingRequirementsEntry
{
    // quint32    Id;                                        // 0       m_ID
    quint32    FacingCasterFlags;                            // 1       m_facingCasterFlags
    quint32    MinFactionId;                                 // 2       m_minFactionID not used
    quint32    MinReputation;                                // 3       m_minReputation not used
    qint32     AreaGroupId;                                  // 4       m_requiredAreaGroupId
    quint32    RequiredAuraVision;                           // 5       m_requiredAuraVision not used
    quint32    RequiresSpellFocus;                           // 6       m_requiresSpellFocus
};

struct SpellCategoriesEntry
{
    // quint32    Id;                                        // 0       m_ID
    quint32    SpellId;                                      // 1       m_spellId
    // quint32    Unk2;                                      // 2       flags ?
    quint32    Category;                                     // 3       m_category
    quint32    DamageClass;                                  // 4       m_defenseType
    quint32    Dispel;                                       // 5       m_dispelType
    quint32    Mechanic;                                     // 6       m_mechanic
    quint32    PreventionType;                               // 7       m_preventionType
    quint32    StartRecoveryCategory;                        // 8       m_startRecoveryCategory
    // quint32    Unk9;                                      // 9       unk9 ?
};

struct SpellClassOptionsEntry
{
    // quint32    Id;                                        // 0        m_ID
    quint32    ModalNextSpell;                               // 1        m_modalNextSpell not used
    quint32    SpellFamilyFlags[3];                          // 2-4      m_spellClassMask NOTE: size is 12 bytes!!!
    // quint32 Unk5                                          // 5
    quint32    SpellFamilyName;                              // 6        m_spellClassSet
};

struct SpellCooldownsEntry
{
    // quint32    Id;                                        // 0       m_ID
    quint32    SpellId;                                      // 1       m_spellId
    // quint32    Unk2;                                      // 2       flags ?
    quint32    CategoryRecoveryTime;                         // 3       m_categoryRecoveryTime
    quint32    RecoveryTime;                                 // 4       m_recoveryTime
    quint32    StartRecoveryTime;                            // 5       m_startRecoveryTime
};

struct SpellEffectEntry
{
    // quint32    Id;                                        // 0        m_ID
    // quint32    Unk1;                                      // 1        flags ?
    quint32    Effect;                                       // 2        m_effect
    float      EffectValueMultiplier;                        // 3        m_effectAmplitude
    quint32    EffectApplyAuraName;                          // 4        m_effectAura
    quint32    EffectAmplitude;                              // 5        m_effectAuraPeriod
    qint32     EffectBasePoints;                             // 6        m_effectBasePoints (don't must be used in spell/auras explicitly, must be used cached Spell::m_currentBasePoints)
    float      EffectBonusCoefficient;                       // 7        m_effectBonusCoefficient
    float      EffectDamageMultiplier;                       // 8        m_effectChainAmplitude
    quint32    EffectChainTarget;                            // 9        m_effectChainTargets
    qint32     EffectDieSides;                               // 10        m_effectDieSides
    quint32    EffectItemType;                               // 11       m_effectItemType
    quint32    EffectMechanic;                               // 12       m_effectMechanic
    qint32     EffectMiscValue;                              // 13       m_effectMiscValue
    qint32     EffectMiscValueB;                             // 14       m_effectMiscValueB
    float      EffectPointsPerComboPoint;                    // 15       m_effectPointsPerCombo
    quint32    EffectRadiusIndex;                            // 16       m_effectRadiusIndex - spellradius.dbc
    quint32    EffectRadiusMaxIndex;                         // 17       4.0.0
    float      EffectRealPointsPerLevel;                     // 18       m_effectRealPointsPerLevel
    quint32    EffectSpellClassMask[3];                      // 19-21       m_effectSpellClassMask, effect 0
    // quint32    Unk22                                      // 22
    quint32    EffectTriggerSpell;                           // 23       m_effectTriggerSpell
    // quint32    Unk24                                      // 24
    quint32    EffectImplicitTargetA;                        // 25       m_implicitTargetA
    quint32    EffectImplicitTargetB;                        // 26       m_implicitTargetB
    quint32    EffectSpellId;                                // 27       new 4.0.0
    quint32    EffectIndex;                                  // 27       new 4.0.0
    //quint32    unk;                                        // 29 - 4.2.0
};

struct SpellEffect
{
    SpellEffect()
    {
        for (quint8 i = 0; i < 20; ++i)
            effects[i] = NULL;
    }
    SpellEffectEntry const* effects[20];
};

typedef std::map<quint32, SpellEffect> SpellEffectMap;

struct SpellEquippedItemsEntry
{
    // quint32    Id;                                        // 0       m_ID
    quint32    SpellId;                                      // 1       m_spellId
    // quint32    Unk2;                                      // 2       flags ?
    qint32     EquippedItemClass;                            // 3       m_equippedItemClass (value)
    qint32     EquippedItemInventoryTypeMask;                // 4       m_equippedItemInvTypes (mask)
    qint32     EquippedItemSubClassMask;                     // 5       m_equippedItemSubclass (mask)
};

struct SpellInterruptsEntry
{
    // quint32    Id;                                        // 0       m_ID
    quint32    SpellId;                                      // 1       m_spellId
    // quint32    Unk2;                                      // 2       flags ?
    quint32    AuraInterruptFlags;                           // 3       m_auraInterruptFlags
    quint32    ChannelInterruptFlags;                        // 4       m_channelInterruptFlags
    quint32    InterruptFlags;                               // 5       m_interruptFlags
    // quint32    Unk6;                                      // 6       Unk6 ?
    // quint32    Unk7;                                      // 7       Unk7 ?
};

struct SpellLevelsEntry
{
    // quint32    Id;                                        // 0       m_ID
    quint32    SpellId;                                      // 1       m_spellId
    // quint32    Unk2;                                      // 2       flags ?
    quint32    BaseLevel;                                    // 3       m_baseLevel
    quint32    MaxLevel;                                     // 4       m_maxLevel
    quint32    SpellLevel;                                   // 5       m_spellLevel
};

struct SpellPowerEntry
{
    // quint32    Id;                                        // 0       m_ID
    quint32    SpellId;                                      // 1       m_spellId
    // quint32    Unk2;                                      // 2       flags ?
    qint32     PowerType;                                    // 3       m_powerType ?
    quint32    ManaCost;                                     // 4       m_manaCost
    quint32    ManaCostPerlevel;                             // 5       m_manaCostPerLevel
    quint32    ManaCostPercentage;                           // 6       m_manaCostPct
    quint32    ManaPerSecond;                                // 7       m_manaPerSecond
    quint32    PowerDisplayId;                               // 8       m_powerDisplayID - id from PowerDisplay.dbc, new in 3.1
    // quint32    Unk9;                                      // 9       4.0.0
    // quint32    Unk10;                                     // 10      4.0.0
    // quint32    Unk11;                                     // 11      4.0.0
    // quint32    Unk12;                                     // 12      4.0.0
};

struct SpellReagentsEntry
{
    // quint32    Id;                                        // 0        m_ID
    quint32    Reagent[MAX_SPELL_REAGENTS];                  // 1-9    m_reagent
    quint32    ReagentCount[MAX_SPELL_REAGENTS];             // 10-17    m_reagentCount
    // quint32 Unk18                                         // 18
    // quint32 Unk19                                         // 19
};

struct SpellScalingEntry
{
    // quint32    Id;                                        // 0        m_ID
    quint32    CastTimeMin;                                  // 1
    quint32    CastTimeMax;                                  // 2
    quint32    CastScalingMaxLevel;                          // 3
    quint32    PlayerClass;                                  // 4        (index * 100) + charLevel => gtSpellScaling.dbc
    float      Coeff1[MAX_EFFECT_INDEX];                     // 5-7
    float      Coeff2[MAX_EFFECT_INDEX];                     // 8-10
    float      Coeff3[MAX_EFFECT_INDEX];                     // 11-13
    float      CoefBase;                                     // 14        some coefficient, mostly 1.0f
    quint32    CoefLevelBase;                                // 15        some level
};

struct SpellShapeshiftEntry
{
    // quint32     Id;                                        // 0        m_ID
    quint32     Stances;                                      // 1        m_shapeshiftMask
    // quint32     Unk2;                                      // 2        m_shapeshiftMask
    quint32     StancesNot;                                   // 3        m_shapeshiftExclude
    // quint32     Unk4;                                      // 4        m_shapeshiftExclude
    quint32     StanceBarOrder;                               // 5        m_stanceBarOrder not used
};

struct SpellTargetRestrictionsEntry
{
    // quint32    Id;                                         // 0        m_ID
    quint32    SpellId;                                       // 1
    // quint32    Unk2;                                       // 2        flags ?
    float      MaxTargetRadius;                               // 3        m_maxTargetRadius
    // float      Unk4;                                       // 4        Unk4
    quint32    MaxAffectedTargets;                            // 5        m_maxTargets
    quint32    MaxTargetLevel;                                // 6        m_maxTargetLevel
    quint32    TargetCreatureType;                            // 7        m_targetCreatureType
    quint32    Targets;                                       // 8        m_targets
};

struct SpellTotemsEntry
{
    // quint32    Id;                                         // 0        m_ID
    quint32    TotemCategory[MAX_SPELL_TOTEM_CATEGORIES];     // 1-2      m_requiredTotemCategoryID
    quint32    Totem[MAX_SPELL_TOTEMS];                       // 3-4      m_totem
};

struct SpellMiscEntry
{
    // quint32 Id,                                              // 0 - Misc id
    quint32 SpellId;                                            // 1 - Spell id
    // quint32 Unk2,                                            // 2 - flags?
    quint32 Attributes;                                         // 3 - Attributes
    quint32 AttributesEx1;                                      // 4 - Attributes
    quint32 AttributesEx2;                                      // 5 - Attributes
    quint32 AttributesEx3;                                      // 6 - Attributes
    quint32 AttributesEx4;                                      // 7 - Attributes
    quint32 AttributesEx5;                                      // 8 - Attributes
    quint32 AttributesEx6;                                      // 9 - Attributes
    quint32 AttributesEx7;                                      // 10 - Attributes
    quint32 AttributesEx8;                                      // 11 - Attributes
    quint32 AttributesEx9;                                      // 12 - Attributes
    quint32 AttributesEx10;                                     // 13 - Attributes
    quint32 AttributesEx11;                                     // 14 - Attributes
    quint32 CastTimeIndex;                                      // 15 - Attributes
    quint32 DurationIndex;                                      // 16 - Attributes
    quint32 RangeIndex;                                         // 17 - Attributes
    float   Speed;                                              // 18 - Attributes
    quint32 SpellVisual[2];                                     // 19-20 - Attributes
    quint32 SpellIconId;                                        // 21 - Attributes
    quint32 SpellBuffIconId;                                    // 22 - Attributes
    quint32 SchoolMask;                                         // 23 - SchoolMask
};

struct SpellEntry
{
    quint32     Id;                                           // 0        m_ID
    char*       SpellName;                                    // 1 - m_name_lang
    char*       Rank;                                         // 2 - m_nameSubtext_lang
    char*       Description;                                  // 3 - m_description_lang not used
    char*       ToolTip;                                      // 4 - m_auraDescription_lang not used
    quint32     RuneCostId;                                   // 5 - m_runeCostID
    quint32     SpellMissileId;                               // 6 - m_spellMissileID not used
    quint32     SpellDescriptionVariableId;                   // 7 - m_spellDescriptionVariableID, 3.2.0
    // float       unk_f1;                                    // 8 - 4.0.1
    quint32     SpellScalingId;                               // 9 - SpellScaling.dbc
    quint32     SpellAuraOptionsId;                           // 10 - SpellAuraOptions.dbc
    quint32     SpellAuraRestrictionsId;                      // 11 - SpellAuraRestrictions.dbc
    quint32     SpellCastingRequirementsId;                   // 12 - SpellCastingRequirements.dbc
    quint32     SpellCategoriesId;                            // 13 - SpellCategories.dbc
    quint32     SpellClassOptionsId;                          // 14 - SpellClassOptions.dbc
    quint32     SpellCooldownsId;                             // 15 - SpellCooldowns.dbc
    quint32     SpellEquippedItemsId;                         // 16 - SpellEquippedItems.dbc
    quint32     SpellInterruptsId;                            // 17 - SpellInterrupts.dbc
    quint32     SpellLevelsId;                                // 18 - SpellLevels.dbc
    quint32     SpellPowerId;                                 // 19 - SpellPower.dbc
    quint32     SpellReagentsId;                              // 20 - SpellReagents.dbc
    quint32     SpellShapeshiftId;                            // 21 - SpellShapeshift.dbc
    quint32     SpellTargetRestrictionsId;                    // 22 - SpellTargetRestrictions.dbc
    quint32     SpellTotemsId;                                // 23 - SpellTotems.dbc
    quint32     SpellMiscId;                                  // 24 - S.dbc

    // struct access functions
    SpellMiscEntry const* getSpellMisc() const;
    SpellAuraOptionsEntry const* getSpellAuraOptions() const;
    SpellAuraRestrictionsEntry const* getSpellAuraRestrictions() const;
    SpellCastingRequirementsEntry const* getSpellCastingRequirements() const;
    SpellCategoriesEntry const* getSpellCategories() const;
    SpellClassOptionsEntry const* getSpellClassOptions() const;
    SpellCooldownsEntry const* getSpellCooldowns() const;
    SpellEffectEntry const* getSpellEffect(quint8 eff) const;
    SpellEquippedItemsEntry const* getSpellEquippedItems() const;
    SpellInterruptsEntry const* getSpellInterrupts() const;
    SpellLevelsEntry const* getSpellLevels() const;
    SpellPowerEntry const* getSpellPower() const;
    SpellReagentsEntry const* getSpellReagents() const;
    SpellScalingEntry const* getSpellScaling() const;
    SpellShapeshiftEntry const* getSpellShapeshift() const;
    SpellTargetRestrictionsEntry const* getSpellTargetRestrictions() const;
    SpellTotemsEntry const* getSpellTotems() const;

    // SpellMisc methods
    quint32 getAttributes() const;
    quint32 getAttributesEx1() const;
    quint32 getAttributesEx2() const;
    quint32 getAttributesEx3() const;
    quint32 getAttributesEx4() const;
    quint32 getAttributesEx5() const;
    quint32 getAttributesEx6() const;
    quint32 getAttributesEx7() const;
    quint32 getAttributesEx8() const;
    quint32 getAttributesEx9() const;
    quint32 getAttributesEx10() const;
    quint32 getAttributesEx11() const;
    quint32 getCastingTimeIndex() const;
    quint32 getDurationIndex() const;
    quint32 getRangeIndex() const;
    float   getSpeed() const;
    quint32 getSpellVisual(quint8 index) const;
    quint32 getSpellIconId() const;
    quint32 getSpellBuffIconId() const;
    quint32 getSchoolMask() const;
    qint32  getPowerType() const;

    // SpellAuraOptions methods
    quint32 getStackAmount() const;
    quint32 getProcCharges() const;
    quint32 getProcChance() const;
    quint32 getProcFlags() const;

    // SpellAuraRestrictions methods
    quint32 getCasterAuraState() const;
    quint32 getTargetAuraState() const;
    quint32 getCasterAuraStateNot() const;
    quint32 getTargetAuraStateNot() const;
    quint32 getCasterAuraSpell() const;
    quint32 getTargetAuraSpell() const;
    quint32 getExcludeCasterAuraSpell() const;
    quint32 getExcludeTargetAuraSpell() const;

    // SpellCastingRequirements methods
    quint32 getFacingCasterFlags() const;
    quint32 getMinFactionId() const;
    quint32 getMinReputation() const;
    qint32  getAreaGroupId() const;
    quint32  getRequiredAuraVision() const;
    quint32 getRequiresSpellFocus() const;

    // SpellCategories methods
    quint32 getCategory() const;
    quint32 getDamageClass() const;
    quint32 getDispel() const;
    quint32 getMechanic() const;
    quint32 getPreventionType() const;
    quint32 getStartRecoveryCategory() const;

    // SpellClassOptions methods
    quint32 getSpellFamilyName() const;
    quint32 getSpellFamilyFlags(quint8 index) const;
    quint32 getModalNextSpell() const;

    // SpellCooldowns methods
    quint32 getStartRecoveryTime() const;
    quint32 getRecoveryTime() const;
    quint32 getCategoryRecoveryTime() const;

    // SpellEquippedItems methods
    qint32 getEquippedItemClass() const;
    qint32 getEquippedItemSubClassMask() const;
    qint32 getEquippedItemInventoryTypeMask() const;

    // SpellInterrupts methods
    quint32 getInterruptFlags() const;
    quint32 getAuraInterruptFlags() const;
    quint32 getChannelInterruptFlags() const;

    // SpellLevels methods
    quint32 getBaseLevel() const;
    quint32 getMaxLevel() const;
    quint32 getSpellLevel() const;

    // SpellPower methods
    quint32 getManaCost() const;
    quint32 getManaCostPercentage() const;
    quint32 getManaPerSecond() const;
    quint32 getManaCostPerLevel() const;
    quint32 getPowerDisplayId() const;

    // SpellReagents methods
    qint32 getReagent(quint8 index) const;
    quint32 getReagentCount(quint8 index) const;

    // SpellScaling methods
    // need implement

    // SpellTotems methods
    quint32 getTotem(quint8 index) const;
    quint32 getTotemCategory(quint8 index) const;

    // SpellShapeshift methods
    quint32 getStances() const;
    quint32 getStancesNot() const;
    quint32 getStanceBarOrder() const;

    // SpellTargetRestrictions methods
    float   getMaxTargetRadius() const;
    quint32 getTargets() const;
    quint32 getTargetCreatureType() const;
    quint32 getMaxAffectedTargets() const;
    quint32 getMaxTargetLevel() const;

    // SpellEffect methods
    quint32 getEffect(quint8 index) const;                                       // 1        m_effect
    float   getEffectValueMultiplier(quint8 index) const;                        // 2        m_effectAmplitude
    quint32 getEffectApplyAuraName(quint8 index) const;                          // 3        m_effectAura
    quint32 getEffectAmplitude(quint8 index) const;                              // 4        m_effectAuraPeriod
    qint32  getEffectBasePoints(quint8 index) const;                             // 5        m_effectBasePoints (don't must be used in spell/auras explicitly, must be used cached Spell::m_currentBasePoints)
    float   getEffectBonusCoefficient(quint8 index) const;                       // 6        m_effectBonusCoefficient
    float   getEffectDamageMultiplier(quint8 index) const;                       // 7        m_effectChainAmplitude
    quint32 getEffectChainTarget(quint8 index) const;                            // 8        m_effectChainTargets
    qint32  getEffectDieSides(quint8 index) const;                               // 9        m_effectDieSides
    quint32 getEffectItemType(quint8 index) const;                               // 10       m_effectItemType
    quint32 getEffectMechanic(quint8 index) const;                               // 11       m_effectMechanic
    qint32  getEffectMiscValue(quint8 index) const;                              // 12       m_effectMiscValue
    qint32  getEffectMiscValueB(quint8 index) const;                             // 13       m_effectMiscValueB
    float   getEffectPointsPerComboPoint(quint8 index) const;                    // 14       m_effectPointsPerCombo
    quint32 getEffectRadiusIndex(quint8 index) const;                            // 15       m_effectRadiusIndex - spellradius.dbc
    quint32 getEffectRadiusMaxIndex(quint8 index) const;                         // 16       4.0.0
    float   getEffectRealPointsPerLevel(quint8 index) const;                     // 17       m_effectRealPointsPerLevel
    const quint32* getEffectSpellClassMask(quint8 index) const;                  // 18       m_effectSpellClassMask, effect 0
    quint32 getEffectTriggerSpell(quint8 index) const;                           // 19       m_effectTriggerSpell
    quint32 getEffectImplicitTargetA(quint8 index) const;                        // 20       m_implicitTargetA
    quint32 getEffectImplicitTargetB(quint8 index) const;                        // 21       m_implicitTargetB
    quint32 getEffectSpellId(quint8 index) const;                                // 22       new 4.0.0
    quint32 getEffectIndex(quint8 index) const;                                  // 23       new 4.0.0
    quint32 getEffectSpellClassMaskA(quint8 index) const;
    quint32 getEffectSpellClassMaskB(quint8 index) const;
    quint32 getEffectSpellClassMaskC(quint8 index) const;

    private:
        SpellEntry(SpellEntry const&);
};

Q_DECLARE_METATYPE(const SpellEntry*);

struct SpellCastTimesEntry
{
    quint32    Id;                                              // 0
    qint32     CastTime;                                        // 1
    float      CastTimePerLevel;                                // 2 unsure / per skill?
    qint32     MinCastTime;                                     // 3 unsure
};

struct SpellRadiusEntry
{
    quint32    Id;
    float      RadiusHostile;   //hostile
    // Unk
    float      RadiusFriendly;  //friedly
};

struct SpellRangeEntry
{
    quint32    Id;                                              // 0
    float      MinRangeHostile;                                        // 1
    float      MinRangeFriendly;                                // 2
    float      MaxRangeHostile;                                        // 3
    float      MaxRangeFriendly;                                // 4
    quint32    Flags;                                           // 5
    char*      Name;                                        // 6-21 unused
    char*      ShortName;                                   // 23-38 unused
};

struct SpellDurationEntry
{
    quint32    Id;
    qint32     Duration[3];
};

struct SpellIconEntry
{
    quint32    IconId;
    char*      IconPath;
};

// GCC have alternative #pragma pack() syntax and old gcc version not support pack(pop), also any gcc version not support it at some platform
#if defined( __GNUC__ )
#pragma pack()
#else
#pragma pack(pop)
#endif

#endif

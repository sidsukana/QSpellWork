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
};

struct SkillLineAbilityEntry
{
    quint32    Id;                                              // 0 INDEX
    quint32    SkillId;                                         // 1
    quint32    SpellId;                                         // 2
    quint32    RaceMask;                                        // 3
    quint32    ClassMask;                                       // 4
    quint32    RacemaskNot;                                     // 5 unknown
    quint32    ClassMaskNot;                                    // 6 unknown
    quint32    ReqSkillValue;                                   // 7 for trade skill.not for training.
    quint32    ForwardSpellId;                                  // 8
    quint32    LearnOnGetSkill;                                 // 9 can be 1 or 2 for spells learned on get skill
    quint32    MaxValue;                                        // 10
    quint32    MinValue;                                        // 11
    quint32    CharPoints[2];                                   // 12-13
};

struct SpellAuraOptionsEntry
{
    // quint32    Id;                                           // 0       m_ID
    quint32    StackAmount;                                  // 1       m_cumulativeAura
    quint32    ProcChance;                                   // 2       m_procChance
    quint32    ProcCharges;                                  // 3       m_procCharges
    quint32    ProcFlags;                                    // 4       m_procTypeMask
};

struct SpellAuraRestrictionsEntry
{
    // quint32    Id;                                           // 0       m_ID
    quint32    CasterAuraState;                              // 1       m_casterAuraState
    quint32    TargetAuraState;                              // 2       m_targetAuraState
    quint32    CasterAuraStateNot;                           // 3       m_excludeCasterAuraState
    quint32    TargetAuraStateNot;                           // 4       m_excludeTargetAuraState
    quint32    CasterAuraSpell;                              // 5       m_casterAuraSpell
    quint32    TargetAuraSpell;                              // 6       m_targetAuraSpell
    quint32    ExcludeCasterAuraSpell;                       // 7       m_excludeCasterAuraSpell
    quint32    ExcludeTargetAuraSpell;                       // 8       m_excludeTargetAuraSpell
};

struct SpellCastingRequirementsEntry
{
    // quint32    Id;                                           // 0       m_ID
    quint32    FacingCasterFlags;                            // 1       m_facingCasterFlags
    quint32    MinFactionId;                                 // 2       m_minFactionID not used
    quint32    MinReputation;                                // 3       m_minReputation not used
    qint32     AreaGroupId;                                  // 4       m_requiredAreaGroupId
    quint32    RequiredAuraVision;                           // 5       m_requiredAuraVision not used
    quint32    RequiresSpellFocus;                           // 6       m_requiresSpellFocus
};

struct SpellCategoriesEntry
{
    // quint32    Id;                                           // 0       m_ID
    quint32    Category;                                     // 1       m_category
    quint32    DamageClass;                                     // 2       m_defenseType
    quint32    Dispel;                                       // 3       m_dispelType
    quint32    Mechanic;                                     // 4       m_mechanic
    quint32    PreventionType;                               // 5       m_preventionType
    quint32    StartRecoveryCategory;                        // 6       m_startRecoveryCategory
};

struct SpellClassOptionsEntry
{
    // quint32    Id;                                          // 1        m_ID
    quint32    ModalNextSpell;                              // 2        m_modalNextSpell not used
    quint32    SpellFamilyFlags[3];                         // 3-5      m_spellClassMask NOTE: size is 12 bytes!!!
    quint32    SpellFamilyName;                             // 6        m_spellClassSet
    char*      Description;                                 // 7
};

struct SpellCooldownsEntry
{
    // quint32    Id;                                           // 0       m_ID
    quint32    CategoryRecoveryTime;                         // 1       m_categoryRecoveryTime
    quint32    RecoveryTime;                                 // 2       m_recoveryTime
    quint32    StartRecoveryTime;                            // 3       m_startRecoveryTime
};

struct SpellEffectEntry
{
    //quint32    Id;                                         // 0        m_ID
    quint32    Effect;                                       // 1        m_effect
    float      EffectValueMultiplier;                        // 2        m_effectAmplitude
    quint32    EffectApplyAuraName;                          // 3        m_effectAura
    quint32    EffectAmplitude;                              // 4        m_effectAuraPeriod
    qint32     EffectBasePoints;                             // 5        m_effectBasePoints (don't must be used in spell/auras explicitly, must be used cached Spell::m_currentBasePoints)
    float      EffectBonusCoefficient;                       // 6        m_effectBonusCoefficient
    float      EffectDamageMultiplier;                       // 7        m_effectChainAmplitude
    quint32    EffectChainTarget;                            // 8        m_effectChainTargets
    qint32     EffectDieSides;                               // 9        m_effectDieSides
    quint32    EffectItemType;                               // 10       m_effectItemType
    quint32    EffectMechanic;                               // 11       m_effectMechanic
    qint32     EffectMiscValue;                              // 12       m_effectMiscValue
    qint32     EffectMiscValueB;                             // 13       m_effectMiscValueB
    float      EffectPointsPerComboPoint;                    // 14       m_effectPointsPerCombo
    quint32    EffectRadiusIndex;                            // 15       m_effectRadiusIndex - spellradius.dbc
    quint32    EffectRadiusMaxIndex;                         // 16       4.0.0
    float      EffectRealPointsPerLevel;                     // 17       m_effectRealPointsPerLevel
    quint32    EffectSpellClassMask[3];                      // 18       m_effectSpellClassMask, effect 0
    quint32    EffectTriggerSpell;                           // 19       m_effectTriggerSpell
    quint32    EffectImplicitTargetA;                        // 20       m_implicitTargetA
    quint32    EffectImplicitTargetB;                        // 21       m_implicitTargetB
    quint32    EffectSpellId;                                // 22       new 4.0.0
    quint32    EffectIndex;                                  // 23       new 4.0.0
    //quint32    unk;                                        // 24 - 4.2.0
};

struct SpellEffect
{
    SpellEffect()
    {
        effects[0] = NULL;
        effects[1] = NULL;
        effects[2] = NULL;
    }
    SpellEffectEntry const* effects[3];
};

typedef std::map<quint32, SpellEffect> SpellEffectMap;

struct SpellEquippedItemsEntry
{
    // quint32    Id;                                           // 0       m_ID
    qint32     EquippedItemClass;                            // 1       m_equippedItemClass (value)
    qint32     EquippedItemInventoryTypeMask;                // 2       m_equippedItemInvTypes (mask)
    qint32     EquippedItemSubClassMask;                     // 3       m_equippedItemSubclass (mask)
};

struct SpellInterruptsEntry
{
    // quint32    Id;                                           // 0        m_ID
    quint32    AuraInterruptFlags;                           // 1       m_auraInterruptFlags
    // quint32    Unk1;                                          // 2       4.0.0
    quint32    ChannelInterruptFlags;                        // 3       m_channelInterruptFlags
    // quint32    Unk2;                                          // 4       4.0.0
    quint32    InterruptFlags;                               // 5       m_interruptFlags
};

struct SpellLevelsEntry
{
    // quint32    Id;                                           // 0        m_ID
    quint32    BaseLevel;                                    // 41       m_baseLevel
    quint32    MaxLevel;                                     // 40       m_maxLevel
    quint32    SpellLevel;                                   // 42       m_spellLevel
};

struct SpellPowerEntry
{
    // quint32    Id;                                           // 0        m_ID
    quint32    ManaCost;                                     // 1       m_manaCost
    quint32    ManaCostPerlevel;                             // 2       m_manaCostPerLevel
    quint32    ManaCostPercentage;                           // 3      m_manaCostPct
    quint32    ManaPerSecond;                                // 4       m_manaPerSecond
    quint32    PowerDisplayId;                               // 5      m_powerDisplayID - id from PowerDisplay.dbc, new in 3.1
    // quint32    Unk1;                                         // 6        4.0.0
};

struct SpellReagentsEntry
{
    // quint32    Id;                          // 0        m_ID
    qint32     Reagent[MAX_SPELL_REAGENTS];                     // 1-9    m_reagent
    quint32    ReagentCount[MAX_SPELL_REAGENTS];                // 10-17    m_reagentCount
};

struct SpellScalingEntry
{
    // quint32    Id;                                           // 0        m_ID
    quint32    CastTimeMin;                                  // 1
    quint32    CastTimeMax;                                  // 2
    quint32    CastScalingMaxLevel;                          // 3
    quint32    PlayerClass;                                  // 4        (index * 100) + charLevel => gtSpellScaling.dbc
    float      Coeff1[MAX_EFFECT_INDEX];                                    // 5-7
    float      Coeff2[MAX_EFFECT_INDEX];                                    // 8-10
    float      Coeff3[MAX_EFFECT_INDEX];                                    // 11-13
    float      UnkMult;                                      // 14        some coefficient, mostly 1.0f
    quint32    UnkLevel;                                     // 15        some level
};

struct SpellShapeshiftEntry
{
    // quint32     Id;                                           // 0        m_ID
    quint32     Stances[2];                                      // 13       m_shapeshiftMask
    quint32     StancesNot[2];                                   // 15       m_shapeshiftExclude
    quint32     StanceBarOrder;                            // 155      m_stanceBarOrder not used
};

struct SpellTargetRestrictionsEntry
{
    // quint32    Id;                                           // 0        m_ID
    float      MaxTargetRadius;                              // 1 - m_maxTargetRadius
    quint32    MaxAffectedTargets;                           // 2        m_maxTargets
    quint32    MaxTargetLevel;                               // 3        m_maxTargetLevel
    quint32    TargetCreatureType;                           // 4        m_targetCreatureType
    quint32    Targets;                                      // 5        m_targets
};

struct SpellTotemsEntry
{
    // quint32    Id;                                        // 0        m_ID
    quint32    TotemCategory[MAX_SPELL_TOTEM_CATEGORIES];                               // 162-163  m_requiredTotemCategoryID
    quint32    Totem[MAX_SPELL_TOTEMS];                                       // 52-53    m_totem
};

struct SpellEntry
{
    quint32     Id;                                           // 0        m_ID
    quint32     Attributes;                                   // 1        m_attribute
    quint32     AttributesEx;                                 // 2        m_attributesEx
    quint32     AttributesEx2;                                // 3        m_attributesExB
    quint32     AttributesEx3;                                // 4        m_attributesExC
    quint32     AttributesEx4;                                // 5        m_attributesExD
    quint32     AttributesEx5;                                // 6        m_attributesExE
    quint32     AttributesEx6;                                // 7        m_attributesExF
    quint32     AttributesEx7;                                // 8       3.2.0 (0x20 - totems, 0x4 - paladin auras, etc...)
    quint32     AttributesEx8;                                // 9        m_attributesExH
    // quint32     unk_400_1;                                 // 10       4.0.0
    // quint32     unk_420;                                   // 11 - 4.2.0
    quint32     CastingTimeIndex;                             // 12 - m_castingTimeIndex
    quint32     DurationIndex;                                // 13 - m_durationIndex
    quint32     PowerType;                                    // 14 - m_powerType
    quint32     RangeIndex;                                   // 15 - m_rangeIndex
    float       Speed;                                        // 16 - m_speed
    quint32     SpellVisual[2];                               // 17 - m_spellVisualID, 18 - m_spellVisualID1
    quint32     SpellIconId;                                  // 19 - m_spellIconID
    quint32     ActiveIconId;                                 // 20 - m_activeIconID
    char*       SpellName;                                    // 21 - m_name_lang
    char*       Rank;                                         // 22 - m_nameSubtext_lang
    char*       Description;                                  // 23 - m_description_lang not used
    char*       ToolTip;                                      // 24 - m_auraDescription_lang not used
    quint32     SchoolMask;                                   // 25 - m_schoolMask
    quint32     RuneCostId;                                   // 26 - m_runeCostID
    quint32     SpellMissileId;                               // 27 - m_spellMissileID not used
    quint32     SpellDescriptionVariableId;                   // 28 - m_spellDescriptionVariableID, 3.2.0
    quint32     SpellDifficultyId;                            // 29 - m_spellDifficultyID - id from SpellDifficulty.dbc
    // float       unk_f1;                                    // 30 - 4.0.1
    quint32     SpellScalingId;                               // 31 - SpellScaling.dbc
    quint32     SpellAuraOptionsId;                           // 32 - SpellAuraOptions.dbc
    quint32     SpellAuraRestrictionsId;                      // 33 - SpellAuraRestrictions.dbc
    quint32     SpellCastingRequirementsId;                   // 34 - SpellCastingRequirements.dbc
    quint32     SpellCategoriesId;                            // 35 - SpellCategories.dbc
    quint32     SpellClassOptionsId;                          // 36 - SpellClassOptions.dbc
    quint32     SpellCooldownsId;                             // 37 - SpellCooldowns.dbc
    // quint32     UnkIndex7;                                 // 38 - all zeros...
    quint32     SpellEquippedItemsId;                         // 39 - SpellEquippedItems.dbc
    quint32     SpellInterruptsId;                            // 40 - SpellInterrupts.dbc
    quint32     SpellLevelsId;                                // 41 - SpellLevels.dbc
    quint32     SpellPowerId;                                 // 42 - SpellPower.dbc
    quint32     SpellReagentsId;                              // 43 - SpellReagents.dbc
    quint32     SpellShapeshiftId;                            // 44 - SpellShapeshift.dbc
    quint32     SpellTargetRestrictionsId;                    // 45 - SpellTargetRestrictions.dbc
    quint32     SpellTotemsId;                                // 46 - SpellTotems.dbc
    // quint32     ResearchProject;                           // 47 - ResearchProject.dbc

    // struct access functions
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
    quint32 getStances(quint8 index) const;
    quint32 getStancesNot(quint8 index) const;
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

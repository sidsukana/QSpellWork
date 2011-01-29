#ifndef DBCSTRUCTURE_H
#define DBCSTRUCTURE_H

#include "Defines.h"
#include "Platform/Define.h"

#include <map>
#include <set>

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
    quint32    SkillCostId;                                     // 2 not used
    char*      Name[16];                                        // 3-18
    quint32    NameFlags;                                       // 19 string flags, not used
    char*      Description[16];                                 // 20-35, not used
    quint32    DescFlags;                                       // 36 string flags, not used
    quint32    SpellIcon;                                       // 37
};

struct SkillLineAbilityEntry
{
    quint32    Id;                                              // 0 INDEX
    quint32    SkillId;                                         // 1
    quint32    SpellId;                                         // 2
    quint32    RaceMask;                                        // 3
    quint32    ClassMask;                                       // 4
    quint32    Unk1;                                            // 5 unknown
    quint32    Unk2;                                            // 6 unknown
    quint32    ReqSkillValue;                                   // 7 for trade skill.not for training.
    quint32    ForwardSpellId;                                  // 8
    quint32    LearnOnGetSkill;                                 // 9 can be 1 or 2 for spells learned on get skill
    quint32    MaxValue;                                        // 10
    quint32    MinValue;                                        // 11
    quint32    CharPoints[2];                                   // 12-13
    quint32    Reqtrainpoints;                                  // 14
};

#define MAX_SPELL_REAGENTS 8
#define MAX_SPELL_TOTEMS 2
#define MAX_SPELL_TOTEM_CATEGORIES 2

struct SpellEntry
{
    quint32    Id;                                              // 0 normally counted from 0 field (but some tools start counting from 1, check this before tool use for data view!)
    quint32    Category;                                        // 1
    quint32    CastUI;                                          // 2 not used
    quint32    Dispel;                                          // 3
    quint32    Mechanic;                                        // 4
    quint32    Attributes;                                      // 5
    quint32    AttributesEx;                                    // 6
    quint32    AttributesEx2;                                   // 7
    quint32    AttributesEx3;                                   // 8
    quint32    AttributesEx4;                                   // 9
    quint32    AttributesEx5;                                   // 10
    quint32    AttributesEx6;                                   // 11
    quint32    Stances;                                         // 12
    quint32    StancesNot;                                      // 13
    quint32    Targets;                                         // 14
    quint32    TargetCreatureType;                              // 15
    quint32    RequiresSpellFocus;                              // 16
    quint32    FacingCasterFlags;                               // 17
    quint32    CasterAuraState;                                 // 18
    quint32    TargetAuraState;                                 // 19
    quint32    CasterAuraStateNot;                              // 20
    quint32    TargetAuraStateNot;                              // 21
    quint32    CastingTimeIndex;                                // 22
    quint32    RecoveryTime;                                    // 23
    quint32    CategoryRecoveryTime;                            // 24
    quint32    InterruptFlags;                                  // 25
    quint32    AuraInterruptFlags;                              // 26
    quint32    ChannelInterruptFlags;                           // 27
    quint32    ProcFlags;                                       // 28
    quint32    ProcChance;                                      // 29
    quint32    ProcCharges;                                     // 30
    quint32    MaxLevel;                                        // 31
    quint32    BaseLevel;                                       // 32
    quint32    SpellLevel;                                      // 33
    quint32    DurationIndex;                                   // 34
    quint32    PowerType;                                       // 35
    quint32    ManaCost;                                        // 36
    quint32    ManaCostPerlevel;                                // 37
    quint32    ManaPerSecond;                                   // 38
    quint32    ManaPerSecondPerLevel;                           // 39
    quint32    RangeIndex;                                      // 40
    float      Speed;                                           // 41
    quint32    ModalNextSpell;                                  // 42
    quint32    StackAmount;                                     // 43
    quint32    Totem[MAX_SPELL_TOTEMS];                         // 44-45
    qint32     Reagent[MAX_SPELL_REAGENTS];                     // 46-53
    quint32    ReagentCount[MAX_SPELL_REAGENTS];                // 54-61
    qint32     EquippedItemClass;                               // 62 (value)
    qint32     EquippedItemSubClassMask;                        // 63 (mask)
    qint32     EquippedItemInventoryTypeMask;                   // 64 (mask)
    quint32    Effect[MAX_EFFECT_INDEX];                        // 65-67
    qint32     EffectDieSides[MAX_EFFECT_INDEX];                // 68-70
    quint32    EffectBaseDice[MAX_EFFECT_INDEX];                // 71-73
    float      EffectDicePerLevel[MAX_EFFECT_INDEX];            // 74-76
    float      EffectRealPointsPerLevel[MAX_EFFECT_INDEX];      // 77-79
    qint32     EffectBasePoints[MAX_EFFECT_INDEX];              // 80-82 (don't must be used in spell/auras explicitly, must be used cached Spell::m_currentBasePoints)
    quint32    EffectMechanic[MAX_EFFECT_INDEX];                // 83-85
    quint32    EffectImplicitTargetA[MAX_EFFECT_INDEX];         // 86-88
    quint32    EffectImplicitTargetB[MAX_EFFECT_INDEX];         // 89-91
    quint32    EffectRadiusIndex[MAX_EFFECT_INDEX];             // 92-94 - spellradius.dbc
    quint32    EffectApplyAuraName[MAX_EFFECT_INDEX];           // 95-97
    quint32    EffectAmplitude[MAX_EFFECT_INDEX];               // 98-100
    float      EffectMultipleValue[MAX_EFFECT_INDEX];           // 101-103
    quint32    EffectChainTarget[MAX_EFFECT_INDEX];             // 104-106
    quint32    EffectItemType[MAX_EFFECT_INDEX];                // 107-109
    qint32     EffectMiscValue[MAX_EFFECT_INDEX];               // 110-112
    qint32     EffectMiscValueB[MAX_EFFECT_INDEX];              // 113-115
    quint32    EffectTriggerSpell[MAX_EFFECT_INDEX];            // 116-118
    float      EffectPointsPerComboPoint[MAX_EFFECT_INDEX];     // 119-121
    quint32    SpellVisual;                                     // 122
    quint32    Unk1;                                            // 123 not used
    quint32    SpellIconID;                                     // 124
    quint32    ActiveIconID;                                    // 125
    quint32    SpellPriority;                                   // 126
    char*      SpellName[16];                                   // 127-142
    quint32    SpellNameFlag;                                   // 143
    char*      Rank[16];                                        // 144-159
    quint32    RankFlags;                                       // 160
    char*      Description[16];                                 // 161-176 not used
    quint32    DescriptionFlags;                                // 177     not used
    char*      ToolTip[16];                                     // 178-193 not used
    quint32    ToolTipFlags;                                    // 194     not used
    quint32    ManaCostPercentage;                              // 195
    quint32    StartRecoveryCategory;                           // 196
    quint32    StartRecoveryTime;                               // 197
    quint32    MaxTargetLevel;                                  // 198
    quint32    SpellFamilyName;                                 // 199
    quint64    SpellFamilyFlags;                                // 200+201
    quint32    MaxAffectedTargets;                              // 202
    quint32    DmgClass;                                        // 203 defenseType
    quint32    PreventionType;                                  // 204
    quint32    StanceBarOrder;                                  // 205 not used
    float      DmgMultiplier[MAX_EFFECT_INDEX];                 // 206-208
    quint32    MinFactionId;                                    // 209 not used, and 0 in 2.4.2
    quint32    MinReputation;                                   // 210 not used, and 0 in 2.4.2
    quint32    RequiredAuraVision;                              // 211 not used
    quint32    TotemCategory[MAX_SPELL_TOTEM_CATEGORIES];       // 212-213
    quint32    AreaId;                                          // 214
    quint32    SchoolMask;                                      // 215 school mask

    private:
        SpellEntry(SpellEntry const&);
};

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
    float      Radius;   //hostile
    qint32     Zero;
    float      Radius2;  //friedly
};

struct SpellRangeEntry
{
    quint32    Id;                                              // 0
    float      MinRange;                                        // 1
    float      MaxRange;                                        // 2
    quint32    Flags;                                           // 3
    char*      Name[16];                                        // 4-19 unused
    quint32    NameFlags;                                       // 20 unused
    char*      ShortName[16];                                   // 21-36 unused
    quint32    ShortNameFlags;                                  // 37 unused
};

struct SpellDurationEntry
{
    quint32    Id;
    qint32     Duration[3];
};

// GCC have alternative #pragma pack() syntax and old gcc version not support pack(pop), also any gcc version not support it at some platform
#if defined( __GNUC__ )
#pragma pack()
#else
#pragma pack(pop)
#endif

#endif

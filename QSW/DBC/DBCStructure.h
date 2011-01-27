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
    quint32    Id;                                   // 0
    qint32     CategoryId;                           // 1 (index from SkillLineCategory.dbc)
    quint32    SkillCostId;                          // 2 not used
    char*      Name[8];                              // 3-10
    quint32    NameFlags;                            // 11 string flags, not used
    char*      Description[8];                       // 12-19, not used
    quint32    DescFlags;                            // 20 string flags, not used
    quint32    SpellIcon;                            // 21
};

struct SkillLineAbilityEntry
{
    quint32    Id;                                           // 0 INDEX
    quint32    SkillId;                                      // 1
    quint32    SpellId;                                      // 2
    quint32    RaceMask;                                     // 3
    quint32    ClassMask;                                    // 4
    quint32    Unk1;                                         // 5 unknown
    quint32    Unk2;                                         // 6 unknown
    quint32    ReqSkillValue;                              // 7 for trade skill.not for training.
    quint32    ForwardSpellId;                              // 8
    quint32    LearnOnGetSkill;                              // 9 can be 1 or 2 for spells learned on get skill
    quint32    MaxValue;                                    // 10
    quint32    MinValue;                                    // 11
    quint32    CharPoints[2];                                // 12-13
    quint32    Reqtrainpoints;                               // 14
};

#define MAX_SPELL_REAGENTS 8
#define MAX_SPELL_TOTEMS 2

struct SpellEntry
{
    quint32    Id;                                           // 0 normally counted from 0 field (but some tools start counting from 1, check this before tool use for data view!)
    quint32    School;                                       // 1 not schoolMask from 2.x - just school type so everything linked with SpellEntry::SchoolMask must be rewrited
    quint32    Category;                                     // 2
    quint32    CastUI;                                       // 3 not used
    quint32    Dispel;                                       // 4
    quint32    Mechanic;                                     // 5
    quint32    Attributes;                                   // 6
    quint32    AttributesEx;                                 // 7
    quint32    AttributesEx2;                                // 8
    quint32    AttributesEx3;                                // 9
    quint32    AttributesEx4;                                // 10
    quint32    Stances;                                      // 11
    quint32    StancesNot;                                   // 12
    quint32    Targets;                                      // 13
    quint32    TargetCreatureType;                           // 14
    quint32    RequiresSpellFocus;                           // 15
    quint32    CasterAuraState;                              // 16
    quint32    TargetAuraState;                              // 17
    quint32    CastingTimeIndex;                             // 18
    quint32    RecoveryTime;                                 // 19
    quint32    CategoryRecoveryTime;                         // 20
    quint32    InterruptFlags;                               // 21
    quint32    AuraInterruptFlags;                           // 22
    quint32    ChannelInterruptFlags;                        // 23
    quint32    ProcFlags;                                    // 24
    quint32    ProcChance;                                   // 25
    quint32    ProcCharges;                                  // 26
    quint32    MaxLevel;                                     // 27
    quint32    BaseLevel;                                    // 28
    quint32    SpellLevel;                                   // 29
    quint32    DurationIndex;                                // 30
    quint32    PowerType;                                    // 31
    quint32    ManaCost;                                     // 32
    quint32    ManaCostPerlevel;                             // 33
    quint32    ManaPerSecond;                                // 34
    quint32    ManaPerSecondPerLevel;                        // 35
    quint32    RangeIndex;                                   // 36
    float      Speed;                                        // 37
    quint32    ModalNextSpell;                               // 38 not used
    quint32    StackAmount;                                  // 39
    quint32    Totem[MAX_SPELL_TOTEMS];                      // 40-41
    qint32     Reagent[MAX_SPELL_REAGENTS];                  // 42-49
    quint32    ReagentCount[MAX_SPELL_REAGENTS];             // 50-57
    qint32     EquippedItemClass;                            // 58 (value)
    qint32     EquippedItemSubClassMask;                     // 59 (mask)
    qint32     EquippedItemInventoryTypeMask;                // 60 (mask)
    quint32    Effect[MAX_EFFECT_INDEX];                     // 61-63
    qint32     EffectDieSides[MAX_EFFECT_INDEX];             // 64-66
    quint32    EffectBaseDice[MAX_EFFECT_INDEX];             // 67-69
    float      EffectDicePerLevel[MAX_EFFECT_INDEX];         // 70-72
    float      EffectRealPointsPerLevel[MAX_EFFECT_INDEX];   // 73-75
    qint32     EffectBasePoints[MAX_EFFECT_INDEX];           // 76-78 (don't must be used in spell/auras explicitly, must be used cached Spell::m_currentBasePoints)
    quint32    EffectMechanic[MAX_EFFECT_INDEX];             // 79-81
    quint32    EffectImplicitTargetA[MAX_EFFECT_INDEX];      // 82-84
    quint32    EffectImplicitTargetB[MAX_EFFECT_INDEX];      // 85-87
    quint32    EffectRadiusIndex[MAX_EFFECT_INDEX];          // 88-90 - spellradius.dbc
    quint32    EffectApplyAuraName[MAX_EFFECT_INDEX];        // 91-93
    quint32    EffectAmplitude[MAX_EFFECT_INDEX];            // 94-96
    float      EffectMultipleValue[MAX_EFFECT_INDEX];        // 97-99
    quint32    EffectChainTarget[MAX_EFFECT_INDEX];          // 100-102
    quint32    EffectItemType[MAX_EFFECT_INDEX];             // 103-105
    qint32     EffectMiscValue[MAX_EFFECT_INDEX];            // 106-108
    quint32    EffectTriggerSpell[MAX_EFFECT_INDEX];         // 109-111
    float      EffectPointsPerComboPoint[MAX_EFFECT_INDEX];  // 112-114
    quint32    SpellVisual;                                  // 115
    quint32    SpellVisual2;                                 // 116 not used
    quint32    SpellIconID;                                  // 117
    quint32    ActiveIconID;                                 // 118
    quint32    SpellPriority;                                // 119
    char*      SpellName[8];                                 // 120-127
    quint32    SpellNameFlag;                                // 128
    char*      Rank[8];                                      // 129-136
    quint32    RankFlags;                                    // 137
    char*      Description[8];                               // 138-145 not used
    quint32    DescriptionFlags;                             // 146     not used
    char*      ToolTip[8];                                   // 147-154 not used
    quint32    ToolTipFlags;                                 // 155     not used
    quint32    ManaCostPercentage;                           // 156
    quint32    StartRecoveryCategory;                        // 157
    quint32    StartRecoveryTime;                            // 158
    quint32    MaxTargetLevel;                               // 159
    quint32    SpellFamilyName;                              // 160
    quint64    SpellFamilyFlags;                             // 161+162
    quint32    MaxAffectedTargets;                           // 163
    quint32    DmgClass;                                     // 164 defenseType
    quint32    PreventionType;                               // 165
    float      StanceBarOrder;                               // 166 not used
    float      DmgMultiplier[MAX_EFFECT_INDEX];              // 167-169
    quint32    MinFactionId;                                 // 170 not used, and 0 in 2.4.2
    quint32    MinReputation;                                // 171 not used, and 0 in 2.4.2
    quint32    RequiredAuraVision;                           // 172 not used

    private:
        SpellEntry(SpellEntry const&);
};

struct SpellCastTimesEntry
{
    quint32    Id;                                           // 0
    qint32     CastTime;                                     // 1
    float      CastTimePerLevel;                             // 2 unsure / per skill?
    qint32     MinCastTime;                                  // 3 unsure
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
    quint32    Id;                                           // 0
    float      MinRange;                                     // 1
    float      MaxRange;                                     // 2
    quint32    Flags;                                        // 3
    char*      Name[8];                                      // 4-11 unused
    quint32    NameFlags;                                    // 12 unused
    char*      ShortName[8];                                 // 13-20 unused
    quint32    ShortNameFlags;                               // 21 unused
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

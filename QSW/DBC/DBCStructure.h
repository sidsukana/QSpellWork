#ifndef DBCSTRUCTURE_H
#define DBCSTRUCTURE_H

#include "SWDefines.h"
#include "Define.h"

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
    char*      Name[8];                                         // 3-10
    quint32    NameFlags;                                       // 11 string flags, not used
    char*      Description[8];                                  // 12-19, not used
    quint32    DescFlags;                                       // 20 string flags, not used
    quint32    SpellIcon;                                       // 21
};

struct SkillLineAbilityEntry
{
    quint32    Id;                                              // 0 Index
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

struct SpellEntry
{
    quint32    Id;                                              // 0 normally counted from 0 field (but some tools start counting from 1, check this before tool use for data view!)
    quint32    School;                                          // 1 not schoolMask from 2.x - just school type so everything linked with SpellEntry::SchoolMask must be rewrited
    quint32    Category;                                        // 2
    quint32    CastUI;                                          // 3 not used
    quint32    Dispel;                                          // 4
    quint32    Mechanic;                                        // 5
    quint32    Attributes;                                      // 6
    quint32    AttributesEx;                                    // 7
    quint32    AttributesEx2;                                   // 8
    quint32    AttributesEx3;                                   // 9
    quint32    AttributesEx4;                                   // 10
    quint32    Stances;                                         // 11
    quint32    StancesNot;                                      // 12
    quint32    Targets;                                         // 13
    quint32    TargetCreatureType;                              // 14
    quint32    RequiresSpellFocus;                              // 15
    quint32    CasterAuraState;                                 // 16
    quint32    TargetAuraState;                                 // 17
    quint32    CastingTimeIndex;                                // 18
    quint32    RecoveryTime;                                    // 19
    quint32    CategoryRecoveryTime;                            // 20
    quint32    InterruptFlags;                                  // 21
    quint32    AuraInterruptFlags;                              // 22
    quint32    ChannelInterruptFlags;                           // 23
    quint32    ProcFlags;                                       // 24
    quint32    ProcChance;                                      // 25
    quint32    ProcCharges;                                     // 26
    quint32    MaxLevel;                                        // 27
    quint32    BaseLevel;                                       // 28
    quint32    SpellLevel;                                      // 29
    quint32    DurationIndex;                                   // 30
    qint32     PowerType;                                       // 31
    quint32    ManaCost;                                        // 32
    quint32    ManaCostPerlevel;                                // 33
    quint32    ManaPerSecond;                                   // 34
    quint32    ManaPerSecondPerLevel;                           // 35
    quint32    RangeIndex;                                      // 36
    float      Speed;                                           // 37
    quint32    ModalNextSpell;                                  // 38 not used
    quint32    StackAmount;                                     // 39
    uarray2    Totem;                                           // 40-41
    iarray8    Reagent;                                         // 42-49
    uarray8    ReagentCount;                                    // 50-57
    qint32     EquippedItemClass;                               // 58 (value)
    qint32     EquippedItemSubClassMask;                        // 59 (mask)
    qint32     EquippedItemInventoryTypeMask;                   // 60 (mask)
    uarray3    Effect;                                          // 61-63
    uarray3    EffectDieSides;                                  // 64-66
    uarray3    EffectBaseDice;                                  // 67-69
    farray3    EffectDicePerLevel;                              // 70-72
    farray3    EffectRealPointsPerLevel;                        // 73-75
    iarray3    EffectBasePoints;                                // 76-78 (don't must be used in spell/auras explicitly, must be used cached Spell::m_currentBasePoints)
    uarray3    EffectMechanic;                                  // 79-81
    uarray3    EffectImplicitTargetA;                           // 82-84
    uarray3    EffectImplicitTargetB;                           // 85-87
    uarray3    EffectRadiusIndex;                               // 88-90 - spellradius.dbc
    uarray3    EffectApplyAuraName;                             // 91-93
    uarray3    EffectAmplitude;                                 // 94-96
    farray3    EffectMultipleValue;                             // 97-99
    uarray3    EffectChainTarget;                               // 100-102
    uarray3    EffectItemType;                                  // 103-105
    iarray3    EffectMiscValue;                                 // 106-108
    uarray3    EffectTriggerSpell;                              // 109-111
    farray3    EffectPointsPerComboPoint;                       // 112-114
    uarray2    SpellVisual;                                     // 115-116
    quint32    SpellIconId;                                     // 117
    quint32    ActiveIconId;                                    // 118
    quint32    SpellPriority;                                   // 119
    char*      SpellName[8];                                    // 120-127
    quint32    SpellNameFlag;                                   // 128
    char*      Rank[8];                                         // 129-136
    quint32    RankFlags;                                       // 137
    char*      Description[8];                                  // 138-145 not used
    quint32    DescriptionFlags;                                // 146     not used
    char*      ToolTip[8];                                      // 147-154 not used
    quint32    ToolTipFlags;                                    // 155     not used
    quint32    ManaCostPercentage;                              // 156
    quint32    StartRecoveryCategory;                           // 157
    quint32    StartRecoveryTime;                               // 158
    quint32    MaxTargetLevel;                                  // 159
    quint32    SpellFamilyName;                                 // 160
    quint64    SpellFamilyFlags;                                // 161+162
    quint32    MaxAffectedTargets;                              // 163
    quint32    DamageClass;                                     // 164 defenseType
    quint32    PreventionType;                                  // 165
    qint32     StanceBarOrder;                                  // 166 not used
    farray3    DamageMultiplier;                                // 167-169
    quint32    MinFactionId;                                    // 170 not used, and 0 in 2.4.2
    quint32    MinReputation;                                   // 171 not used, and 0 in 2.4.2
    quint32    RequiredAuraVision;                              // 172 not used

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
    quint32    Id;                                              // 0
    float      Radius;                                          // 1 Hostile
    qint32     Zero;                                            // 2
    float      Radius2;                                         // 3 Friedly
};

struct SpellRangeEntry
{
    quint32    Id;                                              // 0
    float      MinRange;                                        // 1
    float      MaxRange;                                        // 2
    quint32    Flags;                                           // 3
    char*      Name[8];                                         // 4-11 unused
    quint32    NameFlags;                                       // 12 unused
    char*      ShortName[8];                                    // 13-20 unused
    quint32    ShortNameFlags;                                  // 21 unused
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

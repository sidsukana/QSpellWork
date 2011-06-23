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
    qint32     PowerType;                                       // 35
    quint32    ManaCost;                                        // 36
    quint32    ManaCostPerlevel;                                // 37
    quint32    ManaPerSecond;                                   // 38
    quint32    ManaPerSecondPerLevel;                           // 39
    quint32    RangeIndex;                                      // 40
    float      Speed;                                           // 41
    quint32    ModalNextSpell;                                  // 42
    quint32    StackAmount;                                     // 43
    uarray2    Totem;                                           // 44-45
    iarray8    Reagent;                                         // 46-53
    uarray8    ReagentCount;                                    // 54-61
    qint32     EquippedItemClass;                               // 62 (value)
    qint32     EquippedItemSubClassMask;                        // 63 (mask)
    qint32     EquippedItemInventoryTypeMask;                   // 64 (mask)
    uarray3    Effect;                                          // 65-67
    iarray3    EffectDieSides;                                  // 68-70
    uarray3    EffectBaseDice;                                  // 71-73
    farray3    EffectDicePerLevel;                              // 74-76
    farray3    EffectRealPointsPerLevel;                        // 77-79
    iarray3    EffectBasePoints;                                // 80-82 (don't must be used in spell/auras explicitly, must be used cached Spell::m_currentBasePoints)
    uarray3    EffectMechanic;                                  // 83-85
    uarray3    EffectImplicitTargetA;                           // 86-88
    uarray3    EffectImplicitTargetB;                           // 89-91
    uarray3    EffectRadiusIndex;                               // 92-94 - spellradius.dbc
    uarray3    EffectApplyAuraName;                             // 95-97
    uarray3    EffectAmplitude;                                 // 98-100
    farray3    EffectMultipleValue;                             // 101-103
    uarray3    EffectChainTarget;                               // 104-106
    uarray3    EffectItemType;                                  // 107-109
    iarray3    EffectMiscValue;                                 // 110-112
    iarray3    EffectMiscValueB;                                // 113-115
    uarray3    EffectTriggerSpell;                              // 116-118
    farray3    EffectPointsPerComboPoint;                       // 119-121
    uarray2    SpellVisual;                                     // 122-123
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
    qint32     StanceBarOrder;                                  // 205 not used
    farray3    DmgMultiplier;                                   // 206-208
    quint32    MinFactionId;                                    // 209 not used, and 0 in 2.4.2
    quint32    MinReputation;                                   // 210 not used, and 0 in 2.4.2
    quint32    RequiredAuraVision;                              // 211 not used
    uarray2    TotemCategory;                                   // 212-213
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

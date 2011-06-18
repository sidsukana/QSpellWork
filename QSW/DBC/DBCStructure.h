#ifndef DBCSTRUCTURE_H
#define DBCSTRUCTURE_H

#include "SWDefines.h"
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
    char*      AlternateVerb[16];                               // 38-53, not used
    quint32    VerbFlags;                                       // 54
    quint32    CanLink;                                         // 55
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

struct SpellEntry
{
    quint32    Id;                                              // 0 normally counted from 0 field (but some tools start counting from 1, check this before tool use for data view!)
    quint32    Category;                                        // 1
    quint32    Dispel;                                          // 2
    quint32    Mechanic;                                        // 3
    quint32    Attributes;                                      // 4
    quint32    AttributesEx;                                    // 5
    quint32    AttributesEx2;                                   // 6
    quint32    AttributesEx3;                                   // 7
    quint32    AttributesEx4;                                   // 8
    quint32    AttributesEx5;                                   // 9
    quint32    AttributesEx6;                                   // 10
    quint32    AttributesExG;                                   // 11
    uarray2    Stances;                                         // 12-13
    uarray2    StancesNot;                                      // 14-15
    quint32    Targets;                                         // 16
    quint32    TargetCreatureType;                              // 17
    quint32    RequiresSpellFocus;                              // 18
    quint32    FacingCasterFlags;                               // 19
    quint32    CasterAuraState;                                 // 20
    quint32    TargetAuraState;                                 // 21
    quint32    CasterAuraStateNot;                              // 22
    quint32    TargetAuraStateNot;                              // 23
    quint32    CasterAuraSpell;                                 // 24
    quint32    TargetAuraSpell;                                 // 25
    quint32    ExcludeCasterAuraSpell;                          // 26
    quint32    ExcludeTargetAuraSpell;                          // 27
    quint32    CastingTimeIndex;                                // 28
    quint32    RecoveryTime;                                    // 29
    quint32    CategoryRecoveryTime;                            // 30
    quint32    InterruptFlags;                                  // 31
    quint32    AuraInterruptFlags;                              // 32
    quint32    ChannelInterruptFlags;                           // 33
    quint32    ProcFlags;                                       // 34
    quint32    ProcChance;                                      // 35
    quint32    ProcCharges;                                     // 36
    quint32    MaxLevel;                                        // 37
    quint32    BaseLevel;                                       // 38
    quint32    SpellLevel;                                      // 39
    quint32    DurationIndex;                                   // 40
    qint32     PowerType;                                       // 41
    quint32    ManaCost;                                        // 42
    quint32    ManaCostPerlevel;                                // 43
    quint32    ManaPerSecond;                                   // 44
    quint32    ManaPerSecondPerLevel;                           // 45
    quint32    RangeIndex;                                      // 46
    float      Speed;                                           // 47
    quint32    ModalNextSpell;                                  // 48
    quint32    StackAmount;                                     // 49
    uarray2    Totem;                                           // 50-51
    iarray8    Reagent;                                         // 52-59
    uarray8    ReagentCount;                                    // 60-67
    qint32     EquippedItemClass;                               // 68 (value)
    qint32     EquippedItemSubClassMask;                        // 69 (mask)
    qint32     EquippedItemInventoryTypeMask;                   // 70 (mask)
    uarray3    Effect;                                          // 71-73
    iarray3    EffectDieSides;                                  // 74-76
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
    uarray3    EffectSpellClassMaskA;                           // 122-124  m_effectSpellClassMaskA, effect 0
    uarray3    EffectSpellClassMaskB;                           // 125-127  m_effectSpellClassMaskB, effect 1
    uarray3    EffectSpellClassMaskC;                           // 128-130  m_effectSpellClassMaskC, effect 2
    uarray2    SpellVisual;                                     // 131-132
    quint32    SpellIconID;                                     // 133
    quint32    ActiveIconID;                                    // 134
    quint32    SpellPriority;                                   // 135
    char*      SpellName[16];                                   // 136-151
    quint32    SpellNameFlag;                                   // 152
    char*      Rank[16];                                        // 153-168
    quint32    RankFlags;                                       // 169
    char*      Description[16];                                 // 170-185 not used
    quint32    DescriptionFlags;                                // 186     not used
    char*      ToolTip[16];                                     // 187-202 not used
    quint32    ToolTipFlags;                                    // 203     not used
    quint32    ManaCostPercentage;                              // 204
    quint32    StartRecoveryCategory;                           // 205
    quint32    StartRecoveryTime;                               // 206
    quint32    MaxTargetLevel;                                  // 207
    quint32    SpellFamilyName;                                 // 208
    uarray3    SpellFamilyFlags;                                // 209+211
    quint32    MaxAffectedTargets;                              // 212
    quint32    DmgClass;                                        // 213 defenseType
    quint32    PreventionType;                                  // 214
    qint32     StanceBarOrder;                                  // 215 not used
    farray3    DmgMultiplier;                                   // 216-218
    quint32    MinFactionId;                                    // 219 not used, and 0 in 2.4.2
    quint32    MinReputation;                                   // 220 not used, and 0 in 2.4.2
    quint32    RequiredAuraVision;                              // 221 not used
    uarray2    TotemCategory;                                   // 222-223
    qint32     AreaGroupId;                                     // 224
    quint32    SchoolMask;                                      // 225 school mask
    quint32    RuneCostID;                                      // 226
    quint32    SpellMissileId;                                  // 227
    quint32    PowerDisplayId;                                  // 228
    farray3    Unk3;                                            // 229-231
    quint32    SpellDescriptionVariableId;                      // 232
    quint32    SpellDifficultyId;                               // 233

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
    float      MinRangeFriendly;                                // 2
    float      MaxRange;                                        // 3
    float      MaxRangeFriendly;                                // 4
    quint32    Flags;                                           // 5
    char*      Name[16];                                        // 6-21 unused
    quint32    NameFlags;                                       // 22 unused
    char*      ShortName[16];                                   // 23-38 unused
    quint32    ShortNameFlags;                                  // 39 unused
};

struct SpellDurationEntry
{
    quint32    Id;
    qint32     Duration[3];
};

struct ScreenEffectEntry
{
    quint32 Id;
    char*   Name[16];
    quint32 Unk0;
    float   Unk1;
    quint32 Unk2;
    quint32 Unk3;           // % of smth?
    quint32 Unk4;           // all 0
    qint32  Unk5;
    quint32 Unk6;
    quint32 Unk7;
};

struct OverrideSpellDataEntry
{
    quint32 Id;
    quint32 Spells[10];
    quint32 unk;
};

// GCC have alternative #pragma pack() syntax and old gcc version not support pack(pop), also any gcc version not support it at some platform
#if defined( __GNUC__ )
#pragma pack()
#else
#pragma pack(pop)
#endif

#endif

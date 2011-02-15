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

#define MAX_SPELL_REAGENTS 8
#define MAX_SPELL_TOTEMS 2
#define MAX_SPELL_TOTEM_CATEGORIES 2

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
    quint32    Stances[2];                                      // 12-13
    quint32    StancesNot[2];                                   // 14-15
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
    quint32    PowerType;                                       // 41
    quint32    ManaCost;                                        // 42
    quint32    ManaCostPerlevel;                                // 43
    quint32    ManaPerSecond;                                   // 44
    quint32    ManaPerSecondPerLevel;                           // 45
    quint32    RangeIndex;                                      // 46
    float      Speed;                                           // 47
    quint32    ModalNextSpell;                                  // 48
    quint32    StackAmount;                                     // 49
    quint32    Totem[MAX_SPELL_TOTEMS];                         // 50-51
    qint32     Reagent[MAX_SPELL_REAGENTS];                     // 52-59
    quint32    ReagentCount[MAX_SPELL_REAGENTS];                // 60-67
    qint32     EquippedItemClass;                               // 68 (value)
    qint32     EquippedItemSubClassMask;                        // 69 (mask)
    qint32     EquippedItemInventoryTypeMask;                   // 70 (mask)
    quint32    Effect[MAX_EFFECT_INDEX];                        // 71-73
    qint32     EffectDieSides[MAX_EFFECT_INDEX];                // 74-76
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
    quint32    EffectSpellClassMaskA[MAX_EFFECT_INDEX];         // 122-124  m_effectSpellClassMaskA, effect 0
    quint32    EffectSpellClassMaskB[MAX_EFFECT_INDEX];         // 125-127  m_effectSpellClassMaskB, effect 1
    quint32    EffectSpellClassMaskC[MAX_EFFECT_INDEX];         // 128-130  m_effectSpellClassMaskC, effect 2
    quint32    SpellVisual[2];                                  // 131-132
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
    quint32    SpellFamilyFlags[MAX_EFFECT_INDEX];              // 209+211
    quint32    MaxAffectedTargets;                              // 212
    quint32    DmgClass;                                        // 213 defenseType
    quint32    PreventionType;                                  // 214
    quint32    StanceBarOrder;                                  // 215 not used
    float      DmgMultiplier[MAX_EFFECT_INDEX];                 // 216-218
    quint32    MinFactionId;                                    // 219 not used, and 0 in 2.4.2
    quint32    MinReputation;                                   // 220 not used, and 0 in 2.4.2
    quint32    RequiredAuraVision;                              // 221 not used
    quint32    TotemCategory[MAX_SPELL_TOTEM_CATEGORIES];       // 222-223
    qint32     AreaGroupId;                                     // 224
    quint32    SchoolMask;                                      // 225 school mask
    quint32    RuneCostID;                                      // 226
    quint32    SpellMissileId;                                  // 227
    quint32    PowerDisplayId;                                  // 228
    float      Unk3[MAX_EFFECT_INDEX];                          // 229-231
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

#ifndef DBCSTRUCTURE_H
#define DBCSTRUCTURE_H

#include "DBCEnums.h"
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
    uint32    id;                                   // 0
    int32     categoryId;                           // 1 (index from SkillLineCategory.dbc)
    uint32    skillCostID;                          // 2 not used
    char*     name[8];                              // 3-10
    uint32    nameFlags;                            // 11 string flags, not used
    char*     description[8];                       // 12-19, not used
    uint32    descFlags;                            // 20 string flags, not used
    uint32    spellIcon;                            // 21
};

struct SkillLineAbilityEntry
{
    uint32    id;                                           // 0 INDEX
    uint32    skillId;                                      // 1
    uint32    spellId;                                      // 2
    uint32    racemask;                                     // 3
    uint32    classmask;                                    // 4
    uint32    Unk1;                                         // 5 unknown
    uint32    Unk2;                                         // 6 unknown
    uint32    req_skill_value;                              // 7 for trade skill.not for training.
    uint32    forward_spellid;                              // 8
    uint32    learnOnGetSkill;                              // 9 can be 1 or 2 for spells learned on get skill
    uint32    max_value;                                    // 10
    uint32    min_value;                                    // 11
    uint32    Unk3;                                         // 12 unknown
    uint32    Unk4;                                         // 13 unknown
    uint32    reqtrainpoints;                               // 14
};

#define MAX_SPELL_REAGENTS 8
#define MAX_SPELL_TOTEMS 2

struct SpellEntry
{
    uint32    Id;                                           // 0 normally counted from 0 field (but some tools start counting from 1, check this before tool use for data view!)
    uint32    School;                                       // 1 not schoolMask from 2.x - just school type so everything linked with SpellEntry::SchoolMask must be rewrited
    uint32    Category;                                     // 2
    uint32    castUI;                                       // 3 not used
    uint32    Dispel;                                       // 4
    uint32    Mechanic;                                     // 5
    uint32    Attributes;                                   // 6
    uint32    AttributesEx;                                 // 7
    uint32    AttributesEx2;                                // 8
    uint32    AttributesEx3;                                // 9
    uint32    AttributesEx4;                                // 10
    uint32    Stances;                                      // 11
    uint32    StancesNot;                                   // 12
    uint32    Targets;                                      // 13
    uint32    TargetCreatureType;                           // 14
    uint32    RequiresSpellFocus;                           // 15
    uint32    CasterAuraState;                              // 16
    uint32    TargetAuraState;                              // 17
    uint32    CastingTimeIndex;                             // 18
    uint32    RecoveryTime;                                 // 19
    uint32    CategoryRecoveryTime;                         // 20
    uint32    InterruptFlags;                               // 21
    uint32    AuraInterruptFlags;                           // 22
    uint32    ChannelInterruptFlags;                        // 23
    uint32    procFlags;                                    // 24
    uint32    procChance;                                   // 25
    uint32    procCharges;                                  // 26
    uint32    maxLevel;                                     // 27
    uint32    baseLevel;                                    // 28
    uint32    spellLevel;                                   // 29
    uint32    DurationIndex;                                // 30
    uint32    powerType;                                    // 31
    uint32    manaCost;                                     // 32
    uint32    manaCostPerlevel;                             // 33
    uint32    manaPerSecond;                                // 34
    uint32    manaPerSecondPerLevel;                        // 35
    uint32    rangeIndex;                                   // 36
    float     speed;                                        // 37
    uint32    modalNextSpell;                               // 38 not used
    uint32    StackAmount;                                  // 39
    uint32    Totem[MAX_SPELL_TOTEMS];                      // 40-41
    int32     Reagent[MAX_SPELL_REAGENTS];                  // 42-49
    uint32    ReagentCount[MAX_SPELL_REAGENTS];             // 50-57
    int32     EquippedItemClass;                            // 58 (value)
    int32     EquippedItemSubClassMask;                     // 59 (mask)
    int32     EquippedItemInventoryTypeMask;                // 60 (mask)
    uint32    Effect[MAX_EFFECT_INDEX];                     // 61-63
    int32     EffectDieSides[MAX_EFFECT_INDEX];             // 64-66
    uint32    EffectBaseDice[MAX_EFFECT_INDEX];             // 67-69
    float     EffectDicePerLevel[MAX_EFFECT_INDEX];         // 70-72
    float     EffectRealPointsPerLevel[MAX_EFFECT_INDEX];   // 73-75
    int32     EffectBasePoints[MAX_EFFECT_INDEX];           // 76-78 (don't must be used in spell/auras explicitly, must be used cached Spell::m_currentBasePoints)
    uint32    EffectMechanic[MAX_EFFECT_INDEX];             // 79-81
    uint32    EffectImplicitTargetA[MAX_EFFECT_INDEX];      // 82-84
    uint32    EffectImplicitTargetB[MAX_EFFECT_INDEX];      // 85-87
    uint32    EffectRadiusIndex[MAX_EFFECT_INDEX];          // 88-90 - spellradius.dbc
    uint32    EffectApplyAuraName[MAX_EFFECT_INDEX];        // 91-93
    uint32    EffectAmplitude[MAX_EFFECT_INDEX];            // 94-96
    float     EffectMultipleValue[MAX_EFFECT_INDEX];        // 97-99
    uint32    EffectChainTarget[MAX_EFFECT_INDEX];          // 100-102
    uint32    EffectItemType[MAX_EFFECT_INDEX];             // 103-105
    int32     EffectMiscValue[MAX_EFFECT_INDEX];            // 106-108
    uint32    EffectTriggerSpell[MAX_EFFECT_INDEX];         // 109-111
    float     EffectPointsPerComboPoint[MAX_EFFECT_INDEX];  // 112-114
    uint32    SpellVisual;                                  // 115
    uint32    SpellVisual2;                                 // 116 not used
    uint32    SpellIconID;                                  // 117
    uint32    activeIconID;                                 // 118
    uint32    spellPriority;                                // 119
    char*     SpellName[8];                                 // 120-127
    uint32    SpellNameFlag;                                // 128
    char*     Rank[8];                                      // 129-136
    uint32    RankFlags;                                    // 137
    char*     Description[8];                               // 138-145 not used
    uint32    DescriptionFlags;                             // 146     not used
    char*     ToolTip[8];                                   // 147-154 not used
    uint32    ToolTipFlags;                                 // 155     not used
    uint32    ManaCostPercentage;                           // 156
    uint32    StartRecoveryCategory;                        // 157
    uint32    StartRecoveryTime;                            // 158
    uint32    MaxTargetLevel;                               // 159
    uint32    SpellFamilyName;                              // 160
    uint64    SpellFamilyFlags;                             // 161+162
    uint32    MaxAffectedTargets;                           // 163
    uint32    DmgClass;                                     // 164 defenseType
    uint32    PreventionType;                               // 165
    float     StanceBarOrder;                               // 166 not used
    float     DmgMultiplier[MAX_EFFECT_INDEX];              // 167-169
    uint32    MinFactionId;                                 // 170 not used, and 0 in 2.4.2
    uint32    MinReputation;                                // 171 not used, and 0 in 2.4.2
    uint32    RequiredAuraVision;                           // 172 not used

    // helpers
    int32 CalculateSimpleValue(SpellEffectIndex eff) const { return EffectBasePoints[eff] + int32(EffectBaseDice[eff]); }

    bool IsFitToFamilyMask(uint64 familyFlags) const
    {
        return SpellFamilyFlags & familyFlags;
    }

    bool IsFitToFamily(SpellFamily family, uint64 familyFlags) const
    {
        return SpellFamily(SpellFamilyName) == family && IsFitToFamilyMask(familyFlags);
    }

    private:
        // prevent creating custom entries (copy data from original in fact)
        SpellEntry(SpellEntry const&);                      // DON'T must have implementation
};

struct SpellCastTimesEntry
{
    uint32    ID;                                           // 0
    int32     CastTime;                                     // 1
    float     CastTimePerLevel;                             // 2 unsure / per skill?
    int32     MinCastTime;                                  // 3 unsure
};

struct SpellRadiusEntry
{
    uint32    ID;
    float     Radius;   //hostile
    int32     Zero;
    float     Radius2;  //friedly
};

struct SpellRangeEntry
{
    uint32    ID;                                           // 0
    float     minRange;                                     // 1
    float     maxRange;                                     // 2
    uint32    Flags;                                        // 3
    char*     Name[8];                                      // 4-11 unused
    uint32    NameFlags;                                    // 12 unused
    char*     ShortName[8];                                 // 13-20 unused
    uint32    ShortNameFlags;                               // 21 unused
};

struct SpellDurationEntry
{
    uint32    ID;
    int32     Duration[3];
};

// GCC have alternative #pragma pack() syntax and old gcc version not support pack(pop), also any gcc version not support it at some platform
#if defined( __GNUC__ )
#pragma pack()
#else
#pragma pack(pop)
#endif

typedef std::set<uint32> SpellCategorySet;
typedef std::map<uint32,SpellCategorySet > SpellCategoryStore;

#endif

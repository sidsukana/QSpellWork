#ifndef DBCSTRUCTURE_H_
#define DBCSTRUCTURE_H_

#include <QMetaType>

#include "DBC/DBC.h"

#define MAX_SPELL_REAGENTS 8
#define MAX_SPELL_TOTEMS   2
#define MAX_EFFECT_INDEX   3

namespace SkillLine
{
    struct entry
    {
        quint32     id;                                          // 0 index
        qint32      categoryId;                                  // 1 index from SkillLineCategory.dbc
        quint32     skillCostId;                                 // 2 not used
        const char* name[8];                        // 3-10
        quint32     nameFlags;                                   // 11 string flags, not used
        const char* description[8];                 // 12-19, not used
        quint32     descriptionFlags;                            // 20 string flags, not used
        quint32     spellIcon;                                   // 21
    };

    const DBCFile getDbc();
    const DBCFileHeader* getHeader();
    entry getRecord(quint32 id, bool realId = false);
}

namespace SkillLineAbility
{
    struct entry
    {
        quint32 id;                                              // 0 index
        quint32 skillId;                                         // 1
        quint32 spellId;                                         // 2
        quint32 raceMask;                                        // 3
        quint32 classMask;                                       // 4
        quint32 excludeRaceMask;                                 // 5
        quint32 excludeClassMask;                                // 6
        quint32 requiredSkillValue;                              // 7 for trade skill.not for training.
        quint32 forwardSpellId;                                  // 8
        quint32 learnOnGetSkill;                                 // 9 can be 1 or 2 for spells learned on get skill
        quint32 maxValue;                                        // 10
        quint32 minValue;                                        // 11
        quint32 charPoints[2];                                   // 12-13
        quint32 requiredTrainPoints;                             // 14
    };

    const DBCFile getDbc();
    const DBCFileHeader* getHeader();
    entry getRecord(quint32 id, bool realId = false);
}

namespace Spell
{
    struct entry
    {
        quint32    id;                                              // 0 normally counted from 0 field (but some tools start counting from 1, check this before tool use for data view!)
        quint32    school;                                          // 1 not schoolMask from 2.x - just school type so everything linked with SpellEntry::SchoolMask must be rewrited
        quint32    category;                                        // 2
        quint32    castUI;                                          // 3 not used
        quint32    dispel;                                          // 4
        quint32    mechanic;                                        // 5
        quint32    attributes;                                      // 6
        quint32    attributesEx1;                                   // 7
        quint32    attributesEx2;                                   // 8
        quint32    attributesEx3;                                   // 9
        quint32    attributesEx4;                                   // 10
        quint32    stances;                                         // 11
        quint32    stancesNot;                                      // 12
        quint32    targets;                                         // 13
        quint32    targetCreatureType;                              // 14
        quint32    requiresSpellFocus;                              // 15
        quint32    casterAuraState;                                 // 16
        quint32    targetAuraState;                                 // 17
        quint32    castingTimeIndex;                                // 18
        quint32    recoveryTime;                                    // 19
        quint32    categoryRecoveryTime;                            // 20
        quint32    interruptFlags;                                  // 21
        quint32    auraInterruptFlags;                              // 22
        quint32    channelInterruptFlags;                           // 23
        quint32    procFlags;                                       // 24
        quint32    procChance;                                      // 25
        quint32    procCharges;                                     // 26
        quint32    maxLevel;                                        // 27
        quint32    baseLevel;                                       // 28
        quint32    spellLevel;                                      // 29
        quint32    durationIndex;                                   // 30
        qint32     powerType;                                       // 31
        quint32    manaCost;                                        // 32
        quint32    manaCostPerlevel;                                // 33
        quint32    manaPerSecond;                                   // 34
        quint32    manaPerSecondPerLevel;                           // 35
        quint32    rangeIndex;                                      // 36
        float      speed;                                           // 37
        quint32    modalNextSpell;                                  // 38 not used
        quint32    stackAmount;                                     // 39
        quint32    totem[MAX_SPELL_TOTEMS];                         // 40-41
        qint32     reagent[MAX_SPELL_REAGENTS];                     // 42-49
        quint32    reagentCount[MAX_SPELL_REAGENTS];                // 50-57
        qint32     equippedItemClass;                               // 58 (value)
        qint32     equippedItemSubClassMask;                        // 59 (mask)
        qint32     equippedItemInventoryTypeMask;                   // 60 (mask)
        quint32    effect[MAX_EFFECT_INDEX];                        // 61-63
        quint32    effectDieSides[MAX_EFFECT_INDEX];                // 64-66
        quint32    effectBaseDice[MAX_EFFECT_INDEX];                // 67-69
        float      effectDicePerLevel[MAX_EFFECT_INDEX];            // 70-72
        float      effectRealPointsPerLevel[MAX_EFFECT_INDEX];      // 73-75
        qint32     effectBasePoints[MAX_EFFECT_INDEX];              // 76-78 (don't must be used in spell/auras explicitly, must be used cached Spell::m_currentBasePoints)
        quint32    effectMechanic[MAX_EFFECT_INDEX];                // 79-81
        quint32    effectImplicitTargetA[MAX_EFFECT_INDEX];         // 82-84
        quint32    effectImplicitTargetB[MAX_EFFECT_INDEX];         // 85-87
        quint32    effectRadiusIndex[MAX_EFFECT_INDEX];             // 88-90 - spellradius.dbc
        quint32    effectApplyAuraName[MAX_EFFECT_INDEX];           // 91-93
        quint32    effectAmplitude[MAX_EFFECT_INDEX];               // 94-96
        float      effectMultipleValue[MAX_EFFECT_INDEX];           // 97-99
        quint32    effectChainTarget[MAX_EFFECT_INDEX];             // 100-102
        quint32    effectItemType[MAX_EFFECT_INDEX];                // 103-105
        qint32     effectMiscValue[MAX_EFFECT_INDEX];               // 106-108
        quint32    effectTriggerSpell[MAX_EFFECT_INDEX];            // 109-111
        float      effectPointsPerComboPoint[MAX_EFFECT_INDEX];     // 112-114
        quint32    spellVisual[2];                                  // 115-116
        quint32    spellIconId;                                     // 117
        quint32    activeIconId;                                    // 118
        quint32    spellPriority;                                   // 119
        const char*      spellName[8];                              // 120-127
        quint32    spellNameFlag;                                   // 128
        const char*      rank[8];                                   // 129-136
        quint32    rankFlags;                                       // 137
        const char*      description[8];                            // 138-145 not used
        quint32    descriptionFlags;                                // 146     not used
        const char*      toolTip[8];                                // 147-154 not used
        quint32    toolTipFlags;                                    // 155     not used
        quint32    manaCostPercentage;                              // 156
        quint32    startRecoveryCategory;                           // 157
        quint32    startRecoveryTime;                               // 158
        quint32    maxTargetLevel;                                  // 159
        quint32    spellFamilyName;                                 // 160
        quint64    spellFamilyFlags;                                // 161+162
        quint32    maxAffectedTargets;                              // 163
        quint32    damageClass;                                     // 164 defenseType
        quint32    preventionType;                                  // 165
        qint32     stanceBarOrder;                                  // 166 not used
        float      damageMultiplier[MAX_EFFECT_INDEX];              // 167-169
        quint32    minFactionId;                                    // 170 not used, and 0 in 2.4.2
        quint32    minReputation;                                   // 171 not used, and 0 in 2.4.2
        quint32    requiredAuraVision;                              // 172 not used

        quint32 getAmplitude()
        {
            for (quint8 i = 0; i < MAX_EFFECT_INDEX; ++i)
                if (effectAmplitude[i])
                    return effectAmplitude[i];

            return 0;
        }
    };

    

    const DBCFile getDbc();
    const DBCFileHeader* getHeader();
    entry getRecord(quint32 id, bool realId = false);
}

Q_DECLARE_METATYPE(Spell::entry*);

namespace SpellCastTimes
{
    struct entry
    {
        quint32    id;                                              // 0
        qint32     castTime;                                        // 1
        float      castTimePerLevel;                                // 2 unsure / per skill?
        qint32     minCastTime;                                     // 3 unsure
    };

    const DBCFile getDbc();
    const DBCFileHeader* getHeader();
    entry getRecord(quint32 id, bool realId = false);
}

namespace SpellRadius
{
    struct entry
    {
        quint32    id;                                              // 0
        float      radius;                                          // 1 
        float      radiusPerLevel;                                  // 2
        float      maxRadius;                                       // 3
    };

    const DBCFile getDbc();
    const DBCFileHeader* getHeader();
    entry getRecord(quint32 id, bool realId = false);
}

namespace SpellRange
{
    struct entry
    {
        quint32     id;                                              // 0
        float       minRange;                                        // 1
        float       maxRange;                                        // 2
        quint32     flags;                                           // 3
        const char* name[8];                                         // 4-11 unused
        quint32     nameFlags;                                       // 12 unused
        const char* shortName[8];                                    // 13-20 unused
        quint32     shortNameFlags;                                  // 21 unused
    };

    const DBCFile getDbc();
    const DBCFileHeader* getHeader();
    entry getRecord(quint32 id, bool realId = false);
}

namespace SpellDuration
{
    struct entry
    {
        quint32    id;
        qint32     duration;
        qint32     durationPerLevel;
        qint32     maxDuration;
    };

    const DBCFile getDbc();
    const DBCFileHeader* getHeader();
    entry getRecord(quint32 id, bool realId = false);
}

namespace SpellIcon
{
    struct entry
    {
        quint32     id;
        const char* iconPath;
    };

    const DBCFile getDbc();
    const DBCFileHeader* getHeader();
    entry getRecord(quint32 id, bool realId = false);
}

#endif

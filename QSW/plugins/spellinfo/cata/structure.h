#ifndef DBCSTRUCTURE_H_
#define DBCSTRUCTURE_H_

#include <QObject>
#include <QMap>

#include "../../../qsw.h"

#define MAX_SPELL_REAGENTS 8
#define MAX_SPELL_TOTEMS   2
#define MAX_EFFECT_INDEX   3

#ifdef __GNUC__
#pragma pack(1)
#else
#pragma pack(push,1)
#endif


namespace SkillLine
{
    struct entry
    {
        quint32 id;                                          // 0
        qint32  categoryId;                                  // 1 (index from SkillLineCategory.dbc)
        quint32 nameOffset;                                  // 2
        quint32 descriptionOffset;                           // 3
        quint32 spellIcon;                                   // 4
        quint32 verbOffset;                                  // 5
        quint32 canLink;                                     // 6

        const QString name() const;
        const QString description() const;
        const QString verb() const;
    };

    DBCFile& getDbc();
    quint32 getRecordCount();
    const entry* getRecord(quint32 id, bool realId = false);
}

namespace SkillLineAbility
{
    struct entry
    {
        quint32 id;                                              // 0
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
    };

    DBCFile& getDbc();
    quint32 getRecordCount();
    const entry* getRecord(quint32 id, bool realId = false);
}

namespace SpellAuraOptions
{
    struct entry
    {
        quint32    id;                                           // 0
        quint32    stackAmount;                                  // 1
        quint32    procChance;                                   // 2
        quint32    procCharges;                                  // 3
        quint32    procFlags;                                    // 4
    };

    DBCFile& getDbc();
    quint32 getRecordCount();
    const entry* getRecord(quint32 id, bool realId = false);
}

namespace SpellAuraRestrictions
{
    struct entry
    {
        quint32    id;                                           // 0
        quint32    casterAuraState;                              // 1
        quint32    targetAuraState;                              // 2
        quint32    casterAuraStateNot;                           // 3
        quint32    targetAuraStateNot;                           // 4
        quint32    casterAuraSpell;                              // 5
        quint32    targetAuraSpell;                              // 6
        quint32    excludeCasterAuraSpell;                       // 7
        quint32    excludeTargetAuraSpell;                       // 8
    };

    DBCFile& getDbc();
    quint32 getRecordCount();
    const entry* getRecord(quint32 id, bool realId = false);
}

namespace SpellCastingRequirements
{
    struct entry
    {
        quint32    id;                                           // 0
        quint32    facingCasterFlags;                            // 1
        quint32    minFactionId;                                 // 2
        quint32    minReputation;                                // 3
        qint32     areaGroupId;                                  // 4
        quint32    requiredAuraVision;                           // 5
        quint32    requiresSpellFocus;                           // 6
    };

    DBCFile& getDbc();
    quint32 getRecordCount();
    const entry* getRecord(quint32 id, bool realId = false);
}

namespace SpellCategories
{
    struct entry
    {
        quint32    id;                                           // 0
        quint32    category;                                     // 1
        quint32    damageClass;                                  // 2
        quint32    dispel;                                       // 3
        quint32    mechanic;                                     // 4
        quint32    preventionType;                               // 5
        quint32    startRecoveryCategory;                        // 6
    };

    DBCFile& getDbc();
    quint32 getRecordCount();
    const entry* getRecord(quint32 id, bool realId = false);
}

namespace SpellClassOptions
{
    struct entry
    {
        quint32    id;                                          // 1
        quint32    modalNextSpell;                              // 2
        quint32    spellFamilyFlags[3];                         // 3-5
        quint32    spellFamilyName;                             // 6
        quint32    descriptionOffset;                           // 7
    };

    DBCFile& getDbc();
    quint32 getRecordCount();
    const entry* getRecord(quint32 id, bool realId = false);
}

namespace SpellCooldowns
{
    struct entry
    {
        quint32    id;                                           // 0
        quint32    categoryRecoveryTime;                         // 1
        quint32    recoveryTime;                                 // 2
        quint32    startRecoveryTime;                            // 3
    };

    DBCFile& getDbc();
    quint32 getRecordCount();
    const entry* getRecord(quint32 id, bool realId = false);
}

namespace SpellEffect
{
    struct entry
    {
        quint32    id;                                           // 0
        quint32    effect;                                       // 1
        float      effectValueMultiplier;                        // 2
        quint32    effectApplyAuraName;                          // 3
        quint32    effectAmplitude;                              // 4
        qint32     effectBasePoints;                             // 5
        float      effectBonusCoefficient;                       // 6
        float      effectDamageMultiplier;                       // 7
        quint32    effectChainTarget;                            // 8
        qint32     effectDieSides;                               // 9
        quint32    effectItemType;                               // 10
        quint32    effectMechanic;                               // 11
        qint32     effectMiscValueA;                             // 12
        qint32     effectMiscValueB;                             // 13
        float      effectPointsPerComboPoint;                    // 14
        quint32    effectRadiusIndex;                            // 15
        quint32    effectRadiusMaxIndex;                         // 16
        float      effectRealPointsPerLevel;                     // 17
        quint32    effectSpellClassMask[3];                      // 18-20
        quint32    effectTriggerSpell;                           // 21
        quint32    effectImplicitTargetA;                        // 22
        quint32    effectImplicitTargetB;                        // 23
        quint32    effectSpellId;                                // 23
        quint32    effectIndex;                                  // 24
        quint32    unk;                                          // 25
    };

    DBCFile& getDbc();
    quint32 getRecordCount();
    const entry* getRecord(quint32 id, bool realId = false);
}

namespace SpellEquippedItems
{
    struct entry
    {
        quint32    id;                                           // 0
        qint32     equippedItemClass;                            // 1
        qint32     equippedItemInventoryTypeMask;                // 2
        qint32     equippedItemSubClassMask;                     // 3
    };

    DBCFile& getDbc();
    quint32 getRecordCount();
    const entry* getRecord(quint32 id, bool realId = false);
}

namespace SpellInterrupts
{
    struct entry
    {
        quint32    id;                                           // 0
        quint32    auraInterruptFlags;                           // 1
        quint32    unk1;                                         // 2
        quint32    channelInterruptFlags;                        // 3
        quint32    unk2;                                         // 4
        quint32    interruptFlags;                               // 5
    };

    DBCFile& getDbc();
    quint32 getRecordCount();
    const entry* getRecord(quint32 id, bool realId = false);
}

namespace SpellLevels
{
    struct entry
    {
        quint32    id;                                           // 0
        quint32    baseLevel;                                    // 1
        quint32    maxLevel;                                     // 2
        quint32    spellLevel;                                   // 3
    };

    DBCFile& getDbc();
    quint32 getRecordCount();
    const entry* getRecord(quint32 id, bool realId = false);
}

namespace SpellPower
{
    struct entry
    {
        quint32    id;                                           // 0
        quint32    manaCost;                                     // 1
        quint32    manaCostPerlevel;                             // 2
        quint32    manaCostPercentage;                           // 3
        quint32    manaPerSecond;                                // 4
        quint32    powerDisplayId;                               // 5
        quint32    unk1;                                         // 6
    };

    DBCFile& getDbc();
    quint32 getRecordCount();
    const entry* getRecord(quint32 id, bool realId = false);
}

namespace SpellReagents
{
    struct entry
    {
        quint32    id;                                          // 0
        qint32     reagent[MAX_SPELL_REAGENTS];                 // 1-9
        quint32    reagentCount[MAX_SPELL_REAGENTS];            // 10-17
    };

    DBCFile& getDbc();
    quint32 getRecordCount();
    const entry* getRecord(quint32 id, bool realId = false);
}

namespace SpellScaling
{
    struct entry
    {
        quint32    id;                                           // 0
        quint32    castTimeMin;                                  // 1
        quint32    castTimeMax;                                  // 2
        quint32    castScalingMaxLevel;                          // 3
        quint32    playerClass;                                  // 4        (index * 100) + charLevel => gtSpellScaling.dbc
        float      coeff1[MAX_EFFECT_INDEX];                     // 5-7
        float      coeff2[MAX_EFFECT_INDEX];                     // 8-10
        float      coeff3[MAX_EFFECT_INDEX];                     // 11-13
        float      unkMult;                                      // 14        some coefficient, mostly 1.0f
        quint32    unkLevel;                                     // 15        some level
    };

    DBCFile& getDbc();
    quint32 getRecordCount();
    const entry* getRecord(quint32 id, bool realId = false);
}

namespace SpellShapeshift
{
    struct entry
    {
        quint32     id;                                     // 0
        quint64     stancesNot;                             // 1-2
        quint64     stances;                                // 3-4
        quint32     stanceBarOrder;                         // 5
    };

    DBCFile& getDbc();
    quint32 getRecordCount();
    const entry* getRecord(quint32 id, bool realId = false);
}

namespace SpellTargetRestrictions
{
    struct entry
    {
        quint32    id;                                           // 0
        float      maxTargetRadius;                              // 1
        quint32    maxAffectedTargets;                           // 2
        quint32    maxTargetLevel;                               // 3
        quint32    targetCreatureType;                           // 4
        quint32    targets;                                      // 5
    };

    DBCFile &getDbc();
    quint32 getRecordCount();
    const entry* getRecord(quint32 id, bool realId = false);
}

namespace SpellTotems
{
    struct entry
    {
        quint32    id;                                      // 0
        quint32    totemCategory[MAX_SPELL_TOTEMS];         // 1
        quint32    totem[MAX_SPELL_TOTEMS];                 // 2
    };

    DBCFile &getDbc();
    quint32 getRecordCount();
    const entry* getRecord(quint32 id, bool realId = false);
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

    DBCFile &getDbc();
    quint32 getRecordCount();
    const entry* getRecord(quint32 id, bool realId = false);
}

namespace SpellCastTimes
{
    struct entry
    {
        quint32    id;                                              // 0
        qint32     castTime;                                        // 1
        float      castTimePerLevel;                                // 2 unsure / per skill?
        qint32     minCastTime;                                     // 3 unsure
    };

    DBCFile& getDbc();
    quint32 getRecordCount();
    const entry* getRecord(quint32 id, bool realId = false);
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

    DBCFile& getDbc();
    quint32 getRecordCount();
    const entry* getRecord(quint32 id, bool realId = false);
}

namespace SpellRange
{
    struct entry
    {
        quint32     id;                                              // 0
        float       minRange;                                        // 1
        float       minRangeFriendly;                                // 2
        float       maxRange;                                        // 3
        float       maxRangeFriendly;                                // 4
        quint32     flags;                                           // 5
        quint32     nameOffset;                                      // 6
        quint32     shortNameOffset;                                 // 7

        const QString name() const;
        const QString shortName() const;
    };

    DBCFile& getDbc();
    quint32 getRecordCount();
    const entry* getRecord(quint32 id, bool realId = false);
}

namespace SpellIcon
{
    struct entry
    {
        quint32 id;                                                 // 0 Id
        quint32 iconPathOffset;                                     // 1 Path offset

        const QString iconPath() const;
    };

    DBCFile& getDbc();
    quint32 getRecordCount();
    const entry* getRecord(quint32 id, bool realId = false);
}

typedef QMap<quint8, const SpellEffect::entry*> EffectMap;
typedef QHash<quint32, EffectMap> SpellEffectHash;

namespace Spell
{
    class meta;

    struct entry
    {
        quint32     id;                                           // 0
        quint32     attributes;                                   // 1
        quint32     attributesEx1;                                // 2
        quint32     attributesEx2;                                // 3
        quint32     attributesEx3;                                // 4
        quint32     attributesEx4;                                // 5
        quint32     attributesEx5;                                // 6
        quint32     attributesEx6;                                // 7
        quint32     attributesEx7;                                // 8
        quint32     attributesEx8;                                // 9
        quint32     attributesEx9;                                // 10
        quint32     attributesEx10;                               // 11
        quint32     castingTimeIndex;                             // 12
        quint32     durationIndex;                                // 13
        quint32     powerType;                                    // 14
        quint32     rangeIndex;                                   // 15
        float       speed;                                        // 16
        quint32     spellVisual[2];                               // 17
        quint32     spellIconId;                                  // 19
        quint32     activeIconId;                                 // 20
        quint32     nameOffset;                                   // 21
        quint32     rankOffset;                                   // 22
        quint32     descriptionOffset;                            // 23
        quint32     toolTipOffset;                                // 24
        quint32     schoolMask;                                   // 25
        quint32     runeCostId;                                   // 26
        quint32     spellMissileId;                               // 27
        quint32     spellDescriptionVariableId;                   // 28
        quint32     spellDifficultyId;                            // 29
        float       unk1;                                         // 30
        quint32     spellScalingId;                               // 31
        quint32     spellAuraOptionsId;                           // 32
        quint32     spellAuraRestrictionsId;                      // 33
        quint32     spellCastingRequirementsId;                   // 34
        quint32     spellCategoriesId;                            // 35
        quint32     spellClassOptionsId;                          // 36
        quint32     spellCooldownsId;                             // 37
        quint32     unk2;                                         // 38
        quint32     spellEquippedItemsId;                         // 39
        quint32     spellInterruptsId;                            // 40
        quint32     spellLevelsId;                                // 41
        quint32     spellPowerId;                                 // 42
        quint32     spellReagentsId;                              // 43
        quint32     spellShapeshiftId;                            // 44
        quint32     spellTargetRestrictionsId;                    // 45
        quint32     spellTotemsId;                                // 46
        quint32     ResearchProject;                              // 47

        const QString name() const;
        const QString description() const;
        const QString rank() const;
        const QString toolTip() const;
        const QString nameWithRank() const;

        quint32 getStackAmount() const;
        quint32 getProcChance() const;
        quint32 getProcCharges() const;
        quint32 getProcFlags() const;

        quint32 getCasterAuraState() const;
        quint32 getTargetAuraState() const;
        quint32 getCasterAuraStateNot() const;
        quint32 getTargetAuraStateNot() const;
        quint32 getCasterAuraSpell() const;
        quint32 getTargetAuraSpell() const;
        quint32 getExcludeCasterAuraSpell() const;
        quint32 getExcludeTargetAuraSpell() const;

        quint32 getFacingCasterFlags() const;
        quint32 getMinFactionId() const;
        quint32 getMinReputation() const;
        qint32  getAreaGroupId() const;
        quint32 getRequiredAuraVision() const;
        quint32 getRequiresSpellFocus() const;

        quint32 getCategory() const;
        quint32 getDamageClass() const;
        quint32 getDispel() const;
        quint32 getMechanic() const;
        quint32 getPreventionType() const;
        quint32 getStartRecoveryCategory() const;

        quint32 getModalNextSpell() const;
        quint32 getSpellFamilyFlags(quint8 index) const;
        quint32 getSpellFamilyName() const;

        quint32 getCategoryRecoveryTime() const;
        quint32 getRecoveryTime() const;
        quint32 getStartRecoveryTime() const;

        qint32 getEquippedItemClass() const;
        qint32 getEquippedItemInventoryTypeMask() const;
        qint32 getEquippedItemSubClassMask() const;

        quint32 getAuraInterruptFlags() const;
        quint32 getChannelInterruptFlags() const;
        quint32 getInterruptFlags() const;

        quint32 getBaseLevel() const;
        quint32 getMaxLevel() const;
        quint32 getSpellLevel() const;

        quint32 getManaCost() const;
        quint32 getManaCostPerlevel() const;
        quint32 getManaCostPercentage() const;
        quint32 getManaPerSecond() const;
        quint32 getPowerDisplayId() const;

        qint32  getReagent(quint8 index) const;
        quint32 getReagentCount(quint8 index) const;

        quint64 getStancesNot() const;
        quint64 getStances() const;
        quint32 getStanceBarOrder() const;

        float  getMaxTargetRadius() const;
        quint32 getMaxAffectedTargets() const;
        quint32 getMaxTargetLevel() const;
        quint32 getTargetCreatureType() const;
        quint32 getTargets() const;

        quint32 getTotemCategory(quint8 index) const;
        quint32 getTotem(quint8 index) const;

        const SpellEffect::entry* getEffect(quint8 index) const;
        quint8 getEffectCount() const;

        quint32 getEffectId(quint8 index) const;
        float   getEffectValueMultiplier(quint8 index) const;
        quint32 getEffectApplyAuraName(quint8 index) const;
        quint32 getEffectAmplitude(quint8 index) const;
        qint32  getEffectBasePoints(quint8 index) const;
        float   getEffectBonusCoefficient(quint8 index) const;
        float   getEffectDamageMultiplier(quint8 index) const;
        quint32 getEffectChainTarget(quint8 index) const;
        qint32  getEffectDieSides(quint8 index) const;
        quint32 getEffectItemType(quint8 index) const;
        quint32 getEffectMechanic(quint8 index) const;
        qint32  getEffectMiscValueA(quint8 index) const;
        qint32  getEffectMiscValueB(quint8 index) const;
        float   getEffectPointsPerComboPoint(quint8 index) const;
        quint32 getEffectRadiusIndex(quint8 index) const;
        quint32 getEffectRadiusMaxIndex(quint8 index) const;
        float   getEffectRealPointsPerLevel(quint8 index) const;
        quint32 getEffectSpellClassMask(quint8 index, quint8 maskIndex) const;
        quint32 getEffectTriggerSpell(quint8 index) const;
        quint32 getEffectImplicitTargetA(quint8 index) const;
        quint32 getEffectImplicitTargetB(quint8 index) const;

        quint32 getAmplitude() const
        {
            for (quint8 i = 0; i < getEffectCount(); ++i)
                if (quint32 amplitude = getEffectAmplitude(i))
                    return quint32(amplitude / 1000);

            return 0;
        }

        quint32 getAmplitude(quint8 index) const
        {
            return quint32(getEffectAmplitude(index) / 1000);
        }

        qint32 getDuration() const
        {
            const SpellDuration::entry* durationInfo = SpellDuration::getRecord(durationIndex, true);
            if (durationInfo)
                return qint32(durationInfo->duration / 1000);

            return 0;
        }

        float getRadius(quint8 index) const
        {
            if (const SpellRadius::entry* spellRadius = SpellRadius::getRecord(getEffectRadiusIndex(index), true))
                return spellRadius->radius;

            return 0.0f;
        }

        quint32 getTicks(quint8 index) const
        {
            return quint32(getDuration() / (getEffectAmplitude(index) ? quint32(getEffectAmplitude(index) / 1000) : getDuration()));
        }

        qint32 getTriggerDuration(quint8 index) const;
    };

    static SpellEffectHash spellEffectHash;
    void fillSpellEffects();

    DBCFile &getDbc();
    quint32 getRecordCount();
    const entry* getRecord(quint32 id, bool realId = false);

    class meta : public QObject
    {
        Q_OBJECT

        public:

        meta(const entry* info) : m_info(info) {}

        public slots:

        quint32 Id() { return m_info->id; }
        quint32 Category() { return m_info->getCategory(); }
        quint32 Dispel() { return m_info->getDispel(); }
        quint32 Mechanic() { return m_info->getMechanic(); }
        quint32 Attributes() { return m_info->attributes; }
        quint32 AttributesEx1() { return m_info->attributesEx1; }
        quint32 AttributesEx2() { return m_info->attributesEx2; }
        quint32 AttributesEx3() { return m_info->attributesEx3; }
        quint32 AttributesEx4() { return m_info->attributesEx4; }
        quint32 AttributesEx5() { return m_info->attributesEx5; }
        quint32 AttributesEx6() { return m_info->attributesEx6; }
        quint32 AttributesEx7() { return m_info->attributesEx7; }
        quint32 AttributesEx8() { return m_info->attributesEx8; }
        quint32 AttributesEx9() { return m_info->attributesEx9; }
        quint32 AttributesEx10() { return m_info->attributesEx10; }
        quint64 Stances() { return m_info->getStances(); }
        quint64 StancesNot() { return m_info->getStancesNot(); }
        quint32 Targets() { return m_info->getTargets(); }
        quint32 TargetCreatureType() { return m_info->getTargetCreatureType(); }
        quint32 RequiresSpellFocus() { return m_info->getRequiresSpellFocus(); }
        quint32 FacingCasterFlags() { return m_info->getFacingCasterFlags(); }
        quint32 CasterAuraState() { return m_info->getCasterAuraState(); }
        quint32 TargetAuraState() { return m_info->getTargetAuraState(); }
        quint32 CasterAuraStateNot() { return m_info->getCasterAuraStateNot(); }
        quint32 TargetAuraStateNot() { return m_info->getTargetAuraStateNot(); }
        quint32 CasterAuraSpell() { return m_info->getCasterAuraSpell(); }
        quint32 TargetAuraSpell() { return m_info->getTargetAuraSpell(); }
        quint32 ExcludeCasterAuraSpell() { return m_info->getExcludeCasterAuraSpell(); }
        quint32 ExcludeTargetAuraSpell() { return m_info->getExcludeTargetAuraSpell(); }
        quint32 CastingTimeIndex() { return m_info->castingTimeIndex; }
        quint32 RecoveryTime() { return m_info->getRecoveryTime(); }
        quint32 CategoryRecoveryTime() { return m_info->getCategoryRecoveryTime(); }
        quint32 InterruptFlags() { return m_info->getInterruptFlags(); }
        quint32 AuraInterruptFlags() { return m_info->getAuraInterruptFlags(); }
        quint32 ChannelInterruptFlags() { return m_info->getChannelInterruptFlags(); }
        quint32 ProcFlags() { return m_info->getProcFlags(); }
        quint32 ProcChance() { return m_info->getProcChance(); }
        quint32 ProcCharges() { return m_info->getProcCharges(); }
        quint32 MaxLevel() { return m_info->getMaxLevel(); }
        quint32 BaseLevel() { return m_info->getBaseLevel(); }
        quint32 SpellLevel() { return m_info->getSpellLevel(); }
        quint32 DurationIndex() { return m_info->durationIndex; }
        qint32 PowerType() { return m_info->powerType; }
        quint32 ManaCost() { return m_info->getManaCost(); }
        quint32 ManaCostPerlevel() { return m_info->getManaCostPerlevel(); }
        quint32 ManaPerSecond() { return m_info->getManaPerSecond(); }
        quint32 ManaCostPercentage() { return m_info->getManaCostPercentage(); }
        quint32 RangeIndex() { return m_info->rangeIndex; }
        float Speed() { return m_info->speed; }
        quint32 ModalNextSpell() { return m_info->getModalNextSpell(); }
        quint32 StackAmount() { return m_info->getStackAmount(); }
        quint32 Totem(quint8 index) { return m_info->getTotem(index); }
        qint32 Reagent(quint8 index) { return m_info->getReagent(index); }
        quint32 ReagentCount(quint8 index) { return m_info->getReagentCount(index); }
        qint32 EquippedItemClass() { return m_info->getEquippedItemClass(); }
        qint32 EquippedItemSubClassMask() { return m_info->getEquippedItemSubClassMask(); }
        qint32 EquippedItemInventoryTypeMask() { return m_info->getEquippedItemInventoryTypeMask(); }
        quint32 Effect(quint8 index) { return m_info->getEffectId(index); }
        quint32 EffectDieSides(quint8 index) { return m_info->getEffectDieSides(index); }
        float EffectRealPointsPerLevel(quint8 index) { return m_info->getEffectRealPointsPerLevel(index); }
        qint32 EffectBasePoints(quint8 index) { return m_info->getEffectBasePoints(index); }
        quint32 EffectMechanic(quint8 index) { return m_info->getEffectMechanic(index); }
        quint32 EffectImplicitTargetA(quint8 index) { return m_info->getEffectImplicitTargetA(index); }
        quint32 EffectImplicitTargetB(quint8 index) { return m_info->getEffectImplicitTargetB(index); }
        quint32 EffectRadiusIndex(quint8 index) { return m_info->getEffectRadiusIndex(index); }
        quint32 EffectApplyAuraName(quint8 index) { return m_info->getEffectApplyAuraName(index); }
        quint32 EffectAmplitude(quint8 index) { return m_info->getEffectAmplitude(index); }
        quint32 EffectChainTarget(quint8 index) { return m_info->getEffectChainTarget(index); }
        quint32 EffectItemType(quint8 index) { return m_info->getEffectItemType(index); }
        qint32 EffectMiscValueA(quint8 index) { return m_info->getEffectMiscValueA(index); }
        qint32 EffectMiscValueB(quint8 index) { return m_info->getEffectMiscValueB(index); }
        quint32 EffectTriggerSpell(quint8 index) { return m_info->getEffectTriggerSpell(index); }
        float EffectPointsPerComboPoint(quint8 index) { return m_info->getEffectPointsPerComboPoint(index); }
        quint32 EffectSpellClassMask(quint8 index, quint8 maskIndex) { return m_info->getEffectSpellClassMask(index, maskIndex); }
        quint32 SpellVisual(quint8 index) { return m_info->spellVisual[index]; }
        quint32 SpellIconId() { return m_info->spellIconId; }
        quint32 ActiveIconId() { return m_info->activeIconId; }
        QString Name() { return m_info->name(); }
        QString Rank() { return m_info->rank(); }
        QString Description() { return m_info->description(); }
        QString ToolTip() { return m_info->toolTip(); }
        quint32 StartRecoveryCategory() { return m_info->getStartRecoveryCategory(); }
        quint32 StartRecoveryTime() { return m_info->getStartRecoveryTime(); }
        quint32 MaxTargetLevel() { return m_info->getMaxTargetLevel(); }
        quint32 SpellFamilyName() { return m_info->getSpellFamilyName(); }
        quint32 SpellFamilyFlags(quint8 index) { return m_info->getSpellFamilyFlags(index); }
        quint32 MaxAffectedTargets() { return m_info->getMaxAffectedTargets(); }
        quint32 DamageClass() { return m_info->getDamageClass(); }
        quint32 PreventionType() { return m_info->getPreventionType(); }
        qint32 StanceBarOrder() { return m_info->getStanceBarOrder(); }
        float EffectDamageMultiplier(quint8 index) { return m_info->getEffectDamageMultiplier(index); }
        quint32 MinFactionId() { return m_info->getMinFactionId(); }
        quint32 MinReputation() { return m_info->getMinReputation(); }
        quint32 RequiredAuraVision() { return m_info->getRequiredAuraVision(); }
        quint32 TotemCategory(quint8 index) { return m_info->getTotemCategory(index); }
        quint32 AreaGroupId() { return m_info->getAreaGroupId(); }
        quint32 SchoolMask() { return m_info->schoolMask; }
        quint32 RuneCostId() { return m_info->runeCostId; }
        quint32 SpellMissileId() { return m_info->spellMissileId; }
        quint32 PowerDisplayId() { return m_info->getPowerDisplayId(); }
        float EffectBonusCoefficient(quint8 index) { return m_info->getEffectBonusCoefficient(index); }
        quint32 SpellDescriptionVariableId() { return m_info->spellDescriptionVariableId; }
        quint32 SpellDifficultyId() { return m_info->spellDifficultyId; }
        qint32 Duration() { return m_info->getDuration(); }
        qint32 TriggerDuration(quint8 index) { return m_info->getTriggerDuration(index); }
        QString NameWithRank() { return m_info->nameWithRank(); }

        bool hasAura(quint32 auraId)
        {
            for (quint8 i = 0; i < m_info->getEffectCount(); ++i)
                return (m_info->getEffectApplyAuraName(i) == auraId);
            return false;
        }

        bool hasEffect(quint32 effectId)
        {
            for (quint8 i = 0; i < m_info->getEffectCount(); ++i)
                return (m_info->getEffectId(i) == effectId);
            return false;
        }

        bool hasTargetA(quint32 targetId)
        {
            for (quint8 i = 0; i < m_info->getEffectCount(); ++i)
                return (m_info->getEffectImplicitTargetA(i) == targetId);
            return false;
        }

        bool hasTargetB(quint32 targetId)
        {
            for (quint8 i = 0; i < m_info->getEffectCount(); ++i)
                return (m_info->getEffectImplicitTargetB(i) == targetId);
            return false;
        }

        private:

        const entry* m_info;

        Q_PROPERTY(quint32 Id READ Id)
        Q_PROPERTY(quint32 Category READ Category)
        Q_PROPERTY(quint32 Dispel READ Dispel)
        Q_PROPERTY(quint32 Mechanic READ Mechanic)
        Q_PROPERTY(quint32 Attributes READ Attributes)
        Q_PROPERTY(quint32 AttributesEx1 READ AttributesEx1)
        Q_PROPERTY(quint32 AttributesEx2 READ AttributesEx2)
        Q_PROPERTY(quint32 AttributesEx3 READ AttributesEx3)
        Q_PROPERTY(quint32 AttributesEx4 READ AttributesEx4)
        Q_PROPERTY(quint32 AttributesEx5 READ AttributesEx5)
        Q_PROPERTY(quint32 AttributesEx6 READ AttributesEx6)
        Q_PROPERTY(quint32 AttributesEx7 READ AttributesEx7)
        Q_PROPERTY(quint32 AttributesEx8 READ AttributesEx8)
        Q_PROPERTY(quint32 AttributesEx9 READ AttributesEx9)
        Q_PROPERTY(quint32 AttributesEx10 READ AttributesEx10)
        Q_PROPERTY(quint64 Stances READ Stances)
        Q_PROPERTY(quint64 StancesNot READ StancesNot)
        Q_PROPERTY(quint32 Targets READ Targets)
        Q_PROPERTY(quint32 TargetCreatureType READ TargetCreatureType)
        Q_PROPERTY(quint32 RequiresSpellFocus READ RequiresSpellFocus)
        Q_PROPERTY(quint32 FacingCasterFlags READ FacingCasterFlags)
        Q_PROPERTY(quint32 CasterAuraState READ CasterAuraState)
        Q_PROPERTY(quint32 TargetAuraState READ TargetAuraState)
        Q_PROPERTY(quint32 CasterAuraStateNot READ CasterAuraStateNot)
        Q_PROPERTY(quint32 TargetAuraStateNot READ TargetAuraStateNot)
        Q_PROPERTY(quint32 CasterAuraSpell READ CasterAuraSpell)
        Q_PROPERTY(quint32 TargetAuraSpell READ TargetAuraSpell)
        Q_PROPERTY(quint32 ExcludeCasterAuraSpell READ ExcludeCasterAuraSpell)
        Q_PROPERTY(quint32 ExcludeTargetAuraSpell READ ExcludeTargetAuraSpell)
        Q_PROPERTY(quint32 CastingTimeIndex READ CastingTimeIndex)
        Q_PROPERTY(quint32 RecoveryTime READ RecoveryTime)
        Q_PROPERTY(quint32 CategoryRecoveryTime READ CategoryRecoveryTime)
        Q_PROPERTY(quint32 InterruptFlags READ InterruptFlags)
        Q_PROPERTY(quint32 AuraInterruptFlags READ AuraInterruptFlags)
        Q_PROPERTY(quint32 ChannelInterruptFlags READ ChannelInterruptFlags)
        Q_PROPERTY(quint32 ProcFlags READ ProcFlags)
        Q_PROPERTY(quint32 ProcChance READ ProcChance)
        Q_PROPERTY(quint32 ProcCharges READ ProcCharges)
        Q_PROPERTY(quint32 MaxLevel READ MaxLevel)
        Q_PROPERTY(quint32 BaseLevel READ BaseLevel)
        Q_PROPERTY(quint32 SpellLevel READ SpellLevel)
        Q_PROPERTY(quint32 DurationIndex READ DurationIndex)
        Q_PROPERTY(qint32 PowerType READ PowerType)
        Q_PROPERTY(quint32 ManaCost READ ManaCost)
        Q_PROPERTY(quint32 ManaCostPerlevel READ ManaCostPerlevel)
        Q_PROPERTY(quint32 ManaPerSecond READ ManaPerSecond)
        Q_PROPERTY(quint32 ManaCostPercentage READ ManaCostPercentage)
        Q_PROPERTY(quint32 RangeIndex READ RangeIndex)
        Q_PROPERTY(float Speed READ Speed)
        Q_PROPERTY(quint32 ModalNextSpell READ ModalNextSpell)
        Q_PROPERTY(quint32 StackAmount READ StackAmount)
        Q_PROPERTY(qint32 EquippedItemClass READ EquippedItemClass)
        Q_PROPERTY(qint32 EquippedItemSubClassMask READ EquippedItemSubClassMask)
        Q_PROPERTY(qint32 EquippedItemInventoryTypeMask READ EquippedItemInventoryTypeMask)
        Q_PROPERTY(quint32 SpellIconId READ SpellIconId)
        Q_PROPERTY(quint32 ActiveIconId READ ActiveIconId)
        Q_PROPERTY(QString Name READ Name)
        Q_PROPERTY(QString Rank READ Rank)
        Q_PROPERTY(QString Description READ Description)
        Q_PROPERTY(QString ToolTip READ ToolTip)
        Q_PROPERTY(quint32 StartRecoveryCategory READ StartRecoveryCategory)
        Q_PROPERTY(quint32 StartRecoveryTime READ StartRecoveryTime)
        Q_PROPERTY(quint32 MaxTargetLevel READ MaxTargetLevel)
        Q_PROPERTY(quint32 SpellFamilyName READ SpellFamilyName)
        Q_PROPERTY(quint32 MaxAffectedTargets READ MaxAffectedTargets)
        Q_PROPERTY(quint32 DamageClass READ DamageClass)
        Q_PROPERTY(quint32 PreventionType READ PreventionType)
        Q_PROPERTY(qint32 StanceBarOrder READ StanceBarOrder)
        Q_PROPERTY(quint32 MinFactionId READ MinFactionId)
        Q_PROPERTY(quint32 MinReputation READ MinReputation)
        Q_PROPERTY(quint32 RequiredAuraVision READ RequiredAuraVision)
        Q_PROPERTY(quint32 AreaGroupId READ AreaGroupId)
        Q_PROPERTY(quint32 SchoolMask READ SchoolMask)
        Q_PROPERTY(quint32 RuneCostId READ RuneCostId)
        Q_PROPERTY(quint32 SpellMissileId READ SpellMissileId)
        Q_PROPERTY(quint32 PowerDisplayId READ PowerDisplayId)
        Q_PROPERTY(quint32 SpellDescriptionVariableId READ SpellDescriptionVariableId)
        Q_PROPERTY(quint32 SpellDifficultyId READ SpellDifficultyId)
        Q_PROPERTY(qint32 Duration READ Duration)
        Q_PROPERTY(QString NameWithRank READ NameWithRank)
    };
}

#ifdef __GNUC__
#pragma pack()
#else
#pragma pack(pop)
#endif

#endif

#pragma once

#include <QObject>

#include "../../../qsw.h"

#define MAX_SPELL_REAGENTS 8
#define MAX_SPELL_TOTEMS   2
#define MAX_EFFECT_INDEX   3

#if defined( __GNUC__ )
#pragma pack(1)
#else
#pragma pack(push,1)
#endif


namespace SkillLine
{
    struct entry
    {
        quint32 id;                                          // 0 index
        qint32  categoryId;                                  // 1 index from SkillLineCategory.dbc
        quint32 skillCostId;                                 // 2 not used
        quint32 nameOffset;                                  // 3
        quint32 nameLocalizedOffset[15];                     // 4-18 always empty, not used
        quint32 nameFlags;                                   // 19 not used
        quint32 descriptionOffset;                           // 20
        quint32 descriptionLocalizedOffset[15];              // 21-35 always empty, not used
        quint32 descriptionFlags;                            // 36 not used
        quint32 spellIcon;                                   // 37

        const QString name() const;
        const QString description() const;
    };

    DBCFile& getDbc();
    quint32 getRecordCount();
    const entry* getRecord(quint32 id, bool realId = false);
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

    DBCFile& getDbc();
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

    DBCFile& getDbc();
    quint32 getRecordCount();
    const entry* getRecord(quint32 id, bool realId = false);
}

namespace SpellCastTimes
{
    struct entry
    {
        quint32    id;                                              // 0
        qint32     castTime;                                        // 1
        qint32     castTimePerLevel;                                // 2 unsure / per skill?
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
        float       maxRange;                                        // 2
        quint32     flags;                                           // 3
        quint32     nameOffset;                                      // 4
        quint32     nameLocalizedOffset[15];                         // 5-19 always empty, not used
        quint32     nameFlags;                                       // 20 not used
        quint32     shortNameOffset;                                 // 21
        quint32     shortNameLocalizedOffset[15];                    // 22-36 always empty, not used
        quint32     shortNameFlags;                                  // 37 not used

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
        quint32 id;                                     // 0 Id
        quint32 iconPathOffset;                         // 1 Path offset

        const QString iconPath() const;
    };

    DBCFile& getDbc();
    quint32 getRecordCount();
    const entry* getRecord(quint32 id, bool realId = false);
}

namespace Spell
{
    class meta;

    struct entry
    {
        quint32    id;                                              // 0 normally counted from 0 field (but some tools start counting from 1, check this before tool use for data view!)
        quint32    category;                                        // 1
        quint32    castUI;                                          // 2 not used
        quint32    dispel;                                          // 3
        quint32    mechanic;                                        // 4
        quint32    attributes;                                      // 5
        quint32    attributesEx1;                                   // 6
        quint32    attributesEx2;                                   // 7
        quint32    attributesEx3;                                   // 8
        quint32    attributesEx4;                                   // 9
        quint32    attributesEx5;                                   // 10
        quint32    attributesEx6;                                   // 11
        quint32    stances;                                         // 12
        quint32    stancesNot;                                      // 13
        quint32    targets;                                         // 14
        quint32    targetCreatureType;                              // 15
        quint32    requiresSpellFocus;                              // 16
        quint32    facingCasterFlags;                               // 17
        quint32    casterAuraState;                                 // 18
        quint32    targetAuraState;                                 // 19
        quint32    casterAuraStateNot;                              // 20
        quint32    targetAuraStateNot;                              // 21
        quint32    castingTimeIndex;                                // 22
        quint32    recoveryTime;                                    // 23
        quint32    categoryRecoveryTime;                            // 24
        quint32    interruptFlags;                                  // 25
        quint32    auraInterruptFlags;                              // 26
        quint32    channelInterruptFlags;                           // 27
        quint32    procFlags;                                       // 28
        quint32    procChance;                                      // 29
        quint32    procCharges;                                     // 30
        quint32    maxLevel;                                        // 31
        quint32    baseLevel;                                       // 32
        quint32    spellLevel;                                      // 33
        quint32    durationIndex;                                   // 34
        qint32     powerType;                                       // 35
        quint32    manaCost;                                        // 36
        quint32    manaCostPerlevel;                                // 37
        quint32    manaPerSecond;                                   // 38
        quint32    manaPerSecondPerLevel;                           // 39
        quint32    rangeIndex;                                      // 40
        float      speed;                                           // 41
        quint32    modalNextSpell;                                  // 42 not used
        quint32    stackAmount;                                     // 43
        quint32    totem[MAX_SPELL_TOTEMS];                         // 44-45
        qint32     reagent[MAX_SPELL_REAGENTS];                     // 46-53
        quint32    reagentCount[MAX_SPELL_REAGENTS];                // 54-61
        qint32     equippedItemClass;                               // 62 (value)
        qint32     equippedItemSubClassMask;                        // 63 (mask)
        qint32     equippedItemInventoryTypeMask;                   // 64 (mask)
        quint32    effect[MAX_EFFECT_INDEX];                        // 65-67
        quint32    effectDieSides[MAX_EFFECT_INDEX];                // 68-70
        quint32    effectBaseDice[MAX_EFFECT_INDEX];                // 71-73
        float      effectDicePerLevel[MAX_EFFECT_INDEX];            // 74-76
        float      effectRealPointsPerLevel[MAX_EFFECT_INDEX];      // 77-79
        qint32     effectBasePoints[MAX_EFFECT_INDEX];              // 80-82 (don't must be used in spell/auras explicitly, must be used cached Spell::m_currentBasePoints)
        quint32    effectMechanic[MAX_EFFECT_INDEX];                // 83-85
        quint32    effectImplicitTargetA[MAX_EFFECT_INDEX];         // 86-88
        quint32    effectImplicitTargetB[MAX_EFFECT_INDEX];         // 89-91
        quint32    effectRadiusIndex[MAX_EFFECT_INDEX];             // 92-94 - spellradius.dbc
        quint32    effectApplyAuraName[MAX_EFFECT_INDEX];           // 95-97
        quint32    effectAmplitude[MAX_EFFECT_INDEX];               // 98-100
        float      effectMultipleValue[MAX_EFFECT_INDEX];           // 101-103
        quint32    effectChainTarget[MAX_EFFECT_INDEX];             // 104-106
        quint32    effectItemType[MAX_EFFECT_INDEX];                // 107-109
        qint32     effectMiscValueA[MAX_EFFECT_INDEX];              // 110-112
        qint32     effectMiscValueB[MAX_EFFECT_INDEX];              // 113-115
        quint32    effectTriggerSpell[MAX_EFFECT_INDEX];            // 116-118
        float      effectPointsPerComboPoint[MAX_EFFECT_INDEX];     // 119-121
        quint32    spellVisual;                                     // 122
        quint32    spellVisual2;                                    // 123 not used
        quint32    spellIconId;                                     // 124
        quint32    activeIconId;                                    // 125
        quint32    spellPriority;                                   // 126
        quint32    nameOffset;                                      // 127
        quint32    nameLocalizedOffset[15];                         // 128-142 always empty, not used
        quint32    nameFlag;                                        // 143 not used
        quint32    rankOffset;                                      // 144
        quint32    rankLocalizedOffset[15];                         // 145-159 always empty, not used
        quint32    rankFlags;                                       // 160 not used
        quint32    descriptionOffset;                               // 161
        quint32    descriptionLocalizedOffset[15];                  // 162-176 always empty, not used
        quint32    descriptionFlags;                                // 177 not used
        quint32    toolTipOffset;                                   // 178
        quint32    toolTipLocalizedOffset[15];                      // 179-193 always empty, not used
        quint32    toolTipFlags;                                    // 194 not used
        quint32    manaCostPercentage;                              // 195
        quint32    startRecoveryCategory;                           // 196
        quint32    startRecoveryTime;                               // 197
        quint32    maxTargetLevel;                                  // 198
        quint32    spellFamilyName;                                 // 199
        quint64    spellFamilyFlags;                                // 200+201
        quint32    maxAffectedTargets;                              // 202
        quint32    damageClass;                                     // 203 defenseType
        quint32    preventionType;                                  // 204
        qint32     stanceBarOrder;                                  // 205 not used
        float      damageMultiplier[MAX_EFFECT_INDEX];              // 206-208
        quint32    minFactionId;                                    // 209 not used, and 0 in 2.4.2
        quint32    minReputation;                                   // 210 not used, and 0 in 2.4.2
        quint32    requiredAuraVision;                              // 211 not used
        quint32    totemCategory[MAX_SPELL_TOTEMS];                 // 212-213
        quint32    areaId;                                          // 214
        quint32    schoolMask;                                      // 215 school mask

        const QString name() const;
        const QString description() const;
        const QString rank() const;
        const QString toolTip() const;
        const QString nameWithRank() const;

        quint32 getAmplitude() const
        {
            for (quint8 i = 0; i < MAX_EFFECT_INDEX; ++i)
                if (effectAmplitude[i])
                    return quint32(effectAmplitude[i] / 1000);

            return 0;
        }

        quint32 getAmplitude(quint8 index) const
        {
            return quint32(effectAmplitude[index] / 1000);
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
            if (const SpellRadius::entry* spellRadius = SpellRadius::getRecord(effectRadiusIndex[index], true))
                return spellRadius->radius;

            return 0.0f;
        }

        quint32 getTicks(quint8 index) const
        {
            return quint32(getDuration() / (effectAmplitude[index] ? quint32(effectAmplitude[index] / 1000) : getDuration()));
        }

        qint32 getTriggerDuration(quint8 index) const;
    };

    DBCFile &getDbc();
    quint32 getRecordCount();
    const entry* getRecord(quint32 id, bool realId = false);

    quint32 getMetaSpellCount();
    meta* getMetaSpell(quint32 id, bool realId = false);
    const entry* getMetaRecord(quint32 id, bool realId = false);

    class meta : public QObject
    {
        Q_OBJECT

        public:

            meta(const entry* info) : m_info(info), m_destroyInfo(false) {}

            ~meta()
            {
                if (m_destroyInfo)
                {
                    delete m_info;
                    m_info = nullptr;
                }
            }

            void setSpellInfo(entry* info)
            {
                m_info = info;
                m_destroyInfo = true;
            }

            // Addition properties
            quint8 getServerSide() { return m_serverSide; }
            void setServerSide(quint8 value) { m_serverSide = value; }

            const entry* getInfo() const { Q_ASSERT(m_info); return m_info; }

            float      effectBonusMultiplier[3];                        // 216-218
            float      effectBonusMultiplierAP[3];                      // 219-222

        public slots:

            quint32 Id() { return m_info->id; }
            quint32 Category() { return m_info->category; }
            quint32 CastUI() { return m_info->castUI; }
            quint32 Dispel() { return m_info->dispel; }
            quint32 Mechanic() { return m_info->mechanic; }
            quint32 Attributes() { return m_info->attributes; }
            quint32 AttributesEx1() { return m_info->attributesEx1; }
            quint32 AttributesEx2() { return m_info->attributesEx2; }
            quint32 AttributesEx3() { return m_info->attributesEx3; }
            quint32 AttributesEx4() { return m_info->attributesEx4; }
            quint32 AttributesEx5() { return m_info->attributesEx5; }
            quint32 AttributesEx6() { return m_info->attributesEx6; }
            quint32 Stances() { return m_info->stances; }
            quint32 StancesNot() { return m_info->stancesNot; }
            quint32 Targets() { return m_info->targets; }
            quint32 TargetCreatureType() { return m_info->targetCreatureType; }
            quint32 RequiresSpellFocus() { return m_info->requiresSpellFocus; }
            quint32 FacingCasterFlags() { return m_info->facingCasterFlags; }
            quint32 CasterAuraState() { return m_info->casterAuraState; }
            quint32 TargetAuraState() { return m_info->targetAuraState; }
            quint32 CasterAuraStateNot() { return m_info->casterAuraStateNot; }
            quint32 TargetAuraStateNot() { return m_info->targetAuraStateNot; }
            quint32 CastingTimeIndex() { return m_info->castingTimeIndex; }
            quint32 RecoveryTime() { return m_info->recoveryTime; }
            quint32 CategoryRecoveryTime() { return m_info->categoryRecoveryTime; }
            quint32 InterruptFlags() { return m_info->interruptFlags; }
            quint32 AuraInterruptFlags() { return m_info->auraInterruptFlags; }
            quint32 ChannelInterruptFlags() { return m_info->channelInterruptFlags; }
            quint32 ProcFlags() { return m_info->procFlags; }
            quint32 ProcChance() { return m_info->procChance; }
            quint32 ProcCharges() { return m_info->procCharges; }
            quint32 MaxLevel() { return m_info->maxLevel; }
            quint32 BaseLevel() { return m_info->baseLevel; }
            quint32 SpellLevel() { return m_info->spellLevel; }
            quint32 DurationIndex() { return m_info->durationIndex; }
            qint32 PowerType() { return m_info->powerType; }
            quint32 ManaCost() { return m_info->manaCost; }
            quint32 ManaCostPerlevel() { return m_info->manaCostPerlevel; }
            quint32 ManaPerSecond() { return m_info->manaPerSecond; }
            quint32 ManaPerSecondPerLevel() { return m_info->manaPerSecondPerLevel; }
            quint32 RangeIndex() { return m_info->rangeIndex; }
            float Speed() { return m_info->speed; }
            quint32 ModalNextSpell() { return m_info->modalNextSpell; }
            quint32 StackAmount() { return m_info->stackAmount; }
            quint32 Totem(quint8 index) { return m_info->totem[index]; }
            qint32 Reagent(quint8 index) { return m_info->reagent[index]; }
            quint32 ReagentCount(quint8 index) { return m_info->reagentCount[index]; }
            qint32 EquippedItemClass() { return m_info->equippedItemClass; }
            qint32 EquippedItemSubClassMask() { return m_info->equippedItemSubClassMask; }
            qint32 EquippedItemInventoryTypeMask() { return m_info->equippedItemInventoryTypeMask; }
            quint32 Effect(quint8 index) { return m_info->effect[index]; }
            quint32 EffectDieSides(quint8 index) { return m_info->effectDieSides[index]; }
            quint32 EffectBaseDice(quint8 index) { return m_info->effectBaseDice[index]; }
            float EffectDicePerLevel(quint8 index) { return m_info->effectDicePerLevel[index]; }
            float EffectRealPointsPerLevel(quint8 index) { return m_info->effectRealPointsPerLevel[index]; }
            qint32 EffectBasePoints(quint8 index) { return m_info->effectBasePoints[index]; }
            quint32 EffectMechanic(quint8 index) { return m_info->effectMechanic[index]; }
            quint32 EffectImplicitTargetA(quint8 index) { return m_info->effectImplicitTargetA[index]; }
            quint32 EffectImplicitTargetB(quint8 index) { return m_info->effectImplicitTargetB[index]; }
            quint32 EffectRadiusIndex(quint8 index) { return m_info->effectRadiusIndex[index]; }
            quint32 EffectApplyAuraName(quint8 index) { return m_info->effectApplyAuraName[index]; }
            quint32 EffectAmplitude(quint8 index) { return m_info->effectAmplitude[index]; }
            float EffectMultipleValue(quint8 index) { return m_info->effectMultipleValue[index]; }
            quint32 EffectChainTarget(quint8 index) { return m_info->effectChainTarget[index]; }
            quint32 EffectItemType(quint8 index) { return m_info->effectItemType[index]; }
            qint32 EffectMiscValueA(quint8 index) { return m_info->effectMiscValueA[index]; }
            qint32 EffectMiscValueB(quint8 index) { return m_info->effectMiscValueB[index]; }
            quint32 EffectTriggerSpell(quint8 index) { return m_info->effectTriggerSpell[index]; }
            float EffectPointsPerComboPoint(quint8 index) { return m_info->effectPointsPerComboPoint[index]; }
            quint32 SpellVisual() { return m_info->spellVisual; }
            quint32 SpellIconId() { return m_info->spellIconId; }
            quint32 ActiveIconId() { return m_info->activeIconId; }
            quint32 SpellPriority() { return m_info->spellPriority; }
            QString Name() { return m_info->name(); }
            QString Rank() { return m_info->rank(); }
            QString Description() { return m_info->description(); }
            QString ToolTip() { return m_info->toolTip(); }
            quint32 NameFlag() { return m_info->nameFlag; }
            quint32 RankFlags() { return m_info->rankFlags; }
            quint32 DescriptionFlags() { return m_info->descriptionFlags; }
            quint32 ToolTipFlags() { return m_info->toolTipFlags; }
            quint32 ManaCostPercentage() { return m_info->manaCostPercentage; }
            quint32 StartRecoveryCategory() { return m_info->startRecoveryCategory; }
            quint32 StartRecoveryTime() { return m_info->startRecoveryTime; }
            quint32 MaxTargetLevel() { return m_info->maxTargetLevel; }
            quint32 SpellFamilyName() { return m_info->spellFamilyName; }
            quint64 SpellFamilyFlags() { return m_info->spellFamilyFlags; }
            quint32 MaxAffectedTargets() { return m_info->maxAffectedTargets; }
            quint32 DamageClass() { return m_info->damageClass; }
            quint32 PreventionType() { return m_info->preventionType; }
            qint32 StanceBarOrder() { return m_info->stanceBarOrder; }
            float DamageMultiplier(quint8 index) { return m_info->damageMultiplier[index]; }
            quint32 MinFactionId() { return m_info->minFactionId; }
            quint32 MinReputation() { return m_info->minReputation; }
            quint32 RequiredAuraVision() { return m_info->requiredAuraVision; }
            quint32 TotemCategory(quint8 index) { return m_info->totemCategory[index]; }
            quint32 AreaId() { return m_info->areaId; }
            quint32 SchoolMask() { return m_info->schoolMask; }
            qint32 Duration() { return m_info->getDuration(); }
            qint32 TriggerDuration(quint8 index) { return m_info->getTriggerDuration(index); }
            QString NameWithRank() { return m_info->nameWithRank(); }

            bool hasAura(quint32 auraId)
            {
                for (quint8 i = 0; i < MAX_EFFECT_INDEX; ++i)
                    if (m_info->effectApplyAuraName[i] == auraId)
                        return true;
                return false;
            }

            bool hasEffect(quint32 effectId)
            {
                for (quint8 i = 0; i < MAX_EFFECT_INDEX; ++i)
                    if (m_info->effect[i] == effectId)
                        return true;
                return false;
            }

            bool hasTargetA(quint32 targetId)
            {
                for (quint8 i = 0; i < MAX_EFFECT_INDEX; ++i)
                    if (m_info->effectImplicitTargetA[i] == targetId)
                        return true;
                return false;
            }

            bool hasTargetB(quint32 targetId)
            {
                for (quint8 i = 0; i < MAX_EFFECT_INDEX; ++i)
                    if (m_info->effectImplicitTargetB[i] == targetId)
                        return true;
                return false;
            }

            bool isFitToFamilyMask(quint64 flags) { return !!(m_info->spellFamilyFlags & flags); }

        private:

            const entry* m_info;
            bool m_destroyInfo;
            bool m_serverSide;

            Q_PROPERTY(quint32 Id READ Id)
            Q_PROPERTY(quint32 Category READ Category)
            Q_PROPERTY(quint32 CastUI READ CastUI)
            Q_PROPERTY(quint32 Dispel READ Dispel)
            Q_PROPERTY(quint32 Mechanic READ Mechanic)
            Q_PROPERTY(quint32 Attributes READ Attributes)
            Q_PROPERTY(quint32 AttributesEx1 READ AttributesEx1)
            Q_PROPERTY(quint32 AttributesEx2 READ AttributesEx2)
            Q_PROPERTY(quint32 AttributesEx3 READ AttributesEx3)
            Q_PROPERTY(quint32 AttributesEx4 READ AttributesEx4)
            Q_PROPERTY(quint32 AttributesEx5 READ AttributesEx5)
            Q_PROPERTY(quint32 AttributesEx6 READ AttributesEx6)
            Q_PROPERTY(quint32 Stances READ Stances)
            Q_PROPERTY(quint32 StancesNot READ StancesNot)
            Q_PROPERTY(quint32 Targets READ Targets)
            Q_PROPERTY(quint32 TargetCreatureType READ TargetCreatureType)
            Q_PROPERTY(quint32 RequiresSpellFocus READ RequiresSpellFocus)
            Q_PROPERTY(quint32 FacingCasterFlags READ FacingCasterFlags)
            Q_PROPERTY(quint32 CasterAuraState READ CasterAuraState)
            Q_PROPERTY(quint32 TargetAuraState READ TargetAuraState)
            Q_PROPERTY(quint32 CasterAuraStateNot READ CasterAuraStateNot)
            Q_PROPERTY(quint32 TargetAuraStateNot READ TargetAuraStateNot)
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
            Q_PROPERTY(quint32 ManaPerSecondPerLevel READ ManaPerSecondPerLevel)
            Q_PROPERTY(quint32 RangeIndex READ RangeIndex)
            Q_PROPERTY(float Speed READ Speed)
            Q_PROPERTY(quint32 ModalNextSpell READ ModalNextSpell)
            Q_PROPERTY(quint32 StackAmount READ StackAmount)
            Q_PROPERTY(qint32 EquippedItemClass READ EquippedItemClass)
            Q_PROPERTY(qint32 EquippedItemSubClassMask READ EquippedItemSubClassMask)
            Q_PROPERTY(qint32 EquippedItemInventoryTypeMask READ EquippedItemInventoryTypeMask)
            Q_PROPERTY(quint32 SpellVisual READ SpellVisual)
            Q_PROPERTY(quint32 SpellIconId READ SpellIconId)
            Q_PROPERTY(quint32 ActiveIconId READ ActiveIconId)
            Q_PROPERTY(quint32 SpellPriority READ SpellPriority)
            Q_PROPERTY(QString Name READ Name)
            Q_PROPERTY(QString Rank READ Rank)
            Q_PROPERTY(QString Description READ Description)
            Q_PROPERTY(QString ToolTip READ ToolTip)
            Q_PROPERTY(quint32 NameFlag READ NameFlag)
            Q_PROPERTY(quint32 RankFlags READ RankFlags)
            Q_PROPERTY(quint32 DescriptionFlags READ DescriptionFlags)
            Q_PROPERTY(quint32 ToolTipFlags READ ToolTipFlags)
            Q_PROPERTY(quint32 ManaCostPercentage READ ManaCostPercentage)
            Q_PROPERTY(quint32 StartRecoveryCategory READ StartRecoveryCategory)
            Q_PROPERTY(quint32 StartRecoveryTime READ StartRecoveryTime)
            Q_PROPERTY(quint32 MaxTargetLevel READ MaxTargetLevel)
            Q_PROPERTY(quint32 SpellFamilyName READ SpellFamilyName)
            Q_PROPERTY(quint64 SpellFamilyFlags READ SpellFamilyFlags)
            Q_PROPERTY(quint32 MaxAffectedTargets READ MaxAffectedTargets)
            Q_PROPERTY(quint32 DamageClass READ DamageClass)
            Q_PROPERTY(quint32 PreventionType READ PreventionType)
            Q_PROPERTY(qint32 StanceBarOrder READ StanceBarOrder)
            Q_PROPERTY(quint32 MinFactionId READ MinFactionId)
            Q_PROPERTY(quint32 MinReputation READ MinReputation)
            Q_PROPERTY(quint32 RequiredAuraVision READ RequiredAuraVision)
            Q_PROPERTY(quint32 AreaId READ AreaId)
            Q_PROPERTY(quint32 SchoolMask READ SchoolMask)
            Q_PROPERTY(qint32 Duration READ Duration)
            Q_PROPERTY(QString NameWithRank READ NameWithRank)
            Q_PROPERTY(quint8 ServerSide READ getServerSide WRITE setServerSide)
    };
}

#if defined( __GNUC__ )
#pragma pack()
#else
#pragma pack(pop)
#endif

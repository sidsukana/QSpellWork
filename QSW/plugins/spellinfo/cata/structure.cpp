#include "structure.h"
#include "spellinfo.h"

// SkillLine.dbc
DBCFile& SkillLine::getDbc()
{
    static DBCFile dbc("SkillLine.dbc");
    return dbc;
}

quint32 SkillLine::getRecordCount()
{
    return getDbc().getRecordCount();
}

const SkillLine::entry* SkillLine::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

const QString SkillLine::entry::name() const
{
    return getDbc().getString(nameOffset);
}

const QString SkillLine::entry::description() const
{
    return getDbc().getString(descriptionOffset);
}

const QString SkillLine::entry::verb() const
{
    return getDbc().getString(verbOffset);
}

// SkillLineAbility.dbc
DBCFile& SkillLineAbility::getDbc()
{
    static DBCFile dbc("SkillLineAbility.dbc");
    return dbc;
}

quint32 SkillLineAbility::getRecordCount()
{
    return getDbc().getRecordCount();
}

const SkillLineAbility::entry* SkillLineAbility::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

// SpellCastTimes.dbc
DBCFile& SpellCastTimes::getDbc()
{
    static DBCFile dbc("SpellCastTimes.dbc");
    return dbc;
}

quint32 SpellCastTimes::getRecordCount()
{
    return getDbc().getRecordCount();
}

const SpellCastTimes::entry* SpellCastTimes::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

// SpellRadius.dbc
DBCFile& SpellRadius::getDbc()
{
    static DBCFile dbc("SpellRadius.dbc");
    return dbc;
}

quint32 SpellRadius::getRecordCount()
{
    return getDbc().getRecordCount();
}

const SpellRadius::entry* SpellRadius::getRecord(quint32 id, bool realId)
{
   return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

// SpellRange.dbc
DBCFile& SpellRange::getDbc()
{
    static DBCFile dbc("SpellRange.dbc");
    return dbc;
}

quint32 SpellRange::getRecordCount()
{
    return getDbc().getRecordCount();
}

const SpellRange::entry* SpellRange::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

const QString SpellRange::entry::name() const
{
    return getDbc().getString(nameOffset);
}

const QString SpellRange::entry::shortName() const
{
    return getDbc().getString(shortNameOffset);
}

// SpellDuration.dbc
DBCFile &SpellDuration::getDbc()
{
    static DBCFile dbc("SpellDuration.dbc");
    return dbc;
}

quint32 SpellDuration::getRecordCount()
{
    return getDbc().getRecordCount();
}

const SpellDuration::entry* SpellDuration::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

// SpellIcon.dbc
DBCFile& SpellIcon::getDbc()
{
    static DBCFile dbc("SpellIcon.dbc");
    return dbc;
}

quint32 SpellIcon::getRecordCount()
{
    return getDbc().getRecordCount();
}

const SpellIcon::entry* SpellIcon::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

const QString SpellIcon::entry::iconPath() const
{
    return getDbc().getString(iconPathOffset);
}

// Spell.dbc
DBCFile& Spell::getDbc()
{
    static DBCFile dbc("Spell.dbc");
    return dbc;
}

quint32 Spell::getRecordCount()
{
    return getDbc().getRecordCount();
}

const Spell::entry* Spell::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

const QString Spell::entry::name() const
{
    return getDbc().getString(nameOffset);
}

const QString Spell::entry::description() const
{
    return getDbc().getString(descriptionOffset);
}

const QString Spell::entry::rank() const
{
    return getDbc().getString(rankOffset);
}

const QString Spell::entry::toolTip() const
{
    return getDbc().getString(toolTipOffset);
}

const QString Spell::entry::nameWithRank() const
{
    return (!rank().isEmpty() ? name() + " (" + rank() + ")" : name());
}

// SpellAuraOptions.dbc
DBCFile& SpellAuraOptions::getDbc()
{
    static DBCFile dbc("SpellAuraOptions.dbc");
    return dbc;
}

quint32 SpellAuraOptions::getRecordCount()
{
    return getDbc().getRecordCount();
}

const SpellAuraOptions::entry* SpellAuraOptions::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

quint32 Spell::entry::getStackAmount() const
{
    if (const SpellAuraOptions::entry* auraOptions = SpellAuraOptions::getRecord(spellAuraOptionsId, true))
        return auraOptions->stackAmount;
    return 0;
}

quint32 Spell::entry::getProcChance() const
{
    if (const SpellAuraOptions::entry* auraOptions = SpellAuraOptions::getRecord(spellAuraOptionsId, true))
        return auraOptions->procChance;
    return 0;
}
quint32 Spell::entry::getProcCharges() const
{
    if (const SpellAuraOptions::entry* auraOptions = SpellAuraOptions::getRecord(spellAuraOptionsId, true))
        return auraOptions->procCharges;
    return 0;
}
quint32 Spell::entry::getProcFlags() const
{
    if (const SpellAuraOptions::entry* auraOptions = SpellAuraOptions::getRecord(spellAuraOptionsId, true))
        return auraOptions->procFlags;
    return 0;
}

qint32 Spell::entry::getTriggerDuration(quint8 index) const
{
    const Spell::entry* triggerSpell = Spell::getRecord(getEffectTriggerSpell(index), true);
    if (triggerSpell)
        return triggerSpell->getDuration();
    return 0;
}

// SpellAuraRestrictions.dbc
DBCFile& SpellAuraRestrictions::getDbc()
{
    static DBCFile dbc("SpellAuraRestrictions.dbc");
    return dbc;
}

quint32 SpellAuraRestrictions::getRecordCount()
{
    return getDbc().getRecordCount();
}

const SpellAuraRestrictions::entry* SpellAuraRestrictions::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

quint32 Spell::entry::getCasterAuraState() const
{
    if (const SpellAuraRestrictions::entry* auraRest = SpellAuraRestrictions::getRecord(spellAuraRestrictionsId, true))
        return auraRest->casterAuraState;
    return 0;
}

quint32 Spell::entry::getTargetAuraState() const
{
    if (const SpellAuraRestrictions::entry* auraRest = SpellAuraRestrictions::getRecord(spellAuraRestrictionsId, true))
        return auraRest->targetAuraState;
    return 0;
}

quint32 Spell::entry::getCasterAuraStateNot() const
{
    if (const SpellAuraRestrictions::entry* auraRest = SpellAuraRestrictions::getRecord(spellAuraRestrictionsId, true))
        return auraRest->casterAuraStateNot;
    return 0;
}

quint32 Spell::entry::getTargetAuraStateNot() const
{
    if (const SpellAuraRestrictions::entry* auraRest = SpellAuraRestrictions::getRecord(spellAuraRestrictionsId, true))
        return auraRest->targetAuraStateNot;
    return 0;
}

quint32 Spell::entry::getCasterAuraSpell() const
{
    if (const SpellAuraRestrictions::entry* auraRest = SpellAuraRestrictions::getRecord(spellAuraRestrictionsId, true))
        return auraRest->casterAuraSpell;
    return 0;
}

quint32 Spell::entry::getTargetAuraSpell() const
{
    if (const SpellAuraRestrictions::entry* auraRest = SpellAuraRestrictions::getRecord(spellAuraRestrictionsId, true))
        return auraRest->targetAuraSpell;
    return 0;
}

quint32 Spell::entry::getExcludeCasterAuraSpell() const
{
    if (const SpellAuraRestrictions::entry* auraRest = SpellAuraRestrictions::getRecord(spellAuraRestrictionsId, true))
        return auraRest->excludeCasterAuraSpell;
    return 0;
}

quint32 Spell::entry::getExcludeTargetAuraSpell() const
{
    if (const SpellAuraRestrictions::entry* auraRest = SpellAuraRestrictions::getRecord(spellAuraRestrictionsId, true))
        return auraRest->excludeTargetAuraSpell;
    return 0;
}

// SpellCastingRequirements.dbc
DBCFile& SpellCastingRequirements::getDbc()
{
    static DBCFile dbc("SpellCastingRequirements.dbc");
    return dbc;
}

quint32 SpellCastingRequirements::getRecordCount()
{
    return getDbc().getRecordCount();
}

const SpellCastingRequirements::entry* SpellCastingRequirements::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

quint32 Spell::entry::getFacingCasterFlags() const
{
    if (const SpellCastingRequirements::entry* castReqs = SpellCastingRequirements::getRecord(spellCastingRequirementsId, true))
        return castReqs->facingCasterFlags;
    return 0;
}

quint32 Spell::entry::getMinFactionId() const
{
    if (const SpellCastingRequirements::entry* castReqs = SpellCastingRequirements::getRecord(spellCastingRequirementsId, true))
        return castReqs->minFactionId;
    return 0;
}

quint32 Spell::entry::getMinReputation() const
{
    if (const SpellCastingRequirements::entry* castReqs = SpellCastingRequirements::getRecord(spellCastingRequirementsId, true))
        return castReqs->minFactionId;
    return 0;
}

qint32  Spell::entry::getAreaGroupId() const
{
    if (const SpellCastingRequirements::entry* castReqs = SpellCastingRequirements::getRecord(spellCastingRequirementsId, true))
        return castReqs->areaGroupId;
    return 0;
}

quint32 Spell::entry::getRequiredAuraVision() const
{
    if (const SpellCastingRequirements::entry* castReqs = SpellCastingRequirements::getRecord(spellCastingRequirementsId, true))
        return castReqs->requiredAuraVision;
    return 0;
}

quint32 Spell::entry::getRequiresSpellFocus() const
{
    if (const SpellCastingRequirements::entry* castReqs = SpellCastingRequirements::getRecord(spellCastingRequirementsId, true))
        return castReqs->requiresSpellFocus;
    return 0;
}

// SpellCategories.dbc
DBCFile& SpellCategories::getDbc()
{
    static DBCFile dbc("SpellCategories.dbc");
    return dbc;
}

quint32 SpellCategories::getRecordCount()
{
    return getDbc().getRecordCount();
}

const SpellCategories::entry* SpellCategories::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

quint32 Spell::entry::getCategory() const
{
    if (const SpellCategories::entry* category = SpellCategories::getRecord(spellCategoriesId, true))
        return category->category;
    return 0;
}

quint32 Spell::entry::getDamageClass() const
{
    if (const SpellCategories::entry* category = SpellCategories::getRecord(spellCategoriesId, true))
        return category->damageClass;
    return 0;
}

quint32 Spell::entry::getDispel() const
{
    if (const SpellCategories::entry* category = SpellCategories::getRecord(spellCategoriesId, true))
        return category->dispel;
    return 0;
}

quint32 Spell::entry::getMechanic() const
{
    if (const SpellCategories::entry* category = SpellCategories::getRecord(spellCategoriesId, true))
        return category->mechanic;
    return 0;
}

quint32 Spell::entry::getPreventionType() const
{
    if (const SpellCategories::entry* category = SpellCategories::getRecord(spellCategoriesId, true))
        return category->preventionType;
    return 0;
}

quint32 Spell::entry::getStartRecoveryCategory() const
{
    if (const SpellCategories::entry* category = SpellCategories::getRecord(spellCategoriesId, true))
        return category->startRecoveryCategory;
    return 0;
}

// SpellClassOptions.dbc
DBCFile& SpellClassOptions::getDbc()
{
    static DBCFile dbc("SpellClassOptions.dbc");
    return dbc;
}

quint32 SpellClassOptions::getRecordCount()
{
    return getDbc().getRecordCount();
}

const SpellClassOptions::entry* SpellClassOptions::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

quint32 Spell::entry::getModalNextSpell() const
{
    if (const SpellClassOptions::entry* classOptions = SpellClassOptions::getRecord(spellClassOptionsId, true))
        return classOptions->modalNextSpell;
    return 0;
}

quint32 Spell::entry::getSpellFamilyFlags(quint8 index) const
{
    if (const SpellClassOptions::entry* classOptions = SpellClassOptions::getRecord(spellClassOptionsId, true))
        return classOptions->spellFamilyFlags[index];
    return 0;
}

quint32 Spell::entry::getSpellFamilyName() const
{
    if (const SpellClassOptions::entry* classOptions = SpellClassOptions::getRecord(spellClassOptionsId, true))
        return classOptions->spellFamilyName;
    return 0;
}

// SpellCooldowns.dbc
DBCFile& SpellCooldowns::getDbc()
{
    static DBCFile dbc("SpellCooldowns.dbc");
    return dbc;
}

quint32 SpellCooldowns::getRecordCount()
{
    return getDbc().getRecordCount();
}

const SpellCooldowns::entry* SpellCooldowns::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

quint32 Spell::entry::getCategoryRecoveryTime() const
{
    if (const SpellCooldowns::entry* cooldown = SpellCooldowns::getRecord(spellCooldownsId, true))
        return cooldown->categoryRecoveryTime;
    return 0;
}

quint32 Spell::entry::getRecoveryTime() const
{
    if (const SpellCooldowns::entry* cooldown = SpellCooldowns::getRecord(spellCooldownsId, true))
        return cooldown->recoveryTime;
    return 0;
}

quint32 Spell::entry::getStartRecoveryTime() const
{
    if (const SpellCooldowns::entry* cooldown = SpellCooldowns::getRecord(spellCooldownsId, true))
        return cooldown->startRecoveryTime;
    return 0;
}

// SpellEquippedItems.dbc
DBCFile& SpellEquippedItems::getDbc()
{
    static DBCFile dbc("SpellEquippedItems.dbc");
    return dbc;
}

quint32 SpellEquippedItems::getRecordCount()
{
    return getDbc().getRecordCount();
}

const SpellEquippedItems::entry* SpellEquippedItems::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

qint32 Spell::entry::getEquippedItemClass() const
{
    if (const SpellEquippedItems::entry* equippedItems = SpellEquippedItems::getRecord(spellEquippedItemsId, true))
        return equippedItems->equippedItemClass;
    return 0;
}

qint32 Spell::entry::getEquippedItemInventoryTypeMask() const
{
    if (const SpellEquippedItems::entry* equippedItems = SpellEquippedItems::getRecord(spellEquippedItemsId, true))
        return equippedItems->equippedItemInventoryTypeMask;
    return 0;
}

qint32 Spell::entry::getEquippedItemSubClassMask() const
{
    if (const SpellEquippedItems::entry* equippedItems = SpellEquippedItems::getRecord(spellEquippedItemsId, true))
        return equippedItems->equippedItemSubClassMask;
    return 0;
}

// SpellInterrupts.dbc
DBCFile& SpellInterrupts::getDbc()
{
    static DBCFile dbc("SpellInterrupts.dbc");
    return dbc;
}

quint32 SpellInterrupts::getRecordCount()
{
    return getDbc().getRecordCount();
}

const SpellInterrupts::entry* SpellInterrupts::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

quint32 Spell::entry::getAuraInterruptFlags() const
{
    if (const SpellInterrupts::entry* interrupt = SpellInterrupts::getRecord(spellInterruptsId, true))
        return interrupt->auraInterruptFlags;
    return 0;
}

quint32 Spell::entry::getChannelInterruptFlags() const
{
    if (const SpellInterrupts::entry* interrupt = SpellInterrupts::getRecord(spellInterruptsId, true))
        return interrupt->channelInterruptFlags;
    return 0;
}
quint32 Spell::entry::getInterruptFlags() const
{
    if (const SpellInterrupts::entry* interrupt = SpellInterrupts::getRecord(spellInterruptsId, true))
        return interrupt->interruptFlags;
    return 0;
}

// SpellLevels.dbc
DBCFile& SpellLevels::getDbc()
{
    static DBCFile dbc("SpellLevels.dbc");
    return dbc;
}

quint32 SpellLevels::getRecordCount()
{
    return getDbc().getRecordCount();
}

const SpellLevels::entry* SpellLevels::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

quint32 Spell::entry::getBaseLevel() const
{
    if (const SpellLevels::entry* levels = SpellLevels::getRecord(spellLevelsId, true))
        return levels->baseLevel;
    return 0;
}

quint32 Spell::entry::getMaxLevel() const
{
    if (const SpellLevels::entry* levels = SpellLevels::getRecord(spellLevelsId, true))
        return levels->maxLevel;
    return 0;
}

quint32 Spell::entry::getSpellLevel() const
{
    if (const SpellLevels::entry* levels = SpellLevels::getRecord(spellLevelsId, true))
        return levels->spellLevel;
    return 0;
}

// SpellPower.dbc
DBCFile& SpellPower::getDbc()
{
    static DBCFile dbc("SpellPower.dbc");
    return dbc;
}

quint32 SpellPower::getRecordCount()
{
    return getDbc().getRecordCount();
}

const SpellPower::entry* SpellPower::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

quint32 Spell::entry::getManaCost() const
{
    if (const SpellPower::entry* power = SpellPower::getRecord(spellPowerId, true))
        return power->manaCost;
    return 0;
}

quint32 Spell::entry::getManaCostPerlevel() const
{
    if (const SpellPower::entry* power = SpellPower::getRecord(spellPowerId, true))
        return power->manaCostPerlevel;
    return 0;
}
quint32 Spell::entry::getManaCostPercentage() const
{
    if (const SpellPower::entry* power = SpellPower::getRecord(spellPowerId, true))
        return power->manaCostPercentage;
    return 0;
}

quint32 Spell::entry::getManaPerSecond() const
{
    if (const SpellPower::entry* power = SpellPower::getRecord(spellPowerId, true))
        return power->manaPerSecond;
    return 0;
}

quint32 Spell::entry::getPowerDisplayId() const
{
    if (const SpellPower::entry* power = SpellPower::getRecord(spellPowerId, true))
        return power->powerDisplayId;
    return 0;
}

// SpellReagents.dbc
DBCFile& SpellReagents::getDbc()
{
    static DBCFile dbc("SpellReagents.dbc");
    return dbc;
}

quint32 SpellReagents::getRecordCount()
{
    return getDbc().getRecordCount();
}

const SpellReagents::entry* SpellReagents::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

qint32 Spell::entry::getReagent(quint8 index) const
{
    if (const SpellReagents::entry* reagents = SpellReagents::getRecord(spellReagentsId, true))
        return reagents->reagent[index];
    return 0;
}

quint32 Spell::entry::getReagentCount(quint8 index) const
{
    if (const SpellReagents::entry* reagents = SpellReagents::getRecord(spellReagentsId, true))
        return reagents->reagentCount[index];
    return 0;
}

// SpellShapeshift.dbc
DBCFile& SpellShapeshift::getDbc()
{
    static DBCFile dbc("SpellShapeshift.dbc");
    return dbc;
}

quint32 SpellShapeshift::getRecordCount()
{
    return getDbc().getRecordCount();
}

const SpellShapeshift::entry* SpellShapeshift::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

quint64 Spell::entry::getStancesNot() const
{
    if (const SpellShapeshift::entry* shapeshift = SpellShapeshift::getRecord(spellShapeshiftId, true))
        return shapeshift->stancesNot;
    return 0;
}

quint64 Spell::entry::getStances() const
{
    if (const SpellShapeshift::entry* shapeshift = SpellShapeshift::getRecord(spellShapeshiftId, true))
        return shapeshift->stances;
    return 0;
}

quint32 Spell::entry::getStanceBarOrder() const
{
    if (const SpellShapeshift::entry* shapeshift = SpellShapeshift::getRecord(spellShapeshiftId, true))
        return shapeshift->stanceBarOrder;
    return 0;
}

// SpellTargetRestrictions.dbc
DBCFile& SpellTargetRestrictions::getDbc()
{
    static DBCFile dbc("SpellTargetRestrictions.dbc");
    return dbc;
}

quint32 SpellTargetRestrictions::getRecordCount()
{
    return getDbc().getRecordCount();
}

const SpellTargetRestrictions::entry* SpellTargetRestrictions::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

float Spell::entry::getMaxTargetRadius() const
{
    if (const SpellTargetRestrictions::entry* targets = SpellTargetRestrictions::getRecord(spellTargetRestrictionsId, true))
        return targets->maxTargetRadius;
    return 0.0f;
}

quint32 Spell::entry::getMaxAffectedTargets() const
{
    if (const SpellTargetRestrictions::entry* targets = SpellTargetRestrictions::getRecord(spellTargetRestrictionsId, true))
        return targets->maxAffectedTargets;
    return 0;
}

quint32 Spell::entry::getMaxTargetLevel() const
{
    if (const SpellTargetRestrictions::entry* targets = SpellTargetRestrictions::getRecord(spellTargetRestrictionsId, true))
        return targets->maxTargetLevel;
    return 0;
}

quint32 Spell::entry::getTargetCreatureType() const
{
    if (const SpellTargetRestrictions::entry* targets = SpellTargetRestrictions::getRecord(spellTargetRestrictionsId, true))
        return targets->targetCreatureType;
    return 0;
}

quint32 Spell::entry::getTargets() const
{
    if (const SpellTargetRestrictions::entry* targets = SpellTargetRestrictions::getRecord(spellTargetRestrictionsId, true))
        return targets->targets;
    return 0;
}

// SpellTotems.dbc
DBCFile& SpellTotems::getDbc()
{
    static DBCFile dbc("SpellTotems.dbc");
    return dbc;
}

quint32 SpellTotems::getRecordCount()
{
    return getDbc().getRecordCount();
}

const SpellTotems::entry* SpellTotems::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

quint32 Spell::entry::getTotemCategory(quint8 index) const
{
    if (const SpellTotems::entry* totems = SpellTotems::getRecord(spellTotemsId, true))
        return totems->totemCategory[index];
    return 0;
}

quint32 Spell::entry::getTotem(quint8 index) const
{
    if (const SpellTotems::entry* totems = SpellTotems::getRecord(spellTotemsId, true))
        return totems->totem[index];
    return 0;
}

// SpellEffect.dbc
DBCFile& SpellEffect::getDbc()
{
    static DBCFile dbc("SpellEffect.dbc");
    return dbc;
}

quint32 SpellEffect::getRecordCount()
{
    return getDbc().getRecordCount();
}

const SpellEffect::entry* SpellEffect::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

void Spell::fillSpellEffects()
{
    for (quint32 i = 0; i < SpellEffect::getRecordCount(); ++i)
        if (const SpellEffect::entry* effect = SpellEffect::getRecord(i))
            spellEffectHash[effect->effectSpellId][effect->effectIndex] = effect;
}

const SpellEffect::entry* Spell::entry::getEffect(quint8 index) const
{
    EffectMap effectMap = spellEffectHash[id];
    if (effectMap.contains(index))
        return effectMap[index];
    return nullptr;
}

quint8 Spell::entry::getEffectCount() const
{
    return spellEffectHash[id].size();
}

quint32 Spell::entry::getEffectId(quint8 index) const
{
    if (const SpellEffect::entry* effect = getEffect(index))
        return effect->effect;
    return 0;
}

float Spell::entry::getEffectValueMultiplier(quint8 index) const
{
    if (const SpellEffect::entry* effect = getEffect(index))
        return effect->effectValueMultiplier;
    return 0.0f;
}

quint32 Spell::entry::getEffectApplyAuraName(quint8 index) const
{
    if (const SpellEffect::entry* effect = getEffect(index))
        return effect->effectApplyAuraName;
    return 0;
}

quint32 Spell::entry::getEffectAmplitude(quint8 index) const
{
    if (const SpellEffect::entry* effect = getEffect(index))
        return effect->effectAmplitude;
    return 0;
}

qint32 Spell::entry::getEffectBasePoints(quint8 index) const
{
    if (const SpellEffect::entry* effect = getEffect(index))
        return effect->effectBasePoints;
    return 0;
}

float Spell::entry::getEffectBonusCoefficient(quint8 index) const
{
    if (const SpellEffect::entry* effect = getEffect(index))
        return effect->effectBonusCoefficient;
    return 0.0f;
}

float Spell::entry::getEffectDamageMultiplier(quint8 index) const
{
    if (const SpellEffect::entry* effect = getEffect(index))
        return effect->effectDamageMultiplier;
    return 0.0f;
}

quint32 Spell::entry::getEffectChainTarget(quint8 index) const
{
    if (const SpellEffect::entry* effect = getEffect(index))
        return effect->effectChainTarget;
    return 0;
}

qint32 Spell::entry::getEffectDieSides(quint8 index) const
{
    if (const SpellEffect::entry* effect = getEffect(index))
        return effect->effectDieSides;
    return 0;
}

quint32 Spell::entry::getEffectItemType(quint8 index) const
{
    if (const SpellEffect::entry* effect = getEffect(index))
        return effect->effectItemType;
    return 0;
}

quint32 Spell::entry::getEffectMechanic(quint8 index) const
{
    if (const SpellEffect::entry* effect = getEffect(index))
        return effect->effectMechanic;
    return 0;
}

qint32  Spell::entry::getEffectMiscValueA(quint8 index) const
{
    if (const SpellEffect::entry* effect = getEffect(index))
        return effect->effectMiscValueA;
    return 0;
}

qint32  Spell::entry::getEffectMiscValueB(quint8 index) const
{
    if (const SpellEffect::entry* effect = getEffect(index))
        return effect->effectMiscValueB;
    return 0;
}

float Spell::entry::getEffectPointsPerComboPoint(quint8 index) const
{
    if (const SpellEffect::entry* effect = getEffect(index))
        return effect->effectPointsPerComboPoint;
    return 0.0f;
}

quint32 Spell::entry::getEffectRadiusIndex(quint8 index) const
{
    if (const SpellEffect::entry* effect = getEffect(index))
        return effect->effectRadiusIndex;
    return 0;
}

quint32 Spell::entry::getEffectRadiusMaxIndex(quint8 index) const
{
    if (const SpellEffect::entry* effect = getEffect(index))
        return effect->effectRadiusMaxIndex;
    return 0;
}

float Spell::entry::getEffectRealPointsPerLevel(quint8 index) const
{
    if (const SpellEffect::entry* effect = getEffect(index))
        return effect->effectRealPointsPerLevel;
    return 0.0f;
}

quint32 Spell::entry::getEffectSpellClassMask(quint8 index, quint8 maskIndex) const
{
    if (const SpellEffect::entry* effect = getEffect(index))
        return effect->effectSpellClassMask[maskIndex];
    return 0;
}

quint32 Spell::entry::getEffectTriggerSpell(quint8 index) const
{
    if (const SpellEffect::entry* effect = getEffect(index))
        return effect->effectTriggerSpell;
    return 0;
}

quint32 Spell::entry::getEffectImplicitTargetA(quint8 index) const
{
    if (const SpellEffect::entry* effect = getEffect(index))
        return effect->effectImplicitTargetA;
    return 0;
}

quint32 Spell::entry::getEffectImplicitTargetB(quint8 index) const
{
    if (const SpellEffect::entry* effect = getEffect(index))
        return effect->effectImplicitTargetB;
    return 0;
}

#ifndef DEFINES_H
#define DEFINES_H

enum AttrType
{
    TYPE_ATTR,
    TYPE_ATTR_EX,
    TYPE_ATTR_EX2,
    TYPE_ATTR_EX3,
    TYPE_ATTR_EX4,
    TYPE_TARGETS,
    TYPE_CREATURE
};

enum StringConst
{
    POWER_TYPE_NAME     = 0,
    SPELLFAMILY_NAME    = 1
};

enum PowerType
{
    POWER_MANA          = 0,
    POWER_RAGE          = 1,
    POWER_FOCUS         = 2,
    POWER_ENERGY        = 3,
    POWER_HAPPINESS     = 4,
    POWER_RUNES         = 5,
    POWER_HEALTH        = 0xFFFFFFFE
};

enum SpellFamily
{
    SPELLFAMILY_GENERIC     = 0,
    SPELLFAMILY_MAGE        = 3,
    SPELLFAMILY_WARRIOR     = 4,
    SPELLFAMILY_WARLOCK     = 5,
    SPELLFAMILY_PRIEST      = 6,
    SPELLFAMILY_DRUID       = 7,
    SPELLFAMILY_ROGUE       = 8,
    SPELLFAMILY_HUNTER      = 9,
    SPELLFAMILY_PALADIN     = 10,
    SPELLFAMILY_SHAMAN      = 11,
    SPELLFAMILY_POTION      = 13,
    SPELLFAMILY_DEATHKNIGHT = 15
};

#define TOTAL_SPELL_EFFECTS 130

enum AbilytyLearnType
{
    ABILITY_LEARNED_ON_GET_PROFESSION_SKILL     = 1,
    ABILITY_LEARNED_ON_GET_RACE_OR_CLASS_SKILL  = 2
};

// SpellEntry::Targets
enum SpellCastTargetFlags
{
    TARGET_FLAG_SELF            = 0x00000000,
    TARGET_FLAG_UNUSED1         = 0x00000001,               // not used in any spells (can be set dynamically)
    TARGET_FLAG_UNIT            = 0x00000002,               // pguid
    TARGET_FLAG_UNUSED2         = 0x00000004,               // not used in any spells (can be set dynamically)
    TARGET_FLAG_UNUSED3         = 0x00000008,               // not used in any spells (can be set dynamically)
    TARGET_FLAG_ITEM            = 0x00000010,               // pguid
    TARGET_FLAG_SOURCE_LOCATION = 0x00000020,               // 3 float
    TARGET_FLAG_DEST_LOCATION   = 0x00000040,               // 3 float
    TARGET_FLAG_OBJECT_UNK      = 0x00000080,               // used in 7 spells only
    TARGET_FLAG_UNIT_UNK        = 0x00000100,               // looks like self target (389 spells)
    TARGET_FLAG_PVP_CORPSE      = 0x00000200,               // pguid
    TARGET_FLAG_UNIT_CORPSE     = 0x00000400,               // 10 spells (gathering professions)
    TARGET_FLAG_OBJECT          = 0x00000800,               // pguid, 0 spells
    TARGET_FLAG_TRADE_ITEM      = 0x00001000,               // pguid, 0 spells
    TARGET_FLAG_STRING          = 0x00002000,               // string, 0 spells
    TARGET_FLAG_UNK1            = 0x00004000,               // 199 spells, opening object/lock
    TARGET_FLAG_CORPSE          = 0x00008000,               // pguid, resurrection spells
    TARGET_FLAG_UNK2            = 0x00010000,               // pguid, not used in any spells (can be set dynamically)
};

enum SpellEffectIndex
{
    EFFECT_INDEX_0     = 0,
    EFFECT_INDEX_1     = 1,
    EFFECT_INDEX_2     = 2
};

#define MAX_EFFECT_INDEX 3


#endif
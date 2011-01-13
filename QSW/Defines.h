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
    TYPE_CREATURE,
    TYPE_FORMS,
    TYPE_FORMS_NOT,
    TYPE_ITEM_WEAPON,
    TYPE_ITEM_ARMOR,
    TYPE_ITEM_MISC,
    TYPE_ITEM_INVENTORY,
    TYPE_CR
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

#define TOTAL_SPELL_EFFECTS 130

enum SpellEffectIndex
{
    EFFECT_INDEX_0     = 0,
    EFFECT_INDEX_1     = 1,
    EFFECT_INDEX_2     = 2
};

#define MAX_EFFECT_INDEX 3

enum Threads
{
    THREAD_NONE,
    THREAD_SEARCH
};

enum Events
{
    EVENT_NONE,
    EVENT_SETMODEL
};


#endif
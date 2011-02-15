#ifndef DEFINES_H
#define DEFINES_H

enum AttrType
{
    TYPE_ATTR,
    TYPE_ATTR_EX,
    TYPE_ATTR_EX2,
    TYPE_ATTR_EX3,
    TYPE_ATTR_EX4,
    TYPE_ATTR_EX5,
    TYPE_ATTR_EX6,
    TYPE_ATTR_EXG,
    TYPE_TARGETS,
    TYPE_CREATURE,
    TYPE_FORMS,
    TYPE_FORMS_NOT,
    TYPE_ITEM_WEAPON,
    TYPE_ITEM_ARMOR,
    TYPE_ITEM_MISC,
    TYPE_ITEM_INVENTORY,
    TYPE_CR,
    TYPE_SCHOOL_MASK
};

enum SpellEffectIndex
{
    EFFECT_INDEX_0     = 0,
    EFFECT_INDEX_1     = 1,
    EFFECT_INDEX_2     = 2
};

#define MAX_EFFECT_INDEX 3

enum Threads
{
    THREAD_SEARCH,
    MAX_THREAD
};

#endif

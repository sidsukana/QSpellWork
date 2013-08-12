#ifndef SWDEFINES_H
#define SWDEFINES_H

#include <QtCore/QString>
#include <QtCore/QMetaType>

extern QString CLIENT_VERSION;
extern QString QSW_BUILD;
extern QString CLIENT_BUILD;

extern quint8  Locale;
extern QString ProcFlagDesc[];

#define MAX_PROC 32 
#define MAX_SPELL_REAGENTS 8
#define MAX_SPELL_TOTEMS 2
#define MAX_SPELL_TOTEM_CATEGORIES 2

#define arrayLength(a, b) sizeof(a) / sizeof(b)

enum AttrType
{
    TYPE_ATTR,
    TYPE_ATTR_EX1,
    TYPE_ATTR_EX2,
    TYPE_ATTR_EX3,
    TYPE_ATTR_EX4,
    TYPE_ATTR_EX5,
    TYPE_ATTR_EX6,
    TYPE_ATTR_EX7,
    TYPE_ATTR_EX8,
    TYPE_ATTR_EX9,
    TYPE_ATTR_EX10,
    TYPE_TARGETS,
    TYPE_CREATURE,
    TYPE_FORMS,
    TYPE_FORMS_NOT,
    TYPE_ITEM_WEAPON,
    TYPE_ITEM_ARMOR,
    TYPE_ITEM_MISC,
    TYPE_ITEM_INVENTORY,
    TYPE_CR,
    TYPE_SCHOOL_MASK,
    MAX_ATTR_TYPE
};

enum SpellEffectIndex
{
    EFFECT_INDEX_0     = 0,
    EFFECT_INDEX_1     = 1,
    EFFECT_INDEX_2     = 2,
    MAX_EFFECT_INDEX
};

#endif // SWDEFINES_H

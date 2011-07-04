#ifndef SWDEFINES_H
#define SWDEFINES_H

#include <QtCore/QString>
#include <QtCore/QMetaType>

extern quint8  Locale;
extern QString SpellStruct[];
extern QString ProcFlagDesc[];

#define MAX_STRUCT 91
#define MAX_PROC 32 
#define MAX_SPELL_REAGENTS 8
#define MAX_SPELL_TOTEMS 2

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
    TYPE_CR,
    MAX_ATTR_TYPE
};

enum SpellEffectIndex
{
    EFFECT_INDEX_0     = 0,
    EFFECT_INDEX_1     = 1,
    EFFECT_INDEX_2     = 2,
    MAX_EFFECT_INDEX
};

enum Threads
{
    THREAD_SEARCH,
    MAX_THREAD
};

// Addition structure types for Meta-System
struct uarray2
{
    quint32 value[2];
};

struct iarray2
{
    quint32 value[2];
};

struct farray2
{
    float value[2];
};

struct uarray3
{
    quint32 value[3];
};

struct iarray3
{
    quint32 value[3];
};

struct farray3
{
    float value[3];
};

struct uarray8
{
    quint32 value[8];
};

struct iarray8
{
    quint32 value[8];
};

struct farray8
{
    float value[8];
};

Q_DECLARE_METATYPE(uarray2);
Q_DECLARE_METATYPE(iarray2);
Q_DECLARE_METATYPE(farray2);
Q_DECLARE_METATYPE(uarray3);
Q_DECLARE_METATYPE(iarray3);
Q_DECLARE_METATYPE(farray3);
Q_DECLARE_METATYPE(uarray8);
Q_DECLARE_METATYPE(iarray8);
Q_DECLARE_METATYPE(farray8);

#endif // SWDEFINES_H
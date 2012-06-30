#ifndef SWDEFINES_H
#define SWDEFINES_H

#include <QtCore/QString>
#include <QtCore/QMetaType>

extern QString QSW_VERSION;
extern QString CLIENT_VERSION;
extern QString QSW_BUILD;
extern QString CLIENT_BUILD;

extern quint8  Locale;
extern QString SpellStruct[];
extern QString ProcFlagDesc[];

#define MAX_STRUCT 99
#define MAX_PROC 32 
#define MAX_SPELL_REAGENTS 8
#define MAX_SPELL_TOTEMS 2
#define MAX_SPELL_TOTEM_CATEGORIES 2

enum AttrType
{
    TYPE_ATTR,
    TYPE_ATTR_EX,
    TYPE_ATTR_EX2,
    TYPE_ATTR_EX3,
    TYPE_ATTR_EX4,
    TYPE_ATTR_EX5,
    TYPE_ATTR_EX6,
    TYPE_ATTR_EX7,
    TYPE_ATTR_EX8,
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

// Addition structure types for Meta-System
struct uarray2
{
    quint32 value[2];

    uarray2()
    {
        for (quint8 i = 0; i < 2; i++)
            value[i] = 0;
    }
};

struct iarray2
{
    qint32 value[2];

    iarray2()
    {
        for (quint8 i = 0; i < 2; i++)
            value[i] = 0;
    }
};

struct farray2
{
    float value[2];

    farray2()
    {
        for (quint8 i = 0; i < 2; i++)
            value[i] = 0;
    }
};

struct uarray3
{
    quint32 value[3];

    uarray3()
    {
        for (quint8 i = 0; i < 3; i++)
            value[i] = 0;
    }
};

struct iarray3
{
    qint32 value[3];

    iarray3()
    {
        for (quint8 i = 0; i < 3; i++)
            value[i] = 0;
    }
};

struct farray3
{
    float value[3];

    farray3()
    {
        for (quint8 i = 0; i < 3; i++)
            value[i] = 0;
    }
};

struct uarray8
{
    quint32 value[8];

    uarray8()
    {
        for (quint8 i = 0; i < 8; i++)
            value[i] = 0;
    }
};

struct iarray8
{
    qint32 value[8];

    iarray8()
    {
        for (quint8 i = 0; i < 8; i++)
            value[i] = 0;
    }
};

struct farray8
{
    float value[8];

    farray8()
    {
        for (quint8 i = 0; i < 8; i++)
            value[i] = 0;
    }
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

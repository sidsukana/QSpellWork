#include "SWDefines.h"

quint8 Locale = 0;

QString QSW_VERSION("2.1");
QString CLIENT_VERSION("2.4.3");
QString QSW_BUILD("41");
QString CLIENT_BUILD("8606");

QString SpellStruct[] =
{
    "None",
    "Id",
    "Category",
    "CastUI",
    "Dispel",
    "Mechanic",
    "Attributes",
    "AttributesEx",
    "AttributesEx2",
    "AttributesEx3",
    "AttributesEx4",
    "AttributesEx5",
    "AttributesEx6",
    "Stances",
    "StancesNot",
    "Targets",
    "TargetCreatureType",
    "RequiresSpellFocus",
    "FacingCasterFlags",
    "CasterAuraState",
    "TargetAuraState",
    "CasterAuraStateNot",
    "TargetAuraStateNot",
    "CastingTimeIndex",
    "RecoveryTime",
    "CategoryRecoveryTime",
    "InterruptFlags",
    "AuraInterruptFlags",
    "ChannelInterruptFlags",
    "ProcFlags",
    "ProcChance",
    "ProcCharges",
    "MaxLevel",
    "BaseLevel",
    "SpellLevel",
    "DurationIndex",
    "PowerType",
    "ManaCost",
    "ManaCostPerlevel",
    "ManaPerSecond",
    "ManaPerSecondPerLevel",
    "RangeIndex",
    "Speed",
    "ModalNextSpell",
    "StackAmount",
    "Totem",
    "Reagent",
    "ReagentCount",
    "EquippedItemClass",
    "EquippedItemSubClassMask",
    "EquippedItemInventoryTypeMask",
    "Effect",
    "EffectDieSides",
    "EffectBaseDice",
    "EffectDicePerLevel",
    "EffectRealPointsPerLevel",
    "EffectBasePoints",
    "EffectMechanic",
    "EffectImplicitTargetA",
    "EffectImplicitTargetB",
    "EffectRadiusIndex",
    "EffectApplyAuraName",
    "EffectAmplitude",
    "EffectMultipleValue",
    "EffectChainTarget",
    "EffectItemType",
    "EffectMiscValue",
    "EffectMiscValueB",
    "EffectTriggerSpell",
    "EffectPointsPerComboPoint",
    "SpellVisual",
    "SpellIconId",
    "ActiveIconId",
    "SpellPriority",
    "SpellName",
    "SpellNameFlag",
    "Rank",
    "RankFlags",
    "Description",
    "DescriptionFlags",
    "ToolTip",
    "ToolTipFlags",
    "ManaCostPercentage",
    "StartRecoveryCategory",
    "StartRecoveryTime",
    "MaxTargetLevel",
    "SpellFamilyName",
    "SpellFamilyFlags",
    "MaxAffectedTargets",
    "DamageClass",
    "PreventionType",
    "StanceBarOrder",
    "DamageMultiplier",
    "MinFactionId",
    "MinReputation",
    "RequiredAuraVision",
    "TotemCategory",
    "AreaId",
    "SchoolMask"
};

QString ProcFlagDesc[] =
{
    //00 0x00000001 000000000000000000000001 -
    "00 Killed by aggressor that receive experience or honor",
    //01 0x00000002 000000000000000000000010 -
    "01 Kill that yields experience or honor",
    //02 0x00000004 000000000000000000000100 -
    "02 Successful melee attack",
    //03 0x00000008 000000000000000000001000 -
    "03 Taken damage from melee strike hit",
    //04 0x00000010 000000000000000000010000 -
    "04 Successful attack by Spell that use melee weapon",
    //05 0x00000020 000000000000000000100000 -
    "05 Taken damage by Spell that use melee weapon",
    //06 0x00000040 000000000000000001000000 -
    "06 Successful Ranged attack(and wand spell cast)",
    //07 0x00000080 000000000000000010000000 -
    "07 Taken damage from ranged attack",
    //08 0x00000100 000000000000000100000000 -
    "08 Successful Ranged attack by Spell that use ranged weapon",
    //09 0x00000200 000000000000001000000000 -
    "09 Taken damage by Spell that use ranged weapon",
    //10 0x00000400 000000000000010000000000 -
    "10 Successful ??? spell hit",
    //11 0x00000800 000000000000100000000000 -
    "11 Taken ??? spell hit",
    //12 0x00001000 000000000001000000000000 -
    "12 Successful ??? spell cast",
    //13 0x00002000 000000000010000000000000 -
    "13 Taken ??? spell hit",
    //14 0x00004000 000000000100000000000000 -
    "14 Successful cast positive spell",
    //15 0x00008000 000000001000000000000000 -
    "15 Taken positive spell hit",
    //16 0x00010000 000000010000000000000000 -
    "16 Successful damage from harmful spell cast (каст дамажащего спелла)",
    //17 0x00020000 000000100000000000000000 -
    "17 Taken spell damage",
    //18 0x00040000 000001000000000000000000 -
    "18 Deal periodic damage",
    //19 0x00080000 000010000000000000000000 -
    "19 Taken periodic damage",
    //20 0x00100000 000100000000000000000000 -
    "20 Taken any damage",
    //21 0x00200000 001000000000000000000000 -
    "21 On trap activation (ѕри срабатывании ловушки)",
    //22 0x00800000 010000000000000000000000 -
    "22 Taken off-hand melee attacks",
    //23 0x00800000 100000000000000000000000 -
    "23 Successful off-hand melee attacks",
    "24",
    "25",
    "26",
    "27",
    "28",
    "29",
    "30",
    "31"
};

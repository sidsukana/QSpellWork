#ifndef QDEFINES_H
#define QDEFINES_H

#include <QtCore/QString>

QString SpellStruct[] =
{
    QString("None"),
    QString("Id"),
    QString("School"),
    QString("Category"),
    QString("CastUI"),
    QString("Dispel"),
    QString("Mechanic"),
    QString("Attributes"),
    QString("AttributesEx"),
    QString("AttributesEx2"),
    QString("AttributesEx3"),
    QString("AttributesEx4"),
    QString("Stances"),
    QString("StancesNot"),
    QString("Targets"),
    QString("TargetCreatureType"),
    QString("RequiresSpellFocus"),
    QString("CasterAuraState"),
    QString("TargetAuraState"),
    QString("CastingTimeIndex"),
    QString("RecoveryTime"),
    QString("CategoryRecoveryTime"),
    QString("InterruptFlags"),
    QString("AuraInterruptFlags"),
    QString("ChannelInterruptFlags"),
    QString("ProcFlags"),
    QString("ProcChance"),
    QString("ProcCharges"),
    QString("MaxLevel"),
    QString("BaseLevel"),
    QString("SpellLevel"),
    QString("DurationIndex"),
    QString("PowerType"),
    QString("ManaCost"),
    QString("ManaCostPerlevel"),
    QString("ManaPerSecond"),
    QString("ManaPerSecondPerLevel"),
    QString("RangeIndex"),
    QString("Speed"),
    QString("ModalNextSpell"),
    QString("StackAmount"),
    QString("Totem"),
    QString("Reagent"),
    QString("ReagentCount"),
    QString("EquippedItemClass"),
    QString("EquippedItemSubClassMask"),
    QString("EquippedItemInventoryTypeMask"),
    QString("Effect"),
    QString("EffectDieSides"),
    QString("EffectBaseDice"),
    QString("EffectDicePerLevel"),
    QString("EffectRealPointsPerLevel"),
    QString("EffectBasePoints"),
    QString("EffectMechanic"),
    QString("EffectImplicitTargetA"),
    QString("EffectImplicitTargetB"),
    QString("EffectRadiusIndex"),
    QString("EffectApplyAuraName"),
    QString("EffectAmplitude"),
    QString("EffectMultipleValue"),
    QString("EffectChainTarget"),
    QString("EffectItemType"),
    QString("EffectMiscValue"),
    QString("EffectTriggerSpell"),
    QString("EffectPointsPerComboPoint"),
    QString("SpellVisual"),
    QString("SpellVisual2"),
    QString("SpellIconID"),
    QString("ActiveIconID"),
    QString("SpellPriority"),
    QString("SpellName"),
    QString("SpellNameFlag"),
    QString("Rank"),
    QString("RankFlags"),
    QString("Description"),
    QString("DescriptionFlags"),
    QString("ToolTip"),
    QString("ToolTipFlags"),
    QString("ManaCostPercentage"),
    QString("StartRecoveryCategory"),
    QString("StartRecoveryTime"),
    QString("MaxTargetLevel"),
    QString("SpellFamilyName"),
    QString("SpellFamilyFlags"),
    QString("MaxAffectedTargets"),
    QString("DmgClass"),
    QString("PreventionType"),
    QString("StanceBarOrder"),
    QString("DmgMultiplier"),
    QString("MinFactionId"),
    QString("MinReputation"),
    QString("RequiredAuraVision")
};

QString ProcFlagDesc[] =
{
    //00 0x00000001 000000000000000000000001 -
    QString("00 Killed by aggressor that receive experience or honor"),
    //01 0x00000002 000000000000000000000010 -
    QString("01 Kill that yields experience or honor"),
    //02 0x00000004 000000000000000000000100 -
    QString("02 Successful melee attack"),
    //03 0x00000008 000000000000000000001000 -
    QString("03 Taken damage from melee strike hit"),
    //04 0x00000010 000000000000000000010000 -
    QString("04 Successful attack by Spell that use melee weapon"),
    //05 0x00000020 000000000000000000100000 -
    QString("05 Taken damage by Spell that use melee weapon"),
    //06 0x00000040 000000000000000001000000 -
    QString("06 Successful Ranged attack(and wand spell cast)"),
    //07 0x00000080 000000000000000010000000 -
    QString("07 Taken damage from ranged attack"),
    //08 0x00000100 000000000000000100000000 -
    QString("08 Successful Ranged attack by Spell that use ranged weapon"),
    //09 0x00000200 000000000000001000000000 -
    QString("09 Taken damage by Spell that use ranged weapon"),
    //10 0x00000400 000000000000010000000000 -
    QString("10 Successful ??? spell hit"),
    //11 0x00000800 000000000000100000000000 -
    QString("11 Taken ??? spell hit"),
    //12 0x00001000 000000000001000000000000 -
    QString("12 Successful ??? spell cast"),
    //13 0x00002000 000000000010000000000000 -
    QString("13 Taken ??? spell hit"),
    //14 0x00004000 000000000100000000000000 -
    QString("14 Successful cast positive spell"),
    //15 0x00008000 000000001000000000000000 -
    QString("15 Taken positive spell hit"),
    //16 0x00010000 000000010000000000000000 -
    QString("16 Successful damage from harmful spell cast (каст дамажащего спелла)"),
    //17 0x00020000 000000100000000000000000 -
    QString("17 Taken spell damage"),
    //18 0x00040000 000001000000000000000000 -
    QString("18 Deal periodic damage"),
    //19 0x00080000 000010000000000000000000 -
    QString("19 Taken periodic damage"),
    //20 0x00100000 000100000000000000000000 -
    QString("20 Taken any damage"),
    //21 0x00200000 001000000000000000000000 -
    QString("21 On trap activation (ѕри срабатывании ловушки)"),
    //22 0x00800000 010000000000000000000000 -
    QString("22 Taken off-hand melee attacks"),
    //23 0x00800000 100000000000000000000000 -
    QString("23 Successful off-hand melee attacks"),
    QString("24"),
    QString("25"),
    QString("26"),
    QString("27"),
    QString("28"),
    QString("29"),
    QString("30"),
    QString("31")
};

#endif
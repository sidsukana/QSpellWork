#include "DBCStores.h"
#include "DBCfmt.h"
#include "Define.h"

#include <QtCore/QFile>
#include <QtCore/QStringList>

SpellEffectMap sSpellEffectMap;

DBCStorage <SpellEffectEntry> sSpellEffectStore(SpellEffectEntryfmt);

DBCStorage <SpellAuraOptionsEntry> sSpellAuraOptionsStore(SpellAuraOptionsfmt);
DBCStorage <SpellAuraRestrictionsEntry> sSpellAuraRestrictionsStore(SpellAuraRestrictionsfmt);
DBCStorage <SpellCastingRequirementsEntry> sSpellCastingRequirementsStore(SpellCastingRequirementsfmt);
DBCStorage <SpellCategoriesEntry> sSpellCategoriesStore(SpellCategoriesfmt);
DBCStorage <SpellClassOptionsEntry> sSpellClassOptionsStore(SpellClassOptionsfmt);
DBCStorage <SpellCooldownsEntry> sSpellCooldownsStore(SpellCooldownsfmt);
DBCStorage <SpellEquippedItemsEntry> sSpellEquippedItemsStore(SpellEquippedItemsfmt);
DBCStorage <SpellInterruptsEntry> sSpellInterruptsStore(SpellInterruptsfmt);
DBCStorage <SpellLevelsEntry> sSpellLevelsStore(SpellLevelsfmt);
DBCStorage <SpellPowerEntry> sSpellPowerStore(SpellPowerfmt);
DBCStorage <SpellReagentsEntry> sSpellReagentsStore(SpellReagentsfmt);
DBCStorage <SpellScalingEntry> sSpellScalingStore(SpellScalingfmt);
DBCStorage <SpellShapeshiftEntry> sSpellShapeshiftStore(SpellShapeshiftfmt);
DBCStorage <SpellTargetRestrictionsEntry> sSpellTargetRestrictionsStore(SpellTargetRestrictionsfmt);
DBCStorage <SpellTotemsEntry> sSpellTotemsStore(SpellTotemsfmt);
DBCStorage <SpellMiscEntry> sSpellMiscStore(SpellMiscfmt);
DBCStorage <SkillLineEntry> sSkillLineStore(SkillLinefmt);
DBCStorage <SkillLineAbilityEntry> sSkillLineAbilityStore(SkillLineAbilityfmt);
DBCStorage <SpellEntry> sSpellStore(SpellEntryfmt);
DBCStorage <SpellCastTimesEntry> sSpellCastTimesStore(SpellCastTimefmt);
DBCStorage <SpellDurationEntry> sSpellDurationStore(SpellDurationfmt);
DBCStorage <SpellRadiusEntry> sSpellRadiusStore(SpellRadiusfmt);
DBCStorage <SpellRangeEntry> sSpellRangeStore(SpellRangefmt);
DBCStorage <SpellIconEntry> sSpellIconStore(SpellIconfmt);

typedef QStringList StoreProblemList;

static bool LoadDBC_assert_print(quint32 fsize, quint32 rsize, const QString filename)
{
    // ASSERT must fail after function call
    return false;
}

template<class T>
inline void LoadDBC(StoreProblemList& errlist, DBCStorage<T>& storage, const QString dbc_path, const QString filename)
{
    // Compatibility format and C++ structure sizes
    assert(DBCFileLoader::GetFormatRecordSize(storage.GetFormat()) == sizeof(T) || LoadDBC_assert_print(DBCFileLoader::GetFormatRecordSize(storage.GetFormat()), sizeof(T), filename));

    QString dbc_filename = dbc_path + filename;
    if (!storage.Load(dbc_filename))
    {
        // Sort problematic dbc to (1) non compatible and (2) nonexistent

        QFile file(dbc_filename);
        
        if (file.open(QIODevice::ReadOnly))
        {
            char buf[100];
            sprintf(buf, " (exist, but have %u fields instead %i) Wrong client version DBC file?", storage.GetFieldCount(), strlen(storage.GetFormat()));
            errlist.push_back(dbc_filename + QString(buf));
            file.close();
        }
        else
            errlist.push_back(dbc_filename);
    }
}

void LoadDBCStores()
{
    QString dbcPath("DBC/");

    StoreProblemList bad_dbc_files;

    LoadDBC(bad_dbc_files, sSkillLineStore,           dbcPath, "SkillLine.dbc");
    LoadDBC(bad_dbc_files, sSkillLineAbilityStore,    dbcPath, "SkillLineAbility.dbc");
    LoadDBC(bad_dbc_files, sSpellCastTimesStore,      dbcPath, "SpellCastTimes.dbc");
    LoadDBC(bad_dbc_files, sSpellDurationStore,       dbcPath, "SpellDuration.dbc");
    LoadDBC(bad_dbc_files, sSpellStore,               dbcPath, "Spell.dbc");
    LoadDBC(bad_dbc_files, sSpellRadiusStore,         dbcPath, "SpellRadius.dbc");
    LoadDBC(bad_dbc_files, sSpellRangeStore,          dbcPath, "SpellRange.dbc");
    LoadDBC(bad_dbc_files, sSpellIconStore,           dbcPath, "SpellIcon.dbc");
    LoadDBC(bad_dbc_files, sSpellAuraOptionsStore,    dbcPath, "SpellAuraOptions.dbc");
    LoadDBC(bad_dbc_files, sSpellAuraRestrictionsStore, dbcPath, "SpellAuraRestrictions.dbc");
    LoadDBC(bad_dbc_files, sSpellCastingRequirementsStore, dbcPath, "SpellCastingRequirements.dbc");
    LoadDBC(bad_dbc_files, sSpellCategoriesStore,     dbcPath, "SpellCategories.dbc");
    LoadDBC(bad_dbc_files, sSpellClassOptionsStore,   dbcPath, "SpellClassOptions.dbc");
    LoadDBC(bad_dbc_files, sSpellCooldownsStore,      dbcPath, "SpellCooldowns.dbc");
    LoadDBC(bad_dbc_files, sSpellEquippedItemsStore,  dbcPath, "SpellEquippedItems.dbc");
    LoadDBC(bad_dbc_files, sSpellInterruptsStore,     dbcPath, "SpellInterrupts.dbc");
    LoadDBC(bad_dbc_files, sSpellLevelsStore,         dbcPath, "SpellLevels.dbc");
    LoadDBC(bad_dbc_files, sSpellPowerStore,          dbcPath, "SpellPower.dbc");
    LoadDBC(bad_dbc_files, sSpellReagentsStore,       dbcPath, "SpellReagents.dbc");
    LoadDBC(bad_dbc_files, sSpellScalingStore,        dbcPath, "SpellScaling.dbc");
    LoadDBC(bad_dbc_files, sSpellShapeshiftStore,     dbcPath, "SpellShapeshift.dbc");
    LoadDBC(bad_dbc_files, sSpellTargetRestrictionsStore, dbcPath, "SpellTargetRestrictions.dbc");
    LoadDBC(bad_dbc_files, sSpellTotemsStore,         dbcPath, "SpellTotems.dbc");
    LoadDBC(bad_dbc_files, sSpellEffectStore,         dbcPath, "SpellEffect.dbc");
    LoadDBC(bad_dbc_files, sSpellMiscStore,           dbcPath, "SpellMisc.dbc");

    for(quint32 i = 1; i < sSpellEffectStore.GetNumRows(); ++i)
    {
        if(SpellEffectEntry const *spellEffect = sSpellEffectStore.LookupEntry(i))
            sSpellEffectMap[spellEffect->EffectSpellId].effects[spellEffect->EffectIndex] = spellEffect;
    }
}

SpellEffectEntry const* GetSpellEffectEntry(quint32 spellId, quint8 effect)
{
    SpellEffectMap::const_iterator itr = sSpellEffectMap.find(spellId);
    if(itr == sSpellEffectMap.end())
        return NULL;

    return itr->second.effects[effect];
}

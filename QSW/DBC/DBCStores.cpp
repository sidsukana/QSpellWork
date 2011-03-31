#include <stdio.h>
#include <string.h>
#include "DBCStores.h"
#include "DBCfmt.h"
#include "Includes/Policies/SingletonImp.h"
#include "Includes/Platform/Define.h"

DBCStorage <SkillLineEntry> sSkillLineStore(SkillLinefmt);
DBCStorage <SkillLineAbilityEntry> sSkillLineAbilityStore(SkillLineAbilityfmt);
DBCStorage <SpellEntry> sSpellStore(SpellEntryfmt);
DBCStorage <SpellCastTimesEntry> sSpellCastTimesStore(SpellCastTimefmt);
DBCStorage <SpellDurationEntry> sSpellDurationStore(SpellDurationfmt);
DBCStorage <SpellRadiusEntry> sSpellRadiusStore(SpellRadiusfmt);
DBCStorage <SpellRangeEntry> sSpellRangeStore(SpellRangefmt);

typedef std::list<std::string> StoreProblemList;

static bool LoadDBC_assert_print(quint32 fsize, quint32 rsize, const std::string& filename)
{
    // ASSERT must fail after function call
    return false;
}

template<class T>
inline void LoadDBC(quint32& availableDbcLocales, StoreProblemList& errlist, DBCStorage<T>& storage, const std::string& dbc_path, const std::string& filename)
{
    // compatibility format and C++ structure sizes
    assert(DBCFileLoader::GetFormatRecordSize(storage.GetFormat()) == sizeof(T) || LoadDBC_assert_print(DBCFileLoader::GetFormatRecordSize(storage.GetFormat()), sizeof(T), filename));

    std::string dbc_filename = dbc_path + filename;
    if (!storage.Load(dbc_filename.c_str()))
    {
        // sort problematic dbc to (1) non compatible and (2) nonexistent
        FILE *f = fopen(dbc_filename.c_str(), "rb");
        if (f)
        {
            char buf[100];
            sprintf(buf, " (exist, but have %d fields instead) Wrong client version DBC file?", storage.GetFieldCount(), strlen(storage.GetFormat()));
            errlist.push_back(dbc_filename + buf);
            fclose(f);
        }
        else
            errlist.push_back(dbc_filename);
    }
}

void LoadDBCStores()
{
    std::string dbcPath = "DBC/";

    StoreProblemList bad_dbc_files;

    // bitmask for index of fullLocaleNameList
    quint32 availableDbcLocales = 0xFFFFFFFF;

    LoadDBC(availableDbcLocales, bad_dbc_files, sSkillLineStore,           dbcPath, "SkillLine.dbc");
    LoadDBC(availableDbcLocales, bad_dbc_files, sSkillLineAbilityStore,    dbcPath, "SkillLineAbility.dbc");
    LoadDBC(availableDbcLocales, bad_dbc_files, sSpellStore,               dbcPath, "Spell.dbc");
    LoadDBC(availableDbcLocales, bad_dbc_files, sSpellCastTimesStore,      dbcPath, "SpellCastTimes.dbc");
    LoadDBC(availableDbcLocales, bad_dbc_files, sSpellDurationStore,       dbcPath, "SpellDuration.dbc");
    LoadDBC(availableDbcLocales, bad_dbc_files, sSpellRadiusStore,         dbcPath, "SpellRadius.dbc");
    LoadDBC(availableDbcLocales, bad_dbc_files, sSpellRangeStore,          dbcPath, "SpellRange.dbc");
}

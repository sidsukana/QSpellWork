#include "DBCStores.h"
#include "DBCfmt.h"
#include "Policies/SingletonImp.h"
#include "Platform/Define.h"

char const* localeNames[MAX_LOCALE] = {
  "enUS",                                                   // also enGB
  "koKR",
  "frFR",
  "deDE",
  "zhCN",
  "zhTW",
  "esES",
  "esMX",
};

// used for search by name or iterate all names
LocaleNameStr const fullLocaleNameList[] =
{
    { "enUS", LOCALE_enUS },
    { "enGB", LOCALE_enUS },
    { "koKR", LOCALE_koKR },
    { "frFR", LOCALE_frFR },
    { "deDE", LOCALE_deDE },
    { "zhCN", LOCALE_zhCN },
    { "zhTW", LOCALE_zhTW },
    { "esES", LOCALE_esES },
    { "esMX", LOCALE_esMX },
    { NULL,   LOCALE_enUS }
};

LocaleConstant GetLocaleByName(const std::string& name)
{
    for(LocaleNameStr const* itr = &fullLocaleNameList[0]; itr->name; ++itr)
        if (name==itr->name)
            return itr->locale;

    return LOCALE_enUS;                                     // including enGB case
}

DBCStorage <SkillLineEntry> sSkillLineStore(SkillLinefmt);
DBCStorage <SkillLineAbilityEntry> sSkillLineAbilityStore(SkillLineAbilityfmt);

DBCStorage <SpellEntry> sSpellStore(SpellEntryfmt);
SpellCategoryStore sSpellCategoryStore;

DBCStorage <SpellCastTimesEntry> sSpellCastTimesStore(SpellCastTimefmt);
DBCStorage <SpellDurationEntry> sSpellDurationStore(SpellDurationfmt);

DBCStorage <SpellRadiusEntry> sSpellRadiusStore(SpellRadiusfmt);
DBCStorage <SpellRangeEntry> sSpellRangeStore(SpellRangefmt);


typedef std::list<std::string> StoreProblemList;


static bool LoadDBC_assert_print(uint32 fsize,uint32 rsize, const std::string& filename)
{

    // ASSERT must fail after function call
    return false;
}

template<class T>
inline void LoadDBC(uint32& availableDbcLocales, StoreProblemList& errlist, DBCStorage<T>& storage, const std::string& dbc_path, const std::string& filename)
{
    // compatibility format and C++ structure sizes
    assert(DBCFileLoader::GetFormatRecordSize(storage.GetFormat()) == sizeof(T) || LoadDBC_assert_print(DBCFileLoader::GetFormatRecordSize(storage.GetFormat()),sizeof(T),filename));

    std::string dbc_filename = dbc_path + filename;
    if(storage.Load(dbc_filename.c_str()))
    {
        for(uint8 i = 0; fullLocaleNameList[i].name; ++i)
        {
            if(!(availableDbcLocales & (1 << i)))
                continue;

            std::string dbc_filename_loc = dbc_path + fullLocaleNameList[i].name + "/" + filename;
            if(!storage.LoadStringsFrom(dbc_filename_loc.c_str()))
                availableDbcLocales &= ~(1<<i);             // mark as not available for speedup next checks
        }
    }
    else
    {
        // sort problematic dbc to (1) non compatible and (2) nonexistent
        FILE * f=fopen(dbc_filename.c_str(),"rb");
        if(f)
        {
            char buf[100];
            sprintf(buf," (exist, but have %d fields instead " SIZEFMTD ") Wrong client version DBC file?",storage.GetFieldCount(),strlen(storage.GetFormat()));
            errlist.push_back(dbc_filename + buf);
            fclose(f);
        }
        else
            errlist.push_back(dbc_filename);
    }
}

bool LoadDBCStores()
{
    std::string dbcPath = "DBC/";


    StoreProblemList bad_dbc_files;

    // bitmask for index of fullLocaleNameList
    uint32 availableDbcLocales = 0xFFFFFFFF;

    LoadDBC(availableDbcLocales,bad_dbc_files,sSkillLineStore,           dbcPath,"SkillLine.dbc");
    LoadDBC(availableDbcLocales,bad_dbc_files,sSkillLineAbilityStore,    dbcPath,"SkillLineAbility.dbc");
    LoadDBC(availableDbcLocales,bad_dbc_files,sSpellStore,               dbcPath,"Spell.dbc");
    for(uint32 i = 1; i < sSpellStore.GetNumRows(); ++i)
    {
        SpellEntry const * spell = sSpellStore.LookupEntry(i);
        if(spell && spell->Category)
            sSpellCategoryStore[spell->Category].insert(i);
    }

    for (uint32 j = 0; j < sSkillLineAbilityStore.GetNumRows(); ++j)
    {
        SkillLineAbilityEntry const *skillLine = sSkillLineAbilityStore.LookupEntry(j);

        if(!skillLine)
            continue;

        SpellEntry const* spellInfo = sSpellStore.LookupEntry(skillLine->spellId);
    }

    LoadDBC(availableDbcLocales,bad_dbc_files,sSpellCastTimesStore,      dbcPath,"SpellCastTimes.dbc");
    LoadDBC(availableDbcLocales,bad_dbc_files,sSpellDurationStore,       dbcPath,"SpellDuration.dbc");
    LoadDBC(availableDbcLocales,bad_dbc_files,sSpellRadiusStore,         dbcPath,"SpellRadius.dbc");
    LoadDBC(availableDbcLocales,bad_dbc_files,sSpellRangeStore,          dbcPath,"SpellRange.dbc");

    return true;
}

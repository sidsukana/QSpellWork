#include "DBCStores.h"
#include "DBCfmt.h"
#include "Define.h"

#include <QtCore/QFile>
#include <QtCore/QStringList>

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
            sprintf(buf, " (exist, but have %d fields instead) Wrong client version DBC file?", storage.GetFieldCount(), storage.GetFormat().length());
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
    LoadDBC(bad_dbc_files, sSpellStore,               dbcPath, "Spell.dbc");
    LoadDBC(bad_dbc_files, sSpellCastTimesStore,      dbcPath, "SpellCastTimes.dbc");
    LoadDBC(bad_dbc_files, sSpellDurationStore,       dbcPath, "SpellDuration.dbc");
    LoadDBC(bad_dbc_files, sSpellRadiusStore,         dbcPath, "SpellRadius.dbc");
    LoadDBC(bad_dbc_files, sSpellRangeStore,          dbcPath, "SpellRange.dbc");
    LoadDBC(bad_dbc_files, sSpellIconStore,           dbcPath, "SpellIcon.dbc");
}

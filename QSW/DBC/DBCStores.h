#ifndef DBCSTORES_H
#define DBCSTORES_H
#include <cassert>
#include "DBCStore.h"
#include "DBCStructure.h"

extern DBCStorage <SkillLineEntry>               sSkillLineStore;
extern DBCStorage <SkillLineAbilityEntry>        sSkillLineAbilityStore;
extern DBCStorage <SpellCastTimesEntry>          sSpellCastTimesStore;
extern DBCStorage <SpellDurationEntry>           sSpellDurationStore;
extern DBCStorage <SpellRadiusEntry>             sSpellRadiusStore;
extern DBCStorage <SpellRangeEntry>              sSpellRangeStore;
extern DBCStorage <SpellIconEntry>               sSpellIconStore;
extern DBCStorage <SpellEntry>                   sSpellStore;

void LoadDBCStores();

#endif

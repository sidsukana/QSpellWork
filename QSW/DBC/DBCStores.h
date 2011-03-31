#ifndef DBCSTORES_H
#define DBCSTORES_H

#include <string>
#include <cassert>
#include <cstdio>
#include <stdio.h>
#include <map>
#include <list>

#include "DBCStore.h"
#include "DBCStructure.h"

extern DBCStorage <SkillLineEntry>               sSkillLineStore;
extern DBCStorage <SkillLineAbilityEntry>        sSkillLineAbilityStore;
extern DBCStorage <SpellCastTimesEntry>          sSpellCastTimesStore;
extern DBCStorage <SpellDurationEntry>           sSpellDurationStore;
extern DBCStorage <SpellRadiusEntry>             sSpellRadiusStore;
extern DBCStorage <SpellRangeEntry>              sSpellRangeStore;
extern DBCStorage <SpellEntry>                   sSpellStore;

void LoadDBCStores();

#endif

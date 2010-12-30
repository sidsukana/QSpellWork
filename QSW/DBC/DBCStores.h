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

#define SIZEFMTD ACE_SIZE_T_FORMAT_SPECIFIER

enum LocaleConstant
{
    LOCALE_enUS = 0,                                        // also enGB
    LOCALE_koKR = 1,
    LOCALE_frFR = 2,
    LOCALE_deDE = 3,
    LOCALE_zhCN = 4,
    LOCALE_zhTW = 5,
    LOCALE_esES = 6,
    LOCALE_esMX = 7,
};

#define MAX_LOCALE 8

LocaleConstant GetLocaleByName(const std::string& name);

extern char const* localeNames[MAX_LOCALE];

struct LocaleNameStr
{
    char const* name;
    LocaleConstant locale;
};

// used for iterate all names including alternative
extern LocaleNameStr const fullLocaleNameList[];


extern DBCStorage <SkillLineEntry>               sSkillLineStore;
extern DBCStorage <SkillLineAbilityEntry>        sSkillLineAbilityStore;
extern DBCStorage <SpellCastTimesEntry>          sSpellCastTimesStore;
extern DBCStorage <SpellDurationEntry>           sSpellDurationStore;
extern DBCStorage <SpellRadiusEntry>             sSpellRadiusStore;
extern DBCStorage <SpellRangeEntry>              sSpellRangeStore;
extern DBCStorage <SpellEntry>                   sSpellStore;


bool LoadDBCStores();

#endif

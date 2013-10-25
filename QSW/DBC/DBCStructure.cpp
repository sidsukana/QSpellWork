#include "SWDefines.h"
#include "DBC/DBCStructure.h"

SkillLine::entry SkillLine::getRecord(quint32 id, bool realId)
{
    DBCFile dbc = getDbc();
    entry e = realId ? dbc.getEntry<entry>(id) : dbc.getRecord<entry>(id);
    e.name[QSW::Locale] = dbc.getStringBlock() + quint32(e.name[QSW::Locale]);
    e.description[QSW::Locale] = dbc.getStringBlock() + quint32(e.description[QSW::Locale]);

    return e;
}

const DBCFileHeader* SkillLine::getHeader()
{ 
    return getDbc().getHeader();
}

const DBCFile SkillLine::getDbc()
{
    static DBCFile dbc("DBFilesClient/SkillLine.dbc");
    return dbc;
}

SkillLineAbility::entry SkillLineAbility::getRecord(quint32 id, bool realId)
{
    entry e = realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id);

    return e;
}

const DBCFileHeader* SkillLineAbility::getHeader()
{ 
    return getDbc().getHeader();
}

const DBCFile SkillLineAbility::getDbc()
{
    static DBCFile dbc("DBFilesClient/SkillLineAbility.dbc");
    return dbc;
}

Spell::entry Spell::getRecord(quint32 id, bool realId)
{
    DBCFile dbc = getDbc();
    entry e = realId ? dbc.getEntry<entry>(id) : dbc.getRecord<entry>(id);
    e.spellName[QSW::Locale] = dbc.getStringBlock() + quint32(e.spellName[QSW::Locale]);
    e.description[QSW::Locale] = dbc.getStringBlock() + quint32(e.description[QSW::Locale]);
    e.rank[QSW::Locale] = dbc.getStringBlock() + quint32(e.rank[QSW::Locale]);
    e.toolTip[QSW::Locale] = dbc.getStringBlock() + quint32(e.toolTip[QSW::Locale]);

    return e;
}

const DBCFileHeader* Spell::getHeader()
{
    return getDbc().getHeader();
}

const DBCFile Spell::getDbc()
{
    static DBCFile dbc("DBFilesClient/Spell.dbc");
    return dbc;
}

SpellCastTimes::entry SpellCastTimes::getRecord(quint32 id, bool realId)
{
    entry e = realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id);

    return e;
}

const DBCFileHeader* SpellCastTimes::getHeader()
{ 
    return getDbc().getHeader();
}

const DBCFile SpellCastTimes::getDbc()
{
    static DBCFile dbc("DBFilesClient/SpellCastTimes.dbc");
    return dbc;
}

SpellRadius::entry SpellRadius::getRecord(quint32 id, bool realId)
{
    entry e = realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id);

    return e;
}

const DBCFileHeader* SpellRadius::getHeader()
{ 
    return getDbc().getHeader();
}

const DBCFile SpellRadius::getDbc()
{
    static DBCFile dbc("DBFilesClient/SpellRadius.dbc");
    return dbc;
}

SpellRange::entry SpellRange::getRecord(quint32 id, bool realId)
{
    DBCFile dbc = getDbc();
    entry e = realId ? dbc.getEntry<entry>(id) : dbc.getRecord<entry>(id);
    e.name[QSW::Locale] = dbc.getStringBlock() + quint32(e.name[QSW::Locale]);
    e.shortName[QSW::Locale] = dbc.getStringBlock() + quint32(e.shortName[QSW::Locale]);

    return e;
}

const DBCFileHeader* SpellRange::getHeader()
{ 
    return getDbc().getHeader();
}

const DBCFile SpellRange::getDbc()
{
    static DBCFile dbc("DBFilesClient/SpellRange.dbc");
    return dbc;
}

SpellDuration::entry SpellDuration::getRecord(quint32 id, bool realId)
{
    entry e = realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id);

    return e;
}

const DBCFileHeader* SpellDuration::getHeader()
{ 
    return getDbc().getHeader();
}

const DBCFile SpellDuration::getDbc()
{
    static DBCFile dbc("DBFilesClient/SpellDuration.dbc");
    return dbc;
}

SpellIcon::entry SpellIcon::getRecord(quint32 id, bool realId)
{
    DBCFile dbc = getDbc();
    entry e = realId ? dbc.getEntry<entry>(id) : dbc.getRecord<entry>(id);
    e.iconPath = dbc.getStringBlock() + quint32(e.iconPath);

    return e;
}

const DBCFileHeader* SpellIcon::getHeader()
{ 
    return getDbc().getHeader();
}

const DBCFile SpellIcon::getDbc()
{
    static DBCFile dbc("DBFilesClient/SpellIcon.dbc");
    return dbc;
}
#include "structure.h"
#include "spellinfo.h"

// SkillLine.dbc
DBCFile& SkillLine::getDbc()
{
    static DBCFile dbc("SkillLine.dbc");
    return dbc;
}

quint32 SkillLine::getRecordCount()
{
    return getDbc().getRecordCount();
}

const SkillLine::entry* SkillLine::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

const QString SkillLine::entry::name() const
{
    return getDbc().getString(nameOffset[m_locale]);
}

const QString SkillLine::entry::description() const
{
    return getDbc().getString(descriptionOffset[m_locale]);
}

// SkillLineAbility.dbc
DBCFile& SkillLineAbility::getDbc()
{
    static DBCFile dbc("SkillLineAbility.dbc");
    return dbc;
}

quint32 SkillLineAbility::getRecordCount()
{
    return getDbc().getRecordCount();
}

const SkillLineAbility::entry* SkillLineAbility::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

// Spell.dbc
DBCFile& Spell::getDbc()
{
    static DBCFile dbc("Spell.dbc");
    return dbc;
}

quint32 Spell::getRecordCount()
{
    return getDbc().getRecordCount();
}

const Spell::entry* Spell::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

const QString Spell::entry::name() const
{
    return getDbc().getString(nameOffset[m_locale]);
}

const QString Spell::entry::description() const
{
    return getDbc().getString(descriptionOffset[m_locale]);
}

const QString Spell::entry::rank() const
{
    return getDbc().getString(rankOffset[m_locale]);
}

const QString Spell::entry::toolTip() const
{
    return getDbc().getString(toolTipOffset[m_locale]);
}

const QString Spell::entry::nameWithRank() const
{
    return (!rank().isEmpty() ? name() + " (" + rank() + ")" : name());
}

qint32 Spell::entry::getTriggerDuration(quint8 index) const
{
    const Spell::entry* triggerSpell = Spell::getRecord(effectTriggerSpell[index], true);
    if (triggerSpell)
        return triggerSpell->getDuration();

    return 0;
}

// SpellCastTimes.dbc
DBCFile& SpellCastTimes::getDbc()
{
    static DBCFile dbc("SpellCastTimes.dbc");
    return dbc;
}

quint32 SpellCastTimes::getRecordCount()
{
    return getDbc().getRecordCount();
}

const SpellCastTimes::entry* SpellCastTimes::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

// SpellRadius.dbc
DBCFile& SpellRadius::getDbc()
{
    static DBCFile dbc("SpellRadius.dbc");
    return dbc;
}

quint32 SpellRadius::getRecordCount()
{
    return getDbc().getRecordCount();
}

const SpellRadius::entry* SpellRadius::getRecord(quint32 id, bool realId)
{
   return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

// SpellRange.dbc
DBCFile& SpellRange::getDbc()
{
    static DBCFile dbc("SpellRange.dbc");
    return dbc;
}

quint32 SpellRange::getRecordCount()
{
    return getDbc().getRecordCount();
}

const SpellRange::entry* SpellRange::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

const QString SpellRange::entry::name() const
{
    return getDbc().getString(nameOffset[m_locale]);
}

const QString SpellRange::entry::shortName() const
{
    return getDbc().getString(shortNameOffset[m_locale]);
}

// SpellDuration.dbc
DBCFile &SpellDuration::getDbc()
{
    static DBCFile dbc("SpellDuration.dbc");
    return dbc;
}

quint32 SpellDuration::getRecordCount()
{
    return getDbc().getRecordCount();
}

const SpellDuration::entry* SpellDuration::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

// SpellIcon.dbc
DBCFile& SpellIcon::getDbc()
{
    static DBCFile dbc("SpellIcon.dbc");
    return dbc;
}

quint32 SpellIcon::getRecordCount()
{
    return getDbc().getRecordCount();
}

const SpellIcon::entry* SpellIcon::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

const QString SpellIcon::entry::iconPath() const
{
    return getDbc().getString(iconPathOffset);
}

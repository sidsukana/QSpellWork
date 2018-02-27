#include "spellinfo.h"
#include "structure.h"
#include <QBuffer>
#include <QSet>

EnumHash m_enums;
QStringList m_names;
QObjectList m_metaSpells;
Indexes m_metaSpellIndexes;
Indexes m_internalSpells;
QStringList m_modifiedStrings;

QMap<quint32, QString> procFlags = {
    { 0x00000001, "00 Killed by aggressor that receive experience or honor" },
    { 0x00000002, "01 Kill that yields experience or honor" },
    { 0x00000004, "02 Successful melee attack" },
    { 0x00000008, "03 Taken damage from melee strike hit" },
    { 0x00000010, "04 Successful attack by Spell that use melee weapon" },
    { 0x00000020, "05 Taken damage by Spell that use melee weapon" },
    { 0x00000040, "06 Successful Ranged attack (and wand spell cast)" },
    { 0x00000080, "07 Taken damage from ranged attack" },
    { 0x00000100, "08 Successful Ranged attack by Spell that use ranged weapon" },
    { 0x00000200, "09 Taken damage by Spell that use ranged weapon" },
    { 0x00000400, "10 Successful spell hit" },
    { 0x00000800, "11 Taken spell hit" },
    { 0x00001000, "12 Successful spell cast" },
    { 0x00002000, "13 Taken spell hit" },
    { 0x00004000, "14 Successful cast positive spell" },
    { 0x00008000, "15 Taken positive spell hit" },
    { 0x00010000, "16 Successful damage from harmful spell cast" },
    { 0x00020000, "17 Taken spell damage" },
    { 0x00040000, "18 Deal periodic damage" },
    { 0x00080000, "19 Taken periodic damage" },
    { 0x00100000, "20 Taken any damage" },
    { 0x00200000, "21 On trap activation" },
    { 0x00400000, "22 Taken off-hand melee attacks" },
    { 0x00800000, "23 Successful off-hand melee attacks" },
    { 0x01000000, "24 Unknown flag 24" }
};

bool SpellInfo::init() const
{
    if (!SkillLine::getDbc().load())
        return false;

    if (!SkillLineAbility::getDbc().load())
        return false;

    if (!SpellDuration::getDbc().load())
        return false;

    if (!SpellCastTimes::getDbc().load())
        return false;

    if (!SpellRadius::getDbc().load())
        return false;

    if (!SpellRange::getDbc().load())
        return false;

    if (!SpellIcon::getDbc().load())
        return false;

    if (!Spell::getDbc().load())
        return false;

    qDeleteAll(m_metaSpells);
    m_metaSpells.clear();
    QSet<QString> names;
    for (quint32 i = 0; i < Spell::getRecordCount(); ++i)
    {
        if (const Spell::entry* spellInfo = Spell::getRecord(i))
        {
            m_metaSpells << new Spell::meta(spellInfo);
            QString name = spellInfo->name();
            if (names.find(name) == names.end())
                names << name;
        }
    }

    m_metaSpellIndexes = Spell::getDbc().getIndexes();
    m_names = names.toList();
    m_modifiedStrings.clear();

    return true;
}

QStringList SpellInfo::getModifiedSqlDataQueries()
{
    return QStringList
    {
        QStringLiteral("SELECT * FROM spell_template ORDER BY 1")
    };
}

union UnionedValue
{
    quint64 value;
    struct
    {
        quint32 high;
        quint32 low;
    };
};

void SpellInfo::setModifiedSqlDataResult(quint8 queryIndex, QSqlQuery& query)
{
    Q_UNUSED(queryIndex)

    while (query.next())
    {
        Spell::entry* spell = new Spell::entry();
        quint32 id = query.value(0).toUInt();
        if (const Spell::entry* existSpell = Spell::getMetaRecord(id, true))
        {
            *spell = *existSpell;

            qint32 index = m_metaSpellIndexes.indexOf(id);
            Spell::meta* metaSpell = qobject_cast<Spell::meta*>(m_metaSpells.at(index));
            metaSpell->setSpellInfo(spell);
            m_metaSpells.replace(m_metaSpellIndexes.indexOf(id), metaSpell);
        }
        else
        {
            // add new index for meta spell
            m_metaSpellIndexes.append(id);
            m_internalSpells.append(id);
            m_metaSpells.append(new Spell::meta(spell, true));

            QString str = query.value(133).toString();
            qint32 index = m_modifiedStrings.indexOf(str);
            spell->nameOffset = index != -1 ? index : m_modifiedStrings.size();
            m_modifiedStrings.append(str);

            if (!m_names.contains(str))
                m_names.append(str);

            str = query.value(149).toString();
            index = m_modifiedStrings.indexOf(str);
            spell->rankOffset = m_modifiedStrings.size();
            m_modifiedStrings.append(str);

            // Unused members
            spell->descriptionOffset = 0;
            spell->toolTipOffset = 0;
            spell->modalNextSpell = 0;
            spell->stanceBarOrder = -1;
            spell->minFactionId = 0;
            spell->minReputation = 0;
            spell->requiredAuraVision = 0;
        }

        spell->id = id;
        spell->category = query.value(1).toUInt();
        spell->dispel = query.value(2).toUInt();
        spell->mechanic = query.value(3).toUInt();
        spell->attributes = query.value(4).toUInt();
        spell->attributesEx1 = query.value(5).toUInt();
        spell->attributesEx2 = query.value(6).toUInt();
        spell->attributesEx3 = query.value(7).toUInt();
        spell->attributesEx4 = query.value(8).toUInt();
        spell->attributesEx5 = query.value(9).toUInt();
        spell->attributesEx6 = query.value(10).toUInt();
        spell->attributesEx6 = query.value(11).toUInt();
        spell->stances = query.value(12).toUInt();
        spell->stancesNot = query.value(13).toUInt();
        spell->targets = query.value(14).toUInt();
        spell->targetCreatureType = query.value(15).toUInt();
        spell->requiresSpellFocus = query.value(16).toUInt();
        spell->facingCasterFlags = query.value(17).toUInt();
        spell->casterAuraState = query.value(18).toUInt();
        spell->targetAuraState = query.value(19).toUInt();
        spell->casterAuraStateNot = query.value(20).toUInt();
        spell->targetAuraStateNot = query.value(21).toUInt();
        spell->casterAuraSpell = query.value(22).toUInt();
        spell->targetAuraSpell = query.value(23).toUInt();
        spell->excludeCasterAuraSpell = query.value(24).toUInt();
        spell->excludeTargetAuraSpell = query.value(25).toUInt();
        spell->castingTimeIndex = query.value(26).toUInt();
        spell->recoveryTime = query.value(27).toUInt();
        spell->categoryRecoveryTime = query.value(28).toUInt();
        spell->interruptFlags = query.value(29).toUInt();
        spell->auraInterruptFlags = query.value(30).toUInt();
        spell->channelInterruptFlags = query.value(31).toUInt();
        spell->procFlags = query.value(32).toUInt();
        spell->procChance = query.value(33).toUInt();
        spell->procCharges = query.value(34).toUInt();
        spell->maxLevel = query.value(35).toUInt();
        spell->baseLevel = query.value(36).toUInt();
        spell->spellLevel = query.value(37).toUInt();
        spell->durationIndex = query.value(38).toUInt();
        spell->powerType = query.value(39).toInt();
        spell->manaCost = query.value(40).toUInt();
        spell->manaCostPerlevel = query.value(41).toUInt();
        spell->manaPerSecond = query.value(42).toUInt();
        spell->manaPerSecondPerLevel = query.value(43).toUInt();
        spell->rangeIndex = query.value(44).toUInt();
        spell->speed = query.value(45).toFloat();
        spell->stackAmount = query.value(46).toFloat();

        for (quint8 i = 0; i < MAX_SPELL_TOTEMS; ++i)
        {
            spell->totem[i] = query.value(47 + i).toUInt();
            spell->totemCategory[i] = query.value(178 + i).toUInt();
        }

        for (quint8 i = 0; i < MAX_SPELL_REAGENTS; ++i)
        {
            spell->reagent[i] = query.value(49 + i).toInt();
            spell->reagentCount[i] = query.value(57 + i).toUInt();
        }

        spell->equippedItemClass = query.value(65).toInt();
        spell->equippedItemSubClassMask = query.value(66).toInt();
        spell->equippedItemInventoryTypeMask = query.value(67).toInt();

        for (quint8 i = 0; i < MAX_EFFECT_INDEX; ++i)
        {
            spell->effect[i] = query.value(68 + i).toUInt();
            spell->effectDieSides[i] = query.value(71 + i).toUInt();
            spell->effectRealPointsPerLevel[i] = query.value(74 + i).toFloat();
            spell->effectBasePoints[i] = query.value(77 + i).toInt();
            spell->effectMechanic[i] = query.value(80 + i).toUInt();
            spell->effectImplicitTargetA[i] = query.value(83 + i).toUInt();
            spell->effectImplicitTargetB[i] = query.value(86 + i).toUInt();
            spell->effectRadiusIndex[i] = query.value(89 + i).toUInt();
            spell->effectApplyAuraName[i] = query.value(92 + i).toUInt();
            spell->effectAmplitude[i] = query.value(95 + i).toUInt();
            spell->effectMultipleValue[i] = query.value(98 + i).toFloat();
            spell->effectChainTarget[i] = query.value(101 + i).toUInt();
            spell->effectItemType[i] = query.value(104 + i).toUInt();
            spell->effectMiscValueA[i] = query.value(107 + i).toInt();
            spell->effectMiscValueB[i] = query.value(110 + i).toInt();
            spell->effectTriggerSpell[i] = query.value(113 + i).toUInt();
            spell->effectPointsPerComboPoint[i] = query.value(116 + i).toFloat();
            
            spell->effectSpellClassMaskA[i] = query.value(119 + i).toUInt();
            spell->effectSpellClassMaskB[i] = query.value(122 + i).toUInt();
            spell->effectSpellClassMaskC[i] = query.value(125 + i).toUInt();
            
            spell->damageMultiplier[i] = query.value(175 + i).toFloat();
        }

        spell->spellVisual = query.value(128).toUInt();
        spell->spellIconId = query.value(130).toUInt();
        spell->activeIconId = query.value(131).toUInt();
        spell->spellPriority = query.value(132).toUInt();
        spell->manaCostPercentage = query.value(165).toUInt();
        spell->startRecoveryCategory = query.value(166).toUInt();
        spell->startRecoveryTime = query.value(167).toUInt();
        spell->maxTargetLevel = query.value(168).toUInt();
        spell->spellFamilyName = query.value(169).toUInt();
        
        UnionedValue unionedValue;
        unionedValue.value = query.value(170).toLongLong();

        spell->spellFamilyFlags[0] = unionedValue.high;
        spell->spellFamilyFlags[1] = unionedValue.low;
        spell->spellFamilyFlags[2] = query.value(171).toUInt();
        
        spell->maxAffectedTargets = query.value(172).toUInt();
        spell->damageClass = query.value(173).toUInt();
        spell->preventionType = query.value(174).toUInt();
        
        spell->areaId = query.value(180).toUInt();
        spell->schoolMask = query.value(181).toUInt();
        spell->runeCostId = query.value(182).toUInt();
        spell->spellDifficultyId = query.value(183).toUInt();
    }
}

void SpellInfo::setEnums(EnumHash enums)
{
    m_enums = enums;
}

MPQList SpellInfo::getMPQFiles() const
{
    static MPQList MPQs = {
        MPQPair("%locale%/patch-%locale%-3.MPQ", {}),
        MPQPair("%locale%/patch-%locale%-2.MPQ", {}),
        MPQPair("%locale%/patch-%locale%.MPQ", {}),
        MPQPair("%locale%/locale-%locale%.MPQ", {})
    };
    return MPQs;
}

QObject* SpellInfo::getMetaSpell(quint32 id, bool realId) const
{
    return Spell::getMetaSpell(id, realId);
}

quint32 SpellInfo::getSpellsCount() const
{
    return Spell::getMetaSpellCount();
}

QObjectList SpellInfo::getMetaSpells() const
{
    return m_metaSpells;
}

EnumHash SpellInfo::getEnums() const
{
    return m_enums;
}

QStringList SpellInfo::getNames() const
{
    return m_names;
}

QImage getSpellIcon(quint32 iconId)
{
    const SpellIcon::entry* iconInfo = SpellIcon::getRecord(iconId, true);

    return (iconInfo ? BLP::getBLP(iconInfo->iconPath() + QString(".blp")) : QImage());
}

QString getSpellIconName(quint32 iconId)
{
    const SpellIcon::entry* iconInfo = SpellIcon::getRecord(iconId, true);

    if (!iconInfo)
        return QString();

    return QString(iconInfo->iconPath()).section('\\', -1).toLower();
}

QVariantList getParentSpells(quint32 triggerId)
{
    QVariantList parentSpells;
    for (quint32 i = 0; i < Spell::getMetaSpellCount(); ++i)
    {
        if (const Spell::entry* spellInfo = Spell::getMetaRecord(i))
        {
            QVariantHash parentSpell;
            for (quint8 eff = 0; eff < MAX_EFFECT_INDEX; ++eff)
            {
                if (spellInfo->effectTriggerSpell[eff] == triggerId)
                {
                    parentSpell["id"] = spellInfo->id;
                    parentSpell["name"] = spellInfo->nameWithRank();
                    parentSpells.append(parentSpell);
                    break;
                }
            }
        }
    }

    return parentSpells;
}

QString splitMask(quint32 mask, Enumerator enumerator)
{
    QString str("");

    EnumIterator itr(enumerator);
    while (itr.hasNext())
    {
        itr.next();
        if (mask & itr.key())
        {
            QString tstr(QString("%0, ").arg(itr.value()));
            str += tstr;
        }
    }
    if (!str.isEmpty())
        str.chop(2);
    return str;
}

QVariantList splitMaskToList(quint32 mask, Enumerator enumerator)
{
    QVariantList flags;
    EnumIterator itr(enumerator);
    while (itr.hasNext())
    {
        itr.next();
        if (mask & itr.key())
        {
            QVariantHash flag;
            flag["name"] = itr.value();
            flag["value"] = QString("0x" + QString("%0").arg(itr.key(), 8, 16, QChar('0')).toUpper());
            flags.append(flag);
        }
    }

    return flags;
}

void RegExpU(const Spell::entry* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getMetaRecord(rx.cap(4).toInt(), true))
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(tSpell->stackAmount));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(spellInfo->stackAmount));
    }
}

void RegExpH(const Spell::entry* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getMetaRecord(rx.cap(4).toInt(), true))
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(tSpell->procChance));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(spellInfo->procChance));
    }
}

void RegExpV(const Spell::entry* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getMetaRecord(rx.cap(4).toInt(), true))
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(tSpell->maxTargetLevel));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(spellInfo->maxTargetLevel));
    }
}

void RegExpQ(const Spell::entry* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(3).isEmpty())
    {
        if (!rx.cap(4).isEmpty())
        {
            if (const Spell::entry* tSpell = Spell::getMetaRecord(rx.cap(4).toInt(), true))
            {
                if (rx.cap(2) == QString("/"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(abs(qint32(tSpell->effectMiscValueA[rx.cap(6).toInt()-1] / rx.cap(3).toInt()))));
                }
                else if (rx.cap(2) == QString("*"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(abs(qint32(tSpell->effectMiscValueA[rx.cap(6).toInt()-1] * rx.cap(3).toInt()))));
                }
            }
        }
        else
        {
            if (rx.cap(2) == QString("/"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(abs(qint32(spellInfo->effectMiscValueA[rx.cap(6).toInt()-1] / rx.cap(3).toInt()))));
            }
            else if (rx.cap(2) == QString("*"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(abs(qint32(spellInfo->effectMiscValueA[rx.cap(6).toInt()-1] * rx.cap(3).toInt()))));
            }
        }
    }
    else if (!rx.cap(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getMetaRecord(rx.cap(4).toInt(), true))
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(abs(tSpell->effectMiscValueA[rx.cap(6).toInt()-1])));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(abs(spellInfo->effectMiscValueA[rx.cap(6).toInt()-1])));
    }
}

void RegExpI(const Spell::entry* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getMetaRecord(rx.cap(4).toInt(), true))
        {
            if (tSpell->maxAffectedTargets != 0)
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(tSpell->maxAffectedTargets));
            }
            else
            {
                str.replace(rx.cap(0), QString("nearby"));
            }
        }
    }
    else
    {
        if (spellInfo->maxAffectedTargets != 0)
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(spellInfo->maxAffectedTargets));
        }
        else
        {
            str.replace(rx.cap(0), QString("nearby"));
        }
    }
}

void RegExpB(const Spell::entry* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(3).isEmpty())
    {
        if (!rx.cap(4).isEmpty())
        {

            if (const Spell::entry* tSpell = Spell::getMetaRecord(rx.cap(4).toInt(), true))
            {
                if (rx.cap(2) == QString("/"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(abs(qint32((tSpell->effectPointsPerComboPoint[rx.cap(6).toInt()-1]) / rx.cap(3).toInt()))));
                }
                else if (rx.cap(2) == QString("*"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(abs(qint32((tSpell->effectPointsPerComboPoint[rx.cap(6).toInt()-1]) * rx.cap(3).toInt()))));
                }
            }
        }
        else
        {
            if (rx.cap(2) == QString("/"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(abs(qint32((spellInfo->effectPointsPerComboPoint[rx.cap(6).toInt()-1]) / rx.cap(3).toInt()))));
            }
            else if (rx.cap(2) == QString("*"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(abs(qint32((spellInfo->effectPointsPerComboPoint[rx.cap(6).toInt()-1]) * rx.cap(3).toInt()))));
            }
        }
    }
    else if (!rx.cap(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getMetaRecord(rx.cap(4).toInt(), true))
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(abs(qint32(tSpell->effectPointsPerComboPoint[rx.cap(6).toInt()-1]))));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(abs(qint32(spellInfo->effectPointsPerComboPoint[rx.cap(6).toInt()-1]))));
    }
}

void RegExpA(const Spell::entry* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(3).isEmpty())
    {
        if (!rx.cap(4).isEmpty())
        {
            if (const Spell::entry * tSpell = Spell::getMetaRecord(rx.cap(4).toInt(), true))
            {
                if (rx.cap(2) == QString("/"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(quint32(tSpell->getRadius(rx.cap(6).toInt()-1) / rx.cap(2).toInt())));
                }
                else if (rx.cap(2) == QString("*"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(quint32(tSpell->getRadius(rx.cap(6).toInt()-1) * rx.cap(2).toInt())));
                }
            }
        }
        else
        {
            if (rx.cap(2) == QString("/"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(quint32(spellInfo->getRadius(rx.cap(6).toInt()-1) / rx.cap(2).toInt())));
            }
            else if (rx.cap(2) == QString("*"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(quint32(spellInfo->getRadius(rx.cap(6).toInt()-1) * rx.cap(2).toInt())));
            }
        }
    }
    else if (!rx.cap(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getMetaRecord(rx.cap(4).toInt(), true))
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(tSpell->getRadius(rx.cap(6).toInt()-1)));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(spellInfo->getRadius(rx.cap(6).toInt()-1)));
    }
}

void RegExpD(const Spell::entry* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(3).isEmpty())
    {
        if (!rx.cap(4).isEmpty())
        {
            if (const Spell::entry* tSpell = Spell::getMetaRecord(rx.cap(4).toInt(), true))
            {
                if (rx.cap(2) == QString("/"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(quint32(tSpell->getDuration() / rx.cap(3).toInt())));
                }
                else if (rx.cap(2) == QString("*"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(quint32(tSpell->getDuration() * rx.cap(3).toInt())));
                }
            }
        }
        else
        {
            if (rx.cap(2) == QString("/"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(quint32(spellInfo->getDuration() / rx.cap(3).toInt())));
            }
            else if (rx.cap(2) == QString("*"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(quint32(spellInfo->getDuration() * rx.cap(3).toInt())));
            }
        }
    }
    else if (!rx.cap(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getMetaRecord(rx.cap(4).toInt(), true))
        {
            str.replace(rx.cap(0), QString("%0 seconds")
                .arg(tSpell->getDuration()));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0 seconds")
            .arg(spellInfo->getDuration()));
    }
}

void RegExpO(const Spell::entry* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(3).isEmpty())
    {
        if (!rx.cap(4).isEmpty())
        {
            if (const Spell::entry* tSpell = Spell::getMetaRecord(rx.cap(4).toInt(), true))
            {
                if (rx.cap(2) == QString("/"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(quint32((tSpell->getTicks(rx.cap(6).toInt()-1) * (tSpell->effectBasePoints[rx.cap(6).toInt()-1] + 1)) / rx.cap(3).toInt())));
                }
                else if(rx.cap(2) == QString("*"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(quint32((tSpell->getTicks(rx.cap(6).toInt()-1) * (tSpell->effectBasePoints[rx.cap(6).toInt()-1] + 1)) * rx.cap(3).toInt())));
                }
            }
        }
        else
        {
            if (rx.cap(2) == QString("/"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(quint32((spellInfo->getTicks(rx.cap(6).toInt()-1) * (spellInfo->effectBasePoints[rx.cap(6).toInt()-1] + 1)) / rx.cap(3).toInt())));
            }
            else if (rx.cap(2) == QString("*"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(quint32((spellInfo->getTicks(rx.cap(6).toInt()-1) * (spellInfo->effectBasePoints[rx.cap(6).toInt()-1] + 1)) * rx.cap(3).toInt())));
            }
        }
    }
    else if (!rx.cap(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getMetaRecord(rx.cap(4).toInt(), true))
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(tSpell->getTicks(rx.cap(6).toInt()-1) * (tSpell->effectBasePoints[rx.cap(6).toInt()-1] + 1)));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(spellInfo->getTicks(rx.cap(6).toInt()-1) * (spellInfo->effectBasePoints[rx.cap(6).toInt()-1] + 1)));
    }
}

void RegExpS(const Spell::entry* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(3).isEmpty())
    {
        if (!rx.cap(4).isEmpty())
        {
            if (const Spell::entry* tSpell = Spell::getMetaRecord(rx.cap(4).toInt(), true))
            {
                if (rx.cap(2) == QString("/"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(abs(qint32((tSpell->effectBasePoints[rx.cap(6).toInt()-1] + 1) / rx.cap(3).toInt()))));
                }
                else if (rx.cap(2) == QString("*"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(abs(qint32((tSpell->effectBasePoints[rx.cap(6).toInt()-1] + 1) * rx.cap(3).toInt()))));
                }
            }
        }
        else
        {
            if (rx.cap(2) == QString("/"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(abs(qint32((spellInfo->effectBasePoints[rx.cap(6).toInt()-1] + 1) / rx.cap(3).toInt()))));
            }
            else if (rx.cap(2) == QString("*"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(abs(qint32((spellInfo->effectBasePoints[rx.cap(6).toInt()-1] + 1) * rx.cap(3).toInt()))));
            }
        }
    }
    else if (!rx.cap(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getMetaRecord(rx.cap(4).toInt(), true))
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(abs(tSpell->effectBasePoints[rx.cap(6).toInt()-1] + 1)));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(abs(spellInfo->effectBasePoints[rx.cap(6).toInt()-1] + 1)));
    }
}

void RegExpT(const Spell::entry* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(3).isEmpty())
    {
        if (!rx.cap(4).isEmpty())
        {
            if (const Spell::entry* tSpell = Spell::getMetaRecord(rx.cap(4).toInt(), true))
            {
                if (rx.cap(2) == QString("/"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(quint32(tSpell->getAmplitude(rx.cap(6).toInt()-1) / rx.cap(3).toInt())));
                }
                else if (rx.cap(2) == QString("*"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(quint32(tSpell->getAmplitude(rx.cap(6).toInt()-1) * rx.cap(3).toInt())));
                }
            }
        }
        else
        {
            if (rx.cap(2) == QString("/"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(quint32(spellInfo->getAmplitude(rx.cap(6).toInt()-1) / rx.cap(3).toInt())));
            }
            else if (rx.cap(2) == QString("*"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(quint32(spellInfo->getAmplitude(rx.cap(6).toInt()-1) * rx.cap(3).toInt())));
            }
        }
    }
    else if (!rx.cap(4).isEmpty())
    {

        if (const Spell::entry* tSpell = Spell::getMetaRecord(rx.cap(4).toInt(), true))
        {
            if (tSpell->effectAmplitude[rx.cap(6).toInt()-1])
                str.replace(rx.cap(0), QString("%0").arg(tSpell->getAmplitude(rx.cap(6).toInt()-1)));
            else
                str.replace(rx.cap(0), QString("%0").arg(tSpell->getAmplitude()));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(quint32(spellInfo->effectAmplitude[rx.cap(6).toInt()-1] / 1000)));
    }
}

void RegExpN(const Spell::entry* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getMetaRecord(rx.cap(4).toInt(), true))
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(tSpell->procCharges));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(spellInfo->procCharges));
    }
}

void RegExpX(const Spell::entry* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getMetaRecord(rx.cap(4).toInt(), true))
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(tSpell->effectChainTarget[rx.cap(6).toInt()-1]));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(spellInfo->effectChainTarget[rx.cap(6).toInt()-1]));
    }
}

void RegExpE(const Spell::entry* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getMetaRecord(rx.cap(4).toInt(), true))
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(tSpell->effectMultipleValue[rx.cap(6).toInt()-1], 0, 'f', 2));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(spellInfo->effectMultipleValue[rx.cap(6).toInt()-1], 0, 'f', 2));
    }
}

QString getDescription(QString str, const Spell::entry* spellInfo)
{
    QRegExp rx("\\$+(([/,*])?([0-9]*);)?([d+\\;)(\\d*)?([1-9]*)([A-z])([1-3]*)(([A-z, ]*)\\:([A-z, ]*)\\;)?");
    while (str.contains(rx))
    {
        if (rx.indexIn(str) != -1)
        {
            QChar symbol = rx.cap(5)[0].toLower();
            switch (symbol.toLatin1())
            {
                case 'u': RegExpU(spellInfo, rx, str); break;
                case 'h': RegExpH(spellInfo, rx, str); break;
                case 'v': RegExpV(spellInfo, rx, str); break;
                case 'q': RegExpQ(spellInfo, rx, str); break;
                case 'i': RegExpI(spellInfo, rx, str); break;
                case 'b': RegExpB(spellInfo, rx, str); break;
                case 'm':
                case 's':
                    RegExpS(spellInfo, rx, str);
                    break;
                case 'a': RegExpA(spellInfo, rx, str); break;
                case 'd': RegExpD(spellInfo, rx, str); break;
                case 'o': RegExpO(spellInfo, rx, str); break;
                case 't': RegExpT(spellInfo, rx, str); break;
                case 'n': RegExpN(spellInfo, rx, str); break;
                case 'x': RegExpX(spellInfo, rx, str); break;
                case 'e': RegExpE(spellInfo, rx, str); break;
                case 'l': str.replace(rx.cap(0), rx.cap(9)); break;
                case 'g': str.replace(rx.cap(0), rx.cap(8)); break;
                case 'z': str.replace(rx.cap(0), QString("[Home]")); break;
                default: return str;
            }
        }
    }
    return str;
}

QVariantHash SpellInfo::getValues(quint32 id) const
{
    QVariantHash values;

    const Spell::entry* spellInfo = Spell::getMetaRecord(id, true);
    if (!spellInfo)
        return values;

    QByteArray iconData;
    QBuffer buffer(&iconData);
    getSpellIcon(spellInfo->spellIconId).save(&buffer, "PNG");

    // Try load from Wowhead
    if (iconData.isEmpty())
    {
        values["icon"] = QString("http://wow.zamimg.com/images/wow/icons/large/%0.jpg").arg(getSpellIconName(spellInfo->spellIconId));
    }
    else
    {
        values["icon"] = QStringLiteral("data:image/png;base64,") + iconData.toBase64().data();
    }

    values["id"] = spellInfo->id;
    values["name"] = spellInfo->name();
    values["rank"] = spellInfo->rank();
    values["nameWithRank"] = spellInfo->nameWithRank();
    values["description"] = spellInfo->description();
    values["descriptionRegExp"] = getDescription(spellInfo->description(), spellInfo);
    values["tooltip"] = spellInfo->toolTip();
    values["tooltipRegExp"] = getDescription(spellInfo->toolTip(), spellInfo);

    QVariantList parentSpells = getParentSpells(spellInfo->id);
    if (!parentSpells.isEmpty())
    {
        values["hasParents"] = !parentSpells.isEmpty();
        values["parentSpells"] = parentSpells;
    }

    values["modalNextSpell"] = spellInfo->modalNextSpell;
    values["categoryId"] = spellInfo->category;
    values["spellIconId"] = spellInfo->spellIconId;
    values["activeIconId"] = spellInfo->activeIconId;
    values["spellVisual"] = spellInfo->spellVisual;

    values["spellFamilyId"] = spellInfo->spellFamilyName;
    values["spellFamilyName"] = getEnums()["SpellFamily"][spellInfo->spellFamilyName];

    values["spellFamilyFlags1"] = QString(QString("%0").arg(spellInfo->spellFamilyFlags[0], 8, 16, QChar('0')).toUpper());
    values["spellFamilyFlags2"] = QString(QString("%0").arg(spellInfo->spellFamilyFlags[1], 8, 16, QChar('0')).toUpper());
    values["spellFamilyFlags3"] = QString(QString("%0").arg(spellInfo->spellFamilyFlags[2], 8, 16, QChar('0')).toUpper());

    values["spellSchoolMask"] = spellInfo->schoolMask;
    values["spellSchoolMaskNames"] = splitMask(spellInfo->schoolMask, getEnums()["SchoolMask"]);

    values["damageClassId"] = spellInfo->damageClass;
    values["damageClassName"] = getEnums()["DamageClass"][spellInfo->damageClass];

    values["preventionTypeId"] = spellInfo->preventionType;
    values["preventionTypeName"] = getEnums()["PreventionType"][spellInfo->preventionType];

    if (spellInfo->attributes || spellInfo->attributesEx1 || spellInfo->attributesEx2 ||
        spellInfo->attributesEx3 || spellInfo->attributesEx4 || spellInfo->attributesEx5 ||
        spellInfo->attributesEx6 || spellInfo->attributesEx7)
    {
        values["hasAttributes"] = true;

        if (spellInfo->attributes)
        {
            values["attr"] = QString("0x" + QString("%0").arg(spellInfo->attributes, 8, 16, QChar('0')).toUpper());
            values["attrNames"] = splitMaskToList(spellInfo->attributes, getEnums()["Attributes"]);
        }

        if (spellInfo->attributesEx1)
        {
            values["attrEx1"] = QString("0x" + QString("%0").arg(spellInfo->attributesEx1, 8, 16, QChar('0')).toUpper());
            values["attrEx1Names"] = splitMaskToList(spellInfo->attributesEx1, getEnums()["AttributesEx1"]);
        }

        if (spellInfo->attributesEx2)
        {
            values["attrEx2"] = QString("0x" + QString("%0").arg(spellInfo->attributesEx2, 8, 16, QChar('0')).toUpper());
            values["attrEx2Names"] = splitMaskToList(spellInfo->attributesEx2, getEnums()["AttributesEx2"]);
        }

        if (spellInfo->attributesEx3)
        {
            values["attrEx3"] = QString("0x" + QString("%0").arg(spellInfo->attributesEx3, 8, 16, QChar('0')).toUpper());
            values["attrEx3Names"] = splitMaskToList(spellInfo->attributesEx3, getEnums()["AttributesEx3"]);
        }

        if (spellInfo->attributesEx4)
        {
            values["attrEx4"] = QString("0x" + QString("%0").arg(spellInfo->attributesEx4, 8, 16, QChar('0')).toUpper());
            values["attrEx4Names"] = splitMaskToList(spellInfo->attributesEx4, getEnums()["AttributesEx4"]);
        }

        if (spellInfo->attributesEx5)
        {
            values["attrEx5"] = QString("0x" + QString("%0").arg(spellInfo->attributesEx5, 8, 16, QChar('0')).toUpper());
            values["attrEx5Names"] = splitMaskToList(spellInfo->attributesEx5, getEnums()["AttributesEx5"]);
        }

        if (spellInfo->attributesEx6)
        {
            values["attrEx6"] = QString("0x" + QString("%0").arg(spellInfo->attributesEx6, 8, 16, QChar('0')).toUpper());
            values["attrEx6Names"] = splitMaskToList(spellInfo->attributesEx6, getEnums()["AttributesEx6"]);
        }

        if (spellInfo->attributesEx7)
        {
            values["attrEx7"] = QString("0x" + QString("%0").arg(spellInfo->attributesEx7, 8, 16, QChar('0')).toUpper());
            values["attrEx7Names"] = splitMaskToList(spellInfo->attributesEx7, getEnums()["AttributesEx7"]);
        }
    }

    if (spellInfo->targets)
    {
        values["targets"] = QString("0x" + QString("%0").arg(spellInfo->targets, 8, 16, QChar('0')).toUpper());
        values["targetsNames"] = splitMask(spellInfo->targets, getEnums()["TargetFlag"]);
    }

    if (spellInfo->targetCreatureType)
    {
        values["creatureType"] = QString("0x" + QString("%0").arg(spellInfo->targetCreatureType, 8, 16, QChar('0')).toUpper());
        values["creatureTypeNames"] = splitMask(spellInfo->targetCreatureType, getEnums()["CreatureType"]);
    }

    if (spellInfo->stances)
    {
        values["stances"] = QString("0x" + QString("%0").arg(spellInfo->stances, 16, 16, QChar('0')).toUpper());
        values["stancesNames"] = splitMask(spellInfo->stances, getEnums()["ShapeshiftForm"]);
    }

    if (spellInfo->stancesNot)
    {
        values["stancesNot"] = QString("0x" + QString("%0").arg(spellInfo->stancesNot, 16, 16, QChar('0')).toUpper());
        values["stancesNotNames"] = splitMask(spellInfo->stancesNot, getEnums()["ShapeshiftForm"]);
    }

    for (quint32 i = 0; i < SkillLineAbility::getRecordCount(); ++i)
    {
        const SkillLineAbility::entry* skillInfo = SkillLineAbility::getRecord(i);
        if (skillInfo->id && skillInfo->spellId == spellInfo->id)
        {
            if (const SkillLine::entry* skill = SkillLine::getRecord(skillInfo->skillId, true))
            {
                values["skillId"] = skill->id;
                values["skillName"] = skill->name();
                values["reqSkillValue"] = skillInfo->requiredSkillValue;
                values["forwardSpellId"] = skillInfo->forwardSpellId;
                values["minSkillValue"] = skillInfo->minValue;
                values["maxSkillValue"] = skillInfo->maxValue;
                values["charPoints1"] = skillInfo->charPoints[0];
                values["charPoints2"] = skillInfo->charPoints[1];
            }
            break;
        }
    }

    values["spellLevel"] = spellInfo->spellLevel;
    values["baseLevel"] = spellInfo->baseLevel;
    values["maxLevel"] = spellInfo->maxLevel;
    values["maxTargetLevel"] = spellInfo->maxTargetLevel;

    if (spellInfo->equippedItemClass != -1)
    {
        values["equipItemClass"] = spellInfo->equippedItemClass;
        values["equipItemClassName"] = getEnums()["ItemClass"][spellInfo->equippedItemClass];

        if (spellInfo->equippedItemSubClassMask)
        {
            values["equipItemSubClassMask"] = QString("0x" + QString("%0").arg(spellInfo->equippedItemSubClassMask, 8, 16, QChar('0')).toUpper());

            switch (spellInfo->equippedItemClass)
            {
                case 2: // WEAPON
                    values["equipItemSubClassMaskNames"] = splitMask(spellInfo->equippedItemSubClassMask, getEnums()["ItemSubClassWeapon"]);
                    break;
                case 4: // ARMOR
                    values["equipItemSubClassMaskNames"] = splitMask(spellInfo->equippedItemSubClassMask, getEnums()["ItemSubClassArmor"]);
                    break;
                case 15: // MISC
                    values["equipItemSubClassMaskNames"] = splitMask(spellInfo->equippedItemSubClassMask, getEnums()["ItemSubClassMisc"]);
                    break;
                default: break;
            }
        }

        if (spellInfo->equippedItemInventoryTypeMask)
        {
            values["equipItemInvTypeMask"] = QString("0x" + QString("%0").arg(spellInfo->equippedItemInventoryTypeMask, 8, 16, QChar('0')).toUpper());
            values["equipItemInvTypeMaskNames"] = splitMask(spellInfo->equippedItemInventoryTypeMask, getEnums()["InventoryType"]);
        }
    }

    values["categoryId"] = spellInfo->category;
    values["dispelId"] = spellInfo->dispel;
    values["dispelName"] = getEnums()["DispelType"][spellInfo->dispel];
    values["mechanicId"] = spellInfo->mechanic;
    values["mechanicName"] = getEnums()["Mechanic"][spellInfo->mechanic];

    if (const SpellRange::entry* range = SpellRange::getRecord(spellInfo->rangeIndex, true))
    {
        values["rangeId"] = range->id;
        values["rangeName"] = range->name();
        values["minRange"] = range->minRange;
        values["maxRange"] = range->maxRange;
    }

    if (spellInfo->speed)
        values["speed"] = QString("%0").arg(spellInfo->speed, 0, 'f', 2);

    values["stackAmount"] = spellInfo->stackAmount;

    if (const SpellCastTimes::entry* castInfo = SpellCastTimes::getRecord(spellInfo->castingTimeIndex, true))
    {
        values["castTimeId"] = castInfo->id;
        values["castTimeValue"] = QString("%0").arg(float(castInfo->castTime) / 1000, 0, 'f', 2);
    }

    values["recoveryInfo"] = spellInfo->recoveryTime || spellInfo->categoryRecoveryTime || spellInfo->startRecoveryCategory;

    values["recoveryTime"] = spellInfo->recoveryTime;
    values["categoryRecoveryTime"] = spellInfo->categoryRecoveryTime;

    values["startRecoveryCategory"] = spellInfo->startRecoveryCategory;
    values["startRecoveryTime"] = QString("%0").arg(float(spellInfo->startRecoveryTime), 0, 'f', 2);

    if (const SpellDuration::entry* durationInfo = SpellDuration::getRecord(spellInfo->durationIndex, true))
    {
        values["durationId"] = durationInfo->id;
        values["durationBase"] = durationInfo->duration;
        values["durationPerLevel"] = durationInfo->durationPerLevel;
        values["durationMax"] = durationInfo->maxDuration;
    }

    values["costInfo"] = spellInfo->manaCost || spellInfo->manaCostPercentage;
    values["powerTypeId"] = spellInfo->powerType;
    values["powerTypeName"] = getEnums()["Power"][spellInfo->powerType];
    values["manaCost"] = spellInfo->manaCost;
    values["manaCostPercentage"] = spellInfo->manaCostPercentage;
    values["manaCostPerLevel"] = spellInfo->manaCostPerlevel;
    values["manaPerSecond"] = spellInfo->manaPerSecond;
    values["manaPerSecondPerLevel"] =spellInfo->manaPerSecondPerLevel;

    if (spellInfo->interruptFlags)
    {
        values["interruptFlags"] = QString("0x" + QString("%0").arg(spellInfo->interruptFlags, 8, 16, QChar('0')).toUpper());
        values["interruptFlagsNames"] = splitMaskToList(spellInfo->interruptFlags, getEnums()["SpellInterruptFlags"]);
    }

    if (spellInfo->auraInterruptFlags)
    {
        values["auraInterruptFlags"] = QString("0x" + QString("%0").arg(spellInfo->auraInterruptFlags, 8, 16, QChar('0')).toUpper());
        values["auraInterruptFlagsNames"] = splitMaskToList(spellInfo->auraInterruptFlags, getEnums()["SpellAuraInterruptFlags"]);
    }

    if (spellInfo->channelInterruptFlags)
    {
        values["channelInterruptFlags"] = QString("0x" + QString("%0").arg(spellInfo->channelInterruptFlags, 8, 16, QChar('0')).toUpper());
        values["channelInterruptFlagsNames"] = splitMaskToList(spellInfo->channelInterruptFlags, getEnums()["SpellChannelInterruptFlags"]);
    }

    if (spellInfo->casterAuraState)
    {
        values["casterAuraState"] = spellInfo->casterAuraState;
        values["casterAuraStateName"] = getEnums()["AuraState"][spellInfo->casterAuraState];
    }

    if (spellInfo->targetAuraState)
    {
        values["targetAuraState"] = spellInfo->targetAuraState;
        values["targetAuraStateName"] = getEnums()["AuraState"][spellInfo->targetAuraState];
    }

    if (spellInfo->casterAuraStateNot)
    {
        values["casterAuraStateNot"] = spellInfo->casterAuraStateNot;
        values["casterAuraStateNotName"] = getEnums()["AuraState"][spellInfo->casterAuraStateNot];
    }

    if (spellInfo->targetAuraStateNot)
    {
        values["targetAuraStateNot"] = spellInfo->targetAuraStateNot;
        values["targetAuraStateNotName"] = getEnums()["AuraState"][spellInfo->targetAuraStateNot];
    }

    if (spellInfo->casterAuraSpell)
    {
        if (const Spell::entry* spell = Spell::getRecord(spellInfo->casterAuraSpell, true)) {
            values["casterAuraSpell"] = spellInfo->casterAuraSpell;
            values["casterAuraSpellName"] = spell->nameWithRank();
        }
    }

    if (spellInfo->targetAuraSpell)
    {
        if (const Spell::entry* spell = Spell::getRecord(spellInfo->targetAuraSpell, true)) {
            values["targetAuraSpell"] = spellInfo->targetAuraSpell;
            values["targetAuraSpellName"] = spell->nameWithRank();
        }
    }

    if (spellInfo->excludeCasterAuraSpell)
    {
        if (const Spell::entry* spell = Spell::getRecord(spellInfo->excludeCasterAuraSpell, true)) {
            values["excludeCasterAuraSpell"] = spellInfo->excludeCasterAuraSpell;
            values["excludeCasterAuraSpellName"] = spell->nameWithRank();
        }
    }

    if (spellInfo->excludeTargetAuraSpell)
    {
        if (const Spell::entry* spell = Spell::getRecord(spellInfo->excludeTargetAuraSpell, true)) {
            values["excludeTargetAuraSpell"] = spellInfo->excludeTargetAuraSpell;
            values["excludeTargetAuraSpellName"] = spell->nameWithRank();
        }
    }

    values["reqSpellFocus"] = spellInfo->requiresSpellFocus;
    values["facingCasterFlags"] = spellInfo->facingCasterFlags;

    values["procChance"] = spellInfo->procChance;
    values["procCharges"] = spellInfo->procCharges;

    if (spellInfo->procFlags)
    {
        values["procFlags"] = QString("0x" + QString("%0").arg(spellInfo->procFlags, 8, 16, QChar('0')).toUpper());

        QVariantList procNames;
        for (auto proc = procFlags.begin(); proc != procFlags.end(); ++proc) {
            if (spellInfo->procFlags & proc.key()) {
                QVariantHash procName;
                procName["name"] = proc.value();
                procNames.append(procName);
            }
        }

        values["procNames"] = procNames;
    }

    QVariantList effectList;
    for (quint8 eff = 0; eff < MAX_EFFECT_INDEX; ++eff)
    {
        QVariantHash effectValues;
        effectValues["index"] = eff;
        effectValues["id"] = spellInfo->effect[eff];
        effectValues["name"] = getEnums()["SpellEffect"][spellInfo->effect[eff]];

        effectValues["basePoints"] = spellInfo->effectBasePoints[eff] + 1;

        if (spellInfo->effectRealPointsPerLevel[eff])
            effectValues["perLevelPoints"] = QString("%0").arg(spellInfo->effectRealPointsPerLevel[eff], 0, 'f', 2);

        if (spellInfo->effectDieSides[eff] > 1)
            effectValues["dieSidesPoints"] = spellInfo->effectBasePoints[eff] + 1 + spellInfo->effectDieSides[eff];

        if (spellInfo->effectPointsPerComboPoint[eff])
            effectValues["perComboPoints"] = QString("%0").arg(spellInfo->effectPointsPerComboPoint[eff], 0, 'f', 2);

        if (spellInfo->damageMultiplier[eff] != 1.0f)
            effectValues["damageMultiplier"] = QString("%0").arg(spellInfo->damageMultiplier[eff], 0, 'f', 2);

        if (spellInfo->effectMultipleValue[eff])
            effectValues["multipleValue"] = QString("%0").arg(spellInfo->effectMultipleValue[eff], 0, 'f', 2);

        effectValues["targetA"] = spellInfo->effectImplicitTargetA[eff];
        effectValues["targetB"] = spellInfo->effectImplicitTargetB[eff];
        effectValues["targetNameA"] = getEnums()["Target"][spellInfo->effectImplicitTargetA[eff]];
        effectValues["targetNameB"] = getEnums()["Target"][spellInfo->effectImplicitTargetB[eff]];

        qint32 miscA = spellInfo->effectMiscValueA[eff];
        effectValues["miscValueA"] = miscA;
        effectValues["amplitude"] = spellInfo->effectAmplitude[eff];
        effectValues["auraId"] = spellInfo->effectApplyAuraName[eff];
        effectValues["auraName"] = getEnums()["SpellAura"][spellInfo->effectApplyAuraName[eff]];

        switch (spellInfo->effectApplyAuraName[eff])
        {
            case 29:
                effectValues["mods"] = getEnums()["UnitMod"][miscA];
                break;
            case 107:
            case 108:
                effectValues["mods"] = getEnums()["SpellMod"][miscA];
                break;
            default:
                effectValues["mods"] = miscA;
                break;
        }

        effectValues["miscValueB"] = spellInfo->effectMiscValueB[eff];

        effectValues["radiusId"] = spellInfo->effectRadiusIndex[eff];
        if (const SpellRadius::entry* spellRadius = SpellRadius::getRecord(spellInfo->effectRadiusIndex[eff], true))
            effectValues["radiusValue"] = QString("%0").arg(spellRadius->radius, 0, 'f', 2);

        if (const Spell::entry* triggerSpell = Spell::getMetaRecord(spellInfo->effectTriggerSpell[eff], true))
        {
            effectValues["triggerId"] = triggerSpell->id;
            effectValues["triggerName"] = triggerSpell->nameWithRank();
            effectValues["triggerDescription"] = triggerSpell->description();
            effectValues["triggerDescriptionRegExp"] = getDescription(triggerSpell->description(), triggerSpell);
            effectValues["triggerToolTip"] = triggerSpell->toolTip();
            effectValues["triggerToolTipRegExp"] = getDescription(triggerSpell->toolTip(), triggerSpell);
            effectValues["triggerProcChance"] = triggerSpell->procChance;
            effectValues["triggerProcCharges"] = triggerSpell->procCharges;

            if (triggerSpell->procFlags)
            {
                effectValues["triggerProcFlags"] = triggerSpell->procCharges;

                QVariantList procNames;
                for (auto proc = procFlags.begin(); proc != procFlags.end(); ++proc) {
                    if (triggerSpell->procFlags & proc.key()) {
                        QVariantHash procName;
                        procName["name"] = proc.value();
                        procNames.append(procName);
                    }
                }

                effectValues["triggerProcNames"] = procNames;
            }
        }

        effectValues["chainTarget"] = spellInfo->effectChainTarget[eff];

        effectValues["mechanicId"] = spellInfo->effectMechanic[eff];
        effectValues["mechanicName"] = getEnums()["Mechanic"][spellInfo->effectMechanic[eff]];

        quint32 ClassMask[3];

        switch (eff)
        {
            case 0:
                ClassMask[0] = spellInfo->effectSpellClassMaskA[0];
                ClassMask[1] = spellInfo->effectSpellClassMaskA[1];
                ClassMask[2] = spellInfo->effectSpellClassMaskA[2];
                break;
            case 1:
                ClassMask[0] = spellInfo->effectSpellClassMaskB[0];
                ClassMask[1] = spellInfo->effectSpellClassMaskB[1];
                ClassMask[2] = spellInfo->effectSpellClassMaskB[2];
                break;
            case 2:
                ClassMask[0] = spellInfo->effectSpellClassMaskC[0];
                ClassMask[1] = spellInfo->effectSpellClassMaskC[1];
                ClassMask[2] = spellInfo->effectSpellClassMaskC[2];
                break;
        }

        if (ClassMask[0] || ClassMask[1] || ClassMask[2])
        {
            effectValues["hasClassMask"] = true;
            effectValues["classMask1"] = QString(QString("%0").arg(ClassMask[0], 8, 16, QChar('0')).toUpper());
            effectValues["classMask2"] = QString(QString("%0").arg(ClassMask[1], 8, 16, QChar('0')).toUpper());
            effectValues["classMask3"] = QString(QString("%0").arg(ClassMask[2], 8, 16, QChar('0')).toUpper());

            if (spellInfo->effect[eff] == 6)
            {
                QVariantList affectList;
                for (quint32 i = 0; i < Spell::getMetaSpellCount(); ++i)
                {
                    if (const Spell::entry* t_spellInfo = Spell::getMetaRecord(i))
                    {
                        bool hasSkill = false;
                        if ((t_spellInfo->spellFamilyName == spellInfo->spellFamilyName) &&
                            ((t_spellInfo->spellFamilyFlags[0] & ClassMask[0]) ||
                             (t_spellInfo->spellFamilyFlags[1] & ClassMask[1]) ||
                             (t_spellInfo->spellFamilyFlags[2] & ClassMask[2])))
                        {
                            for (quint32 sk = 0; sk < SkillLineAbility::getRecordCount(); ++sk)
                            {
                                const SkillLineAbility::entry* skillInfo = SkillLineAbility::getRecord(sk);
                                if (skillInfo && skillInfo->spellId == t_spellInfo->id && skillInfo->skillId > 0)
                                {
                                    hasSkill = true;
                                    break;
                                }
                            }

                            QVariantHash affectValues;
                            affectValues["id"] = t_spellInfo->id;
                            affectValues["name"] = t_spellInfo->nameWithRank();
                            affectValues["hasSkill"] = hasSkill;
                            affectList.append(affectValues);
                        }
                    }
                }
                effectValues["affectInfo"] = affectList;
            }
        }
        effectList.append(effectValues);
    }

    values["effect"] = effectList;

    return values;
}

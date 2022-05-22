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

bool SpellInfo::init()
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
    m_names = names.values();
    m_modifiedStrings.clear();

    return true;
}

void SpellInfo::setEnums(EnumHash enums)
{
    m_enums = enums;
}

MPQList SpellInfo::getMPQFiles() const
{
    static MPQList MPQs = {
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

void RegExpU(const Spell::entry* spellInfo, QRegularExpressionMatch match, QString &str)
{
    if (!match.captured(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getMetaRecord(match.captured(4).toInt(), true))
        {
            str.replace(match.captured(0), QString("%0")
                .arg(tSpell->stackAmount));
        }
    }
    else
    {
        str.replace(match.captured(0), QString("%0")
            .arg(spellInfo->stackAmount));
    }
}

void RegExpH(const Spell::entry* spellInfo, QRegularExpressionMatch match, QString &str)
{
    if (!match.captured(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getMetaRecord(match.captured(4).toInt(), true))
        {
            str.replace(match.captured(0), QString("%0")
                .arg(tSpell->procChance));
        }
    }
    else
    {
        str.replace(match.captured(0), QString("%0")
            .arg(spellInfo->procChance));
    }
}

void RegExpV(const Spell::entry* spellInfo, QRegularExpressionMatch match, QString &str)
{
    if (!match.captured(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getMetaRecord(match.captured(4).toInt(), true))
        {
            str.replace(match.captured(0), QString("%0")
                .arg(tSpell->maxTargetLevel));
        }
    }
    else
    {
        str.replace(match.captured(0), QString("%0")
            .arg(spellInfo->maxTargetLevel));
    }
}

void RegExpQ(const Spell::entry* spellInfo, QRegularExpressionMatch match, QString &str)
{
    if (!match.captured(3).isEmpty())
    {
        if (!match.captured(4).isEmpty())
        {
            if (const Spell::entry* tSpell = Spell::getMetaRecord(match.captured(4).toInt(), true))
            {
                if (match.captured(2) == QString("/"))
                {
                    str.replace(match.captured(0), QString("%0")
                        .arg(abs(qint32(tSpell->effectMiscValueA[match.captured(6).toInt()-1] / match.captured(3).toInt()))));
                }
                else if (match.captured(2) == QString("*"))
                {
                    str.replace(match.captured(0), QString("%0")
                        .arg(abs(qint32(tSpell->effectMiscValueA[match.captured(6).toInt()-1] * match.captured(3).toInt()))));
                }
            }
        }
        else
        {
            if (match.captured(2) == QString("/"))
            {
                str.replace(match.captured(0), QString("%0")
                    .arg(abs(qint32(spellInfo->effectMiscValueA[match.captured(6).toInt()-1] / match.captured(3).toInt()))));
            }
            else if (match.captured(2) == QString("*"))
            {
                str.replace(match.captured(0), QString("%0")
                    .arg(abs(qint32(spellInfo->effectMiscValueA[match.captured(6).toInt()-1] * match.captured(3).toInt()))));
            }
        }
    }
    else if (!match.captured(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getMetaRecord(match.captured(4).toInt(), true))
        {
            str.replace(match.captured(0), QString("%0")
                .arg(abs(tSpell->effectMiscValueA[match.captured(6).toInt()-1])));
        }
    }
    else
    {
        str.replace(match.captured(0), QString("%0")
            .arg(abs(spellInfo->effectMiscValueA[match.captured(6).toInt()-1])));
    }
}

void RegExpI(const Spell::entry* spellInfo, QRegularExpressionMatch match, QString &str)
{
    if (!match.captured(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getMetaRecord(match.captured(4).toInt(), true))
        {
            if (tSpell->maxAffectedTargets != 0)
            {
                str.replace(match.captured(0), QString("%0")
                    .arg(tSpell->maxAffectedTargets));
            }
            else
            {
                str.replace(match.captured(0), QString("nearby"));
            }
        }
    }
    else
    {
        if (spellInfo->maxAffectedTargets != 0)
        {
            str.replace(match.captured(0), QString("%0")
                .arg(spellInfo->maxAffectedTargets));
        }
        else
        {
            str.replace(match.captured(0), QString("nearby"));
        }
    }
}

void RegExpB(const Spell::entry* spellInfo, QRegularExpressionMatch match, QString &str)
{
    if (!match.captured(3).isEmpty())
    {
        if (!match.captured(4).isEmpty())
        {

            if (const Spell::entry* tSpell = Spell::getMetaRecord(match.captured(4).toInt(), true))
            {
                if (match.captured(2) == QString("/"))
                {
                    str.replace(match.captured(0), QString("%0")
                        .arg(abs(qint32((tSpell->effectPointsPerComboPoint[match.captured(6).toInt()-1]) / match.captured(3).toInt()))));
                }
                else if (match.captured(2) == QString("*"))
                {
                    str.replace(match.captured(0), QString("%0")
                        .arg(abs(qint32((tSpell->effectPointsPerComboPoint[match.captured(6).toInt()-1]) * match.captured(3).toInt()))));
                }
            }
        }
        else
        {
            if (match.captured(2) == QString("/"))
            {
                str.replace(match.captured(0), QString("%0")
                    .arg(abs(qint32((spellInfo->effectPointsPerComboPoint[match.captured(6).toInt()-1]) / match.captured(3).toInt()))));
            }
            else if (match.captured(2) == QString("*"))
            {
                str.replace(match.captured(0), QString("%0")
                    .arg(abs(qint32((spellInfo->effectPointsPerComboPoint[match.captured(6).toInt()-1]) * match.captured(3).toInt()))));
            }
        }
    }
    else if (!match.captured(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getMetaRecord(match.captured(4).toInt(), true))
        {
            str.replace(match.captured(0), QString("%0")
                .arg(abs(qint32(tSpell->effectPointsPerComboPoint[match.captured(6).toInt()-1]))));
        }
    }
    else
    {
        str.replace(match.captured(0), QString("%0")
            .arg(abs(qint32(spellInfo->effectPointsPerComboPoint[match.captured(6).toInt()-1]))));
    }
}

void RegExpA(const Spell::entry* spellInfo, QRegularExpressionMatch match, QString &str)
{
    if (!match.captured(3).isEmpty())
    {
        if (!match.captured(4).isEmpty())
        {
            if (const Spell::entry * tSpell = Spell::getMetaRecord(match.captured(4).toInt(), true))
            {
                if (match.captured(2) == QString("/"))
                {
                    str.replace(match.captured(0), QString("%0")
                        .arg(quint32(tSpell->getRadius(match.captured(6).toInt()-1) / match.captured(2).toInt())));
                }
                else if (match.captured(2) == QString("*"))
                {
                    str.replace(match.captured(0), QString("%0")
                        .arg(quint32(tSpell->getRadius(match.captured(6).toInt()-1) * match.captured(2).toInt())));
                }
            }
        }
        else
        {
            if (match.captured(2) == QString("/"))
            {
                str.replace(match.captured(0), QString("%0")
                    .arg(quint32(spellInfo->getRadius(match.captured(6).toInt()-1) / match.captured(2).toInt())));
            }
            else if (match.captured(2) == QString("*"))
            {
                str.replace(match.captured(0), QString("%0")
                    .arg(quint32(spellInfo->getRadius(match.captured(6).toInt()-1) * match.captured(2).toInt())));
            }
        }
    }
    else if (!match.captured(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getMetaRecord(match.captured(4).toInt(), true))
        {
            str.replace(match.captured(0), QString("%0")
                .arg(tSpell->getRadius(match.captured(6).toInt()-1)));
        }
    }
    else
    {
        str.replace(match.captured(0), QString("%0")
            .arg(spellInfo->getRadius(match.captured(6).toInt()-1)));
    }
}

void RegExpD(const Spell::entry* spellInfo, QRegularExpressionMatch match, QString &str)
{
    if (!match.captured(3).isEmpty())
    {
        if (!match.captured(4).isEmpty())
        {
            if (const Spell::entry* tSpell = Spell::getMetaRecord(match.captured(4).toInt(), true))
            {
                if (match.captured(2) == QString("/"))
                {
                    str.replace(match.captured(0), QString("%0")
                        .arg(quint32(tSpell->getDuration() / match.captured(3).toInt())));
                }
                else if (match.captured(2) == QString("*"))
                {
                    str.replace(match.captured(0), QString("%0")
                        .arg(quint32(tSpell->getDuration() * match.captured(3).toInt())));
                }
            }
        }
        else
        {
            if (match.captured(2) == QString("/"))
            {
                str.replace(match.captured(0), QString("%0")
                    .arg(quint32(spellInfo->getDuration() / match.captured(3).toInt())));
            }
            else if (match.captured(2) == QString("*"))
            {
                str.replace(match.captured(0), QString("%0")
                    .arg(quint32(spellInfo->getDuration() * match.captured(3).toInt())));
            }
        }
    }
    else if (!match.captured(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getMetaRecord(match.captured(4).toInt(), true))
        {
            str.replace(match.captured(0), QString("%0 seconds")
                .arg(tSpell->getDuration()));
        }
    }
    else
    {
        str.replace(match.captured(0), QString("%0 seconds")
            .arg(spellInfo->getDuration()));
    }
}

void RegExpO(const Spell::entry* spellInfo, QRegularExpressionMatch match, QString &str)
{
    if (!match.captured(3).isEmpty())
    {
        if (!match.captured(4).isEmpty())
        {
            if (const Spell::entry* tSpell = Spell::getMetaRecord(match.captured(4).toInt(), true))
            {
                if (match.captured(2) == QString("/"))
                {
                    str.replace(match.captured(0), QString("%0")
                        .arg(quint32((tSpell->getTicks(match.captured(6).toInt()-1) * (tSpell->effectBasePoints[match.captured(6).toInt()-1] + 1)) / match.captured(3).toInt())));
                }
                else if(match.captured(2) == QString("*"))
                {
                    str.replace(match.captured(0), QString("%0")
                        .arg(quint32((tSpell->getTicks(match.captured(6).toInt()-1) * (tSpell->effectBasePoints[match.captured(6).toInt()-1] + 1)) * match.captured(3).toInt())));
                }
            }
        }
        else
        {
            if (match.captured(2) == QString("/"))
            {
                str.replace(match.captured(0), QString("%0")
                    .arg(quint32((spellInfo->getTicks(match.captured(6).toInt()-1) * (spellInfo->effectBasePoints[match.captured(6).toInt()-1] + 1)) / match.captured(3).toInt())));
            }
            else if (match.captured(2) == QString("*"))
            {
                str.replace(match.captured(0), QString("%0")
                    .arg(quint32((spellInfo->getTicks(match.captured(6).toInt()-1) * (spellInfo->effectBasePoints[match.captured(6).toInt()-1] + 1)) * match.captured(3).toInt())));
            }
        }
    }
    else if (!match.captured(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getMetaRecord(match.captured(4).toInt(), true))
        {
            str.replace(match.captured(0), QString("%0")
                .arg(tSpell->getTicks(match.captured(6).toInt()-1) * (tSpell->effectBasePoints[match.captured(6).toInt()-1] + 1)));
        }
    }
    else
    {
        str.replace(match.captured(0), QString("%0")
            .arg(spellInfo->getTicks(match.captured(6).toInt()-1) * (spellInfo->effectBasePoints[match.captured(6).toInt()-1] + 1)));
    }
}

void RegExpS(const Spell::entry* spellInfo, QRegularExpressionMatch match, QString &str)
{
    if (!match.captured(3).isEmpty())
    {
        if (!match.captured(4).isEmpty())
        {
            if (const Spell::entry* tSpell = Spell::getMetaRecord(match.captured(4).toInt(), true))
            {
                if (match.captured(2) == QString("/"))
                {
                    str.replace(match.captured(0), QString("%0")
                        .arg(abs(qint32((tSpell->effectBasePoints[match.captured(6).toInt()-1] + 1) / match.captured(3).toInt()))));
                }
                else if (match.captured(2) == QString("*"))
                {
                    str.replace(match.captured(0), QString("%0")
                        .arg(abs(qint32((tSpell->effectBasePoints[match.captured(6).toInt()-1] + 1) * match.captured(3).toInt()))));
                }
            }
        }
        else
        {
            if (match.captured(2) == QString("/"))
            {
                str.replace(match.captured(0), QString("%0")
                    .arg(abs(qint32((spellInfo->effectBasePoints[match.captured(6).toInt()-1] + 1) / match.captured(3).toInt()))));
            }
            else if (match.captured(2) == QString("*"))
            {
                str.replace(match.captured(0), QString("%0")
                    .arg(abs(qint32((spellInfo->effectBasePoints[match.captured(6).toInt()-1] + 1) * match.captured(3).toInt()))));
            }
        }
    }
    else if (!match.captured(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getMetaRecord(match.captured(4).toInt(), true))
        {
            str.replace(match.captured(0), QString("%0")
                .arg(abs(tSpell->effectBasePoints[match.captured(6).toInt()-1] + 1)));
        }
    }
    else
    {
        str.replace(match.captured(0), QString("%0")
            .arg(abs(spellInfo->effectBasePoints[match.captured(6).toInt()-1] + 1)));
    }
}

void RegExpT(const Spell::entry* spellInfo, QRegularExpressionMatch match, QString &str)
{
    if (!match.captured(3).isEmpty())
    {
        if (!match.captured(4).isEmpty())
        {
            if (const Spell::entry* tSpell = Spell::getMetaRecord(match.captured(4).toInt(), true))
            {
                if (match.captured(2) == QString("/"))
                {
                    str.replace(match.captured(0), QString("%0")
                        .arg(quint32(tSpell->getAmplitude(match.captured(6).toInt()-1) / match.captured(3).toInt())));
                }
                else if (match.captured(2) == QString("*"))
                {
                    str.replace(match.captured(0), QString("%0")
                        .arg(quint32(tSpell->getAmplitude(match.captured(6).toInt()-1) * match.captured(3).toInt())));
                }
            }
        }
        else
        {
            if (match.captured(2) == QString("/"))
            {
                str.replace(match.captured(0), QString("%0")
                    .arg(quint32(spellInfo->getAmplitude(match.captured(6).toInt()-1) / match.captured(3).toInt())));
            }
            else if (match.captured(2) == QString("*"))
            {
                str.replace(match.captured(0), QString("%0")
                    .arg(quint32(spellInfo->getAmplitude(match.captured(6).toInt()-1) * match.captured(3).toInt())));
            }
        }
    }
    else if (!match.captured(4).isEmpty())
    {

        if (const Spell::entry* tSpell = Spell::getMetaRecord(match.captured(4).toInt(), true))
        {
            if (tSpell->effectAmplitude[match.captured(6).toInt()-1])
                str.replace(match.captured(0), QString("%0").arg(tSpell->getAmplitude(match.captured(6).toInt()-1)));
            else
                str.replace(match.captured(0), QString("%0").arg(tSpell->getAmplitude()));
        }
    }
    else
    {
        str.replace(match.captured(0), QString("%0")
            .arg(quint32(spellInfo->effectAmplitude[match.captured(6).toInt()-1] / 1000)));
    }
}

void RegExpN(const Spell::entry* spellInfo, QRegularExpressionMatch match, QString &str)
{
    if (!match.captured(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getMetaRecord(match.captured(4).toInt(), true))
        {
            str.replace(match.captured(0), QString("%0")
                .arg(tSpell->procCharges));
        }
    }
    else
    {
        str.replace(match.captured(0), QString("%0")
            .arg(spellInfo->procCharges));
    }
}

void RegExpX(const Spell::entry* spellInfo, QRegularExpressionMatch match, QString &str)
{
    if (!match.captured(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getMetaRecord(match.captured(4).toInt(), true))
        {
            str.replace(match.captured(0), QString("%0")
                .arg(tSpell->effectChainTarget[match.captured(6).toInt()-1]));
        }
    }
    else
    {
        str.replace(match.captured(0), QString("%0")
            .arg(spellInfo->effectChainTarget[match.captured(6).toInt()-1]));
    }
}

void RegExpE(const Spell::entry* spellInfo, QRegularExpressionMatch match, QString &str)
{
    if (!match.captured(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getMetaRecord(match.captured(4).toInt(), true))
        {
            str.replace(match.captured(0), QString("%0")
                .arg(tSpell->effectMultipleValue[match.captured(6).toInt()-1], 0, 'f', 2));
        }
    }
    else
    {
        str.replace(match.captured(0), QString("%0")
            .arg(spellInfo->effectMultipleValue[match.captured(6).toInt()-1], 0, 'f', 2));
    }
}

QString getDescription(QString str, const Spell::entry* spellInfo)
{
    QRegularExpression rx("\\$+(([/,*])?([0-9]*);)?([d+\\;)(\\d*)?([1-9]*)([A-z])([1-3]*)(([A-z, ]*)\\:([A-z, ]*)\\;)?");
    while (str.contains(rx))
    {
        QRegularExpressionMatch match = rx.match(str);
        if (match.hasMatch())
        {
            QChar symbol = match.captured(5)[0].toLower();
            switch (symbol.toLatin1())
            {
                case 'u': RegExpU(spellInfo, match, str); break;
                case 'h': RegExpH(spellInfo, match, str); break;
                case 'v': RegExpV(spellInfo, match, str); break;
                case 'q': RegExpQ(spellInfo, match, str); break;
                case 'i': RegExpI(spellInfo, match, str); break;
                case 'b': RegExpB(spellInfo, match, str); break;
                case 'm':
                case 's':
                    RegExpS(spellInfo, match, str);
                    break;
                case 'a': RegExpA(spellInfo, match, str); break;
                case 'd': RegExpD(spellInfo, match, str); break;
                case 'o': RegExpO(spellInfo, match, str); break;
                case 't': RegExpT(spellInfo, match, str); break;
                case 'n': RegExpN(spellInfo, match, str); break;
                case 'x': RegExpX(spellInfo, match, str); break;
                case 'e': RegExpE(spellInfo, match, str); break;
                case 'l': str.replace(match.captured(0), match.captured(9)); break;
                case 'g': str.replace(match.captured(0), match.captured(8)); break;
                case 'z': str.replace(match.captured(0), QString("[Home]")); break;
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
    values["spellFamilyFlags"] = QString("0x" + QString("%0").arg(spellInfo->spellFamilyFlags, 16, 16, QChar('0')).toUpper());

    values["spellSchoolMask"] = spellInfo->schoolMask;
    values["spellSchoolMaskNames"] = splitMask(spellInfo->schoolMask, getEnums()["SchoolMask"]);

    values["damageClassId"] = spellInfo->damageClass;
    values["damageClassName"] = getEnums()["DamageClass"][spellInfo->damageClass];

    values["preventionTypeId"] = spellInfo->preventionType;
    values["preventionTypeName"] = getEnums()["PreventionType"][spellInfo->preventionType];

    if (spellInfo->attributes || spellInfo->attributesEx1 || spellInfo->attributesEx2 ||
        spellInfo->attributesEx3 || spellInfo->attributesEx4 || spellInfo->attributesEx5 || spellInfo->attributesEx6)
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
    }

    if (spellInfo->targets)
    {
        values["targets"] = QString("0x" + QString("%0").arg(spellInfo->targets, 8, 16, QChar('0')).toUpper());
        values["targetsNames"] = splitMaskToList(spellInfo->targets, getEnums()["TargetFlag"]);
    }

    if (spellInfo->targetCreatureType)
    {
        values["creatureType"] = QString("0x" + QString("%0").arg(spellInfo->targetCreatureType, 8, 16, QChar('0')).toUpper());
        values["creatureTypeNames"] = splitMaskToList(spellInfo->targetCreatureType, getEnums()["CreatureType"]);
    }

    if (spellInfo->stances)
    {
        values["stances"] = QString("0x" + QString("%0").arg(spellInfo->stances, 8, 16, QChar('0')).toUpper());
        values["stancesNames"] = splitMaskToList(spellInfo->stances, getEnums()["ShapeshiftForm"]);
    }

    if (spellInfo->stancesNot)
    {
        values["stancesNot"] = QString("0x" + QString("%0").arg(spellInfo->stancesNot, 8, 16, QChar('0')).toUpper());
        values["stancesNotNames"] = splitMaskToList(spellInfo->stancesNot, getEnums()["ShapeshiftForm"]);
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

    values["reqSpellFocus"] = spellInfo->requiresSpellFocus;
    values["facingCasterFlags"] = spellInfo->facingCasterFlags;

    values["procChance"] = spellInfo->procChance;
    values["procCharges"] = spellInfo->procCharges;

    if (spellInfo->procFlags)
    {
        values["procFlags"] = QString("0x" + QString("%0").arg(spellInfo->procFlags, 8, 16, QChar('0')).toUpper());
        values["procNames"] = splitMaskToList(spellInfo->procFlags, getEnums()["ProcFlags"]);
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
                effectValues["triggerProcFlags"] = QString("0x" + QString("%0").arg(triggerSpell->procFlags, 8, 16, QChar('0')).toUpper());
                effectValues["triggerProcNames"] = splitMaskToList(triggerSpell->procFlags, getEnums()["ProcFlags"]);
            }
        }

        effectValues["chainTarget"] = spellInfo->effectChainTarget[eff];

        effectValues["mechanicId"] = spellInfo->effectMechanic[eff];
        effectValues["mechanicName"] = getEnums()["Mechanic"][spellInfo->effectMechanic[eff]];

        if (spellInfo->effectItemType[eff] != 0)
        {
            effectValues["itemType"] = QString("0x" + QString("%0").arg(spellInfo->effectItemType[eff], 8, 16, QChar('0')).toUpper());

            if (spellInfo->effect[eff] == 6)
            {
                QVariantList affectList;
                for (quint32 i = 0; i < Spell::getMetaSpellCount(); ++i)
                {
                    if (const Spell::entry* t_spellInfo = Spell::getMetaRecord(i))
                    {
                        bool hasSkill = false;
                        if ((t_spellInfo->spellFamilyName == spellInfo->spellFamilyName) &&
                            (t_spellInfo->spellFamilyFlags & spellInfo->effectItemType[eff]))
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

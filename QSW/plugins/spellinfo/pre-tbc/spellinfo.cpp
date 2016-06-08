#include "spellinfo.h"
#include "structure.h"
#include <QBuffer>
#include <QSet>

QString ProcFlagDesc[] =
{
    // 00 0x00000001
    "00 Killed by aggressor that receive experience or honor",
    // 01 0x00000002
    "01 Kill that yields experience or honor",
    // 02 0x00000004
    "02 Successful melee attack",
    // 03 0x00000008
    "03 Taken damage from melee strike hit",
    // 04 0x00000010
    "04 Successful attack by Spell that use melee weapon",
    // 05 0x00000020
    "05 Taken damage by Spell that use melee weapon",
    // 06 0x00000040
    "06 Successful Ranged attack (and wand spell cast)",
    // 07 0x00000080
    "07 Taken damage from ranged attack",
    // 08 0x00000100
    "08 Successful Ranged attack by Spell that use ranged weapon",
    // 09 0x00000200
    "09 Taken damage by Spell that use ranged weapon",
    // 10 0x00000400
    "10 Successful spell hit",
    // 11 0x00000800
    "11 Taken spell hit",
    // 12 0x00001000
    "12 Successful spell cast",
    // 13 0x00002000
    "13 Taken spell hit",
    // 14 0x00004000
    "14 Successful cast positive spell",
    // 15 0x00008000
    "15 Taken positive spell hit",
    // 16 0x00010000
    "16 Successful damage from harmful spell cast",
    // 17 0x00020000
    "17 Taken spell damage",
    // 18 0x00040000
    "18 Deal periodic damage",
    // 19 0x00080000
    "19 Taken periodic damage",
    // 20 0x00100000
    "20 Taken any damage",
    // 21 0x00200000
    "21 On trap activation"
};

void SpellInfo::init() const
{
    QSet<QString> names;
    for (quint32 i = 0; i < Spell::getHeader()->recordCount; ++i) {
        if (const Spell::entry* spellInfo = Spell::getRecord(i)) {
            getMetaSpells().append(new Spell::meta(spellInfo));
            QString name = spellInfo->name();
            if (names.find(name) == names.end())
                names << name;
        }
    }

    getNames() = names.toList();

    if (const Spell::entry* spellInfo = Spell::getRecord(0)) {
        for (quint8 i = 0; i < 8; ++i) {
            if (spellInfo->nameOffset[i]) {
                getLocale() = i;
                break;
            }
        }
    }

    //getEnums() = QSW::loadEnumFile(QString("plugins/spellinfo/pre-tbc.xml"));
}

QObject* SpellInfo::getMetaSpell(quint32 id, bool realId) const
{
    return realId ? getMetaSpells().at(Spell::getDbc().getIndex(id)) : getMetaSpells().at(id);
}

quint32 SpellInfo::getSpellsCount() const
{
    return Spell::getHeader()->recordCount;
}

QObjectList& SpellInfo::getMetaSpells() const
{
    static QObjectList m_metaSpells;
    return m_metaSpells;
}

EnumHash& SpellInfo::getEnums() const
{
    static EnumHash m_enums;
    return m_enums;
}

quint8& SpellInfo::getLocale() const
{
    static quint8 m_locale;
    return m_locale;
}

QStringList& SpellInfo::getNames() const
{
    static QStringList m_names;
    return m_names;
}

QString getSpellIconName(quint32 iconId)
{
    const SpellIcon::entry* iconInfo = SpellIcon::getRecord(iconId, true);

    return (iconInfo ? iconInfo->iconPath().section('\\', -1) : QString(""));
}

QImage getSpellIcon(quint32 iconId)
{
    const SpellIcon::entry* iconInfo = SpellIcon::getRecord(iconId, true);

    return (iconInfo ? BLP::getBLP(iconInfo->iconPath() + QString(".blp")) : QImage());
}

QVariantList getParentSpells(quint32 triggerId)
{
    QVariantList parentSpells;
    for (quint32 i = 0; i < Spell::getHeader()->recordCount; ++i)
    {
        if (const Spell::entry* spellInfo = Spell::getRecord(i))
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

void RegExpU(const Spell::entry* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
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
        if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
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
        if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
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
            if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
            {
                if (rx.cap(2) == QString("/"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(abs(qint32(tSpell->effectMiscValue[rx.cap(6).toInt()-1] / rx.cap(3).toInt()))));
                }
                else if (rx.cap(2) == QString("*"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(abs(qint32(tSpell->effectMiscValue[rx.cap(6).toInt()-1] * rx.cap(3).toInt()))));
                }
            }
        }
        else
        {
            if (rx.cap(2) == QString("/"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(abs(qint32(spellInfo->effectMiscValue[rx.cap(6).toInt()-1] / rx.cap(3).toInt()))));
            }
            else if (rx.cap(2) == QString("*"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(abs(qint32(spellInfo->effectMiscValue[rx.cap(6).toInt()-1] * rx.cap(3).toInt()))));
            }
        }
    }
    else if (!rx.cap(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(abs(tSpell->effectMiscValue[rx.cap(6).toInt()-1])));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(abs(spellInfo->effectMiscValue[rx.cap(6).toInt()-1])));
    }
}

void RegExpI(const Spell::entry* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
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

            if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
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
        if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
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
            if (const Spell::entry * tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
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
        if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
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
            if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
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
        if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
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
            if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
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
        if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
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
            if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
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
        if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
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
            if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
            {
                if (rx.cap(2) == QString("/"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(quint32(quint32(tSpell->effectAmplitude[rx.cap(6).toInt()-1] / 1000) / rx.cap(3).toInt())));
                }
                else if (rx.cap(2) == QString("*"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(quint32(quint32(tSpell->effectAmplitude[rx.cap(6).toInt()-1] / 1000) * rx.cap(3).toInt())));
                }
            }
        }
        else
        {
            if (rx.cap(2) == QString("/"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(quint32(quint32(spellInfo->effectAmplitude[rx.cap(6).toInt()-1] / 1000) / rx.cap(3).toInt())));
            }
            else if (rx.cap(2) == QString("*"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(quint32(quint32(spellInfo->effectAmplitude[rx.cap(6).toInt()-1] / 1000) * rx.cap(3).toInt())));
            }
        }
    }
    else if (!rx.cap(4).isEmpty())
    {

        if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
        {
            if (tSpell->effectAmplitude[rx.cap(6).toInt()-1])
                str.replace(rx.cap(0), QString("%0").arg(quint32(tSpell->effectAmplitude[rx.cap(6).toInt()-1] / 1000)));
            else
                str.replace(rx.cap(0), QString("%0").arg(quint32(tSpell->getAmplitude() / 1000)));
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
        if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
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
        if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
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
        if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
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
    //if (!m_form->isRegExp())
    //    return str;

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

    const Spell::entry* spellInfo = Spell::getRecord(id, true);
    if (!spellInfo)
        return values;

    QString sSpellFamilyFlags("0x" + QString("%0").arg(spellInfo->spellFamilyFlags, 16, 16, QChar('0')).toUpper());
    QString sAttributes("0x" + QString("%0").arg(spellInfo->attributes, 8, 16, QChar('0')).toUpper());
    QString sAttributesEx1("0x" + QString("%0").arg(spellInfo->attributesEx1, 8, 16, QChar('0')).toUpper());
    QString sAttributesEx2("0x" + QString("%0").arg(spellInfo->attributesEx2, 8, 16, QChar('0')).toUpper());
    QString sAttributesEx3("0x" + QString("%0").arg(spellInfo->attributesEx3, 8, 16, QChar('0')).toUpper());
    QString sAttributesEx4("0x" + QString("%0").arg(spellInfo->attributesEx4, 8, 16, QChar('0')).toUpper());
    QString sTargetMask("0x" + QString("%0").arg(spellInfo->targets, 8, 16, QChar('0')).toUpper());
    QString sCreatureTypeMask("0x" + QString("%0").arg(spellInfo->targetCreatureType, 8, 16, QChar('0')).toUpper());
    QString sFormMask("0x" + QString("%0").arg(spellInfo->stances, 8, 16, QChar('0')).toUpper());
    QString sIF("0x" + QString("%0").arg(spellInfo->interruptFlags, 8, 16, QChar('0')).toUpper());
    QString sAIF("0x" + QString("%0").arg(spellInfo->auraInterruptFlags, 8, 16, QChar('0')).toUpper());
    QString sCIF("0x" + QString("%0").arg(spellInfo->channelInterruptFlags, 8, 16, QChar('0')).toUpper());

    QByteArray byteArray[3];
    QBuffer buffer[3];
    buffer[0].setBuffer(&byteArray[0]);
    buffer[0].open(QIODevice::WriteOnly);
    getSpellIcon(spellInfo->spellIconId).save(&buffer[0], "PNG");

    buffer[1].setBuffer(&byteArray[1]);
    buffer[1].open(QIODevice::WriteOnly);
    QImage(":/qsw/resources/border.png").save(&buffer[1], "PNG");

    buffer[2].setBuffer(&byteArray[2]);
    buffer[2].open(QIODevice::WriteOnly);
    QImage(":/qsw/resources/borderHover.png").save(&buffer[2], "PNG");

    values["icon1"] = byteArray[0].toBase64().data();
    values["icon2"] = byteArray[1].toBase64().data();
    values["icon3"] = byteArray[2].toBase64().data();

    values["id"] = spellInfo->id;
    values["name"] = spellInfo->name();
    values["rank"] = spellInfo->rank();
    values["nameWithRank"] = spellInfo->nameWithRank();
    values["description"] = getDescription(spellInfo->description(), spellInfo);
    values["tooltip"] = getDescription(spellInfo->toolTip(), spellInfo);

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
    values["spellVisual1"] = spellInfo->spellVisual[0];
    values["spellVisual2"] = spellInfo->spellVisual[1];

    values["spellFamilyId"] = spellInfo->spellFamilyName;
    values["spellFamilyName"] = getEnums()["SpellFamily"][spellInfo->spellFamilyName];
    values["spellFamilyFlags"] = sSpellFamilyFlags;

    values["spellSchoolId"] = spellInfo->school;
    values["spellSchoolName"] = getEnums()["School"][spellInfo->school];

    values["damageClassId"] = spellInfo->damageClass;
    values["damageClassName"] = getEnums()["DamageClass"][spellInfo->damageClass];

    values["preventionTypeId"] = spellInfo->preventionType;
    values["preventionTypeName"] = getEnums()["PreventionType"][spellInfo->preventionType];

    if (spellInfo->attributes || spellInfo->attributesEx1 || spellInfo->attributesEx2 ||
        spellInfo->attributesEx3 || spellInfo->attributesEx4)
    {
        values["hasAttributes"] = true;

        if (spellInfo->attributes)
        {
            values["attr"] = sAttributes;
            values["attrNames"] = splitMask(spellInfo->attributes, getEnums()["Attributes"]);
        }

        if (spellInfo->attributesEx1)
        {
            values["attrEx1"] = sAttributesEx1;
            values["attrEx1Names"] = splitMask(spellInfo->attributesEx1, getEnums()["AttributesEx1"]);
        }

        if (spellInfo->attributesEx2)
        {
            values["attrEx2"] = sAttributesEx2;
            values["attrEx2Names"] = splitMask(spellInfo->attributesEx2, getEnums()["AttributesEx2"]);
        }

        if (spellInfo->attributesEx3)
        {
            values["attrEx3"] = sAttributesEx3;
            values["attrEx3Names"] = splitMask(spellInfo->attributesEx3, getEnums()["AttributesEx3"]);
        }

        if (spellInfo->attributesEx4)
        {
            values["attrEx4"] = sAttributesEx4;
            values["attrEx4Names"] = splitMask(spellInfo->attributesEx4, getEnums()["AttributesEx4"]);
        }
    }

    if (spellInfo->targets)
    {
        values["targets"] = sTargetMask;
        values["targetsNames"] = splitMask(spellInfo->targets, getEnums()["TargetFlag"]);
    }

    if (spellInfo->targetCreatureType)
    {
        values["creatureType"] = sCreatureTypeMask;
        values["creatureTypeNames"] = splitMask(spellInfo->targetCreatureType, getEnums()["CreatureType"]);
    }

    if (spellInfo->stances)
    {
        values["stances"] = sFormMask;
        values["stancesNames"] = splitMask(spellInfo->stances, getEnums()["ShapeshiftForm"]);
    }

    if (spellInfo->stancesNot)
    {
        values["stancesNot"] = sFormMask;
        values["stancesNotNames"] = splitMask(spellInfo->stancesNot, getEnums()["ShapeshiftForm"]);
    }

    for (quint32 i = 0; i < SkillLineAbility::getHeader()->recordCount; ++i)
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
            QString sItemSubClassMask("0x" + QString("%0").arg(spellInfo->equippedItemSubClassMask, 8, 16, QChar('0')).toUpper());
            values["equipItemSubClassMask"] = sItemSubClassMask;

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
            QString sItemInventoryMask("0x" + QString("%0").arg(spellInfo->equippedItemInventoryTypeMask, 8, 16, QChar('0')).toUpper());
            values["equipItemInvTypeMask"] = sItemInventoryMask;
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

    values["interruptFlags"] = sIF;
    values["auraInterruptFlags"] = sAIF;
    values["channelInterruptFlags"] = sCIF;

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

    values["reqSpellFocus"] = spellInfo->requiresSpellFocus;

    values["procChance"] = spellInfo->procChance;
    values["procCharges"] = spellInfo->procCharges;

    if (spellInfo->procFlags)
    {
        QString sProcFlags("0x" + QString("%0").arg(spellInfo->procFlags, 8, 16, QChar('0')).toUpper());
        values["procFlags"] = sProcFlags;

        quint8 i = 0;
        quint64 proc = spellInfo->procFlags;

        QVariantList procNames;
        while (proc != 0)
        {
            if ((proc & 1) != 0) {
                QVariantHash procName;
                procName["name"] = ProcFlagDesc[i];
                procNames.append(procName);
            }
            ++i;
            proc >>= 1;
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

        quint32 misc = spellInfo->effectMiscValue[eff];
        effectValues["miscValue"] = misc;
        effectValues["amplitude"] = spellInfo->effectAmplitude[eff];
        effectValues["auraId"] = spellInfo->effectApplyAuraName[eff];
        effectValues["auraName"] = getEnums()["SpellAura"][spellInfo->effectApplyAuraName[eff]];

        switch (spellInfo->effectApplyAuraName[eff])
        {
            case 29:
                effectValues["mods"] = getEnums()["UnitMod"][misc];
                break;
            case 107:
            case 108:
                effectValues["mods"] = getEnums()["SpellMod"][misc];
                break;
            default:
                effectValues["mods"] = misc;
                break;
        }

        if (const SpellRadius::entry* spellRadius = SpellRadius::getRecord(spellInfo->effectRadiusIndex[eff], true))
            effectValues["radiusValue"] = QString("%0").arg(spellRadius->radius, 0, 'f', 2);

        if (const Spell::entry* triggerSpell = Spell::getRecord(spellInfo->effectTriggerSpell[eff], true))
        {
            effectValues["triggerId"] = triggerSpell->id;
            effectValues["triggerName"] = triggerSpell->nameWithRank();
            effectValues["triggerDescription"] = getDescription(triggerSpell->description(), triggerSpell);
            effectValues["triggerToolTip"] = getDescription(triggerSpell->toolTip(), triggerSpell);
            effectValues["triggerProcChance"] = triggerSpell->procChance;
            effectValues["triggerProcCharges"] = triggerSpell->procCharges;

            if (triggerSpell->procFlags)
            {
                effectValues["triggerProcFlags"] = triggerSpell->procCharges;

                quint8 i = 0;
                quint64 proc = triggerSpell->procFlags;

                QVariantList procNames;
                while (proc != 0)
                {
                    if ((proc & 1) != 0) {
                        QVariantHash procName;
                        procName["name"] = ProcFlagDesc[i];
                        procNames.append(procName);
                    }
                    ++i;
                    proc >>= 1;
                }

                effectValues["triggerProcNames"] = procNames;
            }
        }

        effectValues["chainTarget"] = spellInfo->effectChainTarget[eff];

        effectValues["mechanicId"] = spellInfo->effectMechanic[eff];
        effectValues["mechanicName"] = getEnums()["Mechanic"][spellInfo->effectMechanic[eff]];

        if (spellInfo->effectItemType[eff] != 0)
        {
            QString sEffectItemType("0x" + QString("%0").arg(spellInfo->effectItemType[eff], 8, 16, QChar('0')).toUpper());
            effectValues["itemType"] = sEffectItemType;

            if (spellInfo->effect[eff] == 6)
            {
                QVariantList affectList;
                for (quint32 i = 0; i < Spell::getHeader()->recordCount; ++i)
                {
                    if (const Spell::entry* t_spellInfo = Spell::getRecord(i))
                    {
                        bool hasSkill = false;
                        if ((t_spellInfo->spellFamilyName == spellInfo->spellFamilyName) &&
                            (t_spellInfo->spellFamilyFlags & spellInfo->effectItemType[eff]))
                        {
                            for (quint32 sk = 0; sk < SkillLineAbility::getHeader()->recordCount; ++sk)
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

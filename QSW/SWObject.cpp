#include "SWObject.h"
#include "SWSearch.h"

#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

SWObject::SWObject(SWMainForm* form)
    : m_form(form), m_regExp(false), m_type(0)
{
    LoadDBCStores();
}

void SWObject::search()
{
    SWSearch* search = new SWSearch(this);
    search->search();
    delete search;
}

void SWObject::setMetaEnum(const char* enumName)
{
    m_metaEnum = Enums::staticMetaObject.enumerator(Enums::staticMetaObject.indexOfEnumerator(enumName));
}

float getRadius(SpellEntry const* spellInfo, quint8 effIndex)
{
    SpellRadiusEntry const* spellRadius = sSpellRadiusStore.LookupEntry(spellInfo->EffectRadiusIndex[effIndex]);
    if (spellRadius)
        return spellRadius->Radius;

    return 0.0f;
}

quint32 getDuration(SpellEntry const* spellInfo)
{
    SpellDurationEntry const* durationInfo = sSpellDurationStore.LookupEntry(spellInfo->DurationIndex);
    if (durationInfo)
        return quint32(durationInfo->Duration[0] / 1000);

    return 1;
}

quint32 getRealDuration(SpellEntry const* spellInfo, quint8 effIndex)
{
    return quint32(getDuration(spellInfo) / (spellInfo->EffectAmplitude[effIndex] ? quint32(spellInfo->EffectAmplitude[effIndex] / 1000) : 5));
}

void RegExpU(SpellEntry const* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(4).isEmpty())
    {
        SpellEntry const* tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
        if (tSpell)
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(tSpell->StackAmount));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(spellInfo->StackAmount));
    }
}

void RegExpH(SpellEntry const* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(4).isEmpty())
    {
        SpellEntry const* tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
        if (tSpell)
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(tSpell->ProcChance));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(spellInfo->ProcChance));
    }
}

void RegExpV(SpellEntry const* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(4).isEmpty())
    {
        SpellEntry const* tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
        if (tSpell)
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(tSpell->MaxTargetLevel));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(spellInfo->MaxTargetLevel));
    }
}

void RegExpQ(SpellEntry const* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(3).isEmpty())
    {
        if (!rx.cap(4).isEmpty())
        {
            SpellEntry const* tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
            if (tSpell)
            {
                if (rx.cap(2) == QString("/"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(abs(qint32(tSpell->EffectMiscValue[rx.cap(6).toInt()-1] / rx.cap(3).toInt()))));
                }
                else if (rx.cap(2) == QString("*"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(abs(qint32(tSpell->EffectMiscValue[rx.cap(6).toInt()-1] * rx.cap(3).toInt()))));
                }
            }
        }
        else
        {
            if (rx.cap(2) == QString("/"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(abs(qint32(spellInfo->EffectMiscValue[rx.cap(6).toInt()-1] / rx.cap(3).toInt()))));
            }
            else if (rx.cap(2) == QString("*"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(abs(qint32(spellInfo->EffectMiscValue[rx.cap(6).toInt()-1] * rx.cap(3).toInt()))));
            }
        }
    }
    else if (!rx.cap(4).isEmpty())
    {
        SpellEntry const* tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
        if (tSpell)
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(abs(tSpell->EffectMiscValue[rx.cap(6).toInt()-1])));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(abs(spellInfo->EffectMiscValue[rx.cap(6).toInt()-1])));
    }
}

void RegExpI(SpellEntry const* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(4).isEmpty())
    {
        SpellEntry const* tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
        if (tSpell)
        {
            if (tSpell->MaxAffectedTargets != 0)
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(tSpell->MaxAffectedTargets));
            }
            else
            {
                str.replace(rx.cap(0), QString("nearby"));
            }
        }
    }
    else
    {
        if (spellInfo->MaxAffectedTargets != 0)
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(spellInfo->MaxAffectedTargets));
        }
        else
        {
            str.replace(rx.cap(0), QString("nearby"));
        }
    }
}

void RegExpB(SpellEntry const* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(3).isEmpty())
    {
        if (!rx.cap(4).isEmpty())
        {
            SpellEntry const* tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
            if (tSpell)
            {
                if (rx.cap(2) == QString("/"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(abs(qint32((tSpell->EffectPointsPerComboPoint[rx.cap(6).toInt()-1]) / rx.cap(3).toInt()))));
                }
                else if (rx.cap(2) == QString("*"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(abs(qint32((tSpell->EffectPointsPerComboPoint[rx.cap(6).toInt()-1]) * rx.cap(3).toInt()))));
                }
            }
        }
        else
        {
            if (rx.cap(2) == QString("/"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(abs(qint32((spellInfo->EffectPointsPerComboPoint[rx.cap(6).toInt()-1]) / rx.cap(3).toInt()))));
            }
            else if (rx.cap(2) == QString("*"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(abs(qint32((spellInfo->EffectPointsPerComboPoint[rx.cap(6).toInt()-1]) * rx.cap(3).toInt()))));
            }
        }
    }
    else if (!rx.cap(4).isEmpty())
    {
        SpellEntry const* tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
        if (tSpell)
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(abs(qint32(tSpell->EffectPointsPerComboPoint[rx.cap(6).toInt()-1]))));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(abs(qint32(spellInfo->EffectPointsPerComboPoint[rx.cap(6).toInt()-1]))));
    }
}

void RegExpM(SpellEntry const* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(3).isEmpty())
    {
        if (!rx.cap(4).isEmpty())
        {
            SpellEntry const* tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
            if (tSpell)
            {
                if (rx.cap(2) == QString("/"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(abs(qint32((tSpell->EffectBasePoints[rx.cap(6).toInt()-1] + 1) / rx.cap(3).toInt()))));
                }
                else if (rx.cap(2) == QString("*"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(abs(qint32((tSpell->EffectBasePoints[rx.cap(6).toInt()-1] + 1) * rx.cap(3).toInt()))));
                }
            }
        }
        else
        {
            if (rx.cap(2) == QString("/"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(abs(qint32((spellInfo->EffectBasePoints[rx.cap(6).toInt()-1] + 1) / rx.cap(3).toInt()))));
            }
            else if (rx.cap(2) == QString("*"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(abs(qint32((spellInfo->EffectBasePoints[rx.cap(6).toInt()-1] + 1) * rx.cap(3).toInt()))));
            }
        }
    }
    else if (!rx.cap(4).isEmpty())
    {
        SpellEntry const* tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
        if (tSpell)
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(abs(tSpell->EffectBasePoints[rx.cap(6).toInt()-1] + 1)));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(abs(spellInfo->EffectBasePoints[rx.cap(6).toInt()-1] + 1)));
    }
}

void RegExpA(SpellEntry const* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(3).isEmpty())
    {
        if (!rx.cap(4).isEmpty())
        {
            SpellEntry const* tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
            if (tSpell)
            {
                if (rx.cap(2) == QString("/"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(quint32(getRadius(tSpell, rx.cap(6).toInt()-1) / rx.cap(2).toInt())));
                }
                else if (rx.cap(2) == QString("*"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(quint32(getRadius(tSpell, rx.cap(6).toInt()-1) * rx.cap(2).toInt())));
                }
            }
        }
        else
        {
            if (rx.cap(2) == QString("/"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(quint32(getRadius(spellInfo, rx.cap(6).toInt()-1) / rx.cap(2).toInt())));
            }
            else if (rx.cap(2) == QString("*"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(quint32(getRadius(spellInfo, rx.cap(6).toInt()-1) * rx.cap(2).toInt())));
            }
        }
    }
    else if (!rx.cap(4).isEmpty())
    {
        SpellEntry const* tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
        if (tSpell)
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(getRadius(tSpell, rx.cap(6).toInt()-1)));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(getRadius(spellInfo, rx.cap(6).toInt()-1)));
    }
}

void RegExpD(SpellEntry const* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(3).isEmpty())
    {
        if (!rx.cap(4).isEmpty())
        {
            SpellEntry const* tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
            if (tSpell)
            {
                if (rx.cap(2) == QString("/"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(quint32(getDuration(tSpell) / rx.cap(3).toInt())));
                }
                else if (rx.cap(2) == QString("*"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(quint32(getDuration(tSpell) * rx.cap(3).toInt())));
                }
            }
        }
        else
        {
            if (rx.cap(2) == QString("/"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(quint32(getDuration(spellInfo) / rx.cap(3).toInt())));
            }
            else if (rx.cap(2) == QString("*"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(quint32(getDuration(spellInfo) * rx.cap(3).toInt())));
            }
        }
    }
    else if (!rx.cap(4).isEmpty())
    {
        SpellEntry const* tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
        if (tSpell)
        {
            str.replace(rx.cap(0), QString("%0 seconds")
                .arg(getDuration(tSpell)));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0 seconds")
            .arg(getDuration(spellInfo)));
    }
}

void RegExpO(SpellEntry const* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(3).isEmpty())
    {
        if (!rx.cap(4).isEmpty())
        {
            SpellEntry const* tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
            if (tSpell)
            {
                if (rx.cap(2) == QString("/"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(quint32((getRealDuration(tSpell, rx.cap(6).toInt()-1) * (tSpell->EffectBasePoints[rx.cap(6).toInt()-1] + 1)) / rx.cap(3).toInt())));
                }
                else if(rx.cap(2) == QString("*"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(quint32((getRealDuration(tSpell, rx.cap(6).toInt()-1) * (tSpell->EffectBasePoints[rx.cap(6).toInt()-1] + 1)) * rx.cap(3).toInt())));
                }
            }
        }
        else
        {
            if (rx.cap(2) == QString("/"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(quint32((getRealDuration(spellInfo, rx.cap(6).toInt()-1) * (spellInfo->EffectBasePoints[rx.cap(6).toInt()-1] + 1)) / rx.cap(3).toInt())));
            }
            else if (rx.cap(2) == QString("*"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(quint32((getRealDuration(spellInfo, rx.cap(6).toInt()-1) * (spellInfo->EffectBasePoints[rx.cap(6).toInt()-1] + 1)) * rx.cap(3).toInt())));
            }
        }
    }
    else if (!rx.cap(4).isEmpty())
    {
        SpellEntry const* tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
        if (tSpell)
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(getRealDuration(tSpell, rx.cap(6).toInt()-1) * (tSpell->EffectBasePoints[rx.cap(6).toInt()-1] + 1)));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(getRealDuration(spellInfo, rx.cap(6).toInt()-1) * (spellInfo->EffectBasePoints[rx.cap(6).toInt()-1] + 1)));
    }
}

void RegExpS(SpellEntry const* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(3).isEmpty())
    {
        if (!rx.cap(4).isEmpty())
        {
            SpellEntry const* tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
            if (tSpell)
            {
                if (rx.cap(2) == QString("/"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(abs(qint32((tSpell->EffectBasePoints[rx.cap(6).toInt()-1] + 1) / rx.cap(3).toInt()))));
                }
                else if (rx.cap(2) == QString("*"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(abs(qint32((tSpell->EffectBasePoints[rx.cap(6).toInt()-1] + 1) * rx.cap(3).toInt()))));
                }
            }
        }
        else
        {
            if (rx.cap(2) == QString("/"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(abs(qint32((spellInfo->EffectBasePoints[rx.cap(6).toInt()-1] + 1) / rx.cap(3).toInt()))));
            }
            else if (rx.cap(2) == QString("*"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(abs(qint32((spellInfo->EffectBasePoints[rx.cap(6).toInt()-1] + 1) * rx.cap(3).toInt()))));
            }
        }
    }
    else if (!rx.cap(4).isEmpty())
    {
        SpellEntry const* tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
        if (tSpell)
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(abs(tSpell->EffectBasePoints[rx.cap(6).toInt()-1] + 1)));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(abs(spellInfo->EffectBasePoints[rx.cap(6).toInt()-1] + 1)));
    }
}

void RegExpT(SpellEntry const* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(3).isEmpty())
    {
        if (!rx.cap(4).isEmpty())
        {
            SpellEntry const* tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
            if (tSpell)
            {
                if (rx.cap(2) == QString("/"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(quint32(quint32(tSpell->EffectAmplitude[rx.cap(6).toInt()-1] / 1000) / rx.cap(3).toInt())));
                }
                else if (rx.cap(2) == QString("*"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(quint32(quint32(tSpell->EffectAmplitude[rx.cap(6).toInt()-1] / 1000) * rx.cap(3).toInt())));
                }
            }
        }
        else
        {
            if (rx.cap(2) == QString("/"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(quint32(quint32(spellInfo->EffectAmplitude[rx.cap(6).toInt()-1] / 1000) / rx.cap(3).toInt())));
            }
            else if (rx.cap(2) == QString("*"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(quint32(quint32(spellInfo->EffectAmplitude[rx.cap(6).toInt()-1] / 1000) * rx.cap(3).toInt())));
            }
        }
    }
    else if (!rx.cap(4).isEmpty())
    {
        SpellEntry const* tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
        if (tSpell)
        {
            if (tSpell->EffectAmplitude[rx.cap(6).toInt()-1])
                str.replace(rx.cap(0), QString("%0").arg(quint32(tSpell->EffectAmplitude[rx.cap(6).toInt()-1] / 1000)));
            else
                str.replace(rx.cap(0), QString("%0").arg(quint32(spellInfo->getAmplitude() / 1000)));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(quint32(spellInfo->EffectAmplitude[rx.cap(6).toInt()-1] / 1000)));
    }
}

void RegExpN(SpellEntry const* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(4).isEmpty())
    {
        SpellEntry const* tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
        if (tSpell)
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(tSpell->ProcCharges));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(spellInfo->ProcCharges));
    }
}

void RegExpX(SpellEntry const* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(4).isEmpty())
    {
        SpellEntry const* tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
        if (tSpell)
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(tSpell->EffectChainTarget[rx.cap(6).toInt()-1]));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(spellInfo->EffectChainTarget[rx.cap(6).toInt()-1]));
    }
}

void RegExpE(SpellEntry const* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(4).isEmpty())
    {
        SpellEntry const* tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
        if (tSpell)
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(tSpell->EffectMultipleValue[rx.cap(6).toInt()-1], 0, 'f', 2));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(spellInfo->EffectMultipleValue[rx.cap(6).toInt()-1], 0, 'f', 2));
    }
}

QString SWObject::getDescription(QString str, SpellEntry const* spellInfo)
{
    if (!m_form->isRegExp())
        return str;

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
                case 'm': RegExpM(spellInfo, rx, str); break;
                case 'a': RegExpA(spellInfo, rx, str); break;
                case 'd': RegExpD(spellInfo, rx, str); break;
                case 'o': RegExpO(spellInfo, rx, str); break;
                case 's': RegExpS(spellInfo, rx, str); break;
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

quint32 SWObject::getParentSpellId(quint32 triggerId)
{
    for (quint32 i = 0; i < sSpellStore.GetNumRows(); ++i)
        if (SpellEntry const* spellInfo = sSpellStore.LookupEntry(i))
            for (quint8 eff = EFFECT_INDEX_0; eff < MAX_EFFECT_INDEX; ++eff)
                if (spellInfo->EffectTriggerSpell[eff] == triggerId)
                    return spellInfo->Id;
    return 0;
}

QString SWObject::getSpellIconName(quint32 iconId)
{
    SpellIconEntry const* iconInfo = sSpellIconStore.LookupEntry(iconId);

    if (!iconInfo)
        return QString("");

    return QString(iconInfo->IconPath).section('\\', -1);
}

void SWObject::showInfo(SpellEntry const* spellInfo, quint8 num)
{
    if (!spellInfo)
        return;

    QWebView* browser = m_form->getBrowser(num);
    html.clear();

    QString sName(QString::fromUtf8(spellInfo->SpellName[Locale]));
    QString sDescription(QString::fromUtf8(spellInfo->Description[Locale]));
    QString sRank(QString::fromUtf8(spellInfo->Rank[Locale]));
    QString sToolTip(QString::fromUtf8(spellInfo->ToolTip[Locale]));
    QString sSpellFamilyFlags(QString("%0").arg(spellInfo->SpellFamilyFlags, 16, 16, QChar('0')));
    QString sAttributes(QString("%0").arg(spellInfo->Attributes, 8, 16, QChar('0')));
    QString sAttributesEx1(QString("%0").arg(spellInfo->AttributesEx1, 8, 16, QChar('0')));
    QString sAttributesEx2(QString("%0").arg(spellInfo->AttributesEx2, 8, 16, QChar('0')));
    QString sAttributesEx3(QString("%0").arg(spellInfo->AttributesEx3, 8, 16, QChar('0')));
    QString sAttributesEx4(QString("%0").arg(spellInfo->AttributesEx4, 8, 16, QChar('0')));
    QString sTargetMask(QString("%0").arg(spellInfo->Targets, 8, 16, QChar('0')));
    QString sCreatureTypeMask(QString("%0").arg(spellInfo->TargetCreatureType, 8, 16, QChar('0')));
    QString sFormMask(QString("%0").arg(spellInfo->Stances, 8, 16, QChar('0')));
    QString sIF(QString("%0").arg(spellInfo->InterruptFlags, 8, 16, QChar('0')));
    QString sAIF(QString("%0").arg(spellInfo->AuraInterruptFlags, 8, 16, QChar('0')));
    QString sCIF(QString("%0").arg(spellInfo->ChannelInterruptFlags, 8, 16, QChar('0')));

    html.append("<html>"
                "<head>"
                "<link rel='stylesheet' type='text/css' href='qrc:///SpellWork/Recources/styles.css'>"
                "</head>");

    html.append(QString("<body>"
                        "<div class='b-tooltip_icon'>"
	                    "<style>"
                        "div.icon { width: 68px; height: 68px; background: url(http://wow.zamimg.com/images/wow/icons/large/%0.jpg) no-repeat center; }"
                        "div.icon div { background: url(http://wow.zamimg.com/images/Icon/large/border/default.png) no-repeat center;}"
                        "div.icon div div:hover { background: url(http://wow.zamimg.com/images/Icon/large/hilite/default.png) no-repeat center; }"
                        "div.icon div div {width: 68px; height: 68px;}"
                        "</style>"
                        "<div class='icon'><div><div>"
                        "</div></div></div>"
                        "</div>").arg(getSpellIconName(spellInfo->SpellIconId).toLower()));

    html.append("<div class='b-tooltip_body'>");

    if (!sRank.isEmpty())
        sName.append(QString(" (%0)").arg(sRank));

    html.append(QString("<b>Id:</b> %0<br />")
        .arg(spellInfo->Id));

    html.append(QString("<b>Name:</b> %0<br />")
        .arg(sName));

    if (!sDescription.isEmpty())
        html.append(QString("<b>Description:</b> %0<br />").arg(getDescription(sDescription, spellInfo)));

    if (!sToolTip.isEmpty())
        html.append(QString("<b>ToolTip:</b> %0<br />").arg(getDescription(sToolTip, spellInfo)));

    html.append("</div>");

    quint32 parentId = getParentSpellId(spellInfo->Id);
    if (parentId)
    {
        if (SpellEntry const* parentInfo = sSpellStore.LookupEntry(parentId))
        {
            QString sParentName(QString::fromUtf8(parentInfo->SpellName[Locale]));
            QString sParentRank(QString::fromUtf8(parentInfo->Rank[Locale]));

            if (!sParentRank.isEmpty())
                sParentName.append(" (" + sParentRank + ")");

            html.append(QString("<div class='b-vlink'><b>Parent spell:</b> <a href='http://spellwork/%0' class='blue_link'>%0 - %1</a></div>")
                .arg(parentId)
                .arg(sParentName));
        }
    }

    html.append("<div class='b-box-title'>General info</div>"
                "<div class='b-box-body'>"
                "<div class='b-box'>"
                "<ul>");

     if (spellInfo->ModalNextSpell)
        html.append(QString("<li>ModalNextSpell: %0</li>")
            .arg(spellInfo->ModalNextSpell));

    html.append(QString("<li>Category = %0, SpellIconId = %1, ActiveIconId = %2, SpellVisual = (%3, %4)</li>")
        .arg(spellInfo->Category)
        .arg(spellInfo->SpellIconId)
        .arg(spellInfo->ActiveIconId)
        .arg(spellInfo->SpellVisual[0])
        .arg(spellInfo->SpellVisual[1]));

    html.append(QString("<li>SpellFamilyName = %0, SpellFamilyFlags = 0x%1</li>")
        .arg(m_form->getEnums()->getSpellFamilies()[spellInfo->SpellFamilyName])
        .arg(sSpellFamilyFlags.toUpper()));

    html.append(QString("<li>SpellSchool = %0 (%1)</li>")
        .arg(spellInfo->School)
        .arg(m_form->getEnums()->getSchools()[spellInfo->School]));

    html.append(QString("<li>DamageClass = %0 (%1)</li>")
        .arg(spellInfo->DamageClass)
        .arg(m_form->getEnums()->getDamageClasses()[spellInfo->DamageClass]));

    html.append(QString("<li>PreventionType = %0 (%1)</li>")
        .arg(spellInfo->PreventionType)
        .arg(m_form->getEnums()->getPreventionTypes()[spellInfo->PreventionType]));

    html.append("</ul></div></div>");

    if (spellInfo->Attributes || spellInfo->AttributesEx1 || spellInfo->AttributesEx2 ||
        spellInfo->AttributesEx3 || spellInfo->AttributesEx4)
    {
        html.append("<div class='b-box-title'>Attributes</div>"
                    "<div class='b-box-body'>"
                    "<div class='b-box'>"
                    "<ul>");

        if (spellInfo->Attributes)
            html.append(QString("<li>Attributes: 0x%0 (%1)</li>")
                .arg(sAttributes.toUpper())
                .arg(containAttributes(spellInfo, TYPE_ATTR)));

            html.append(QString("<li>AttributesEx1: 0x%0 (%1)</li>")
                .arg(sAttributesEx1.toUpper())
                .arg(containAttributes(spellInfo, TYPE_ATTR_EX1)));

        if (spellInfo->AttributesEx2)
            html.append(QString("<li>AttributesEx2: 0x%0 (%1)</li>")
                .arg(sAttributesEx2.toUpper())
                .arg(containAttributes(spellInfo, TYPE_ATTR_EX2)));

        if (spellInfo->AttributesEx3)
            html.append(QString("<li>AttributesEx3: 0x%0 (%1)</li>")
                .arg(sAttributesEx3.toUpper())
                .arg(containAttributes(spellInfo, TYPE_ATTR_EX3)));

        if (spellInfo->AttributesEx4)
            html.append(QString("<li>AttributesEx4: 0x%0 (%1)</li>")
                .arg(sAttributesEx4.toUpper())
                .arg(containAttributes(spellInfo, TYPE_ATTR_EX4)));

        html.append("</ul>"
	                "</div>"
                    "</div>");
    }

    html.append("<div class='b-box-title'>Advanced info</div>"
                "<div class='b-box-body'>"
                "<div class='b-box'>"
                "<ul>");

    if (spellInfo->Targets)
        html.append(QString("<li>Targets Mask = 0x%0 (%1)</li>")
            .arg(sTargetMask.toUpper())
            .arg(containAttributes(spellInfo, TYPE_TARGETS)));

    if (spellInfo->TargetCreatureType)
        html.append(QString("<li>Creature Type Mask = 0x%0 (%1)</li>")
            .arg(sCreatureTypeMask.toUpper())
            .arg(containAttributes(spellInfo, TYPE_CREATURE)));

    if (spellInfo->Stances)
        html.append(QString("<li>Stances: 0x%0 (%1)</li>")
            .arg(sFormMask.toUpper())
            .arg(containAttributes(spellInfo, TYPE_FORMS)));

    if (spellInfo->StancesNot)
        html.append(QString("<li>Stances not: 0x%0 (%1)</li>")
            .arg(sFormMask.toUpper())
            .arg(containAttributes(spellInfo, TYPE_FORMS_NOT)));

    appendSkillInfo(spellInfo, num);

    html.append(QString("<li>Spell Level = %0, BaseLevel %1, MaxLevel %2, MaxTargetLevel %3</li>")
        .arg(spellInfo->SpellLevel)
        .arg(spellInfo->BaseLevel)
        .arg(spellInfo->MaxLevel)
        .arg(spellInfo->MaxTargetLevel));

    if (spellInfo->EquippedItemClass != -1)
    {
        html.append(QString("<li>EquippedItemClass = %0 (%1)</li>")
            .arg(spellInfo->EquippedItemClass)
            .arg(m_form->getEnums()->getItemClasses()[spellInfo->EquippedItemClass]));

        if (spellInfo->EquippedItemSubClassMask)
        {
            html.append("<ul>");
            QString sItemSubClassMask(QString("%0").arg(spellInfo->EquippedItemSubClassMask, 8, 16, QChar('0')));
            switch (spellInfo->EquippedItemClass)
            {
                case 2: // WEAPON
                html.append(QString("<li>SubClass mask 0x%0 (%1)</li>")
                    .arg(sItemSubClassMask.toUpper())
                    .arg(containAttributes(spellInfo, TYPE_ITEM_WEAPON)));
                    break;
                case 4: // ARMOR
                html.append(QString("<li>SubClass mask 0x%0 (%1)</li>")
                    .arg(sItemSubClassMask.toUpper())
                    .arg(containAttributes(spellInfo, TYPE_ITEM_ARMOR)));
                    break;
                case 15: // MISC
                html.append(QString("<li>SubClass mask 0x%0 (%1)</li>")
                    .arg(sItemSubClassMask.toUpper())
                    .arg(containAttributes(spellInfo, TYPE_ITEM_MISC)));
                    break;
            }

            html.append("</ul>");
        }

        if (spellInfo->EquippedItemInventoryTypeMask)
        {
            QString sItemInventoryMask(QString("%0").arg(spellInfo->EquippedItemInventoryTypeMask, 8, 16, QChar('0')));
            html.append(QString("<li>InventoryType mask = 0x%0 (%1)</li>")
                .arg(sItemInventoryMask.toUpper())
                .arg(containAttributes(spellInfo, TYPE_ITEM_INVENTORY)));
        }
    }

    html.append(QString("<li>Category = %0</li>")
        .arg(spellInfo->Category));

    html.append(QString("<li>DispelType = %0 (%1)</li>")
        .arg(spellInfo->Dispel)
        .arg(m_form->getEnums()->getDispelTypes()[spellInfo->Dispel]));

    html.append(QString("<li>Mechanic = %0 (%1)</li>")
        .arg(spellInfo->Mechanic)
        .arg(m_form->getEnums()->getMechanics()[spellInfo->Mechanic]));

    appendRangeInfo(spellInfo, num);

    if (spellInfo->Speed)
        html.append(QString("<li>Speed: %0</li>")
            .arg(spellInfo->Speed, 0, 'f', 2));

    if (spellInfo->StackAmount)
        html.append(QString("<li>Stackable up to %0</li>")
            .arg(spellInfo->StackAmount));

    appendCastTimeInfo(spellInfo, num);

    if (spellInfo->RecoveryTime || spellInfo->CategoryRecoveryTime || spellInfo->StartRecoveryCategory)
    {
        html.append(QString("<li>RecoveryTime: %0 ms, CategoryRecoveryTime: %1 ms</li>")
            .arg(spellInfo->RecoveryTime)
            .arg(spellInfo->CategoryRecoveryTime));

        html.append(QString("<li>StartRecoveryCategory = %0, StartRecoveryTime = %1 ms</li>")
            .arg(spellInfo->StartRecoveryCategory)
            .arg(float(spellInfo->StartRecoveryTime), 0, 'f', 2));
    }

    appendDurationInfo(spellInfo, num);

    if (spellInfo->ManaCost || spellInfo->ManaCostPercentage)
    {
        if (spellInfo->ManaCost)
        {
            html.append(QString("<li>Power Type = %0, Cost %1")
                .arg(m_form->getEnums()->getPowers()[spellInfo->PowerType])
                .arg(spellInfo->ManaCost));
        }
        else if (spellInfo->ManaCostPercentage)
        {
            html.append(QString("<li>Power Type = %0, Cost %1% of base mana")
                .arg(m_form->getEnums()->getPowers()[spellInfo->PowerType])
                .arg(spellInfo->ManaCostPercentage));
        }

        if (spellInfo->ManaCostPerlevel)
            html.append(QString(" + lvl * %0")
                .arg(spellInfo->ManaCostPerlevel));

        if (spellInfo->ManaPerSecond)
            html.append(QString(" + %0 Per Second")
                .arg(spellInfo->ManaPerSecond));

        if (spellInfo->ManaPerSecondPerLevel)
            html.append(QString(" + lvl * %0")
                .arg(spellInfo->ManaPerSecondPerLevel));

        html.append("</li>");
    }

    html.append(QString("<li>Interrupt Flags: 0x%0, AuraIF 0x%1, ChannelIF 0x%2</li>")
        .arg(sIF.toUpper())
        .arg(sAIF.toUpper())
        .arg(sCIF.toUpper()));

    if (spellInfo->CasterAuraState)
        html.append(QString("<li>CasterAuraState = %0 (%1)</li>")
            .arg(spellInfo->CasterAuraState)
            .arg(m_form->getEnums()->getAuraStates()[spellInfo->CasterAuraState]));

    if (spellInfo->TargetAuraState)
        html.append(QString("<li>TargetAuraState = %0 (%1)</li>")
            .arg(spellInfo->TargetAuraState)
            .arg(m_form->getEnums()->getAuraStates()[spellInfo->TargetAuraState]));

    if (spellInfo->RequiresSpellFocus)
        html.append(QString("<li>Requires Spell Focus %0</li>")
            .arg(spellInfo->RequiresSpellFocus));

    if (spellInfo->ProcFlags)
    {
        QString sProcFlags(QString("%0").arg(spellInfo->ProcFlags, 8, 16, QChar('0')));
        html.append(QString("<li><b>Proc flag 0x%0, chance = %1, charges - %2</b></li>")
            .arg(sProcFlags.toUpper())
            .arg(spellInfo->ProcChance)
            .arg(spellInfo->ProcCharges));

        appendProcInfo(spellInfo, num);
    }
    else
    {
        html.append(QString("<li>Chance = %0, charges - %1</li>")
            .arg(spellInfo->ProcChance)
            .arg(spellInfo->ProcCharges));
    }

    html.append("</ul></div></div>");

    appendSpellEffectInfo(spellInfo, num);

    html.append("</body></html>");

    // Formatting for debug
    html.replace("><", ">\n<");

    browser->setHtml(html, QUrl(QString("http://spellwork/%0").arg(spellInfo->Id)));
    browser->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
}

void SWObject::appendRangeInfo(SpellEntry const* spellInfo, quint8 num)
{
    SpellRangeEntry const* range = sSpellRangeStore.LookupEntry(spellInfo->RangeIndex);
    if (range)
    {
        html.append(QString("<li>SpellRange (Id %0) \"%1\"</li>"
                            "<ul><li>MinRange = %2</li>"
                            "<li>MaxRange = %3</li></ul>")
            .arg(range->Id)
            .arg(QString::fromUtf8(range->Name[Locale]))
            .arg(range->MinRange)
            .arg(range->MaxRange));
    }
}

void SWObject::appendProcInfo(SpellEntry const* spellInfo, quint8 num)
{
    quint8 i = 0;
    quint64 proc = spellInfo->ProcFlags;

    html.append("<ul>");
    while (proc != 0)
    {
        if ((proc & 1) != 0)
            html.append(QString("<li>%0</li>").arg(ProcFlagDesc[i]));
        ++i;
        proc >>= 1;
    }
    html.append("</ul>");
}

void SWObject::appendSpellEffectInfo(SpellEntry const* spellInfo, quint8 num)
{
    html.append("<div class='b-box-title'>Effects</div>"
                "<div class='b-box-body'>"
                "<div class='b-box'>");

    for (quint8 eff = EFFECT_INDEX_0; eff < MAX_EFFECT_INDEX; ++eff)
    {
        if (!spellInfo->Effect[eff])
        {
            html.append(QString("<div class='b-effect_name'>Effect %0:</div>"
                                "<ul>"
		                        "<li>NO EFFECT</li>"
		                        "</ul>").arg(eff));
        }
        else
        {
            QString _BasePoints(QString("<li>BasePoints = %0").arg(spellInfo->EffectBasePoints[eff] + 1));

            QString _RealPoints;
            if (spellInfo->EffectRealPointsPerLevel[eff] != 0)
                _RealPoints = QString(" + Level * %0").arg(spellInfo->EffectRealPointsPerLevel[eff], 0, 'f', 2);

            QString _DieSides;
            if (1 < spellInfo->EffectDieSides[eff])
            {
                if (spellInfo->EffectRealPointsPerLevel[eff] != 0)
                    _DieSides = QString(" to %0 + lvl * %1")
                        .arg(spellInfo->EffectBasePoints[eff] + 1 + spellInfo->EffectDieSides[eff])
                        .arg(spellInfo->EffectRealPointsPerLevel[eff], 0, 'f', 2);
                else
                    _DieSides = QString(" to %0").arg(spellInfo->EffectBasePoints[eff] + 1 + spellInfo->EffectDieSides[eff]);
            }

            QString _PointsPerCombo;
            if (spellInfo->EffectPointsPerComboPoint[eff] != 0)
                _PointsPerCombo = QString(" + combo * %0").arg(spellInfo->EffectPointsPerComboPoint[eff], 0, 'f', 2);

            QString _DamageMultiplier;
            if (spellInfo->DamageMultiplier[eff] != 1.0f)
                _DamageMultiplier = QString(" * %0").arg(spellInfo->DamageMultiplier[eff], 0, 'f', 2);

            QString _Multiple;
            if (spellInfo->EffectMultipleValue[eff] != 0)
                _Multiple = QString(", Multiple = %0").arg(spellInfo->EffectMultipleValue[eff], 0, 'f', 2);

            QString _Result = _BasePoints + _RealPoints + _DieSides + _PointsPerCombo + _DamageMultiplier + _Multiple + "</li>";

            html.append(QString("<div class='b-effect_name'>Effect %0:</div>"
                                "<ul>").arg(eff));

            html.append(QString("<li>Id: %0 (%1)</li>")
                .arg(spellInfo->Effect[eff])
                .arg(m_form->getEnums()->getSpellEffects()[spellInfo->Effect[eff]]));

            html.append(_Result);

            html.append(QString("<li>Targets (%0, %1) (%2, %3)</li>")
                .arg(spellInfo->EffectImplicitTargetA[eff])
                .arg(spellInfo->EffectImplicitTargetB[eff])
                .arg(m_form->getEnums()->getTargets()[spellInfo->EffectImplicitTargetA[eff]])
                .arg(m_form->getEnums()->getTargets()[spellInfo->EffectImplicitTargetB[eff]]));

            appendAuraInfo(spellInfo, eff, num);

            appendRadiusInfo(spellInfo, eff, num);

            appendTriggerInfo(spellInfo, eff, num);

            if (spellInfo->EffectChainTarget[eff] != 0)
                html.append(QString("<li>EffectChainTarget = %0</li>").arg(spellInfo->EffectChainTarget[eff]));

            if (spellInfo->EffectMechanic[eff] != 0)
            {
                html.append(QString("<li>Effect Mechanic = %0 (%1)</li>")
                    .arg(spellInfo->EffectMechanic[eff])
                    .arg(m_form->getEnums()->getMechanics()[spellInfo->EffectMechanic[eff]]));
            }

            if (spellInfo->EffectItemType[eff] != 0)
            {
                QString sEffectItemType(QString("%0").arg(spellInfo->EffectItemType[eff], 8, 16, QChar('0')));
                html.append(QString("<li>EffectItemType = 0x%0</li>").arg(sEffectItemType.toUpper()));

                if (spellInfo->Effect[eff] == 6)
                {
                    html.append("<ul>");
                    for (quint32 i = 0; i < sSpellStore.GetNumRows(); ++i)
                    {
                        SpellEntry const* t_spellInfo = sSpellStore.LookupEntry(i);
                        if (t_spellInfo)
                        {
                            bool hasSkill = false;
                            if ((t_spellInfo->SpellFamilyName == spellInfo->SpellFamilyName) &&
                                (t_spellInfo->SpellFamilyFlags & spellInfo->EffectItemType[eff]))
                            {
                                QString sName(QString::fromUtf8(t_spellInfo->SpellName[Locale]));
                                QString sRank(QString::fromUtf8(t_spellInfo->Rank[Locale]));

                                if (!sRank.isEmpty())
                                    sName.append(" (" + sRank + ")");

                                for (quint32 sk = 0; sk < sSkillLineAbilityStore.GetNumRows(); ++sk)
                                {
                                    SkillLineAbilityEntry const* skillInfo = sSkillLineAbilityStore.LookupEntry(sk);
                                    if (skillInfo && skillInfo->SpellId == t_spellInfo->Id && skillInfo->SkillId > 0)
                                    {
                                        hasSkill = true;
                                        html.append(QString("<li><a href='http://spellwork/%1' class='blue_link'>+ %1 - %2</a></li>")
                                            .arg(t_spellInfo->Id)
                                            .arg(sName));
                                        break;
                                    }
                                }

                                if (!hasSkill)
                                {
                                    html.append(QString("<li><a href='http://spellwork/%1' class='red_link'>- %1 - %2</a></li>")
                                        .arg(t_spellInfo->Id)
                                        .arg(sName));
                                }
                            }
                        }
                    }
                    html.append("</ul>");
                }
            }
            html.append("</ul>");
        }
    }
    html.append("</div></div>");
}

void SWObject::appendTriggerInfo(SpellEntry const* spellInfo, quint8 index, quint8 num)
{
    quint32 trigger = spellInfo->EffectTriggerSpell[index];
    if (trigger != 0)
    {
        SpellEntry const* triggerSpell = sSpellStore.LookupEntry(trigger);
        if (triggerSpell)
        {
            QString sName(QString::fromUtf8(triggerSpell->SpellName[Locale]));
            QString sRank(QString::fromUtf8(triggerSpell->Rank[Locale]));

            if (!sRank.isEmpty())
                sName.append(" (" + sRank + ")");

            html.append(QString("<li><b>Trigger spell:</b> <a href='http://spellwork/%0' class='blue_link'>%0 - %1</a>. Chance = %2</li>")
                .arg(trigger)
                .arg(sName)
                .arg(triggerSpell->ProcChance));

                QString sDescription(QString::fromUtf8(triggerSpell->Description[Locale]));
                QString sTooltip(QString::fromUtf8(triggerSpell->ToolTip[Locale]));

                html.append("<ul>");

                if (!sDescription.isEmpty())
                    html.append(QString("<li>Description: %0</li>").arg(getDescription(sDescription, triggerSpell)));

                if (!sTooltip.isEmpty())
                    html.append(QString("<li>ToolTip: %0</li>").arg(getDescription(sTooltip, triggerSpell)));

                if (triggerSpell->ProcFlags != 0)
                {
                    html.append(QString("<li>Charges - %0</li>").arg(triggerSpell->ProcCharges));
                    html.append("<hr style='margin: 0 25px;'>");
                    appendProcInfo(triggerSpell, num);
                }

                html.append("</ul>");
        }
        else
        {
            html.append(QString("<li>Trigger spell: %0 Not found</li>").arg(trigger));
        }
    }
}

void SWObject::appendRadiusInfo(SpellEntry const* spellInfo, quint8 index, quint8 num)
{
    quint16 rIndex = spellInfo->EffectRadiusIndex[index];
    if (rIndex != 0)
    {
        SpellRadiusEntry const* spellRadius = sSpellRadiusStore.LookupEntry(rIndex);
        if (spellRadius)
        {
            html.append(QString("<li>Radius (Id %0) %1</li>")
                .arg(rIndex)
                .arg(spellRadius->Radius, 0, 'f', 2));
        }
        else
            html.append(QString("<li>Radius (Id %0) Not found</li>").arg(rIndex));
    }
}

void SWObject::appendAuraInfo(SpellEntry const* spellInfo, quint8 index, quint8 num)
{
    QString sAura(m_form->getEnums()->getSpellAuras()[spellInfo->EffectApplyAuraName[index]]);
    quint32 misc = spellInfo->EffectMiscValue[index];

    if (spellInfo->EffectApplyAuraName[index] == 0)
    {
        if (spellInfo->EffectMiscValue[index] != 0)
            html.append(QString("<li>EffectMiscValue = %0</li>").arg(spellInfo->EffectMiscValue[index]));

        if (spellInfo->EffectAmplitude[index] != 0)
            html.append(QString("<li>EffectAmplitude = %0</li>").arg(spellInfo->EffectAmplitude[index]));

        return;
    }

    QString _BaseAuraInfo;
    _BaseAuraInfo = QString("<li>Aura Id %0 (%1), value = %2, misc = %3 ")
        .arg(spellInfo->EffectApplyAuraName[index])
        .arg(sAura)
        .arg(spellInfo->EffectBasePoints[index] + 1)
        .arg(misc);

    QString _SpecialAuraInfo;
    switch (spellInfo->EffectApplyAuraName[index])
    {
        case 29:
            _SpecialAuraInfo = QString("(%0").arg(m_form->getEnums()->getUnitMods()[misc]);
            break;
        case 107:
        case 108:
            _SpecialAuraInfo = QString("(%0").arg(m_form->getEnums()->getSpellMods()[misc]);
            break;
        // todo: more case
        default:
            _SpecialAuraInfo = QString("(%0").arg(misc);
            break;
    }

    QString _Periodic = QString("), periodic = %0").arg(spellInfo->EffectAmplitude[index]);
    QString _Result = _BaseAuraInfo + _SpecialAuraInfo + _Periodic;
    html.append(_Result + "</li>");
}

QString SWObject::containAttributes(SpellEntry const* spellInfo, AttrType attr, quint8 index)
{
    QString str("");
    switch (attr)
    {
        case TYPE_ATTR:
        {
            EnumIterator itr(m_form->getEnums()->getAttributes());
            while (itr.hasNext())
            {
                itr.next();
                if (spellInfo->Attributes & itr.key())
                {
                    QString tstr(QString("%0, ").arg(itr.value()));
                    str += tstr;
                }
            }
            if (!str.isEmpty())
                str.chop(2);
            return str;
        }
        break;
        case TYPE_ATTR_EX1:
        {
            EnumIterator itr(m_form->getEnums()->getAttributesEx1());
            while (itr.hasNext())
            {
                itr.next();
                if (spellInfo->AttributesEx1 & itr.key())
                {
                    QString tstr(QString("%0, ").arg(itr.value()));
                    str += tstr;
                }
            }
            if (!str.isEmpty())
                str.chop(2);
            return str;
        }
        break;
        case TYPE_ATTR_EX2:
        {
            EnumIterator itr(m_form->getEnums()->getAttributesEx2());
            while (itr.hasNext())
            {
                itr.next();
                if (spellInfo->AttributesEx2 & itr.key())
                {
                    QString tstr(QString("%0, ").arg(itr.value()));
                    str += tstr;
                }
            }
            if (!str.isEmpty())
                str.chop(2);
            return str;
        }
        break;
        case TYPE_ATTR_EX3:
        {
            EnumIterator itr(m_form->getEnums()->getAttributesEx3());
            while (itr.hasNext())
            {
                itr.next();
                if (spellInfo->AttributesEx3 & itr.key())
                {
                    QString tstr(QString("%0, ").arg(itr.value()));
                    str += tstr;
                }
            }
            if (!str.isEmpty())
                str.chop(2);
            return str;
        }
        break;
        case TYPE_ATTR_EX4:
        {
            EnumIterator itr(m_form->getEnums()->getAttributesEx4());
            while (itr.hasNext())
            {
                itr.next();
                if (spellInfo->AttributesEx4 & itr.key())
                {
                    QString tstr(QString("%0, ").arg(itr.value()));
                    str += tstr;
                }
            }
            if (!str.isEmpty())
                str.chop(2);
            return str;
        }
        break;
        case TYPE_TARGETS:
        {
            EnumIterator itr(m_form->getEnums()->getTargetFlags());
            while (itr.hasNext())
            {
                itr.next();
                if (spellInfo->Targets & itr.key())
                {
                    QString tstr(QString("%0, ").arg(itr.value()));
                    str += tstr;
                }
            }
            if (!str.isEmpty())
                str.chop(2);
            return str;
        }
        break;
        case TYPE_CREATURE:
        {
            EnumIterator itr(m_form->getEnums()->getCreatureTypes());
            while (itr.hasNext())
            {
                itr.next();
                if (spellInfo->TargetCreatureType & itr.key())
                {
                    QString tstr(QString("%0, ").arg(itr.value()));
                    str += tstr;
                }
            }
            if (!str.isEmpty())
                str.chop(2);
            return str;
        }
        break;
        case TYPE_FORMS:
        {
            EnumIterator itr(m_form->getEnums()->getShapeshiftForms());
            while (itr.hasNext())
            {
                itr.next();
                if (spellInfo->Stances & itr.key())
                {
                    QString tstr(QString("%0, ").arg(itr.value()));
                    str += tstr;
                }
            }
            if (!str.isEmpty())
                str.chop(2);
            return str;
        }
        break;
        case TYPE_FORMS_NOT:
        {
            EnumIterator itr(m_form->getEnums()->getShapeshiftForms());
            while (itr.hasNext())
            {
                itr.next();
                if (spellInfo->StancesNot & itr.key())
                {
                    QString tstr(QString("%0, ").arg(itr.value()));
                    str += tstr;
                }
            }
            if (!str.isEmpty())
                str.chop(2);
            return str;
        }
        break;
        case TYPE_ITEM_WEAPON:
        {
            EnumIterator itr(m_form->getEnums()->getItemSubClassWeapons());
            while (itr.hasNext())
            {
                itr.next();
                if (spellInfo->EquippedItemSubClassMask & itr.key())
                {
                    QString tstr(QString("%0, ").arg(itr.value()));
                    str += tstr;
                }
            }
            if (!str.isEmpty())
                str.chop(2);
            return str;
        }
        break;
        case TYPE_ITEM_ARMOR:
        {
            EnumIterator itr(m_form->getEnums()->getItemSubClassArmors());
            while (itr.hasNext())
            {
                itr.next();
                if (spellInfo->EquippedItemSubClassMask & itr.key())
                {
                    QString tstr(QString("%0, ").arg(itr.value()));
                    str += tstr;
                }
            }
            if (!str.isEmpty())
                str.chop(2);
            return str;
        }
        break;
        case TYPE_ITEM_MISC:
        {
            EnumIterator itr(m_form->getEnums()->getItemSubClassMiscs());
            while (itr.hasNext())
            {
                itr.next();
                if (spellInfo->EquippedItemSubClassMask & itr.key())
                {
                    QString tstr(QString("%0, ").arg(itr.value()));
                    str += tstr;
                }
            }
            if (!str.isEmpty())
                str.chop(2);
            return str;
        }
        break;
        case TYPE_ITEM_INVENTORY:
        {
            EnumIterator itr(m_form->getEnums()->getInventoryTypes());
            while (itr.hasNext())
            {
                itr.next();
                if (spellInfo->EquippedItemInventoryTypeMask & itr.key())
                {
                    QString tstr(QString("%0, ").arg(itr.value()));
                    str += tstr;
                }
            }
            if (!str.isEmpty())
                str.chop(2);
            return str;
        }
        break;
        default:
        break;
    }
    return str;
}

void SWObject::appendSkillInfo(SpellEntry const* spellInfo, quint8 num)
{
    for (quint32 i = 0; i < sSkillLineAbilityStore.GetNumRows(); ++i)
    {
        SkillLineAbilityEntry const* skillInfo = sSkillLineAbilityStore.LookupEntry(i);
        if (skillInfo && skillInfo->SpellId == spellInfo->Id)
        {
            SkillLineEntry const* skill = sSkillLineStore.LookupEntry(skillInfo->SkillId);
            html.append(QString("<li>Skill (Id %0) \"%1\"</li>"
                           "<ul><li>ReqSkillValue = %2</li>"
                           "<li>Forward Spell = %3</li>"
                           "<li>MinMaxValue (%4, %5)</li>"
                           "<li>CharacterPoints (%6, %7)</li></ul>")
                .arg(skill->Id)
                .arg(QString::fromUtf8(skill->Name[Locale]))
                .arg(skillInfo->ReqSkillValue)
                .arg(skillInfo->ForwardSpellId)
                .arg(skillInfo->MinValue)
                .arg(skillInfo->MaxValue)
                .arg(skillInfo->CharPoints[0])
                .arg(skillInfo->CharPoints[1]));
            break;
        }
    }
}

void SWObject::appendCastTimeInfo(SpellEntry const* spellInfo, quint8 num)
{
    SpellCastTimesEntry const* castInfo = sSpellCastTimesStore.LookupEntry(spellInfo->CastingTimeIndex);
    if (castInfo)
    {
        html.append(QString("<li>CastingTime (Id %0) = %1</li>")
            .arg(castInfo->Id)
            .arg(float(castInfo->CastTime) / 1000, 0, 'f', 2));
    }
}

void SWObject::appendDurationInfo(SpellEntry const* spellInfo, quint8 num)
{
    SpellDurationEntry const* durationInfo = sSpellDurationStore.LookupEntry(spellInfo->DurationIndex);
    if (durationInfo)
    {
        html.append(QString("<li>Duration: ID (%0)  %1, %2, %3</li>")
            .arg(durationInfo->Id)
            .arg(durationInfo->Duration[0])
            .arg(durationInfo->Duration[1])
            .arg(durationInfo->Duration[2]));
    }
}

void SWObject::compare()
{
    QStringList list1 = m_form->webView2->page()->mainFrame()->toHtml().split("\n");
    QStringList list2 = m_form->webView3->page()->mainFrame()->toHtml().split("\n");

    QString html2;
    html.clear();
    html2.clear();

    QRegExp rx("(<[A-Za-z_0-9]*>)+([A-Za-z_0-9-!\"#$%&'()*+,./:;=?@[\\]_`{|}~\\s]*)+(</[A-Za-z_0-9]*>)");

    for (QStringList::iterator itr1 = list1.begin(); itr1 != list1.end(); ++itr1)
    {
        bool yes = false;

        for (QStringList::iterator itr2 = list2.begin(); itr2 != list2.end(); ++itr2)
        {
            if ((*itr1) == (*itr2))
            {
                yes = true;
                break;
            }
        }

        if (yes)
        {
            if (rx.indexIn((*itr1)) != -1)
            {
                QString r1 = rx.cap(0); // Full
                QString r2 = rx.cap(1); // <xxx>
                QString r3 = rx.cap(2); // <>xxx</>
                QString r4 = rx.cap(3); // </xxx>

                if (r2 == "<b>")
                    html.append(QString("<span style='background-color: cyan'>%0</span>").arg((*itr1)));
                else if (r2 == "<style>")
                {
                    html.append((*itr1));
                }
                else
                {
                    r3 = QString("<span style='background-color: cyan'>%0</span>").arg(r3);
                    r3.prepend(r2);
                    r3.append(r4);
                    html.append(r3);
                }
            }
            else
                html.append((*itr1));
        }
        else
        {
            if (rx.indexIn((*itr1)) != -1)
            {
                QString r1 = rx.cap(0); // Full
                QString r2 = rx.cap(1); // <xxx>
                QString r3 = rx.cap(2); // <>xxx</>
                QString r4 = rx.cap(3); // </xxx>

                if (r2 == "<b>")
                    html.append(QString("<span style='background-color: salmon'>%0</span>").arg((*itr1)));
                else if (r2 == "<style>")
                {
                    html.append((*itr1));
                }
                else
                {
                    r3 = QString("<span style='background-color: salmon'>%0</span>").arg(r3);
                    r3.prepend(r2);
                    r3.append(r4);
                    html.append(r3);
                }
            }
            else
                html.append((*itr1));
        }
    }

    // second
    for (QStringList::iterator itr2 = list2.begin(); itr2 != list2.end(); ++itr2)
    {
        bool yes = false;

        for (QStringList::iterator itr1 = list1.begin(); itr1 != list1.end(); ++itr1)
        {
            if ((*itr2) == (*itr1))
            {
                yes = true;
                break;
            }
        }

        if (yes)
        {
            if (rx.indexIn((*itr2)) != -1)
            {
                QString r1 = rx.cap(0); // Full
                QString r2 = rx.cap(1); // <xxx>
                QString r3 = rx.cap(2); // <>xxx</>
                QString r4 = rx.cap(3); // </xxx>

                if (r2 == "<b>")
                    html2.append(QString("<span style='background-color: cyan'>%0</span>").arg((*itr2)));
                else if (r2 == "<style>")
                {
                    html2.append((*itr2));
                }
                else
                {
                    r3 = QString("<span style='background-color: cyan'>%0</span>").arg(r3);
                    r3.prepend(r2);
                    r3.append(r4);
                    html2.append(r3);
                }
            }
            else
                html2.append((*itr2));
        }
        else
        {
            if (rx.indexIn((*itr2)) != -1)
            {
                QString r1 = rx.cap(0); // Full
                QString r2 = rx.cap(1); // <xxx>
                QString r3 = rx.cap(2); // <>xxx</>
                QString r4 = rx.cap(3); // </xxx>

                if (r2 == "<b>")
                    html2.append(QString("<span style='background-color: salmon'>%0</span>").arg((*itr2)));
                else if (r2 == "<style>")
                {
                    html2.append((*itr2));
                }
                else
                {
                    r3 = QString("<span style='background-color: salmon'>%0</span>").arg(r3);
                    r3.prepend(r2);
                    r3.append(r4);
                    html2.append(r3);
                }
            }
            else
                html2.append((*itr2));
        }
    }

    m_form->webView2->setHtml(html, m_form->webView2->url());
    m_form->webView3->setHtml(html2, m_form->webView3->url());
}

quint64 Converter::getULongLong(QString value)
{
    bool ok;
    quint64 dec = value.toULongLong(&ok, 10);
    return ok ? dec : value.toULongLong(&ok, 16);
}

qint64 Converter::getLongLong(QString value)
{
    bool ok;
    qint64 dec = value.toLongLong(&ok, 10);
    return ok ? dec : value.toLongLong(&ok, 16);
}

quint32 Converter::getULong(QString value)
{
    bool ok;
    quint32 dec = value.toULong(&ok, 10);
    return ok ? dec : value.toULong(&ok, 16);
}

qint32 Converter::getLong(QString value)
{
    bool ok;
    qint32 dec = value.toLong(&ok, 10);;
    return ok ? dec : value.toLong(&ok, 16);
}

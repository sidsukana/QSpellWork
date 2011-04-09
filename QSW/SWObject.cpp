#include "SWObject.h"
#include "QtGui/QStandardItemModel"

SWObject::SWObject(SWForm *form)
    : m_form(form), useRegExp(false), m_type(0), locale(0)
{
    for (quint8 i = 0; i < MAX_THREAD; i++)
        ThreadSemaphore[i] = false;

    mo = Enums::staticMetaObject;

    LoadDBCStores();
}

void SWObject::ThreadBegin(quint8 id)
{
    if (!ThreadExist(id))
    {
        TObject *thread = new TObject(id, this);
        thread->start();
    }
}

float GetRadius(SpellEntry const *spellInfo, quint8 effIndex)
{
    SpellRadiusEntry const *spellRadius = sSpellRadiusStore.LookupEntry(spellInfo->EffectRadiusIndex[effIndex]);
    if (spellRadius)
        return spellRadius->Radius;

    return 0.0f;
}

quint32 GetDuration(SpellEntry const *spellInfo)
{
    SpellDurationEntry const *durationInfo = sSpellDurationStore.LookupEntry(spellInfo->DurationIndex);
    if (durationInfo)
        return quint32(durationInfo->Duration[0] / 1000);

    return 1;
}

quint32 GetRealDuration(SpellEntry const *spellInfo, quint8 effIndex)
{
    return quint32(GetDuration(spellInfo) / quint32(spellInfo->EffectAmplitude[effIndex] / 1000));
}

void RegExpU(SpellEntry const *spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(4).isEmpty())
    {
        SpellEntry const *tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
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

void RegExpH(SpellEntry const *spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(4).isEmpty())
    {
        SpellEntry const *tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
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

void RegExpV(SpellEntry const *spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(4).isEmpty())
    {
        SpellEntry const *tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
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

void RegExpQ(SpellEntry const *spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(3).isEmpty())
    {
        if (!rx.cap(4).isEmpty())
        {
            SpellEntry const *tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
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
        SpellEntry const *tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
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

void RegExpI(SpellEntry const *spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(4).isEmpty())
    {
        SpellEntry const *tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
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

void RegExpB(SpellEntry const *spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(3).isEmpty())
    {
        if (!rx.cap(4).isEmpty())
        {
            SpellEntry const *tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
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
        SpellEntry const *tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
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

void RegExpM(SpellEntry const *spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(3).isEmpty())
    {
        if (!rx.cap(4).isEmpty())
        {
            SpellEntry const *tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
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
        SpellEntry const *tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
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

void RegExpA(SpellEntry const *spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(3).isEmpty())
    {
        if (!rx.cap(4).isEmpty())
        {
            SpellEntry const *tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
            if (tSpell)
            {
                if (rx.cap(2) == QString("/"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(quint32(GetRadius(tSpell, rx.cap(6).toInt()-1) / rx.cap(2).toInt())));
                }
                else if (rx.cap(2) == QString("*"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(quint32(GetRadius(tSpell, rx.cap(6).toInt()-1) * rx.cap(2).toInt())));
                }
            }
        }
        else
        {
            if (rx.cap(2) == QString("/"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(quint32(GetRadius(spellInfo, rx.cap(5).toInt()-1) / rx.cap(2).toInt())));
            }
            else if (rx.cap(2) == QString("*"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(quint32(GetRadius(spellInfo, rx.cap(5).toInt()-1) * rx.cap(2).toInt())));
            }
        }
    }
    else if (!rx.cap(4).isEmpty())
    {
        SpellEntry const *tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
        if (tSpell)
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(GetRadius(tSpell, rx.cap(6).toInt()-1)));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(GetRadius(spellInfo, rx.cap(6).toInt()-1)));
    }
}

void RegExpD(SpellEntry const *spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(3).isEmpty())
    {
        if (!rx.cap(4).isEmpty())
        {
            SpellEntry const *tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
            if (tSpell)
            {
                if (rx.cap(2) == QString("/"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(quint32(GetDuration(tSpell) / rx.cap(3).toInt())));
                }
                else if (rx.cap(2) == QString("*"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(quint32(GetDuration(tSpell) * rx.cap(3).toInt())));
                }
            }
        }
        else
        {
            if (rx.cap(2) == QString("/"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(quint32(GetDuration(spellInfo) / rx.cap(3).toInt())));
            }
            else if (rx.cap(2) == QString("*"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(quint32(GetDuration(spellInfo) * rx.cap(3).toInt())));
            }
        }
    }
    else if (!rx.cap(4).isEmpty())
    {
        SpellEntry const *tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
        if (tSpell)
        {
            str.replace(rx.cap(0), QString("%0 seconds")
                .arg(GetDuration(tSpell)));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0 seconds")
            .arg(GetDuration(spellInfo)));
    }
}

void RegExpO(SpellEntry const *spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(3).isEmpty())
    {
        if (!rx.cap(4).isEmpty())
        {
            SpellEntry const *tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
            if (tSpell)
            {
                if (rx.cap(2) == QString("/"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(quint32((GetRealDuration(tSpell, rx.cap(6).toInt()-1) * (tSpell->EffectBasePoints[rx.cap(6).toInt()-1] + 1)) / rx.cap(3).toInt())));
                }
                else if(rx.cap(2) == QString("*"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(quint32((GetRealDuration(tSpell, rx.cap(6).toInt()-1) * (tSpell->EffectBasePoints[rx.cap(6).toInt()-1] + 1)) * rx.cap(3).toInt())));
                }
            }
        }
        else
        {
            if (rx.cap(2) == QString("/"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(quint32((GetRealDuration(spellInfo, rx.cap(6).toInt()-1) * (spellInfo->EffectBasePoints[rx.cap(6).toInt()-1] + 1)) / rx.cap(3).toInt())));
            }
            else if (rx.cap(2) == QString("*"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(quint32((GetRealDuration(spellInfo, rx.cap(6).toInt()-1) * (spellInfo->EffectBasePoints[rx.cap(6).toInt()-1] + 1)) * rx.cap(3).toInt())));
            }
        }
    }
    else if (!rx.cap(4).isEmpty())
    {
        SpellEntry const *tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
        if (tSpell)
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(GetRealDuration(tSpell, rx.cap(6).toInt()-1) * (tSpell->EffectBasePoints[rx.cap(6).toInt()-1] + 1)));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(GetRealDuration(spellInfo, rx.cap(6).toInt()-1) * (spellInfo->EffectBasePoints[rx.cap(6).toInt()-1] + 1)));
    }
}

void RegExpS(SpellEntry const *spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(3).isEmpty())
    {
        if (!rx.cap(4).isEmpty())
        {
            SpellEntry const *tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
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
        SpellEntry const *tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
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

void RegExpT(SpellEntry const *spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(3).isEmpty())
    {
        if (!rx.cap(4).isEmpty())
        {
            SpellEntry const *tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
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
        SpellEntry const *tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
        if (tSpell)
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(quint32(tSpell->EffectAmplitude[rx.cap(6).toInt()-1] / 1000)));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(quint32(spellInfo->EffectAmplitude[rx.cap(6).toInt()-1] / 1000)));
    }
}

void RegExpN(SpellEntry const *spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(4).isEmpty())
    {
        SpellEntry const *tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
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

void RegExpX(SpellEntry const *spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(4).isEmpty())
    {
        SpellEntry const *tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
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

QString SWObject::GetDescription(QString str, SpellEntry const *spellInfo)
{
    if (!IsRegExp())
        return str;

    QRegExp rx("\\$+(([/,*])?([0-9]*);)?([d+\\;)(\\d*)?([1-9]*)([A-z])([1-3]*)(([A-z, ]*)\\:([A-z, ]*)\\;)?");
    while (str.contains(rx))
    {
        if (rx.indexIn(str) != -1)
        {
            QChar symbol = rx.cap(5)[0].toLower();
            switch (symbol.toAscii())
            {
                case 'u':
                    RegExpU(spellInfo, rx, str);
                break;
                case 'h':
                    RegExpH(spellInfo, rx, str);
                break;
                case 'z':
                    str.replace(rx.cap(0), QString("[Home]"));
                break;
                case 'v':
                    RegExpV(spellInfo, rx, str);
                break;
                case 'q':
                    RegExpQ(spellInfo, rx, str);
                break;
                case 'i':
                    RegExpI(spellInfo, rx, str);
                break;
                case 'b':
                    RegExpB(spellInfo, rx, str);
                break;
                case 'm':
                    RegExpM(spellInfo, rx, str);
                break;
                case 'a':
                    RegExpA(spellInfo, rx, str);
                break;
                case 'd':
                    RegExpD(spellInfo, rx, str);
                break;
                case 'o':
                    RegExpO(spellInfo, rx, str);
                break;
                case 's':
                    RegExpS(spellInfo, rx, str);
                break;
                case 't':
                    RegExpT(spellInfo, rx, str);
                break;
                case 'l':
                    str.replace(rx.cap(0), rx.cap(9));
                break;
                case 'g':
                    str.replace(rx.cap(0), rx.cap(8));
                break;
                case 'n':
                    RegExpN(spellInfo, rx, str);
                break;
                case 'x':
                    RegExpX(spellInfo, rx, str);
                break;
                default:
                    return str;
            }
        }
    }
    return str;
}

void SWObject::ShowInfo(SpellEntry const *spellInfo, quint8 num)
{
    if (!spellInfo)
        return;

    QTextBrowser *browser = m_form->GetBrowser(num);
    browser->clear();
    QTextCursor cur = browser->textCursor();
    cur.clearSelection();
    browser->setTextCursor(cur);

    QString line("==================================================");

    QString sName(QString::fromUtf8(spellInfo->SpellName[locale]));
    QString sDescription(QString::fromUtf8(spellInfo->Description[locale]));
    QString sRank(QString::fromUtf8(spellInfo->Rank[locale]));
    QString sToolTip(QString::fromUtf8(spellInfo->ToolTip[locale]));
    QString sSpellFamilyFlags(QString("%0").arg(spellInfo->SpellFamilyFlags, 16, 16, QChar('0')));
    QString sAttributes(QString("%0").arg(spellInfo->Attributes, 8, 16, QChar('0')));
    QString sAttributesEx(QString("%0").arg(spellInfo->AttributesEx, 8, 16, QChar('0')));
    QString sAttributesEx2(QString("%0").arg(spellInfo->AttributesEx2, 8, 16, QChar('0')));
    QString sAttributesEx3(QString("%0").arg(spellInfo->AttributesEx3, 8, 16, QChar('0')));
    QString sAttributesEx4(QString("%0").arg(spellInfo->AttributesEx4, 8, 16, QChar('0')));
    QString sAttributesEx5(QString("%0").arg(spellInfo->AttributesEx5, 8, 16, QChar('0')));
    QString sAttributesEx6(QString("%0").arg(spellInfo->AttributesEx6, 8, 16, QChar('0')));
    QString sTargetMask(QString("%0").arg(spellInfo->Targets, 8, 16, QChar('0')));
    QString sCreatureTypeMask(QString("%0").arg(spellInfo->TargetCreatureType, 8, 16, QChar('0')));
    QString sFormMask(QString("%0").arg(spellInfo->Stances, 8, 16, QChar('0')));
    QString sIF(QString("%0").arg(spellInfo->InterruptFlags, 8, 16, QChar('0')));
    QString sAIF(QString("%0").arg(spellInfo->AuraInterruptFlags, 8, 16, QChar('0')));
    QString sCIF(QString("%0").arg(spellInfo->ChannelInterruptFlags, 8, 16, QChar('0')));

    browser->append(QString("<b>ID:</b> %0").arg(spellInfo->Id));

    if (sRank.isEmpty())
        browser->append(QString("<b>Name:</b> %0").arg(sName));
    else
        browser->append(QString("<b>Name:</b> %0 (%1)")
            .arg(sName)
            .arg(sRank));

    if (!sDescription.isEmpty())
        browser->append(QString("<b>Description:</b> %0").arg(GetDescription(sDescription, spellInfo)));

    if (!sToolTip.isEmpty())
        browser->append(QString("<b>ToolTip:</b> %0").arg(GetDescription(sToolTip, spellInfo)));

    browser->append(line);

     if (spellInfo->ModalNextSpell)
        browser->append(QString("ModalNextSpell: %0").arg(spellInfo->ModalNextSpell));

    browser->append(QString("Category = %0, SpellIconID = %1, ActiveIconID = %2, SpellVisual = (%3 ,%4)")
        .arg(spellInfo->Category)
        .arg(spellInfo->SpellIconID)
        .arg(spellInfo->ActiveIconID)
        .arg(spellInfo->SpellVisual[0])
        .arg(spellInfo->SpellVisual[1]));

    SetMetaEnum("SpellFamilyNames");
    browser->append(QString("SpellFamilyName = %0, SpellFamilyFlags = 0x%1\n")
        .arg(me.valueToKey(spellInfo->SpellFamilyName))
        .arg(sSpellFamilyFlags.toUpper()));

    browser->append(QString("SpellSchoolMask = %0 (%1)")
        .arg(spellInfo->SchoolMask)
        .arg(ContainAttributes(spellInfo, TYPE_SCHOOL_MASK)));

    SetMetaEnum("DamageClass");
    browser->append(QString("DamageClass = %0 (%1)")
        .arg(spellInfo->DmgClass)
        .arg(me.valueToKey(spellInfo->DmgClass)));

    SetMetaEnum("PreventionType");
    browser->append(QString("PreventionType = %0 (%1)")
        .arg(spellInfo->PreventionType)
        .arg(me.valueToKey(spellInfo->PreventionType)));

    if (spellInfo->Attributes || spellInfo->AttributesEx || spellInfo->AttributesEx2 ||
        spellInfo->AttributesEx3 || spellInfo->AttributesEx4 || spellInfo->AttributesEx5 || spellInfo->AttributesEx6)
        browser->append(line);

    if (spellInfo->Attributes)
        browser->append(QString("Attributes: 0x%0 (%1)")
            .arg(sAttributes.toUpper())
            .arg(ContainAttributes(spellInfo, TYPE_ATTR)));

    if (spellInfo->AttributesEx)
        browser->append(QString("AttributesEx: 0x%0 (%1)")
            .arg(sAttributesEx.toUpper())
            .arg(ContainAttributes(spellInfo, TYPE_ATTR_EX)));

    if (spellInfo->AttributesEx2)
        browser->append(QString("AttributesEx2: 0x%0 (%1)")
            .arg(sAttributesEx2.toUpper())
            .arg(ContainAttributes(spellInfo, TYPE_ATTR_EX2)));

    if (spellInfo->AttributesEx3)
        browser->append(QString("AttributesEx3: 0x%0 (%1)")
            .arg(sAttributesEx3.toUpper())
            .arg(ContainAttributes(spellInfo, TYPE_ATTR_EX3)));

    if (spellInfo->AttributesEx4)
        browser->append(QString("AttributesEx4: 0x%0 (%1)")
            .arg(sAttributesEx4.toUpper())
            .arg(ContainAttributes(spellInfo, TYPE_ATTR_EX4)));

    if (spellInfo->AttributesEx5)
        browser->append(QString("AttributesEx5: 0x%0 (%1)")
            .arg(sAttributesEx5.toUpper())
            .arg(ContainAttributes(spellInfo, TYPE_ATTR_EX5)));

    if (spellInfo->AttributesEx6)
        browser->append(QString("AttributesEx6: 0x%0 (%1)")
            .arg(sAttributesEx6.toUpper())
            .arg(ContainAttributes(spellInfo, TYPE_ATTR_EX6)));

    browser->append(line);

    if (spellInfo->Targets)
        browser->append(QString("Targets Mask = 0x%0 (%1)")
            .arg(sTargetMask.toUpper())
            .arg(ContainAttributes(spellInfo, TYPE_TARGETS)));

    if (spellInfo->TargetCreatureType)
        browser->append(QString("Creature Type Mask = 0x%0 (%1)")
            .arg(sCreatureTypeMask.toUpper())
            .arg(ContainAttributes(spellInfo, TYPE_CREATURE)));

    if (spellInfo->Stances)
        browser->append(QString("Stances: 0x%0 (%1)")
            .arg(sFormMask.toUpper())
            .arg(ContainAttributes(spellInfo, TYPE_FORMS)));

    if (spellInfo->StancesNot)
        browser->append(QString("Stances not: 0x%0 (%1)")
            .arg(sFormMask.toUpper())
            .arg(ContainAttributes(spellInfo, TYPE_FORMS_NOT)));

    AppendSkillLine(spellInfo, num);

    browser->append(QString("Spell Level = %0, BaseLevel %1, MaxLevel %2, MaxTargetLevel %3")
        .arg(spellInfo->SpellLevel)
        .arg(spellInfo->BaseLevel)
        .arg(spellInfo->MaxLevel)
        .arg(spellInfo->MaxTargetLevel));

    if (spellInfo->EquippedItemClass != -1)
    {
        SetMetaEnum("ItemClass");
        browser->append(QString("EquippedItemClass = %0 (%1)")
            .arg(spellInfo->EquippedItemClass)
            .arg(me.valueToKey(spellInfo->EquippedItemClass)));

        if (spellInfo->EquippedItemSubClassMask)
        {
            QString sItemSubClassMask(QString("%0").arg(spellInfo->EquippedItemSubClassMask, 8, 16, QChar('0')));
            switch (spellInfo->EquippedItemClass)
            {
                case 2: // WEAPON
                browser->append(QString("  SubClass mask 0x%0 (%1)")
                    .arg(sItemSubClassMask.toUpper())
                    .arg(ContainAttributes(spellInfo, TYPE_ITEM_WEAPON)));
                    break;
                case 4: // ARMOR
                browser->append(QString("  SubClass mask 0x%0 (%1)")
                    .arg(sItemSubClassMask.toUpper())
                    .arg(ContainAttributes(spellInfo, TYPE_ITEM_ARMOR)));
                    break;
                case 15: // MISC
                browser->append(QString("  SubClass mask 0x%0 (%1)")
                    .arg(sItemSubClassMask.toUpper())
                    .arg(ContainAttributes(spellInfo, TYPE_ITEM_MISC)));
                    break;
            }
        }

        if (spellInfo->EquippedItemInventoryTypeMask)
        {
            QString sItemInventoryMask(QString("%0").arg(spellInfo->EquippedItemInventoryTypeMask, 8, 16, QChar('0')));
            browser->append(QString("  InventoryType mask = 0x%0 (%1)")
                .arg(sItemInventoryMask.toUpper())
                .arg(ContainAttributes(spellInfo, TYPE_ITEM_INVENTORY)));
        }
    }

    browser->append(QString());

    browser->append(QString("Category = %0").arg(spellInfo->Category));

    SetMetaEnum("DispelType");
    browser->append(QString("DispelType = %0 (%1)")
        .arg(spellInfo->Dispel)
        .arg(me.valueToKey(spellInfo->Dispel)));

    SetMetaEnum("Mechanic");
    browser->append(QString("Mechanic = %0 (%1)")
        .arg(spellInfo->Mechanic)
        .arg(me.valueToKey(spellInfo->Mechanic)));

    AppendRangeInfo(spellInfo, num);

    if (spellInfo->Speed)
        browser->append(QString("Speed: %0").arg(spellInfo->Speed, 0, 'f', 2));

    if (spellInfo->StackAmount)
        browser->append(QString("Stackable up to %0").arg(spellInfo->StackAmount));

    AppendCastTimeLine(spellInfo, num);

    if (spellInfo->RecoveryTime || spellInfo->CategoryRecoveryTime || spellInfo->StartRecoveryCategory)
    {
        browser->append(QString("RecoveryTime: %0 ms, CategoryRecoveryTime: %1 ms")
            .arg(spellInfo->RecoveryTime)
            .arg(spellInfo->CategoryRecoveryTime));

        browser->append(QString("StartRecoveryCategory = %0, StartRecoveryTime = %1 ms")
            .arg(spellInfo->StartRecoveryCategory)
            .arg(float(spellInfo->StartRecoveryTime), 0, 'f', 2));
    }

    AppendDurationLine(spellInfo, num);

    if (spellInfo->ManaCost || spellInfo->ManaCostPercentage)
    {
        SetMetaEnum("Powers");
        browser->append(QString("Power Type = %0, Cost %1")
            .arg(me.valueToKey(spellInfo->PowerType))
            .arg(spellInfo->ManaCost));

        if (spellInfo->ManaCostPerlevel)
            browser->append(QString("  + lvl * %0").arg(spellInfo->ManaCostPerlevel));

        if (spellInfo->ManaPerSecond)
            browser->append(QString("  + %0 Per Second").arg(spellInfo->ManaPerSecond));

        if (spellInfo->ManaPerSecondPerLevel)
            browser->append(QString("  + lvl * %0").arg(spellInfo->ManaPerSecondPerLevel));
    }

    browser->append(QString());

    browser->append(QString("Interrupt Flags: 0x%0, AuraIF 0x%1, ChannelIF 0x%2")
        .arg(sIF.toUpper())
        .arg(sAIF.toUpper())
        .arg(sCIF.toUpper()));

    SetMetaEnum("AuraState");
    if (spellInfo->CasterAuraState)
        browser->append(QString("CasterAuraState = %0 (%1)")
            .arg(spellInfo->CasterAuraState)
            .arg(me.valueToKey(spellInfo->CasterAuraState)));

    if (spellInfo->TargetAuraState)
        browser->append(QString("TargetAuraState = %0 (%1)")
            .arg(spellInfo->TargetAuraState)
            .arg(me.valueToKey(spellInfo->TargetAuraState)));

    if (spellInfo->CasterAuraStateNot)
        browser->append(QString("CasterAuraStateNot = %0 (%1)")
            .arg(spellInfo->CasterAuraStateNot)
            .arg(me.valueToKey(spellInfo->CasterAuraStateNot)));

    if (spellInfo->TargetAuraStateNot)
        browser->append(QString("TargetAuraStateNot = %0 (%1)")
            .arg(spellInfo->TargetAuraStateNot)
            .arg(me.valueToKey(spellInfo->TargetAuraStateNot)));

    if (spellInfo->RequiresSpellFocus)
        browser->append(QString("Requires Spell Focus %0").arg(spellInfo->RequiresSpellFocus));

    if (spellInfo->ProcFlags)
    {
        QString sProcFlags(QString("%0").arg(spellInfo->ProcFlags, 8, 16, QChar('0')));
        browser->append(QString("<b>Proc flag 0x%0, chance = %1, charges - %2</b>")
            .arg(sProcFlags.toUpper())
            .arg(spellInfo->ProcChance)
            .arg(spellInfo->ProcCharges));
        browser->append(line);

        AppendProcInfo(spellInfo, num);
    }
    else
    {
        browser->append(QString("Chance = %0, charges - %1")
            .arg(spellInfo->ProcChance)
            .arg(spellInfo->ProcCharges));
    }

    browser->append(line);

    AppendSpellEffectInfo(spellInfo, num);

    if (num == 1)
        Compare();
}

void SWObject::AppendRangeInfo(SpellEntry const* spellInfo, quint8 num)
{
    QTextBrowser *browser = m_form->GetBrowser(num);

    SpellRangeEntry const *range = sSpellRangeStore.LookupEntry(spellInfo->RangeIndex);
    if (range)
    {
        browser->append(QString("SpellRange: (Id %0) \"%1\": MinRange = %2, MaxRange = %3")
            .arg(range->Id)
            .arg(QString::fromUtf8(range->Name[locale]))
            .arg(range->MinRange)
            .arg(range->MaxRange));
    }
}

void SWObject::AppendProcInfo(SpellEntry const *spellInfo, quint8 num)
{
    QTextBrowser *browser = m_form->GetBrowser(num);

    quint8 i = 0;
    quint64 proc = spellInfo->ProcFlags;
    while (proc != 0)
    {
        if ((proc & 1) != 0)
            browser->append(QString("  %0").arg(ProcFlagDesc[i]));
        i++;
        proc >>= 1;
    }
}

void SWObject::AppendSpellEffectInfo(SpellEntry const* spellInfo, quint8 num)
{
    QTextBrowser *browser = m_form->GetBrowser(num);

    for (quint8 eff = EFFECT_INDEX_0; eff < MAX_EFFECT_INDEX; eff++)
    {
        if (!spellInfo->Effect[eff])
        {
            browser->append(QString("<b>Effect %0:  NO EFFECT</b>").arg(eff));
            browser->append(QString());
        }
        else
        {
            QString _BasePoints(QString("BasePoints = %0").arg(spellInfo->EffectBasePoints[eff] + 1));

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

            QString _DmgMultiplier;
            if (spellInfo->DmgMultiplier[eff] != 1.0f)
                _DmgMultiplier = QString(" * %0").arg(spellInfo->DmgMultiplier[eff], 0, 'f', 2);

            QString _Multiple;
            if (spellInfo->EffectMultipleValue[eff] != 0)
                _Multiple = QString(", Multiple = %0").arg(spellInfo->EffectMultipleValue[eff], 0, 'f', 2);

            QString _Result = _BasePoints + _RealPoints + _DieSides + _PointsPerCombo + _DmgMultiplier + _Multiple;

            SetMetaEnum("Effects");
            browser->append(QString("<b>Effect %0: Id %1 (%2)</b>")
                .arg(eff)
                .arg(spellInfo->Effect[eff])
                .arg(me.valueToKey(spellInfo->Effect[eff])));

            browser->append(_Result);

            SetMetaEnum("Targets");
            browser->append(QString("Targets (%0, %1) (%2, %3)")
                .arg(spellInfo->EffectImplicitTargetA[eff])
                .arg(spellInfo->EffectImplicitTargetB[eff])
                .arg(me.valueToKey(spellInfo->EffectImplicitTargetA[eff]))
                .arg(me.valueToKey(spellInfo->EffectImplicitTargetB[eff])));

            AppendAuraInfo(spellInfo, eff, num);

            AppendRadiusInfo(spellInfo, eff, num);

            AppendTriggerInfo(spellInfo, eff, num);

            if (spellInfo->EffectChainTarget[eff] != 0)
                browser->append(QString("EffectChainTarget = %0").arg(spellInfo->EffectChainTarget[eff]));

            if (spellInfo->EffectMechanic[eff] != 0)
            {
                SetMetaEnum("Mechanic");
                browser->append(QString("Effect Mechanic = %0 (%1)")
                    .arg(spellInfo->EffectMechanic[eff])
                    .arg(me.valueToKey(spellInfo->EffectMechanic[eff])));
            }

            if (spellInfo->EffectItemType[eff] != 0)
            {
                QString sEffectItemType(QString("%0").arg(spellInfo->EffectItemType[eff], 8, 16, QChar('0')));
                browser->append(QString("EffectItemType = 0x%0").arg(sEffectItemType.toUpper()));

                if (spellInfo->Effect[eff] == 6)
                {
                    for (quint32 i = 0; i < sSpellStore.GetNumRows(); i++)
                    {
                        SpellEntry const *t_spellInfo = sSpellStore.LookupEntry(i);
                        if (t_spellInfo)
                        {
                            bool hasSkill = false;
                            if ((t_spellInfo->SpellFamilyName == spellInfo->SpellFamilyName) &&
                                (t_spellInfo->SpellFamilyFlags & spellInfo->EffectItemType[eff]))
                            {
                                QString sRank(QString::fromUtf8(t_spellInfo->Rank[locale]));
                                for (quint32 sk = 0; sk < sSkillLineAbilityStore.GetNumRows(); sk++)
                                {
                                    SkillLineAbilityEntry const *skillInfo = sSkillLineAbilityStore.LookupEntry(sk);
                                    if (skillInfo && skillInfo->SpellId == t_spellInfo->Id && skillInfo->SkillId > 0)
                                    {
                                        hasSkill = true;
                                        if (!sRank.isEmpty())
                                            browser->append(QString("%0<font color=blue>+ %1 - %2 (%3)</font>").arg(QChar(QChar::Nbsp), 4, QChar(QChar::Nbsp)).arg(t_spellInfo->Id).arg(QString::fromUtf8(t_spellInfo->SpellName[locale])).arg(sRank));
                                        else
                                            browser->append(QString("%0<font color=blue>+ %1 - %2</font>").arg(QChar(QChar::Nbsp), 4, QChar(QChar::Nbsp)).arg(t_spellInfo->Id).arg(QString::fromUtf8(t_spellInfo->SpellName[locale])));
                                        break;
                                    }
                                }

                                if (!hasSkill)
                                {
                                    if (!sRank.isEmpty())
                                        browser->append(QString("%0<font color=red>- %1 - %2 (%3)</font>").arg(QChar(QChar::Nbsp), 4, QChar(QChar::Nbsp)).arg(t_spellInfo->Id).arg(QString::fromUtf8(t_spellInfo->SpellName[locale])).arg(sRank));
                                    else
                                        browser->append(QString("%0<font color=red>- %1 - %2</font>").arg(QChar(QChar::Nbsp), 4, QChar(QChar::Nbsp)).arg(t_spellInfo->Id).arg(QString::fromUtf8(t_spellInfo->SpellName[locale])));
                                }
                            }
                        }
                    }
                }
            }

            browser->append(QString());
        }
    }
}

void SWObject::AppendTriggerInfo(SpellEntry const* spellInfo, quint8 index, quint8 num)
{
    QTextBrowser *browser = m_form->GetBrowser(num);

    quint32 trigger = spellInfo->EffectTriggerSpell[index];
    if (trigger != 0)
    {
        SpellEntry const *triggerSpell = sSpellStore.LookupEntry(trigger);
        if (triggerSpell)
        {
            browser->append(QString("<b><font color='blue'>   Trigger spell (%0) %1. Chance = %2</font></b>")
                .arg(trigger)
                .arg(QString("%0 (%1)").arg(QString::fromUtf8(triggerSpell->SpellName[locale])).arg(QString::fromUtf8(triggerSpell->Rank[locale])))
                .arg(triggerSpell->ProcChance));

                QString sDescription(QString::fromUtf8(triggerSpell->Description[locale]));
                QString sTooltip(QString::fromUtf8(triggerSpell->ToolTip[locale]));

                if (!sDescription.isEmpty())
                    browser->append(QString("   Description: %0").arg(GetDescription(sDescription, triggerSpell)));

                if (!sTooltip.isEmpty())
                    browser->append(QString("   ToolTip: %0").arg(GetDescription(sTooltip, triggerSpell)));

                if (triggerSpell->ProcFlags != 0)
                {
                    browser->append(QString("Charges - %0").arg(triggerSpell->ProcCharges));
                    browser->append(QString());

                    AppendProcInfo(triggerSpell, num);

                    browser->append(QString());
                }
        }
        else
        {
            browser->append(QString("Trigger spell (%0) Not found").arg(trigger));
        }
    }
}

void SWObject::AppendRadiusInfo(SpellEntry const* spellInfo, quint8 index, quint8 num)
{
    QTextBrowser *browser = m_form->GetBrowser(num);

    quint16 rIndex = spellInfo->EffectRadiusIndex[index];
    if (rIndex != 0)
    {
        SpellRadiusEntry const *spellRadius = sSpellRadiusStore.LookupEntry(rIndex);
        if (spellRadius)
            browser->append(QString("Radius (Id %0) %1")
                .arg(rIndex)
                .arg(spellRadius->Radius, 0, 'f', 2));
        else
            browser->append(QString("Radius (Id %0) Not found").arg(rIndex));
    }
}

void SWObject::AppendAuraInfo(SpellEntry const* spellInfo, quint8 index, quint8 num)
{
    QTextBrowser *browser = m_form->GetBrowser(num);

    SetMetaEnum("AuraType");
    QString sAura(me.valueToKey(spellInfo->EffectApplyAuraName[index]));
    quint32 misc = spellInfo->EffectMiscValue[index];

    if (spellInfo->EffectApplyAuraName[index] == 0)
    {
        if (spellInfo->EffectMiscValue[index] != 0)
            browser->append(QString("EffectMiscValueA = %0").arg(spellInfo->EffectMiscValue[index]));

        if (spellInfo->EffectMiscValueB[index] != 0)
            browser->append(QString("EffectMiscValueB = %0").arg(spellInfo->EffectMiscValueB[index]));

        if (spellInfo->EffectAmplitude[index] != 0)
            browser->append(QString("EffectAmplitude = %0").arg(spellInfo->EffectAmplitude[index]));

        return;
    }

    QString _BaseAuraInfo;
    _BaseAuraInfo = QString("Aura Id %0 (%1), value = %2, misc = %3 ")
        .arg(spellInfo->EffectApplyAuraName[index])
        .arg(sAura)
        .arg(spellInfo->EffectBasePoints[index] + 1)
        .arg(misc);

    QString _SpecialAuraInfo;
    switch (spellInfo->EffectApplyAuraName[index])
    {
        case 29:
            SetMetaEnum("UnitMods");
            _SpecialAuraInfo = QString("(%0").arg(me.valueToKey(misc));
            break;
        case 189:
            _SpecialAuraInfo = QString("(%0").arg(ContainAttributes(spellInfo, TYPE_CR, index));
            break;
        case 107:
        case 108:
            SetMetaEnum("SpellModOp");
            _SpecialAuraInfo = QString("(%0").arg(me.valueToKey(misc));
            break;
        // todo: more case
        default:
            _SpecialAuraInfo = QString("(%0").arg(misc);
            break;
    }

    QString _MiscB = QString("), miscB = %0").arg(spellInfo->EffectMiscValueB[index]);
    QString _Periodic = QString(", periodic = %0").arg(spellInfo->EffectAmplitude[index]);
    QString _Result = _BaseAuraInfo + _SpecialAuraInfo + _MiscB + _Periodic;
    browser->append(_Result);
}

QString SWObject::ContainAttributes(SpellEntry const* spellInfo, AttrType attr, quint8 index)
{
    QString str("");
    switch (attr)
    {
        case TYPE_ATTR:
        {
            SetMetaEnum("Attributes");
            for (quint8 i = 0; i < me.keyCount(); i++)
            {
                if (spellInfo->Attributes & me.value(i))
                {
                    QString tstr(QString("%0, ").arg(me.key(i)));
                    str += tstr;
                }
            }
            if (!str.isEmpty())
                str.chop(2);
            return str;
        }
        break;
        case TYPE_ATTR_EX:
        {
            SetMetaEnum("AttributesEx");
            for (quint8 i = 0; i < me.keyCount(); i++)
            {
                if (spellInfo->AttributesEx & me.value(i))
                {
                    QString tstr(QString("%0, ").arg(me.key(i)));
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
            SetMetaEnum("AttributesEx2");
            for (quint8 i = 0; i < me.keyCount(); i++)
            {
                if (spellInfo->AttributesEx2 & me.value(i))
                {
                    QString tstr(QString("%0, ").arg(me.key(i)));
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
            SetMetaEnum("AttributesEx3");
            for (quint8 i = 0; i < me.keyCount(); i++)
            {
                if (spellInfo->AttributesEx3 & me.value(i))
                {
                    QString tstr(QString("%0, ").arg(me.key(i)));
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
            SetMetaEnum("AttributesEx4");
            for (quint8 i = 0; i < me.keyCount(); i++)
            {
                if (spellInfo->AttributesEx4 & me.value(i))
                {
                    QString tstr(QString("%0, ").arg(me.key(i)));
                    str += tstr;
                }
            }
            if (!str.isEmpty())
                str.chop(2);
            return str;
        }
        break;
        case TYPE_ATTR_EX5:
        {
            SetMetaEnum("AttributesEx5");
            for (quint8 i = 0; i < me.keyCount(); i++)
            {
                if (spellInfo->AttributesEx5 & me.value(i))
                {
                    QString tstr(QString("%0, ").arg(me.key(i)));
                    str += tstr;
                }
            }
            if (!str.isEmpty())
                str.chop(2);
            return str;
        }
        break;
        case TYPE_ATTR_EX6:
        {
            SetMetaEnum("AttributesEx6");
            for (quint8 i = 0; i < me.keyCount(); i++)
            {
                if (spellInfo->AttributesEx6 & me.value(i))
                {
                    QString tstr(QString("%0, ").arg(me.key(i)));
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
            SetMetaEnum("TargetFlags");
            for (quint8 i = 0; i < me.keyCount(); i++)
            {
                if (spellInfo->Targets & me.value(i))
                {
                    QString tstr(QString("%0, ").arg(me.key(i)));
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
            SetMetaEnum("CreatureType");
            for (quint8 i = 0; i < me.keyCount(); i++)
            {
                if (spellInfo->TargetCreatureType & me.value(i))
                {
                    QString tstr(QString("%0, ").arg(me.key(i)));
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
            SetMetaEnum("ShapeshiftFormMask");
            for (quint8 i = 0; i < me.keyCount(); i++)
            {
                if (spellInfo->Stances & me.value(i))
                {
                    QString tstr(QString("%0, ").arg(me.key(i)));
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
            SetMetaEnum("ShapeshiftFormMask");
            for (quint8 i = 0; i < me.keyCount(); i++)
            {
                if (spellInfo->StancesNot & me.value(i))
                {
                    QString tstr(QString("%0, ").arg(me.key(i)));
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
            SetMetaEnum("ItemSubClassWeaponMask");
            for (quint8 i = 0; i < me.keyCount(); i++)
            {
                if (spellInfo->EquippedItemSubClassMask & me.value(i))
                {
                    QString tstr(QString("%0, ").arg(me.key(i)));
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
            SetMetaEnum("ItemSubClassArmorMask");
            for (quint8 i = 0; i < me.keyCount(); i++)
            {
                if (spellInfo->EquippedItemSubClassMask & me.value(i))
                {
                    QString tstr(QString("%0, ").arg(me.key(i)));
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
            SetMetaEnum("ItemSubClassMiscMask");
            for (quint8 i = 0; i < me.keyCount(); i++)
            {
                if (spellInfo->EquippedItemSubClassMask & me.value(i))
                {
                    QString tstr(QString("%0, ").arg(me.key(i)));
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
            SetMetaEnum("InventoryTypeMask");
            for (quint8 i = 0; i < me.keyCount(); i++)
            {
                if (spellInfo->EquippedItemInventoryTypeMask & me.value(i))
                {
                    QString tstr(QString("%0, ").arg(me.key(i)));
                    str += tstr;
                }
            }
            if (!str.isEmpty())
                str.chop(2);
            return str;
        }
        break;
        case TYPE_CR:
        {
            SetMetaEnum("CombatRating");
            for (quint8 i = 0; i < me.keyCount(); i++)
            {
                if (spellInfo->EffectMiscValue[index] & me.value(i))
                {
                    QString tstr(QString("%0, ").arg(me.key(i)));
                    str += tstr;
                }
            }
            if (!str.isEmpty())
                str.chop(2);
            return str;
        }
        break;
        case TYPE_SCHOOL_MASK:
        {
            SetMetaEnum("SpellSchoolMask");
            for (quint8 i = 0; i < me.keyCount(); i++)
            {
                if (spellInfo->SchoolMask == me.value(i))
                {
                    QString tstr(QString("%0, ").arg(me.key(i)));
                    str += tstr;
                }
            }
            if (!str.isEmpty())
                str.chop(2);
            return str;
        }
        break;
    }
    return str;
}

void SWObject::AppendSkillLine(SpellEntry const* spellInfo, quint8 num)
{
    QTextBrowser *browser = m_form->GetBrowser(num);

    for (quint32 i = 0; i < sSkillLineAbilityStore.GetNumRows(); i++)
    {
        SkillLineAbilityEntry const *skillInfo = sSkillLineAbilityStore.LookupEntry(i);
        if (skillInfo && skillInfo->SpellId == spellInfo->Id)
        {
            SkillLineEntry const *skill = sSkillLineStore.LookupEntry(skillInfo->SkillId);
            browser->append(QString("Skill (Id %0) \"%1\", ReqSkillValue = %2, Forward Spell = %3, MinMaxValue (%4, %5), CharacterPoints (%6, %7)")
                .arg(skill->Id)
                .arg(QString::fromUtf8(skill->Name[locale]))
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

void SWObject::AppendCastTimeLine(SpellEntry const* spellInfo, quint8 num)
{
    QTextBrowser *browser = m_form->GetBrowser(num);

    SpellCastTimesEntry const *castInfo = sSpellCastTimesStore.LookupEntry(spellInfo->CastingTimeIndex);
    if (castInfo)
    {
        browser->append(QString("CastingTime (Id %0) = %1")
            .arg(castInfo->Id)
            .arg(float(castInfo->CastTime) / 1000, 0, 'f', 2));
    }
}

void SWObject::AppendDurationLine(SpellEntry const* spellInfo, quint8 num)
{
    QTextBrowser *browser = m_form->GetBrowser(num);

    SpellDurationEntry const *durationInfo = sSpellDurationStore.LookupEntry(spellInfo->DurationIndex);
    if (durationInfo)
    {
        browser->append(QString("Duration: ID (%0)  %1, %2, %3")
            .arg(durationInfo->Id)
            .arg(durationInfo->Duration[0])
            .arg(durationInfo->Duration[1])
            .arg(durationInfo->Duration[2]));
    }
}

void SWObject::Compare()
{
    QStringList list1 = m_form->SpellInfoBrowser->toPlainText().split("\n");
    QStringList list2 = m_form->SpellInfoBrowser2->toPlainText().split("\n");

    m_form->SpellInfoBrowser->clear();
    m_form->SpellInfoBrowser2->clear();

    QString line("==================================================");

    for (quint32 i = 0; i < list1.size(); i++)
    {
        bool yes = false;

        for (quint32 j = 0; j < list2.size(); j++)
        {
            if (list1.at(i) == list2.at(j))
            {
                yes = true;
                break;
            }
        }

        if (list1.at(i) == line)
        {
            m_form->SpellInfoBrowser->append(line);
            continue;
        }

        if (yes)
        {
            m_form->SpellInfoBrowser->append(QString("<span style='background-color: cyan'>%0</span>").arg(list1.at(i)));
        }
        else
        {
            m_form->SpellInfoBrowser->append(QString("<span style='background-color: salmon'>%0</span>").arg(list1.at(i)));
        }
    }

    // second
    for (quint32 i = 0; i < list2.size(); i++)
    {
        bool yes = false;

        for (quint32 j = 0; j < list1.size(); j++)
        {
            if (list2.at(i) == list1.at(j))
            {
                yes = true;
                break;
            }
        }

        if (list2.at(i) == line)
        {
            m_form->SpellInfoBrowser2->append(line);
            continue;
        }

        if (yes)
        {
            m_form->SpellInfoBrowser2->append(QString("<span style='background-color: cyan'>%0</span>").arg(list2.at(i)));
        }
        else
        {
            m_form->SpellInfoBrowser2->append(QString("<span style='background-color: salmon'>%0</span>").arg(list2.at(i)));
        }
    }
}
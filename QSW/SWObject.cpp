#include "SWObject.h"
#include "Alphanum.h"

SpellListSortedModel::SpellListSortedModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

bool SpellListSortedModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    QVariant leftData = sourceModel()->data(left);
    QVariant rightData = sourceModel()->data(right);

    if (compare(leftData.toString(), rightData.toString()) < 0)
        return true;

    return false;
}

SpellListModel::SpellListModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    m_spellList.clear();
}

void SpellListModel::clear()
{
    beginResetModel();
    m_spellList.clear();
    endResetModel();
}

int SpellListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_spellList.size();
}

int SpellListModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}

QVariant SpellListModel::data(const QModelIndex &index, int role) const
{
    if (m_spellList.isEmpty())
        return QVariant();

    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_spellList.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole)
        return m_spellList.at(index.row()).at(index.column());

    return QVariant();
}

QVariant SpellListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
    {
        switch (section)
        {
            case 0: return QString("ID");
            case 1: return QString("Name");
        }
    }

    return QVariant();
}

Qt::ItemFlags SpellListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

SWObject::SWObject(SWForm* form)
    : m_form(form), m_regExp(false), m_type(0)
{
    for (quint8 i = 0; i < MAX_THREAD; i++)
        threadSemaphore[i] = false;

    LoadDBCStores();
}

void SWObject::setMetaEnum(const char* enumName)
{
    m_metaEnum = Enums::staticMetaObject.enumerator(Enums::staticMetaObject.indexOfEnumerator(enumName));
}

void SWObject::threadBegin(quint8 id)
{
    if (!threadExist(id))
    {
        TObject* thread = new TObject(id, this);
        thread->start();
    }
}

float getRadius(SpellEntry const* spellInfo, quint8 effIndex)
{
    SpellRadiusEntry const* spellRadius = sSpellRadiusStore.LookupEntry(spellInfo->getEffectRadiusIndex(effIndex));
    if (spellRadius)
        return spellRadius->RadiusFriendly;

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
    return quint32(getDuration(spellInfo) / (spellInfo->getEffectAmplitude(effIndex) ? quint32(spellInfo->getEffectAmplitude(effIndex) / 1000) : 5));
}

void RegExpU(SpellEntry const* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(4).isEmpty())
    {
        SpellEntry const* tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
        if (tSpell)
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(tSpell->getStackAmount()));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(spellInfo->getStackAmount()));
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
                .arg(tSpell->getProcChance()));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(spellInfo->getProcChance()));
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
                .arg(tSpell->getMaxTargetLevel()));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(spellInfo->getMaxTargetLevel()));
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
                        .arg(abs(qint32(tSpell->getEffectMiscValue(rx.cap(6).toInt()-1) / rx.cap(3).toInt()))));
                }
                else if (rx.cap(2) == QString("*"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(abs(qint32(tSpell->getEffectMiscValue(rx.cap(6).toInt()-1) * rx.cap(3).toInt()))));
                }
            }
        }
        else
        {
            if (rx.cap(2) == QString("/"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(abs(qint32(spellInfo->getEffectMiscValue(rx.cap(6).toInt()-1) / rx.cap(3).toInt()))));
            }
            else if (rx.cap(2) == QString("*"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(abs(qint32(spellInfo->getEffectMiscValue(rx.cap(6).toInt()-1) * rx.cap(3).toInt()))));
            }
        }
    }
    else if (!rx.cap(4).isEmpty())
    {
        SpellEntry const* tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
        if (tSpell)
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(abs(tSpell->getEffectMiscValue(rx.cap(6).toInt()-1))));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(abs(spellInfo->getEffectMiscValue(rx.cap(6).toInt()-1))));
    }
}

void RegExpI(SpellEntry const* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(4).isEmpty())
    {
        SpellEntry const* tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
        if (tSpell)
        {
            if (tSpell->getMaxAffectedTargets() != 0)
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(tSpell->getMaxAffectedTargets()));
            }
            else
            {
                str.replace(rx.cap(0), QString("nearby"));
            }
        }
    }
    else
    {
        if (spellInfo->getMaxAffectedTargets() != 0)
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(spellInfo->getMaxAffectedTargets()));
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
                        .arg(abs(qint32((tSpell->getEffectPointsPerComboPoint(rx.cap(6).toInt()-1)) / rx.cap(3).toInt()))));
                }
                else if (rx.cap(2) == QString("*"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(abs(qint32((tSpell->getEffectPointsPerComboPoint(rx.cap(6).toInt()-1) * rx.cap(3).toInt())))));
                }
            }
        }
        else
        {
            if (rx.cap(2) == QString("/"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(abs(qint32((spellInfo->getEffectPointsPerComboPoint(rx.cap(6).toInt()-1) / rx.cap(3).toInt())))));
            }
            else if (rx.cap(2) == QString("*"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(abs(qint32((spellInfo->getEffectPointsPerComboPoint(rx.cap(6).toInt()-1) * rx.cap(3).toInt())))));
            }
        }
    }
    else if (!rx.cap(4).isEmpty())
    {
        SpellEntry const* tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
        if (tSpell)
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(abs(qint32(tSpell->getEffectPointsPerComboPoint(rx.cap(6).toInt()-1)))));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(abs(qint32(spellInfo->getEffectPointsPerComboPoint(rx.cap(6).toInt()-1)))));
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
                        .arg(abs(qint32((tSpell->getEffectBasePoints(rx.cap(6).toInt()-1)) / rx.cap(3).toInt()))));
                }
                else if (rx.cap(2) == QString("*"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(abs(qint32((tSpell->getEffectBasePoints(rx.cap(6).toInt()-1)) * rx.cap(3).toInt()))));
                }
            }
        }
        else
        {
            if (rx.cap(2) == QString("/"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(abs(qint32((spellInfo->getEffectBasePoints(rx.cap(6).toInt()-1)) / rx.cap(3).toInt()))));
            }
            else if (rx.cap(2) == QString("*"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(abs(qint32((spellInfo->getEffectBasePoints(rx.cap(6).toInt()-1)) * rx.cap(3).toInt()))));
            }
        }
    }
    else if (!rx.cap(4).isEmpty())
    {
        SpellEntry const* tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
        if (tSpell)
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(abs(tSpell->getEffectBasePoints(rx.cap(6).toInt()-1))));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(abs(spellInfo->getEffectBasePoints(rx.cap(6).toInt()-1))));
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
                        .arg(quint32((getRealDuration(tSpell, rx.cap(6).toInt()-1) * (tSpell->getEffectBasePoints(rx.cap(6).toInt()-1))) / rx.cap(3).toInt())));
                }
                else if(rx.cap(2) == QString("*"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(quint32((getRealDuration(tSpell, rx.cap(6).toInt()-1) * (tSpell->getEffectBasePoints(rx.cap(6).toInt()-1))) * rx.cap(3).toInt())));
                }
            }
        }
        else
        {
            if (rx.cap(2) == QString("/"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(quint32((getRealDuration(spellInfo, rx.cap(6).toInt()-1) * (spellInfo->getEffectBasePoints(rx.cap(6).toInt()-1))) / rx.cap(3).toInt())));
            }
            else if (rx.cap(2) == QString("*"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(quint32((getRealDuration(spellInfo, rx.cap(6).toInt()-1) * (spellInfo->getEffectBasePoints(rx.cap(6).toInt()-1))) * rx.cap(3).toInt())));
            }
        }
    }
    else if (!rx.cap(4).isEmpty())
    {
        SpellEntry const* tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
        if (tSpell)
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(getRealDuration(tSpell, rx.cap(6).toInt()-1) * (tSpell->getEffectBasePoints(rx.cap(6).toInt()-1))));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(getRealDuration(spellInfo, rx.cap(6).toInt()-1) * (spellInfo->getEffectBasePoints(rx.cap(6).toInt()-1))));
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
                        .arg(abs(qint32((tSpell->getEffectBasePoints(rx.cap(6).toInt()-1)) / rx.cap(3).toInt()))));
                }
                else if (rx.cap(2) == QString("*"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(abs(qint32((tSpell->getEffectBasePoints(rx.cap(6).toInt()-1)) * rx.cap(3).toInt()))));
                }
            }
        }
        else
        {
            if (rx.cap(2) == QString("/"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(abs(qint32((spellInfo->getEffectBasePoints(rx.cap(6).toInt()-1)) / rx.cap(3).toInt()))));
            }
            else if (rx.cap(2) == QString("*"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(abs(qint32((spellInfo->getEffectBasePoints(rx.cap(6).toInt()-1)) * rx.cap(3).toInt()))));
            }
        }
    }
    else if (!rx.cap(4).isEmpty())
    {
        SpellEntry const* tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
        if (tSpell)
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(abs(tSpell->getEffectBasePoints(rx.cap(6).toInt()-1))));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(abs(spellInfo->getEffectBasePoints(rx.cap(6).toInt()-1))));
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
                        .arg(quint32(quint32(tSpell->getEffectAmplitude(rx.cap(6).toInt()-1) / 1000) / rx.cap(3).toInt())));
                }
                else if (rx.cap(2) == QString("*"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(quint32(quint32(tSpell->getEffectAmplitude(rx.cap(6).toInt()-1) / 1000) * rx.cap(3).toInt())));
                }
            }
        }
        else
        {
            if (rx.cap(2) == QString("/"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(quint32(quint32(spellInfo->getEffectAmplitude(rx.cap(6).toInt()-1) / 1000) / rx.cap(3).toInt())));
            }
            else if (rx.cap(2) == QString("*"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(quint32(quint32(spellInfo->getEffectAmplitude(rx.cap(6).toInt()-1) / 1000) * rx.cap(3).toInt())));
            }
        }
    }
    else if (!rx.cap(4).isEmpty())
    {
        SpellEntry const* tSpell = sSpellStore.LookupEntry(rx.cap(4).toInt());
        if (tSpell)
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(quint32(tSpell->getEffectAmplitude(rx.cap(6).toInt()-1) / 1000)));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(quint32(spellInfo->getEffectAmplitude(rx.cap(6).toInt()-1) / 1000)));
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
                .arg(tSpell->getProcCharges()));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(spellInfo->getProcCharges()));
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
                .arg(tSpell->getEffectChainTarget(rx.cap(6).toInt()-1)));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(spellInfo->getEffectChainTarget(rx.cap(6).toInt()-1)));
    }
}

QString SWObject::getDescription(QString str, SpellEntry const* spellInfo)
{
    if (!isRegExp())
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

quint32 SWObject::getParentSpellId(quint32 triggerId)
{
    for (quint32 i = 0; i < sSpellStore.GetNumRows(); i++)
        if (SpellEntry const* spellInfo = sSpellStore.LookupEntry(i))
            for (quint8 eff = EFFECT_INDEX_0; eff < MAX_EFFECT_INDEX; eff++)
                if (spellInfo->getEffectTriggerSpell(eff) == triggerId)
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
    QString line("==================================================<br>");

    QString sName(QString::fromUtf8(spellInfo->SpellName));
    QString sDescription(QString::fromUtf8(spellInfo->Description));
    QString sRank(QString::fromUtf8(spellInfo->Rank));
    QString sToolTip(QString::fromUtf8(spellInfo->ToolTip));
    QString sSpellFamilyFlags0(QString("%0").arg(spellInfo->getSpellFamilyFlags().value[0], 8, 16, QChar('0')));
    QString sSpellFamilyFlags1(QString("%0").arg(spellInfo->getSpellFamilyFlags().value[1], 8, 16, QChar('0')));
    QString sSpellFamilyFlags2(QString("%0").arg(spellInfo->getSpellFamilyFlags().value[2], 8, 16, QChar('0')));
    QString sAttributes(QString("%0").arg(spellInfo->Attributes, 8, 16, QChar('0')));
    QString sAttributesEx(QString("%0").arg(spellInfo->AttributesEx, 8, 16, QChar('0')));
    QString sAttributesEx2(QString("%0").arg(spellInfo->AttributesEx2, 8, 16, QChar('0')));
    QString sAttributesEx3(QString("%0").arg(spellInfo->AttributesEx3, 8, 16, QChar('0')));
    QString sAttributesEx4(QString("%0").arg(spellInfo->AttributesEx4, 8, 16, QChar('0')));
    QString sAttributesEx5(QString("%0").arg(spellInfo->AttributesEx5, 8, 16, QChar('0')));
    QString sAttributesEx6(QString("%0").arg(spellInfo->AttributesEx6, 8, 16, QChar('0')));
    QString sAttributesEx7(QString("%0").arg(spellInfo->AttributesEx7, 8, 16, QChar('0')));
    QString sAttributesEx8(QString("%0").arg(spellInfo->AttributesEx8, 8, 16, QChar('0')));
    QString sTargetMask(QString("%0").arg(spellInfo->getTargets(), 8, 16, QChar('0')));
    QString sCreatureTypeMask(QString("%0").arg(spellInfo->getTargetCreatureType(), 8, 16, QChar('0')));
    QString sFormMask(QString("%0").arg(spellInfo->getStances().value[0], 8, 16, QChar('0')));
    QString sFormMaskNot(QString("%0").arg(spellInfo->getStancesNot().value[0], 8, 16, QChar('0')));
    QString sIF(QString("%0").arg(spellInfo->getInterruptFlags(), 8, 16, QChar('0')));
    QString sAIF(QString("%0").arg(spellInfo->getAuraInterruptFlags(), 8, 16, QChar('0')));
    QString sCIF(QString("%0").arg(spellInfo->getChannelInterruptFlags(), 8, 16, QChar('0')));

    html.append("<font size=2>");
    quint32 parentId = getParentSpellId(spellInfo->Id);
    if (parentId)
    {
        if (SpellEntry const* parentInfo = sSpellStore.LookupEntry(parentId))
        {
            QString sParentName(QString::fromUtf8(parentInfo->SpellName));
            QString sParentRank(QString::fromUtf8(parentInfo->Rank));

            if (!sParentRank.isEmpty())
                sParentName.append(" (" + sParentRank + ")");

            html.append(QString("<b><font color=blue>Triggered by: <a href='http://spellwork/%0'>%0</a> - %1</font></b><br>")
                .arg(parentId)
                .arg(sParentName));
        }
    }

    html.append("<table>");

    html.append(QString("<tr><td rowspan=5>"
                        "<style>"
                        "div.icon { width: 68px; height: 68px; background: url(http://static.wowhead.com/images/wow/icons/large/%0.jpg) no-repeat center; }"
                        "div.icon div { background: url(http://static.wowhead.com/images/Icon/large/border/default.png) no-repeat center;}"
                        "div.icon div div:hover { background: url(http://static.wowhead.com/images/Icon/large/hilite/default.png) no-repeat center; }"
                        "div.icon div div {width: 68px; height: 68px;}"
                        "</style>"
                        "<div class='icon'><div><div>"
                        "</div></div></div> </td></tr>").arg(getSpellIconName(spellInfo->SpellIconId).toLower()));

    if (!sRank.isEmpty())
        sName.append(QString(" (%0)").arg(sRank));

    html.append(QString("<tr><td><font size=2><b>ID:</b> %0</font></td></tr>")
        .arg(spellInfo->Id));

    html.append(QString("<tr><td><font size=2><b>Name:</b> %0</font></td></tr>")
        .arg(sName));

    if (!sDescription.isEmpty())
        html.append(QString("<tr><td><font size=2><b>Description:</b> %0</font></td></tr>").arg(getDescription(sDescription, spellInfo)));

    if (!sToolTip.isEmpty())
        html.append(QString("<tr><td><font size=2><b>ToolTip:</b> %0</font></td></tr>").arg(getDescription(sToolTip, spellInfo)));

    html.append("</table>");
    html.append(line);

    if (spellInfo->getModalNextSpell())
        html.append(QString("ModalNextSpell: %0<br>").arg(spellInfo->getModalNextSpell()));

    html.append(QString("Category = %0, SpellIconID = %1, ActiveIconID = %2, SpellVisual = (%3 ,%4)<br>")
        .arg(spellInfo->getCategory())
        .arg(spellInfo->SpellIconId)
        .arg(spellInfo->ActiveIconId)
        .arg(spellInfo->SpellVisual.value[0])
        .arg(spellInfo->SpellVisual.value[1]));

    setMetaEnum("SpellFamilyNames");
    html.append(QString("SpellFamilyName = %0, SpellFamilyFlags = 0x%1 %2 %3<br>")
        .arg(m_metaEnum.valueToKey(spellInfo->getSpellFamilyName()))
        .arg(sSpellFamilyFlags2.toUpper())
        .arg(sSpellFamilyFlags1.toUpper())
        .arg(sSpellFamilyFlags0.toUpper()));

    html.append(QString("SpellSchoolMask = %0 (%1)<br>")
        .arg(spellInfo->SchoolMask)
        .arg(containAttributes(spellInfo, TYPE_SCHOOL_MASK)));

    setMetaEnum("DamageClass");
    html.append(QString("DamageClass = %0 (%1)<br>")
        .arg(spellInfo->getDmgClass())
        .arg(m_metaEnum.valueToKey(spellInfo->getDmgClass())));

    setMetaEnum("PreventionType");
    html.append(QString("PreventionType = %0 (%1)<br>")
        .arg(spellInfo->getPreventionType())
        .arg(m_metaEnum.valueToKey(spellInfo->getPreventionType())));

    if (spellInfo->Attributes || spellInfo->AttributesEx || spellInfo->AttributesEx2 ||
        spellInfo->AttributesEx3 || spellInfo->AttributesEx4 || spellInfo->AttributesEx5 ||
        spellInfo->AttributesEx6 || spellInfo->AttributesEx7)
        html.append(line);

    if (spellInfo->Attributes)
        html.append(QString("Attributes: 0x%0 (%1)<br>")
            .arg(sAttributes.toUpper())
            .arg(containAttributes(spellInfo, TYPE_ATTR)));

    if (spellInfo->AttributesEx)
        html.append(QString("AttributesEx: 0x%0 (%1)<br>")
            .arg(sAttributesEx.toUpper())
            .arg(containAttributes(spellInfo, TYPE_ATTR_EX)));

    if (spellInfo->AttributesEx2)
        html.append(QString("AttributesEx2: 0x%0 (%1)<br>")
            .arg(sAttributesEx2.toUpper())
            .arg(containAttributes(spellInfo, TYPE_ATTR_EX2)));

    if (spellInfo->AttributesEx3)
        html.append(QString("AttributesEx3: 0x%0 (%1)<br>")
            .arg(sAttributesEx3.toUpper())
            .arg(containAttributes(spellInfo, TYPE_ATTR_EX3)));

    if (spellInfo->AttributesEx4)
        html.append(QString("AttributesEx4: 0x%0 (%1)<br>")
            .arg(sAttributesEx4.toUpper())
            .arg(containAttributes(spellInfo, TYPE_ATTR_EX4)));

    if (spellInfo->AttributesEx5)
        html.append(QString("AttributesEx5: 0x%0 (%1)<br>")
            .arg(sAttributesEx5.toUpper())
            .arg(containAttributes(spellInfo, TYPE_ATTR_EX5)));

    if (spellInfo->AttributesEx6)
        html.append(QString("AttributesEx6: 0x%0 (%1)<br>")
            .arg(sAttributesEx6.toUpper())
            .arg(containAttributes(spellInfo, TYPE_ATTR_EX6)));

    if (spellInfo->AttributesEx7)
        html.append(QString("AttributesEx7: 0x%0 (%1)<br>")
            .arg(sAttributesEx7.toUpper())
            .arg(containAttributes(spellInfo, TYPE_ATTR_EX7)));

    if (spellInfo->AttributesEx8)
        html.append(QString("AttributesEx8: 0x%0 (%1)<br>")
            .arg(sAttributesEx8.toUpper())
            .arg(containAttributes(spellInfo, TYPE_ATTR_EX8)));

    html.append(line);

    if (spellInfo->getTargets())
        html.append(QString("Targets Mask = 0x%0 (%1)<br>")
            .arg(sTargetMask.toUpper())
            .arg(containAttributes(spellInfo, TYPE_TARGETS)));

    if (spellInfo->getTargetCreatureType())
        html.append(QString("Creature Type Mask = 0x%0 (%1)<br>")
            .arg(sCreatureTypeMask.toUpper())
            .arg(containAttributes(spellInfo, TYPE_CREATURE)));

    if (spellInfo->getStances().value[0])
        html.append(QString("Stances: 0x%0 (%1)<br>")
            .arg(sFormMask.toUpper())
            .arg(containAttributes(spellInfo, TYPE_FORMS)));

    if (spellInfo->getStancesNot().value[0])
        html.append(QString("Stances not: 0x%0 (%1)<br>")
            .arg(sFormMaskNot.toUpper())
            .arg(containAttributes(spellInfo, TYPE_FORMS_NOT)));

    appendSkillLine(spellInfo, num);

    html.append(QString("Spell Level = %0, BaseLevel %1, MaxLevel %2, MaxTargetLevel %3<br>")
        .arg(spellInfo->getSpellLevel())
        .arg(spellInfo->getBaseLevel())
        .arg(spellInfo->getMaxLevel())
        .arg(spellInfo->getMaxTargetLevel()));

    if (spellInfo->getEquippedItemClass() != -1)
    {
        setMetaEnum("ItemClass");
        html.append(QString("EquippedItemClass = %0 (%1)<br>")
            .arg(spellInfo->getEquippedItemClass())
            .arg(m_metaEnum.valueToKey(spellInfo->getEquippedItemClass())));

        if (spellInfo->getEquippedItemSubClassMask())
        {
            QString sItemSubClassMask(QString("%0").arg(spellInfo->getEquippedItemSubClassMask(), 8, 16, QChar('0')));
            switch (spellInfo->getEquippedItemClass())
            {
                case 2: // WEAPON
                html.append(QString("  SubClass mask 0x%0 (%1)<br>")
                    .arg(sItemSubClassMask.toUpper())
                    .arg(containAttributes(spellInfo, TYPE_ITEM_WEAPON)));
                    break;
                case 4: // ARMOR
                html.append(QString("  SubClass mask 0x%0 (%1)<br>")
                    .arg(sItemSubClassMask.toUpper())
                    .arg(containAttributes(spellInfo, TYPE_ITEM_ARMOR)));
                    break;
                case 15: // MISC
                html.append(QString("  SubClass mask 0x%0 (%1)<br>")
                    .arg(sItemSubClassMask.toUpper())
                    .arg(containAttributes(spellInfo, TYPE_ITEM_MISC)));
                    break;
            }
        }

        if (spellInfo->getEquippedItemInventoryTypeMask())
        {
            QString sItemInventoryMask(QString("%0").arg(spellInfo->getEquippedItemInventoryTypeMask(), 8, 16, QChar('0')));
            html.append(QString("  InventoryType mask = 0x%0 (%1)<br>")
                .arg(sItemInventoryMask.toUpper())
                .arg(containAttributes(spellInfo, TYPE_ITEM_INVENTORY)));
        }
    }

    html.append(QString("<br>"));

    html.append(QString("Category = %0<br>")
        .arg(spellInfo->getCategory()));

    setMetaEnum("DispelType");
    html.append(QString("DispelType = %0 (%1)<br>")
        .arg(spellInfo->getDispel())
        .arg(m_metaEnum.valueToKey(spellInfo->getDispel())));

    setMetaEnum("Mechanic");
    html.append(QString("Mechanic = %0 (%1)<br>")
        .arg(spellInfo->getMechanic())
        .arg(m_metaEnum.valueToKey(spellInfo->getMechanic())));

    appendRangeInfo(spellInfo, num);

    if (spellInfo->Speed)
        html.append(QString("Speed: %0<br>")
            .arg(spellInfo->Speed, 0, 'f', 2));

    if (spellInfo->getStackAmount())
        html.append(QString("Stackable up to %0<br>")
            .arg(spellInfo->getStackAmount()));

    appendCastTimeLine(spellInfo, num);

    if (spellInfo->getRecoveryTime() || spellInfo->getCategoryRecoveryTime() || spellInfo->getStartRecoveryCategory())
    {
        html.append(QString("RecoveryTime: %0 ms, CategoryRecoveryTime: %1 ms<br>")
            .arg(spellInfo->getRecoveryTime())
            .arg(spellInfo->getCategoryRecoveryTime()));

        html.append(QString("StartRecoveryCategory = %0, StartRecoveryTime = %1 ms<br>")
            .arg(spellInfo->getStartRecoveryCategory())
            .arg(float(spellInfo->getStartRecoveryTime()), 0, 'f', 2));
    }

    appendDurationLine(spellInfo, num);

    if (spellInfo->getManaCost() || spellInfo->getManaCostPercentage())
    {
        setMetaEnum("Powers");
        html.append(QString("Power Type = %0, Cost %1<br>")
            .arg(m_metaEnum.valueToKey(spellInfo->PowerType))
            .arg(spellInfo->getManaCost()));

        if (spellInfo->getManaCostPerLevel())
            html.append(QString("  + lvl * %0<br>")
                .arg(spellInfo->getManaCostPerLevel()));

        if (spellInfo->getManaPerSecond())
            html.append(QString("  + %0 Per Second<br>")
                .arg(spellInfo->getManaPerSecond()));
    }

    html.append(QString("<br>"));

    html.append(QString("Interrupt Flags: 0x%0, AuraIF 0x%1, ChannelIF 0x%2<br>")
        .arg(sIF.toUpper())
        .arg(sAIF.toUpper())
        .arg(sCIF.toUpper()));

    setMetaEnum("AuraState");
    if (spellInfo->getCasterAuraState())
        html.append(QString("CasterAuraState = %0 (%1)<br>")
            .arg(spellInfo->getCasterAuraState())
            .arg(m_metaEnum.valueToKey(spellInfo->getCasterAuraState())));

    if (spellInfo->getTargetAuraState())
        html.append(QString("TargetAuraState = %0 (%1)<br>")
            .arg(spellInfo->getTargetAuraState())
            .arg(m_metaEnum.valueToKey(spellInfo->getTargetAuraState())));

    if (spellInfo->getCasterAuraStateNot())
        html.append(QString("CasterAuraStateNot = %0 (%1)<br>")
            .arg(spellInfo->getCasterAuraStateNot())
            .arg(m_metaEnum.valueToKey(spellInfo->getCasterAuraStateNot())));

    if (spellInfo->getTargetAuraStateNot())
        html.append(QString("TargetAuraStateNot = %0 (%1)<br>")
            .arg(spellInfo->getTargetAuraStateNot())
            .arg(m_metaEnum.valueToKey(spellInfo->getTargetAuraStateNot())));

    if (spellInfo->getCasterAuraSpell())
    {
        if(SpellEntry const* spell = sSpellStore.LookupEntry(spellInfo->getCasterAuraSpell()))
        {
            html.append(QString("Caster Aura Spell (%0) %1<br>")
                .arg(spellInfo->getCasterAuraSpell())
                .arg(QString::fromUtf8(spell->SpellName)));
        }
        else
            html.append(QString("Caster Aura Spell (%0) ?????<br>").arg(spellInfo->getCasterAuraSpell()));
    }

    if (spellInfo->getTargetAuraSpell())
    {
        if(SpellEntry const* spell = sSpellStore.LookupEntry(spellInfo->getTargetAuraSpell()))
        {
            html.append(QString("Target Aura Spell (%0) %1<br>")
                .arg(spellInfo->getTargetAuraSpell())
                .arg(QString::fromUtf8(spell->SpellName)));
        }
        else
            html.append(QString("Target Aura Spell (%0) ?????<br>").arg(spellInfo->getTargetAuraSpell()));
    }

    if (spellInfo->getExcludeCasterAuraSpell())
    {
        if(SpellEntry const* spell = sSpellStore.LookupEntry(spellInfo->getExcludeCasterAuraSpell()))
        {
            html.append(QString("Ex Caster Aura Spell (%0) %1<br>")
                .arg(spellInfo->getExcludeCasterAuraSpell())
                .arg(QString::fromUtf8(spell->SpellName)));
        }
        else
            html.append(QString("Ex Caster Aura Spell (%0) ?????<br>").arg(spellInfo->getExcludeCasterAuraSpell()));
    }

    if (spellInfo->getExcludeTargetAuraSpell())
    {
        if(SpellEntry const* spell = sSpellStore.LookupEntry(spellInfo->getExcludeTargetAuraSpell()))
        {
            html.append(QString("Ex Target Aura Spell (%0) %1<br>")
                .arg(spellInfo->getExcludeTargetAuraSpell())
                .arg(QString::fromUtf8(spell->SpellName)));
        }
        else
            html.append(QString("Ex Target Aura Spell (%0) ?????<br>").arg(spellInfo->getExcludeTargetAuraSpell()));
    }

    if (spellInfo->getRequiresSpellFocus())
        html.append(QString("Requires Spell Focus %0<br>")
            .arg(spellInfo->getRequiresSpellFocus()));

    if (spellInfo->getProcFlags())
    {
        QString sProcFlags(QString("%0").arg(spellInfo->getProcFlags(), 8, 16, QChar('0')));
        html.append(QString("<b>Proc flag 0x%0, chance = %1, charges - %2</b><br>")
            .arg(sProcFlags.toUpper())
            .arg(spellInfo->getProcChance())
            .arg(spellInfo->getProcCharges()));
        html.append(line);

        appendProcInfo(spellInfo, num);
    }
    else
    {
        html.append(QString("Chance = %0, charges - %1<br>")
            .arg(spellInfo->getProcChance())
            .arg(spellInfo->getProcCharges()));
    }

    html.append(line);

    appendSpellEffectInfo(spellInfo, num);

    html.append("</font>");
    browser->setHtml(html, QUrl(QString("http://spellwork/%0").arg(spellInfo->Id)));
    browser->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);

    if (num == 1)
        compare();
}

void SWObject::appendRangeInfo(SpellEntry const* spellInfo, quint8 num)
{
    QWebView* browser = m_form->getBrowser(num);

    SpellRangeEntry const* range = sSpellRangeStore.LookupEntry(spellInfo->RangeIndex);
    if (range)
    {
        html.append(QString("SpellRange: (Id %0) \"%1\": MinRange = %2, MaxRange = %3<br>")
            .arg(range->Id)
            .arg(QString::fromUtf8(range->Name))
            .arg(range->MinRangeFriendly)
            .arg(range->MaxRangeFriendly));
    }
}

void SWObject::appendProcInfo(SpellEntry const* spellInfo, quint8 num)
{
    QWebView* browser = m_form->getBrowser(num);

    quint8 i = 0;
    quint64 proc = spellInfo->getProcFlags();
    while (proc != 0)
    {
        if ((proc & 1) != 0)
            html.append(QString("  %0<br>").arg(ProcFlagDesc[i]));
        i++;
        proc >>= 1;
    }
}

void SWObject::appendSpellEffectInfo(SpellEntry const* spellInfo, quint8 num)
{
    QWebView* browser = m_form->getBrowser(num);

    for (quint8 eff = EFFECT_INDEX_0; eff < MAX_EFFECT_INDEX; eff++)
    {
        if (!spellInfo->getEffect(eff))
        {
            html.append(QString("<b>Effect %0:  NO EFFECT</b><br>").arg(eff));
            html.append(QString("<br>"));
        }
        else
        {
            QString _BasePoints(QString("BasePoints = %0").arg(spellInfo->getEffectBasePoints(eff)));

            QString _RealPoints;
            if (spellInfo->getEffectRealPointsPerLevel(eff) != 0)
                _RealPoints = QString(" + Level * %0").arg(spellInfo->getEffectRealPointsPerLevel(eff), 0, 'f', 2);

            QString _DieSides;
            if (1 < spellInfo->getEffectDieSides(eff))
            {
                if (spellInfo->getEffectRealPointsPerLevel(eff) != 0)
                    _DieSides = QString(" to %0 + lvl * %1")
                    .arg(spellInfo->getEffectBasePoints(eff) + spellInfo->getEffectDieSides(eff))
                        .arg(spellInfo->getEffectRealPointsPerLevel(eff), 0, 'f', 2);
                else
                    _DieSides = QString(" to %0").arg(spellInfo->getEffectBasePoints(eff) + spellInfo->getEffectDieSides(eff));
            }

            QString _PointsPerCombo;
            if (spellInfo->getEffectPointsPerComboPoint(eff) != 0)
                _PointsPerCombo = QString(" + combo * %0").arg(spellInfo->getEffectPointsPerComboPoint(eff), 0, 'f', 2);

            QString _DmgMultiplier;
            if (spellInfo->getEffectDamageMultiplier(eff) != 1.0f)
                _DmgMultiplier = QString(" * %0").arg(spellInfo->getEffectDamageMultiplier(eff), 0, 'f', 2);

            QString _Multiple;
            if (spellInfo->getEffectValueMultiplier(eff) != 0)
                _Multiple = QString(", Multiple = %0").arg(spellInfo->getEffectValueMultiplier(eff), 0, 'f', 2);

            QString _Result = _BasePoints + _RealPoints + _DieSides + _PointsPerCombo + _DmgMultiplier + _Multiple + "<br>";

            setMetaEnum("Effects");
            html.append(QString("<b>Effect %0: Id %1 (%2)</b><br>")
                .arg(eff)
                .arg(spellInfo->getEffect(eff))
                .arg(m_metaEnum.valueToKey(spellInfo->getEffect(eff))));

            html.append(_Result);

            setMetaEnum("Targets");
            html.append(QString("Targets (%0, %1) (%2, %3)<br>")
                .arg(spellInfo->getEffectImplicitTargetA(eff))
                .arg(spellInfo->getEffectImplicitTargetB(eff))
                .arg(m_metaEnum.valueToKey(spellInfo->getEffectImplicitTargetA(eff)))
                .arg(m_metaEnum.valueToKey(spellInfo->getEffectImplicitTargetB(eff))));

            appendAuraInfo(spellInfo, eff, num);

            appendRadiusInfo(spellInfo, eff, num);

            appendTriggerInfo(spellInfo, eff, num);

            if (spellInfo->getEffectChainTarget(eff) != 0)
                html.append(QString("EffectChainTarget = %0<br>").arg(spellInfo->getEffectChainTarget(eff)));

            if (spellInfo->getEffectMechanic(eff) != 0)
            {
                setMetaEnum("Mechanic");
                html.append(QString("Effect Mechanic = %0 (%1)<br>")
                    .arg(spellInfo->getEffectMechanic(eff))
                    .arg(m_metaEnum.valueToKey(spellInfo->getEffectMechanic(eff))));
            }

            quint32 ClassMask[3];

            for (quint8 i = 0; i < 3; i++)
                ClassMask[i] = spellInfo->getEffectSpellClassMask(eff).value[i];

            if (ClassMask[0] || ClassMask[1] || ClassMask[2])
            {
                QString sClassMask2(QString("%0").arg(ClassMask[2], 8, 16, QChar('0')));
                QString sClassMask1(QString("%0").arg(ClassMask[1], 8, 16, QChar('0')));
                QString sClassMask0(QString("%0").arg(ClassMask[0], 8, 16, QChar('0')));

                html.append(QString("SpellClassMask = %0 %1 %2<br>")
                                .arg(sClassMask2.toUpper())
                                .arg(sClassMask1.toUpper())
                                .arg(sClassMask0.toUpper()));

                for (quint32 i = 0; i < sSpellStore.GetNumRows(); i++)
                {
                    SpellEntry const* t_spellInfo = sSpellStore.LookupEntry(i);
                    if (t_spellInfo)
                    {
                        bool hasSkill = false;
                        if ((t_spellInfo->getSpellFamilyName() == spellInfo->getSpellFamilyName()) &&
                            ((t_spellInfo->getSpellFamilyFlags().value[0] & ClassMask[0]) ||
                             (t_spellInfo->getSpellFamilyFlags().value[1] & ClassMask[1]) ||
                             (t_spellInfo->getSpellFamilyFlags().value[2] & ClassMask[2])))
                        {
                            QString sName(QString::fromUtf8(t_spellInfo->SpellName));
                            QString sRank(QString::fromUtf8(t_spellInfo->Rank));

                            if (!sRank.isEmpty())
                                sName.append(" (" + sRank + ")");

                            for (quint32 sk = 0; sk < sSkillLineAbilityStore.GetNumRows(); sk++)
                            {
                                SkillLineAbilityEntry const* skillInfo = sSkillLineAbilityStore.LookupEntry(sk);
                                if (skillInfo && skillInfo->SpellId == t_spellInfo->Id && skillInfo->SkillId > 0)
                                {
                                    hasSkill = true;
                                    html.append(QString("%0<font color=blue>+ <a href='http://spellwork/%1'>%1</a> - %2</font><br>")
                                            .arg(QChar(QChar::Nbsp), 4, QChar(QChar::Nbsp))
                                            .arg(t_spellInfo->Id)
                                            .arg(sName));
                                    break;
                                }
                            }

                            if (!hasSkill)
                            {
                                html.append(QString("%0<font color=red>- <a href='http://spellwork/%1'>%1</a> - %2</font><br>")
                                        .arg(QChar(QChar::Nbsp), 4, QChar(QChar::Nbsp))
                                        .arg(t_spellInfo->Id)
                                        .arg(sName));
                            }
                        }
                    }
                }
            }

            html.append(QString("<br>"));
        }
    }
}

void SWObject::appendTriggerInfo(SpellEntry const* spellInfo, quint8 index, quint8 num)
{
    QWebView* browser = m_form->getBrowser(num);

    quint32 trigger = spellInfo->getEffectTriggerSpell(index);
    if (trigger != 0)
    {
        SpellEntry const* triggerSpell = sSpellStore.LookupEntry(trigger);
        if (triggerSpell)
        {
            QString sName(QString::fromUtf8(triggerSpell->SpellName));
            QString sRank(QString::fromUtf8(triggerSpell->Rank));

            if (!sRank.isEmpty())
                sName.append(" (" + sRank + ")");

            html.append(QString("<b><font color='blue'> Trigger spell: <a href='http://spellwork/%0'>%0</a> - %1. Chance = %2</font></b><br>")
                .arg(trigger)
                .arg(sName)
                .arg(triggerSpell->getProcChance()));

                QString sDescription(QString::fromUtf8(triggerSpell->Description));
                QString sTooltip(QString::fromUtf8(triggerSpell->ToolTip));

                if (!sDescription.isEmpty())
                    html.append(QString("Description: %0<br>").arg(getDescription(sDescription, triggerSpell)));

                if (!sTooltip.isEmpty())
                    html.append(QString("ToolTip: %0<br>").arg(getDescription(sTooltip, triggerSpell)));

                if (triggerSpell->getProcFlags() != 0)
                {
                    html.append(QString("Charges - %0<br>").arg(triggerSpell->getProcCharges()));
                    html.append(QString("<br>"));

                    appendProcInfo(triggerSpell, num);

                    html.append(QString("<br>"));
                }
        }
        else
        {
            html.append(QString("Trigger spell (%0) Not found<br>").arg(trigger));
        }
    }
}

void SWObject::appendRadiusInfo(SpellEntry const* spellInfo, quint8 index, quint8 num)
{
    QWebView* browser = m_form->getBrowser(num);

    quint16 rIndex = spellInfo->getEffectRadiusIndex(index);
    if (rIndex != 0)
    {
        SpellRadiusEntry const* spellRadius = sSpellRadiusStore.LookupEntry(rIndex);
        if (spellRadius)
        {
            html.append(QString("Radius (Id %0) %1<br>")
                .arg(rIndex)
                .arg(spellRadius->RadiusFriendly, 0, 'f', 2));
        }
        else
            html.append(QString("Radius (Id %0) Not found<br>").arg(rIndex));
    }
}

void SWObject::appendAuraInfo(SpellEntry const* spellInfo, quint8 index, quint8 num)
{
    QWebView* browser = m_form->getBrowser(num);

    setMetaEnum("AuraType");
    QString sAura(m_metaEnum.valueToKey(spellInfo->getEffectApplyAuraName(index)));
    quint32 misc = spellInfo->getEffectMiscValue(index);

    if (spellInfo->getEffectApplyAuraName(index) == 0)
    {
        if (spellInfo->getEffectMiscValue(index) != 0)
            html.append(QString("EffectMiscValueA = %0<br>").arg(spellInfo->getEffectMiscValue(index)));

        if (spellInfo->getEffectMiscValueB(index) != 0)
            html.append(QString("EffectMiscValueB = %0<br>").arg(spellInfo->getEffectMiscValueB(index)));

        if (spellInfo->getEffectAmplitude(index) != 0)
            html.append(QString("EffectAmplitude = %0<br>").arg(spellInfo->getEffectAmplitude(index)));

        return;
    }

    QString _BaseAuraInfo;
    _BaseAuraInfo = QString("Aura Id %0 (%1), value = %2, misc = %3<br>")
        .arg(spellInfo->getEffectApplyAuraName(index))
        .arg(sAura)
        .arg(spellInfo->getEffectBasePoints(index))
        .arg(misc);

    QString _SpecialAuraInfo;
    switch (spellInfo->getEffectApplyAuraName(index))
    {
        case 29:
            setMetaEnum("UnitMods");
            _SpecialAuraInfo = QString("(%0").arg(m_metaEnum.valueToKey(misc));
            break;
        case 189:
            _SpecialAuraInfo = QString("(%0").arg(containAttributes(spellInfo, TYPE_CR, index));
            break;
        case 107:
        case 108:
            setMetaEnum("SpellModOp");
            _SpecialAuraInfo = QString("(%0").arg(m_metaEnum.valueToKey(misc));
            break;
        // todo: more case
        default:
            _SpecialAuraInfo = QString("(%0").arg(misc);
            break;
    }

    QString _MiscB = QString("), miscB = %0").arg(spellInfo->getEffectMiscValueB(index));
    QString _Periodic = QString(", periodic = %0").arg(spellInfo->getEffectAmplitude(index));
    QString _Result = _BaseAuraInfo + _SpecialAuraInfo + _MiscB + _Periodic;
    html.append(_Result + "<br>");
}

QString SWObject::containAttributes(SpellEntry const* spellInfo, AttrType attr, quint8 index)
{
    QString str("");
    switch (attr)
    {
        case TYPE_ATTR:
        {
            setMetaEnum("Attributes");
            for (quint8 i = 0; i < m_metaEnum.keyCount(); i++)
            {
                if (spellInfo->Attributes & m_metaEnum.value(i))
                {
                    QString tstr(QString("%0, ").arg(m_metaEnum.key(i)));
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
            setMetaEnum("AttributesEx");
            for (quint8 i = 0; i < m_metaEnum.keyCount(); i++)
            {
                if (spellInfo->AttributesEx & m_metaEnum.value(i))
                {
                    QString tstr(QString("%0, ").arg(m_metaEnum.key(i)));
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
            setMetaEnum("AttributesEx2");
            for (quint8 i = 0; i < m_metaEnum.keyCount(); i++)
            {
                if (spellInfo->AttributesEx2 & m_metaEnum.value(i))
                {
                    QString tstr(QString("%0, ").arg(m_metaEnum.key(i)));
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
            setMetaEnum("AttributesEx3");
            for (quint8 i = 0; i < m_metaEnum.keyCount(); i++)
            {
                if (spellInfo->AttributesEx3 & m_metaEnum.value(i))
                {
                    QString tstr(QString("%0, ").arg(m_metaEnum.key(i)));
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
            setMetaEnum("AttributesEx4");
            for (quint8 i = 0; i < m_metaEnum.keyCount(); i++)
            {
                if (spellInfo->AttributesEx4 & m_metaEnum.value(i))
                {
                    QString tstr(QString("%0, ").arg(m_metaEnum.key(i)));
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
            setMetaEnum("AttributesEx5");
            for (quint8 i = 0; i < m_metaEnum.keyCount(); i++)
            {
                if (spellInfo->AttributesEx5 & m_metaEnum.value(i))
                {
                    QString tstr(QString("%0, ").arg(m_metaEnum.key(i)));
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
            setMetaEnum("AttributesEx6");
            for (quint8 i = 0; i < m_metaEnum.keyCount(); i++)
            {
                if (spellInfo->AttributesEx6 & m_metaEnum.value(i))
                {
                    QString tstr(QString("%0, ").arg(m_metaEnum.key(i)));
                    str += tstr;
                }
            }
            if (!str.isEmpty())
                str.chop(2);
            return str;
        }
        break;
        case TYPE_ATTR_EX7:
        {
            setMetaEnum("AttributesEx7");
            for (quint8 i = 0; i < m_metaEnum.keyCount(); i++)
            {
                if (spellInfo->AttributesEx7 & m_metaEnum.value(i))
                {
                    QString tstr(QString("%0, ").arg(m_metaEnum.key(i)));
                    str += tstr;
                }
            }
            if (!str.isEmpty())
                str.chop(2);
            return str;
        }
        break;
        case TYPE_ATTR_EX8:
        {
            setMetaEnum("AttributesEx8");
            for (quint8 i = 0; i < m_metaEnum.keyCount(); i++)
            {
                if (spellInfo->AttributesEx8 & m_metaEnum.value(i))
                {
                    QString tstr(QString("%0, ").arg(m_metaEnum.key(i)));
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
            setMetaEnum("TargetFlags");
            for (quint8 i = 0; i < m_metaEnum.keyCount(); i++)
            {
                if (spellInfo->getTargets() & m_metaEnum.value(i))
                {
                    QString tstr(QString("%0, ").arg(m_metaEnum.key(i)));
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
            setMetaEnum("CreatureType");
            for (quint8 i = 0; i < m_metaEnum.keyCount(); i++)
            {
                if (spellInfo->getTargetCreatureType() & m_metaEnum.value(i))
                {
                    QString tstr(QString("%0, ").arg(m_metaEnum.key(i)));
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
            setMetaEnum("ShapeshiftFormMask");
            for (quint8 i = 0; i < m_metaEnum.keyCount(); i++)
            {
                if (spellInfo->getStances().value[0] & m_metaEnum.value(i))
                {
                    QString tstr(QString("%0, ").arg(m_metaEnum.key(i)));
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
            setMetaEnum("ShapeshiftFormMask");
            for (quint8 i = 0; i < m_metaEnum.keyCount(); i++)
            {
                if (spellInfo->getStancesNot().value[0] & m_metaEnum.value(i))
                {
                    QString tstr(QString("%0, ").arg(m_metaEnum.key(i)));
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
            setMetaEnum("ItemSubClassWeaponMask");
            for (quint8 i = 0; i < m_metaEnum.keyCount(); i++)
            {
                if (spellInfo->getEquippedItemSubClassMask() & m_metaEnum.value(i))
                {
                    QString tstr(QString("%0, ").arg(m_metaEnum.key(i)));
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
            setMetaEnum("ItemSubClassArmorMask");
            for (quint8 i = 0; i < m_metaEnum.keyCount(); i++)
            {
                if (spellInfo->getEquippedItemSubClassMask() & m_metaEnum.value(i))
                {
                    QString tstr(QString("%0, ").arg(m_metaEnum.key(i)));
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
            setMetaEnum("ItemSubClassMiscMask");
            for (quint8 i = 0; i < m_metaEnum.keyCount(); i++)
            {
                if (spellInfo->getEquippedItemSubClassMask() & m_metaEnum.value(i))
                {
                    QString tstr(QString("%0, ").arg(m_metaEnum.key(i)));
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
            setMetaEnum("InventoryTypeMask");
            for (quint8 i = 0; i < m_metaEnum.keyCount(); i++)
            {
                if (spellInfo->getEquippedItemInventoryTypeMask() & m_metaEnum.value(i))
                {
                    QString tstr(QString("%0, ").arg(m_metaEnum.key(i)));
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
            setMetaEnum("CombatRating");
            for (quint8 i = 0; i < m_metaEnum.keyCount(); i++)
            {
                if (spellInfo->getEffectMiscValue(index) & m_metaEnum.value(i))
                {
                    QString tstr(QString("%0, ").arg(m_metaEnum.key(i)));
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
            setMetaEnum("SpellSchoolMask");
            for (quint8 i = 0; i < m_metaEnum.keyCount(); i++)
            {
                if (spellInfo->SchoolMask == m_metaEnum.value(i))
                {
                    QString tstr(QString("%0, ").arg(m_metaEnum.key(i)));
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

void SWObject::appendSkillLine(SpellEntry const* spellInfo, quint8 num)
{
    QWebView* browser = m_form->getBrowser(num);

    for (quint32 i = 0; i < sSkillLineAbilityStore.GetNumRows(); i++)
    {
        SkillLineAbilityEntry const* skillInfo = sSkillLineAbilityStore.LookupEntry(i);
        if (skillInfo && skillInfo->SpellId == spellInfo->Id)
        {
            SkillLineEntry const* skill = sSkillLineStore.LookupEntry(skillInfo->SkillId);
            html.append(QString("Skill (Id %0) \"%1\", ReqSkillValue = %2, Forward Spell = %3, MinMaxValue (%4, %5), CharacterPoints (%6, %7)<br>")
                .arg(skill->Id)
                .arg(QString::fromUtf8(skill->Name))
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

void SWObject::appendCastTimeLine(SpellEntry const* spellInfo, quint8 num)
{
    QWebView* browser = m_form->getBrowser(num);

    SpellCastTimesEntry const* castInfo = sSpellCastTimesStore.LookupEntry(spellInfo->CastingTimeIndex);
    if (castInfo)
    {
        html.append(QString("CastingTime (Id %0) = %1<br>")
            .arg(castInfo->Id)
            .arg(float(castInfo->CastTime) / 1000, 0, 'f', 2));
    }
}

void SWObject::appendDurationLine(SpellEntry const* spellInfo, quint8 num)
{
    QWebView* browser = m_form->getBrowser(num);

    SpellDurationEntry const* durationInfo = sSpellDurationStore.LookupEntry(spellInfo->DurationIndex);
    if (durationInfo)
    {
        html.append(QString("Duration: ID (%0)  %1, %2, %3<br>")
            .arg(durationInfo->Id)
            .arg(durationInfo->Duration[0])
            .arg(durationInfo->Duration[1])
            .arg(durationInfo->Duration[2]));
    }
}

void SWObject::compare()
{
    QStringList list1 = m_form->webView->page()->mainFrame()->toPlainText().split("\n");
    QStringList list2 = m_form->webView_2->page()->mainFrame()->toPlainText().split("\n");

    QString html2;
    html.clear();
    html2.clear();

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
            html.append(line + "<br>");
            continue;
        }

        if (yes)
            html.append(QString("<span style='background-color: cyan'>%0</span><br>").arg(list1.at(i)));
        else
            html.append(QString("<span style='background-color: salmon'>%0</span><br>").arg(list1.at(i)));
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
            html2.append(line + "<br>");
            continue;
        }

        if (yes)
            html2.append(QString("<span style='background-color: cyan'>%0</span><br>").arg(list2.at(i)));
        else
            html2.append(QString("<span style='background-color: salmon'>%0</span><br>").arg(list2.at(i)));
    }

    m_form->webView->setHtml(html);
    m_form->webView_2->setHtml(html2);
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
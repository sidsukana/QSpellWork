#include <QBuffer>
#include <QThread>
#include <QResource>

#include "SWObject.h"
#include "SWModels.h"
#include "Defines.h"
#include "blp/BLP.h"

#include "mustache/mustache.h"

Q_DECLARE_METATYPE(Spell::meta*)

SWObject::SWObject(MainForm* form)
    : QObject(form), m_form(form), m_regExp(false), m_type(0), m_enums(form->getEnums())
{
    QFile templateFile("data/template.html");
    templateFile.open(QIODevice::ReadOnly);
    m_templateHtml = templateFile.readAll();
    templateFile.close();

    QFile styleFile("data/style.css");
    styleFile.open(QIODevice::ReadOnly);
    m_styleCss = styleFile.readAll();
    styleFile.close();
}

QList<QEvent*> SWObject::search()
{
    SpellListModel *model = new SpellListModel();
    QList<QEvent*> eventList;

    if (getType() == 1)
    {
        for (quint32 i = 0; i < Spell::getHeader()->recordCount; ++i)
        {
            bool family = false;
            bool aura = false;
            bool effect = false;
            bool targetA = false;
            bool targetB = false;

            if (const Spell::entry* m_spellInfo = Spell::getRecord(i))
            {
                if (m_form->comboBox->currentIndex() > 0)
                {
                    quint16 familyId = m_form->comboBox->itemData(m_form->comboBox->currentIndex()).toInt();
                    if (m_spellInfo->spellFamilyName == familyId)
                        family = true;
                }
                else
                    family = true;

                if (m_form->comboBox_2->currentIndex() > 0)
                {
                    quint16 auraId = m_form->comboBox_2->itemData(m_form->comboBox_2->currentIndex()).toInt();
                    for (quint8 i = 0; i < MAX_EFFECT_INDEX; ++i)
                    {
                        if (m_spellInfo->effectApplyAuraName[i] == auraId)
                        {
                            aura = true;
                            break;
                        }
                    }
                }
                else
                    aura = true;

                if (m_form->comboBox_3->currentIndex() > 0)
                {
                    quint16 effectId = m_form->comboBox_3->itemData(m_form->comboBox_3->currentIndex()).toInt();
                    for (quint8 i = 0; i < MAX_EFFECT_INDEX; ++i)
                    {
                        if (m_spellInfo->effect[i] == effectId)
                        {
                            effect = true;
                            break;
                        }
                    }
                }
                else
                    effect = true;

                if (m_form->comboBox_4->currentIndex() > 0)
                {
                    quint16 targetId = m_form->comboBox_4->itemData(m_form->comboBox_4->currentIndex()).toInt();
                    for (quint8 i = 0; i < MAX_EFFECT_INDEX; ++i)
                    {
                        if (m_spellInfo->effectImplicitTargetA[i] == targetId)
                        {
                            targetA = true;
                            break;
                        }
                    }
                }
                else
                    targetA = true;

                if (m_form->comboBox_5->currentIndex() > 0)
                {
                    quint16 targetId = m_form->comboBox_5->itemData(m_form->comboBox_5->currentIndex()).toInt();
                    for (quint8 i = 0; i < MAX_EFFECT_INDEX; ++i)
                    {
                        if (m_spellInfo->effectImplicitTargetB[i] == targetId)
                        {
                            targetB = true;
                            break;
                        }
                    }
                }
                else
                    targetB = true;

                if (family && aura && effect && targetA && targetB)
                {
                    QStringList spellRecord;
                    spellRecord << QString("%0").arg(m_spellInfo->id) << m_spellInfo->nameWithRank();

                    model->appendRecord(spellRecord);
                }
            }
        }
        Event* ev = new Event(Event::Type(Event::EVENT_SEND_MODEL));
        ev->addValue(QVariant::fromValue(model));
        eventList << ev;
    }
    else if (getType() == 3)
    {
        QJSEngine engine;

        EnumHash enums = m_form->getEnums()->getEnums();

        for (EnumHash::const_iterator itr = enums.begin(); itr != enums.end(); ++itr)
            for (Enumerator::const_iterator itr2 = itr->begin(); itr2 != itr->end(); ++itr2)
                engine.globalObject().setProperty(itr2.value(), qreal(itr2.key()));

        QString text = m_form->getFilterText();
        QJSValue script = engine.evaluate(text.contains("function()") ? "(" + text + ")" : "(function() { return (" + text + "); })");

        for (quint32 i = 0; i < Spell::getHeader()->recordCount; ++i)
        {
            const Spell::entry* m_spellInfo = Spell::getRecord(i);

            if (!m_spellInfo)
                continue;

            Spell::meta metaSpell(m_spellInfo);

            engine.globalObject().setProperty("spell", engine.newQObject(&metaSpell));

            if (script.call(QJSValueList()).toBool())
            {
                QStringList spellRecord;
                spellRecord << QString("%0").arg(m_spellInfo->id) << m_spellInfo->nameWithRank();

                model->appendRecord(spellRecord);
            }
        }

        Event* ev = new Event(Event::Type(Event::EVENT_SEND_MODEL));
        ev->addValue(QVariant::fromValue(model));
        eventList << ev;
    }
    else
    {
        if (!m_form->findLine_e1->text().isEmpty())
        {
            if (!m_form->findLine_e1->text().toInt())
            {
                for (quint32 i = 0; i < Spell::getHeader()->recordCount; ++i)
                {
                    const Spell::entry* m_spellInfo = Spell::getRecord(i);
                    if (m_spellInfo && m_spellInfo->name().contains(m_form->findLine_e1->text(), Qt::CaseInsensitive))
                    {
                        QStringList spellRecord;
                        spellRecord << QString("%0").arg(m_spellInfo->id) << m_spellInfo->nameWithRank();

                        model->appendRecord(spellRecord);
                    }
                }

                Event* ev = new Event(Event::Type(Event::EVENT_SEND_MODEL));
                ev->addValue(QVariant::fromValue(model));
                eventList << ev;
            }
            else
            {
                if (const Spell::entry* m_spellInfo = Spell::getRecord(m_form->findLine_e1->text().toInt(), true))
                {
                    QStringList spellRecord;
                    spellRecord << QString("%0").arg(m_spellInfo->id) << m_spellInfo->nameWithRank();

                    model->appendRecord(spellRecord);

                    Event* ev1 = new Event(Event::Type(Event::EVENT_SEND_MODEL));
                    ev1->addValue(QVariant::fromValue(model));
                    eventList << ev1;

                    Event* ev2 = new Event(Event::Type(Event::EVENT_SEND_SPELL));
                    ev2->addValue(m_spellInfo->id);
                    eventList << ev2;
                }
            }
        }
        else if (!m_form->findLine_e3->text().isEmpty())
        {
            for (quint32 i = 0; i < Spell::getHeader()->recordCount; ++i)
            {
                const Spell::entry* m_spellInfo = Spell::getRecord(i);
                if (m_spellInfo && m_spellInfo->description().contains(m_form->findLine_e3->text(), Qt::CaseInsensitive))
                {
                    QStringList spellRecord;
                    spellRecord << QString("%0").arg(m_spellInfo->id) << m_spellInfo->nameWithRank();

                    model->appendRecord(spellRecord);
                }
            }

            Event* ev = new Event(Event::Type(Event::EVENT_SEND_MODEL));
            ev->addValue(QVariant::fromValue(model));
            eventList << ev;
        }
        else
        {
            for (quint32 i = 0; i < Spell::getHeader()->recordCount; ++i)
            {
                if (const Spell::entry* m_spellInfo = Spell::getRecord(i))
                {
                    QStringList spellRecord;
                    spellRecord << QString("%0").arg(m_spellInfo->id) << m_spellInfo->nameWithRank();

                    model->appendRecord(spellRecord);
                }
            }

            Event* ev = new Event(Event::Type(Event::EVENT_SEND_MODEL));
            ev->addValue(QVariant::fromValue(model));
            eventList << ev;
        }
    }

    return eventList;
}

void SWObject::setMetaEnum(const char* enumName)
{
    m_metaEnum = Enums::staticMetaObject.enumerator(Enums::staticMetaObject.indexOfEnumerator(enumName));
}

float getRadius(const Spell::entry* spellInfo, quint8 effIndex)
{
    if (const SpellRadius::entry* spellRadius = SpellRadius::getRecord(spellInfo->effectRadiusIndex[effIndex], true))
        return spellRadius->radius;

    return 0.0f;
}

quint32 getDuration(const Spell::entry* spellInfo)
{
    if (const SpellDuration::entry* durationInfo = SpellDuration::getRecord(spellInfo->durationIndex, true))
        return quint32(durationInfo->duration / 1000);

    return 1;
}

quint32 getRealDuration(const Spell::entry* spellInfo, quint8 effIndex)
{
    return quint32(getDuration(spellInfo) / (spellInfo->effectAmplitude[effIndex] ? quint32(spellInfo->effectAmplitude[effIndex] / 1000) : 5));
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
        if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
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
        if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
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
                        .arg(quint32((getRealDuration(tSpell, rx.cap(6).toInt()-1) * (tSpell->effectBasePoints[rx.cap(6).toInt()-1] + 1)) / rx.cap(3).toInt())));
                }
                else if(rx.cap(2) == QString("*"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(quint32((getRealDuration(tSpell, rx.cap(6).toInt()-1) * (tSpell->effectBasePoints[rx.cap(6).toInt()-1] + 1)) * rx.cap(3).toInt())));
                }
            }
        }
        else
        {
            if (rx.cap(2) == QString("/"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(quint32((getRealDuration(spellInfo, rx.cap(6).toInt()-1) * (spellInfo->effectBasePoints[rx.cap(6).toInt()-1] + 1)) / rx.cap(3).toInt())));
            }
            else if (rx.cap(2) == QString("*"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(quint32((getRealDuration(spellInfo, rx.cap(6).toInt()-1) * (spellInfo->effectBasePoints[rx.cap(6).toInt()-1] + 1)) * rx.cap(3).toInt())));
            }
        }
    }
    else if (!rx.cap(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(getRealDuration(tSpell, rx.cap(6).toInt()-1) * (tSpell->effectBasePoints[rx.cap(6).toInt()-1] + 1)));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(getRealDuration(spellInfo, rx.cap(6).toInt()-1) * (spellInfo->effectBasePoints[rx.cap(6).toInt()-1] + 1)));
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

QString SWObject::getDescription(QString str, const Spell::entry* spellInfo)
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

QVariantList SWObject::getParentSpells(quint32 triggerId)
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

QString SWObject::getSpellIconName(quint32 iconId)
{
    const SpellIcon::entry* iconInfo = SpellIcon::getRecord(iconId, true);

    return (iconInfo ? iconInfo->iconPath().section('\\', -1) : QString(""));
}

QImage SWObject::getSpellIcon(quint32 iconId)
{
    const SpellIcon::entry* iconInfo = SpellIcon::getRecord(iconId, true);

    return (iconInfo ? BLP::getImage(iconInfo->iconPath() + QString(".blp")) : QImage());
}

void SWObject::showInfo(const Spell::entry* spellInfo, QSW::Pages pageId)
{
    if (!spellInfo)
        return;

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

    QVariantHash values;
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
    values["spellFamilyName"] = m_enums->getSpellFamilies()[spellInfo->spellFamilyName];
    values["spellFamilyFlags"] = sSpellFamilyFlags;

    values["spellSchoolId"] = spellInfo->school;
    values["spellSchoolName"] = m_enums->getSchools()[spellInfo->school];

    values["damageClassId"] = spellInfo->damageClass;
    values["damageClassName"] = m_enums->getDamageClasses()[spellInfo->damageClass];

    values["preventionTypeId"] = spellInfo->preventionType;
    values["preventionTypeName"] = m_enums->getPreventionTypes()[spellInfo->preventionType];

    if (spellInfo->attributes || spellInfo->attributesEx1 || spellInfo->attributesEx2 ||
        spellInfo->attributesEx3 || spellInfo->attributesEx4)
    {
        values["hasAttributes"] = true;

        if (spellInfo->attributes)
        {
            values["attr"] = sAttributes;
            values["attrNames"] = containAttributes(spellInfo, TYPE_ATTR);
        }

        if (spellInfo->attributesEx1)
        {
            values["attrEx1"] = sAttributesEx1;
            values["attrEx1Names"] = containAttributes(spellInfo, TYPE_ATTR_EX1);
        }

        if (spellInfo->attributesEx2)
        {
            values["attrEx2"] = sAttributesEx2;
            values["attrEx2Names"] = containAttributes(spellInfo, TYPE_ATTR_EX2);
        }

        if (spellInfo->attributesEx3)
        {
            values["attrEx3"] = sAttributesEx3;
            values["attrEx3Names"] = containAttributes(spellInfo, TYPE_ATTR_EX3);
        }

        if (spellInfo->attributesEx4)
        {
            values["attrEx4"] = sAttributesEx4;
            values["attrEx4Names"] = containAttributes(spellInfo, TYPE_ATTR_EX4);
        }
    }

    if (spellInfo->targets)
    {
        values["targets"] = sTargetMask;
        values["targetsNames"] = containAttributes(spellInfo, TYPE_TARGETS);
    }

    if (spellInfo->targetCreatureType)
    {
        values["creatureType"] = sCreatureTypeMask;
        values["creatureTypeNames"] = containAttributes(spellInfo, TYPE_CREATURE);
    }

    if (spellInfo->stances)
    {
        values["stances"] = sFormMask;
        values["stancesNames"] = containAttributes(spellInfo, TYPE_FORMS);
    }

    if (spellInfo->stancesNot)
    {
        values["stancesNot"] = sFormMask;
        values["stancesNotNames"] = containAttributes(spellInfo, TYPE_FORMS_NOT);
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
        values["equipItemClassName"] = m_enums->getItemClasses()[spellInfo->equippedItemClass];

        if (spellInfo->equippedItemSubClassMask)
        {
            QString sItemSubClassMask("0x" + QString("%0").arg(spellInfo->equippedItemSubClassMask, 8, 16, QChar('0')).toUpper());
            values["equipItemSubClassMask"] = sItemSubClassMask;

            switch (spellInfo->equippedItemClass)
            {
                case 2: // WEAPON
                    values["equipItemSubClassMaskNames"] = containAttributes(spellInfo, TYPE_ITEM_WEAPON);
                    break;
                case 4: // ARMOR
                    values["equipItemSubClassMaskNames"] = containAttributes(spellInfo, TYPE_ITEM_ARMOR);
                    break;
                case 15: // MISC
                    values["equipItemSubClassMaskNames"] = containAttributes(spellInfo, TYPE_ITEM_MISC);
                    break;
                default: break;
            }
        }

        if (spellInfo->equippedItemInventoryTypeMask)
        {
            QString sItemInventoryMask("0x" + QString("%0").arg(spellInfo->equippedItemInventoryTypeMask, 8, 16, QChar('0')).toUpper());
            values["equipItemInvTypeMask"] = sItemInventoryMask;
            values["equipItemInvTypeMaskNames"] = containAttributes(spellInfo, TYPE_ITEM_INVENTORY);
        }
    }

    values["categoryId"] = spellInfo->category;
    values["dispelId"] = spellInfo->dispel;
    values["dispelName"] = m_enums->getDispelTypes()[spellInfo->dispel];
    values["mechanicId"] = spellInfo->mechanic;
    values["mechanicName"] = m_enums->getMechanics()[spellInfo->mechanic];

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
    values["powerTypeName"] = m_enums->getPowers()[spellInfo->powerType];
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
        values["casterAuraStateName"] = m_enums->getAuraStates()[spellInfo->casterAuraState];
    }

    if (spellInfo->targetAuraState)
    {
        values["targetAuraState"] = spellInfo->targetAuraState;
        values["targetAuraStateName"] = m_enums->getAuraStates()[spellInfo->targetAuraState];
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
        effectValues["name"] = m_enums->getSpellEffects()[spellInfo->effect[eff]];

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
        effectValues["targetNameA"] = m_enums->getTargets()[spellInfo->effectImplicitTargetA[eff]];
        effectValues["targetNameB"] = m_enums->getTargets()[spellInfo->effectImplicitTargetB[eff]];

        quint32 misc = spellInfo->effectMiscValue[eff];
        effectValues["miscValue"] = misc;
        effectValues["amplitude"] = spellInfo->effectAmplitude[eff];
        effectValues["auraId"] = spellInfo->effectApplyAuraName[eff];
        effectValues["auraName"] = m_enums->getSpellAuras()[spellInfo->effectApplyAuraName[eff]];

        switch (spellInfo->effectApplyAuraName[eff])
        {
            case 29:
                effectValues["mods"] = m_enums->getUnitMods()[misc];
                break;
            case 107:
            case 108:
                effectValues["mods"] = m_enums->getSpellMods()[misc];
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
        effectValues["mechanicName"] = m_enums->getMechanics()[spellInfo->effectMechanic[eff]];

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
    values["style"] = m_styleCss;

    Mustache::Renderer renderer;
    Mustache::QtVariantContext context(values);

    QString html;
    QTextStream stream(&html);
    stream << renderer.render(m_templateHtml, &context);

    html.replace("\n", "");
    html.replace("><", ">\n<");

    m_form->getPage(pageId)->setInfo(html, spellInfo->id);
}

QString SWObject::containAttributes(Spell::entry const* spellInfo, MaskType type)
{
    QString str("");
    switch (type)
    {
        case TYPE_ATTR:
        {
            EnumIterator itr(m_enums->getAttributes());
            while (itr.hasNext())
            {
                itr.next();
                if (spellInfo->attributes & itr.key())
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
            EnumIterator itr(m_enums->getAttributesEx1());
            while (itr.hasNext())
            {
                itr.next();
                if (spellInfo->attributesEx1 & itr.key())
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
            EnumIterator itr(m_enums->getAttributesEx2());
            while (itr.hasNext())
            {
                itr.next();
                if (spellInfo->attributesEx2 & itr.key())
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
            EnumIterator itr(m_enums->getAttributesEx3());
            while (itr.hasNext())
            {
                itr.next();
                if (spellInfo->attributesEx3 & itr.key())
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
            EnumIterator itr(m_enums->getAttributesEx4());
            while (itr.hasNext())
            {
                itr.next();
                if (spellInfo->attributesEx4 & itr.key())
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
            EnumIterator itr(m_enums->getTargetFlags());
            while (itr.hasNext())
            {
                itr.next();
                if (spellInfo->targets & itr.key())
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
            EnumIterator itr(m_enums->getCreatureTypes());
            while (itr.hasNext())
            {
                itr.next();
                if (spellInfo->targetCreatureType & itr.key())
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
            EnumIterator itr(m_enums->getShapeshiftForms());
            while (itr.hasNext())
            {
                itr.next();
                if (spellInfo->stances & itr.key())
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
            EnumIterator itr(m_enums->getShapeshiftForms());
            while (itr.hasNext())
            {
                itr.next();
                if (spellInfo->stancesNot & itr.key())
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
            EnumIterator itr(m_enums->getItemSubClassWeapons());
            while (itr.hasNext())
            {
                itr.next();
                if (spellInfo->equippedItemSubClassMask & itr.key())
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
            EnumIterator itr(m_enums->getItemSubClassArmors());
            while (itr.hasNext())
            {
                itr.next();
                if (spellInfo->equippedItemSubClassMask & itr.key())
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
            EnumIterator itr(m_enums->getItemSubClassMiscs());
            while (itr.hasNext())
            {
                itr.next();
                if (spellInfo->equippedItemSubClassMask & itr.key())
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
            EnumIterator itr(m_enums->getInventoryTypes());
            while (itr.hasNext())
            {
                itr.next();
                if (spellInfo->equippedItemInventoryTypeMask & itr.key())
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

void SWObject::compare()
{
    QStringList list1 = m_form->getPage(QSW::PAGE_CLEFT)->getSourceHtml().split("\n");
    QStringList list2 = m_form->getPage(QSW::PAGE_CRIGHT)->getSourceHtml().split("\n");

    QString html1, html2;

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
                // QString r1 = rx.cap(0); // Full
                QString r2 = rx.cap(1); // <xxx>
                QString r3 = rx.cap(2); // <>xxx</>
                QString r4 = rx.cap(3); // </xxx>

                if (r2 == "<b>")
                    html1.append(QString("<span style='background-color: cyan'>%0</span>").arg((*itr1)));
                else if (r2 == "<style>")
                {
                    html1.append((*itr1));
                }
                else
                {
                    r3 = QString("<span style='background-color: cyan'>%0</span>").arg(r3);
                    r3.prepend(r2);
                    r3.append(r4);
                    html1.append(r3);
                }
            }
            else
                html1.append((*itr1));
        }
        else
        {
            if (rx.indexIn((*itr1)) != -1)
            {
                // QString r1 = rx.cap(0); // Full
                QString r2 = rx.cap(1); // <xxx>
                QString r3 = rx.cap(2); // <>xxx</>
                QString r4 = rx.cap(3); // </xxx>

                if (r2 == "<b>")
                    html1.append(QString("<span style='background-color: salmon'>%0</span>").arg((*itr1)));
                else if (r2 == "<style>")
                {
                    html1.append((*itr1));
                }
                else
                {
                    r3 = QString("<span style='background-color: salmon'>%0</span>").arg(r3);
                    r3.prepend(r2);
                    r3.append(r4);
                    html1.append(r3);
                }
            }
            else
                html1.append((*itr1));
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
                // QString r1 = rx.cap(0); // Full
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
                // QString r1 = rx.cap(0); // Full
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

    m_form->getPage(QSW::PAGE_CLEFT)->setCompareInfo(html1);
    m_form->getPage(QSW::PAGE_CRIGHT)->setCompareInfo(html2);
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

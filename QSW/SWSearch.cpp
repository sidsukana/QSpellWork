#include "SWSearch.h"
#include "SWModels.h"
#include "SWDefines.h"

Q_DECLARE_METATYPE(MetaSpell*)

MetaSpell::MetaSpell() : m_spellInfo(NULL)
{

}

SWSearch::SWSearch(SWObject* sw, QObject* parent)
: QObject(parent), m_sw(sw), m_form(sw->getForm())
{
    m_scriptEngine = new QScriptEngine(this);

    EnumHash enums = m_form->getEnums()->getEnums();

    for (EnumHash::const_iterator itr = enums.begin(); itr != enums.end(); ++itr)
        for (Enumerator::const_iterator itr2 = itr->begin(); itr2 != itr->end(); ++itr2)
            m_scriptEngine->globalObject().setProperty(itr2.value(), qsreal(itr2.key()));

    m_script = m_scriptEngine->evaluate("(function() { return (" + m_form->getFilterText() + "); })");
}

SWSearch::~SWSearch()
{
    delete m_scriptEngine;
}

bool SWSearch::hasValue(const Spell::entry* spellInfo)
{
    if (!spellInfo)
        return false;

    MetaSpell metaSpell;
    metaSpell.setSpell(spellInfo);

    m_scriptEngine->globalObject().setProperty("spell", m_scriptEngine->newQObject(&metaSpell));

    return m_script.call(QScriptValue()).toBool();
}

QList<QEvent*> SWSearch::search()
{
    SpellListModel *model = new SpellListModel();
    QList<QEvent*> eventList;

    if (m_sw->getType() == 1)
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
                    QString sRank(m_spellInfo->rank());
                    QString sFullName(m_spellInfo->name());

                    if (!sRank.isEmpty())
                        sFullName.append(QString(" (%0)").arg(sRank));

                    QStringList spellRecord;
                    spellRecord << QString("%0").arg(m_spellInfo->id) << sFullName;

                    model->appendRecord(spellRecord);
                }
            }
        }
        Event* ev = new Event(Event::Type(Event::EVENT_SEND_MODEL));
        ev->addValue(QVariant::fromValue(model));
        eventList << ev;
    }
    else if (m_sw->getType() == 3)
    {
        for (quint32 i = 0; i < Spell::getHeader()->recordCount; ++i)
        {
            const Spell::entry* m_spellInfo = Spell::getRecord(i);
            if (hasValue(m_spellInfo))
            {
                QString sRank(m_spellInfo->rank());
                QString sFullName(m_spellInfo->name());

                if (!sRank.isEmpty())
                    sFullName.append(QString(" (%0)").arg(sRank));

                QStringList spellRecord;
                spellRecord << QString("%0").arg(m_spellInfo->id) << sFullName;

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
                        QString sRank(m_spellInfo->rank());
                        QString sFullName(m_spellInfo->name());

                        if (!sRank.isEmpty())
                            sFullName.append(QString(" (%0)").arg(sRank));

                        QStringList spellRecord;
                        spellRecord << QString("%0").arg(m_spellInfo->id) << sFullName;

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
                    QString sRank(m_spellInfo->rank());
                    QString sFullName(m_spellInfo->name());

                    if (!sRank.isEmpty())
                        sFullName.append(QString(" (%0)").arg(sRank));

                    QStringList spellRecord;
                    spellRecord << QString("%0").arg(m_spellInfo->id) << sFullName;

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
                    QString sRank(m_spellInfo->rank());
                    QString sFullName(m_spellInfo->name());

                    if (!sRank.isEmpty())
                        sFullName.append(QString(" (%0)").arg(sRank));

                    QStringList spellRecord;
                    spellRecord << QString("%0").arg(m_spellInfo->id) << sFullName;

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
                    QString sRank(m_spellInfo->rank());
                    QString sFullName(m_spellInfo->name());

                    if (!sRank.isEmpty())
                        sFullName.append(QString(" (%0)").arg(sRank));

                    QStringList spellRecord;
                    spellRecord << QString("%0").arg(m_spellInfo->id) << sFullName;

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

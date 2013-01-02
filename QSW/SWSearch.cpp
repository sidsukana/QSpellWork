#include "SWSearch.h"
#include "SWModels.h"

SWSearch::SWSearch(SWObject* sw)
: m_sw(sw), m_form(sw->getForm())
{
}

SWSearch::~SWSearch()
{
}

bool SWSearch::hasValue(int index, QString value, SpellEntry const* spellInfo)
{
    QString signature = m_form->adBox1->itemData(index, 33).toString();
    quint8 arraySize = m_form->adBox1->itemData(index, 34).toUInt();

    MetaSpell metaSpell(spellInfo);

    QMetaMethod handler = metaSpell.metaObject()->method(metaSpell.metaObject()->indexOfMethod(qPrintable(signature)));

    QVariant spellValue;

    value.remove(QChar(32));

    switch (value.at(0).toLatin1())
    {
        case '=':
        {
            value.remove(0, 1);

            if (arraySize)
            {
                for (quint8 i = 0; i < arraySize; ++i)
                    if (handler.invoke(&metaSpell, Q_RETURN_ARG(QVariant, spellValue), Q_ARG(quint8, i)))
                        if (spellValue.toLongLong() == Converter::getLongLong(value))
                            return true;
            }
            else
            {
                if (handler.invoke(&metaSpell, Q_RETURN_ARG(QVariant, spellValue)))
                    if (spellValue.toLongLong() == Converter::getLongLong(value))
                        return true;
            }
        }
        break;
        case '>':
        {
            value.remove(0, 1);

            if (arraySize)
            {
                for (quint8 i = 0; i < arraySize; ++i)
                    if (handler.invoke(&metaSpell, Q_RETURN_ARG(QVariant, spellValue), Q_ARG(quint8, i)))
                        if (spellValue.toLongLong() > Converter::getLongLong(value))
                            return true;
            }
            else
            {
                if (handler.invoke(&metaSpell, Q_RETURN_ARG(QVariant, spellValue)))
                    if (spellValue.toLongLong() > Converter::getLongLong(value))
                        return true;
            }
        }
        break;
        case '<':
        {
            value.remove(0, 1);

            if (arraySize)
            {
                for (quint8 i = 0; i < arraySize; ++i)
                    if (handler.invoke(&metaSpell, Q_RETURN_ARG(QVariant, spellValue), Q_ARG(quint8, i)))
                        if (spellValue.toLongLong() < Converter::getLongLong(value))
                            return true;
            }
            else
            {
                if (handler.invoke(&metaSpell, Q_RETURN_ARG(QVariant, spellValue)))
                    if (spellValue.toLongLong() < Converter::getLongLong(value))
                        return true;
            }
        }
        break;
        case '&':
        {
            value.remove(0, 1);

            if (arraySize)
            {
                for (quint8 i = 0; i < arraySize; ++i)
                    if (handler.invoke(&metaSpell, Q_RETURN_ARG(QVariant, spellValue), Q_ARG(quint8, i)))
                        if (spellValue.toLongLong() & Converter::getLongLong(value))
                            return true;
            }
            else
            {
                if (handler.invoke(&metaSpell, Q_RETURN_ARG(QVariant, spellValue)))
                    if (spellValue.toLongLong() & Converter::getLongLong(value))
                        return true;
            }
        }
        break;
        case '~':
        {
            value.remove(0, 1);

            if (arraySize)
            {
                for (quint8 i = 0; i < arraySize; ++i)
                    if (handler.invoke(&metaSpell, Q_RETURN_ARG(QVariant, spellValue), Q_ARG(quint8, i)))
                        if (~spellValue.toLongLong() & Converter::getLongLong(value))
                            return true;
            }
            else
            {
                if (handler.invoke(&metaSpell, Q_RETURN_ARG(QVariant, spellValue)))
                    if (~spellValue.toLongLong() & Converter::getLongLong(value))
                        return true;
            }
        }
        break;
        case '!':
        {
            value.remove(0, 1);

            if (arraySize)
            {
                for (quint8 i = 0; i < arraySize; ++i)
                    if (handler.invoke(&metaSpell, Q_RETURN_ARG(QVariant, spellValue), Q_ARG(quint8, i)))
                        if (spellValue.toLongLong() != Converter::getLongLong(value))
                            return true;
            }
            else
            {
                if (handler.invoke(&metaSpell, Q_RETURN_ARG(QVariant, spellValue)))
                    if (spellValue.toLongLong() != Converter::getLongLong(value))
                        return true;
            }
        }
        break;
        default:
        {
            if (arraySize)
            {
                for (quint8 i = 0; i < arraySize; ++i)
                    if (handler.invoke(&metaSpell, Q_RETURN_ARG(QVariant, spellValue), Q_ARG(quint8, i)))
                        if (spellValue.toLongLong() == Converter::getLongLong(value))
                            return true;
            }
            else
            {
                if (handler.invoke(&metaSpell, Q_RETURN_ARG(QVariant, spellValue)))
                    if (spellValue.toLongLong() == Converter::getLongLong(value))
                        return true;
            }
        }
        break;
    }

    return false;
}

void SWSearch::search()
{
    SpellListModel *model = new SpellListModel(m_form);

    if (m_sw->getType() == 1)
    {
        for (quint32 i = 0; i < sSpellStore.GetNumRows(); ++i)
        {
            bool family = false;
            bool aura = false;
            bool effect = false;
            bool adFilter1 = false;
            bool adFilter2 = false;
            bool targetA = false;
            bool targetB = false;

            SpellEntry const* m_spellInfo = sSpellStore.LookupEntry(i);

            if (m_spellInfo)
            {
                m_sw->setMetaEnum("SpellFamilyNames");
                if (m_form->comboBox->currentIndex() > 0)
                {
                    quint16 familyId = m_form->comboBox->itemData(m_form->comboBox->currentIndex()).toInt();
                    if (m_spellInfo->getSpellFamilyName() == familyId)
                        family = true;
                }
                else
                    family = true;

                m_sw->setMetaEnum("AuraType");
                if (m_form->comboBox_2->currentIndex() > 0)
                {
                    quint16 auraId = m_form->comboBox_2->itemData(m_form->comboBox_2->currentIndex()).toInt();
                    for (quint8 i = EFFECT_INDEX_0; i < MAX_EFFECT_INDEX; ++i)
                    {
                        if (m_spellInfo->getEffectApplyAuraName(i) == auraId)
                        {
                            aura = true;
                            break;
                        }
                    }
                }
                else
                    aura = true;

                m_sw->setMetaEnum("Effects");
                if (m_form->comboBox_3->currentIndex() > 0)
                {
                    quint16 effectId = m_form->comboBox_3->itemData(m_form->comboBox_3->currentIndex()).toInt();
                    for (quint8 i = EFFECT_INDEX_0; i < MAX_EFFECT_INDEX; ++i)
                    {
                        if (m_spellInfo->getEffect(i) == effectId)
                        {
                            effect = true;
                            break;
                        }
                    }
                }
                else
                    effect = true;

                m_sw->setMetaEnum("Targets");
                if (m_form->comboBox_4->currentIndex() > 0)
                {
                    quint16 targetId = m_form->comboBox_4->itemData(m_form->comboBox_4->currentIndex()).toInt();
                    for (quint8 i = EFFECT_INDEX_0; i < MAX_EFFECT_INDEX; ++i)
                    {
                        if (m_spellInfo->getEffectImplicitTargetA(i) == targetId)
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
                    for (quint8 i = EFFECT_INDEX_0; i < MAX_EFFECT_INDEX; ++i)
                    {
                        if (m_spellInfo->getEffectImplicitTargetB(i) == targetId)
                        {
                            targetB = true;
                            break;
                        }
                    }
                }
                else
                    targetB = true;

                if (m_form->adBox1->currentIndex() > 0)
                {
                    if (hasValue(m_form->adBox1->currentIndex(), m_form->adLine1->text(), m_spellInfo))
                        adFilter1 = true;
                }
                else
                    adFilter1 = true;

                if (m_form->adBox2->currentIndex() > 0)
                {
                    if (hasValue(m_form->adBox2->currentIndex(), m_form->adLine2->text(), m_spellInfo))
                        adFilter2 = true;
                }
                else
                    adFilter2 = true;

                if (family && aura && effect && adFilter1 && adFilter2 && targetA && targetB)
                {
                    QString sRank(QString::fromUtf8(m_spellInfo->Rank));
                    QString sFullName(QString::fromUtf8(m_spellInfo->SpellName));

                    if (!sRank.isEmpty())
                        sFullName.append(QString(" (%0)").arg(sRank));

                    QStringList spellRecord;
                    spellRecord << QString("%0").arg(m_spellInfo->Id) << sFullName;

                    model->appendRecord(spellRecord);
                }
            }
        }
        Event* ev = new Event(Event::Type(Event::EVENT_SEND_MODEL));
        ev->addValue(QVariant::fromValue(model));
        QApplication::postEvent(m_form, ev);
    }
    else if (m_sw->getType() == 2)
    {
        if (!m_form->compareSpell_1->text().isEmpty() && !m_form->compareSpell_2->text().isEmpty())
        {
            SpellEntry const* sInfo1 = sSpellStore.LookupEntry(m_form->compareSpell_1->text().toInt());
            SpellEntry const* sInfo2 = sSpellStore.LookupEntry(m_form->compareSpell_2->text().toInt());

            if (sInfo1 && sInfo2)
            {
                Event* ev = new Event(Event::Type(Event::EVENT_SEND_CSPELL));
                ev->addValue(QVariant::fromValue(sInfo1));
                ev->addValue(QVariant::fromValue(sInfo2));
                QApplication::postEvent(m_form, ev);
            }
        }
    }
    else
    {
        if (!m_form->findLine_e1->text().isEmpty())
        {
            if (!m_form->findLine_e1->text().toInt())
            {
                for (quint32 i = 0; i < sSpellStore.GetNumRows(); ++i)
                {
                    SpellEntry const* m_spellInfo = sSpellStore.LookupEntry(i);
                    if (m_spellInfo && QString(QString::fromUtf8(m_spellInfo->SpellName)).contains(m_form->findLine_e1->text(), Qt::CaseInsensitive))
                    {
                        QString sRank(QString::fromUtf8(m_spellInfo->Rank));
                        QString sFullName(QString::fromUtf8(m_spellInfo->SpellName));

                        if (!sRank.isEmpty())
                            sFullName.append(QString(" (%0)").arg(sRank));

                        QStringList spellRecord;
                        spellRecord << QString("%0").arg(m_spellInfo->Id) << sFullName;

                        model->appendRecord(spellRecord);
                    }
                }

                Event* ev = new Event(Event::Type(Event::EVENT_SEND_MODEL));
                ev->addValue(QVariant::fromValue(model));
                QApplication::postEvent(m_form, ev);
            }
            else
            {
                SpellEntry const* m_spellInfo = sSpellStore.LookupEntry(m_form->findLine_e1->text().toInt());

                if (m_spellInfo)
                {
                    QString sRank(QString::fromUtf8(m_spellInfo->Rank));
                    QString sFullName(QString::fromUtf8(m_spellInfo->SpellName));

                    if (!sRank.isEmpty())
                        sFullName.append(QString(" (%0)").arg(sRank));

                    QStringList spellRecord;
                    spellRecord << QString("%0").arg(m_spellInfo->Id) << sFullName;

                    model->appendRecord(spellRecord);

                    Event* ev1 = new Event(Event::Type(Event::EVENT_SEND_MODEL));
                    ev1->addValue(QVariant::fromValue(model));
                    QApplication::postEvent(m_form, ev1);

                    Event* ev2 = new Event(Event::Type(Event::EVENT_SEND_SPELL));
                    ev2->addValue(QVariant::fromValue(m_spellInfo));
                    QApplication::postEvent(m_form, ev2);
                }
            }
        }
        else if (!m_form->findLine_e2->text().isEmpty())
        {
            for (quint32 i = 0; i < sSpellStore.GetNumRows(); ++i)
            {
                SpellEntry const* m_spellInfo = sSpellStore.LookupEntry(i);
                if (m_spellInfo && m_spellInfo->SpellIconId == m_form->findLine_e2->text().toUInt())
                {
                    QString sRank(QString::fromUtf8(m_spellInfo->Rank));
                    QString sFullName(QString::fromUtf8(m_spellInfo->SpellName));

                    if (!sRank.isEmpty())
                        sFullName.append(QString(" (%0)").arg(sRank));

                    QStringList spellRecord;
                    spellRecord << QString("%0").arg(m_spellInfo->Id) << sFullName;

                    model->appendRecord(spellRecord);
                }
            }
            Event* ev = new Event(Event::Type(Event::EVENT_SEND_MODEL));
            ev->addValue(QVariant::fromValue(model));
            QApplication::postEvent(m_form, ev);
        }
        else if (!m_form->findLine_e3->text().isEmpty())
        {
            for (quint32 i = 0; i < sSpellStore.GetNumRows(); ++i)
            {
                SpellEntry const* m_spellInfo = sSpellStore.LookupEntry(i);
                if (m_spellInfo && QString(QString::fromUtf8(m_spellInfo->Description)).contains(m_form->findLine_e3->text(), Qt::CaseInsensitive))
                {
                    QString sRank(QString::fromUtf8(m_spellInfo->Rank));
                    QString sFullName(QString::fromUtf8(m_spellInfo->SpellName));

                    if (!sRank.isEmpty())
                        sFullName.append(QString(" (%0)").arg(sRank));

                    QStringList spellRecord;
                    spellRecord << QString("%0").arg(m_spellInfo->Id) << sFullName;

                    model->appendRecord(spellRecord);
                }
            }

            Event* ev = new Event(Event::Type(Event::EVENT_SEND_MODEL));
            ev->addValue(QVariant::fromValue(model));
            QApplication::postEvent(m_form, ev);
        }
        else
        {
            for (quint32 i = 0; i < sSpellStore.GetNumRows(); ++i)
            {
                SpellEntry const* m_spellInfo = sSpellStore.LookupEntry(i);
                if (m_spellInfo)
                {
                    QString sRank(QString::fromUtf8(m_spellInfo->Rank));
                    QString sFullName(QString::fromUtf8(m_spellInfo->SpellName));

                    if (!sRank.isEmpty())
                        sFullName.append(QString(" (%0)").arg(sRank));

                    QStringList spellRecord;
                    spellRecord << QString("%0").arg(m_spellInfo->Id) << sFullName;

                    model->appendRecord(spellRecord);
                }
            }

            Event* ev = new Event(Event::Type(Event::EVENT_SEND_MODEL));
            ev->addValue(QVariant::fromValue(model));
            QApplication::postEvent(m_form, ev);
        }
    }
}

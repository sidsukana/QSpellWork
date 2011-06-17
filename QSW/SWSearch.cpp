#include "SWSearch.h"
#include "QtGui/QStandardItemModel"

MetaSpell::MetaSpell(SpellEntry const *spellInfo)
    : m_spellInfo(spellInfo)
{
    // Тяжелый код. Необходим другой способ передачи массивов.
    for (quint8 i = 0; i < MAX_SPELL_TOTEMS; i++)
    {
        Totem << spellInfo->Totem[i];
        SpellVisual << spellInfo->SpellVisual[i];
    }

    for (quint8 i = 0; i < MAX_SPELL_REAGENTS; i++)
    {
        Reagent << spellInfo->Reagent[i];
        ReagentCount << spellInfo->ReagentCount[i];
    }

    for (quint8 i = 0; i < MAX_EFFECT_INDEX; i++)
    {
        Effect << spellInfo->Effect[i];
        EffectDieSides << spellInfo->EffectDieSides[i];
        EffectBaseDice << spellInfo->EffectBaseDice[i];
        EffectDicePerLevel << spellInfo->EffectDicePerLevel[i];
        EffectRealPointsPerLevel << spellInfo->EffectRealPointsPerLevel[i];
        EffectBasePoints << spellInfo->EffectBasePoints[i];
        EffectMechanic << spellInfo->EffectMechanic[i];
        EffectImplicitTargetA << spellInfo->EffectImplicitTargetA[i];
        EffectImplicitTargetB << spellInfo->EffectImplicitTargetB[i];
        EffectRadiusIndex << spellInfo->EffectRadiusIndex[i];
        EffectApplyAuraName << spellInfo->EffectApplyAuraName[i];
        EffectAmplitude << spellInfo->EffectAmplitude[i];
        EffectMultipleValue << spellInfo->EffectMultipleValue[i];
        EffectChainTarget << spellInfo->EffectChainTarget[i];
        EffectItemType << spellInfo->EffectItemType[i];
        EffectMiscValue << spellInfo->EffectMiscValue[i];
        EffectTriggerSpell << spellInfo->EffectTriggerSpell[i];
        EffectPointsPerComboPoint << spellInfo->EffectPointsPerComboPoint[i];
        DmgMultiplier << spellInfo->DmgMultiplier[i];
    }
}

MetaSpell::~MetaSpell()
{
}

SWSearch::SWSearch(SWObject *sw)
: m_sw(sw), m_form(sw->GetForm())
{
}

SWSearch::~SWSearch()
{
}

bool SWSearch::hasValue(QString name, QString value, SpellEntry const *spellInfo)
{
    MetaSpell metaSpell(spellInfo);

    QVariant spellValue = metaSpell.property(name.toAscii().data());
    QString typeName(spellValue.typeName());

    bool isList = typeName == "QVariantList";

    value.remove(QChar(32));

    switch (value.at(0).toAscii())
    {
        case '=':
        {
            value.remove(0, 1);
            if (isList)
            {
                if (spellValue.toList().contains(value.toLongLong()))
                    return true;
            }
            else
            {
                if (spellValue.toString().toLongLong() == value.toLongLong())
                    return true;
            }
            
        }
        break;
        case '>':
        {
            value.remove(0, 1);
            if (isList)
            {
                QVariantList values = spellValue.toList();
                for (QVariantList::iterator itr = values.begin(); itr != values.end(); ++itr)
                    if ((*itr).toLongLong() > value.toLongLong())
                        return true;
            }
            else
            {
                if (spellValue.toString().toLongLong() > value.toLongLong())
                    return true;
            }
        }
        break;
        case '<':
        {
            value.remove(0, 1);
            if (isList)
            {
                QVariantList values = spellValue.toList();
                for (QVariantList::iterator itr = values.begin(); itr != values.end(); ++itr)
                    if ((*itr).toLongLong() < value.toLongLong())
                        return true;
            }
            else
            {
                if (spellValue.toString().toLongLong() < value.toLongLong())
                    return true;
            }
        }
        break;
        case '&':
        {
            value.remove(0, 1);
            if (isList)
            {
                QVariantList values = spellValue.toList();
                for (QVariantList::iterator itr = values.begin(); itr != values.end(); ++itr)
                    if ((*itr).toLongLong() & value.toLongLong())
                        return true;
            }
            else
            {
                if (spellValue.toLongLong() & value.toLongLong())
                    return true;
            }
        }
        break;
        case '~':
        {
            value.remove(0, 1);
            if (isList)
            {
                QVariantList values = spellValue.toList();
                for (QVariantList::iterator itr = values.begin(); itr != values.end(); ++itr)
                    if (~(*itr).toLongLong() & value.toLongLong())
                        return true;
            }
            else
            {
                if (~spellValue.toLongLong() & value.toLongLong())
                    return true;
            }
        }
        break;
        default:
        {
            if (isList)
            {
                if (spellValue.toList().contains(value))
                    return true;
            }
            else
            {
                if (spellValue.toString() == value)
                    return true;
            }
        }
        break;
    }

    return false;
}

void SWSearch::search()
{
    m_sw->ThreadSet(THREAD_SEARCH);
    bool isString = false;
    qint32 count = -1;

    QStandardItemModel *model = new QStandardItemModel(1, 2);
    model->setHorizontalHeaderItem(0, new QStandardItem("ID"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Name"));

    if (m_sw->GetType() == 1)
    {
        for (quint32 i = 0; i < sSpellStore.GetNumRows(); i++)
        {
            bool family = false;
            bool aura = false;
            bool effect = false;
            bool adFilter1 = false;
            bool adFilter2 = false;
            bool targetA = false;
            bool targetB = false;

            SpellEntry const *m_spellInfo = sSpellStore.LookupEntry(i);

            if (m_spellInfo)
            {
                m_sw->SetMetaEnum("SpellFamilyNames");
                if (m_form->comboBox->currentIndex() < m_sw->GetMetaEnum().keyCount())
                {
                    if (m_spellInfo->SpellFamilyName == m_sw->GetMetaEnum().value(m_form->comboBox->currentIndex()))
                        family = true;
                }
                else
                    family = true;

                m_sw->SetMetaEnum("AuraType");
                if (m_form->comboBox_2->currentIndex() < m_sw->GetMetaEnum().keyCount())
                {
                    for (quint8 i = EFFECT_INDEX_0; i < MAX_EFFECT_INDEX; i++)
                    {
                        if (m_spellInfo->EffectApplyAuraName[i] == m_sw->GetMetaEnum().value(m_form->comboBox_2->currentIndex()))
                        {
                            aura = true;
                            break;
                        }
                    }
                }
                else
                    aura = true;

                m_sw->SetMetaEnum("Effects");
                if (m_form->comboBox_3->currentIndex() < m_sw->GetMetaEnum().keyCount())
                {
                    for (quint8 i = EFFECT_INDEX_0; i < MAX_EFFECT_INDEX; i++)
                    {
                        if (m_spellInfo->Effect[i] == m_sw->GetMetaEnum().value(m_form->comboBox_3->currentIndex()))
                        {
                            effect = true;
                            break;
                        }
                    }
                }
                else
                    effect = true;

                m_sw->SetMetaEnum("Targets");
                if (m_form->comboBox_4->currentIndex() < m_sw->GetMetaEnum().keyCount())
                {
                    for (quint8 i = EFFECT_INDEX_0; i < MAX_EFFECT_INDEX; i++)
                    {
                        if (m_spellInfo->EffectImplicitTargetA[i] == m_sw->GetMetaEnum().value(m_form->comboBox_4->currentIndex()))
                        {
                            targetA = true;
                            break;
                        }
                    }
                }
                else
                    targetA = true;

                if (m_form->comboBox_5->currentIndex() < m_sw->GetMetaEnum().keyCount())
                {
                    for (quint8 i = EFFECT_INDEX_0; i < MAX_EFFECT_INDEX; i++)
                    {
                        if (m_spellInfo->EffectImplicitTargetB[i] == m_sw->GetMetaEnum().value(m_form->comboBox_5->currentIndex()))
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
                    if (hasValue(m_form->adBox1->itemText(m_form->adBox1->currentIndex()), m_form->adLine1->text(), m_spellInfo))
                        adFilter1 = true;
                }
                else
                    adFilter1 = true;

                if (m_form->adBox2->currentIndex() > 0)
                {
                    if (hasValue(m_form->adBox2->itemText(m_form->adBox2->currentIndex()), m_form->adLine2->text(), m_spellInfo))
                        adFilter2 = true;
                }
                else
                    adFilter2 = true;

                if (family && aura && effect && adFilter1 && adFilter2 && targetA && targetB)
                {
                    count++;
                    QString sRank(QString::fromUtf8(m_spellInfo->Rank[Locale]));
                    QString sFullName(QString::fromUtf8(m_spellInfo->SpellName[Locale]));

                    QStandardItem *item_id = new QStandardItem(QString("%0").arg(m_spellInfo->Id));
                    QStandardItem *item_name;

                    if (!sRank.isEmpty())
                        sFullName.append(QString(" (%0)").arg(QString::fromUtf8(m_spellInfo->Rank[Locale])));

                    item_name = new QStandardItem(sFullName);

                    model->setItem(count, 0, item_id);
                    model->setItem(count, 1, item_name);
                }
            }
        }
        QApplication::postEvent(m_form, new SendModel(m_form, model));
    }
    else if (m_sw->GetType() == 2)
    {
        if (!m_form->compareSpell_1->text().isEmpty() && !m_form->compareSpell_2->text().isEmpty())
        {
            SpellEntry const *sInfo1 = sSpellStore.LookupEntry(m_form->compareSpell_1->text().toInt());
            SpellEntry const *sInfo2 = sSpellStore.LookupEntry(m_form->compareSpell_2->text().toInt());

            if (sInfo1 && sInfo2)
            {
                QApplication::postEvent(m_form, new SendCompareSpell(m_form, sInfo1, 0));
                QApplication::postEvent(m_form, new SendCompareSpell(m_form, sInfo2, 1));
            }
        }
    }
    else
    {
        if (!m_form->findLine_e1->text().isEmpty())
        {
            for (quint8 i = 0; i < m_form->findLine_e1->text().size(); ++i)
            {
                if (m_form->findLine_e1->text().at(i) > QChar('9'))
                {
                    isString = true;
                    break;
                }
            }

            if (isString)
            {
                for (quint32 i = 0; i < sSpellStore.GetNumRows(); i++)
                {
                    SpellEntry const *m_spellInfo = sSpellStore.LookupEntry(i);
                    if (m_spellInfo && QString(QString::fromUtf8(m_spellInfo->SpellName[Locale])).contains(m_form->findLine_e1->text(), Qt::CaseInsensitive))
                    {
                        count++;
                        QString sRank(QString::fromUtf8(m_spellInfo->Rank[Locale]));
                        QString sFullName(QString::fromUtf8(m_spellInfo->SpellName[Locale]));

                        QStandardItem *item_id = new QStandardItem(QString("%0").arg(m_spellInfo->Id));
                        QStandardItem *item_name;

                        if (!sRank.isEmpty())
                            sFullName.append(QString(" (%0)").arg(QString::fromUtf8(m_spellInfo->Rank[Locale])));

                        item_name = new QStandardItem(sFullName);

                        model->setItem(count, 0, item_id);
                        model->setItem(count, 1, item_name);
                    }
                }
                QApplication::postEvent(m_form, new SendModel(m_form, model));
            }
            else
            {
                SpellEntry const *m_spellInfo = sSpellStore.LookupEntry(m_form->findLine_e1->text().toInt());

                if (m_spellInfo)
                {
                    QString sRank(QString::fromUtf8(m_spellInfo->Rank[Locale]));
                    QString sFullName(QString::fromUtf8(m_spellInfo->SpellName[Locale]));

                    QStandardItem  *item_id = new QStandardItem (QString("%0").arg(m_spellInfo->Id));
                    QStandardItem  *item_name;

                    if (!sRank.isEmpty())
                        sFullName.append(QString(" (%0)").arg(QString::fromUtf8(m_spellInfo->Rank[Locale])));

                    item_name = new QStandardItem(sFullName);

                    model->setItem(0, 0, item_id);
                    model->setItem(0, 1, item_name);
                    QApplication::postEvent(m_form, new SendModel(m_form, model));
                    QApplication::postEvent(m_form, new SendSpell(m_form, m_spellInfo));
                }
            }
        }
        else if (!m_form->findLine_e2->text().isEmpty())
        {
            for (quint32 i = 0; i < sSpellStore.GetNumRows(); i++)
            {
                SpellEntry const *m_spellInfo = sSpellStore.LookupEntry(i);
                if (m_spellInfo && m_spellInfo->SpellIconID == m_form->findLine_e2->text().toInt())
                {
                    count++;
                    QString sRank(QString::fromUtf8(m_spellInfo->Rank[Locale]));
                    QString sFullName(QString::fromUtf8(m_spellInfo->SpellName[Locale]));

                    QStandardItem *item_id = new QStandardItem(QString("%0").arg(m_spellInfo->Id));
                    QStandardItem *item_name;

                    if (!sRank.isEmpty())
                        sFullName.append(QString(" (%0)").arg(QString::fromUtf8(m_spellInfo->Rank[Locale])));

                    item_name = new QStandardItem(sFullName);

                    model->setItem(count, 0, item_id);
                    model->setItem(count, 1, item_name);
                }
            }
            QApplication::postEvent(m_form, new SendModel(m_form, model));
        }
        else if (!m_form->findLine_e3->text().isEmpty())
        {
            for (quint32 i = 0; i < sSpellStore.GetNumRows(); i++)
            {
                SpellEntry const *m_spellInfo = sSpellStore.LookupEntry(i);
                if (m_spellInfo && QString(QString::fromUtf8(m_spellInfo->Description[Locale])).contains(m_form->findLine_e3->text(), Qt::CaseInsensitive))
                {
                    count++;
                    QString sRank(QString::fromUtf8(m_spellInfo->Rank[Locale]));
                    QString sFullName(QString::fromUtf8(m_spellInfo->SpellName[Locale]));

                    QStandardItem *item_id = new QStandardItem(QString("%0").arg(m_spellInfo->Id));
                    QStandardItem *item_name;

                    if (!sRank.isEmpty())
                        sFullName.append(QString(" (%0)").arg(QString::fromUtf8(m_spellInfo->Rank[Locale])));

                    item_name = new QStandardItem(sFullName);

                    model->setItem(count, 0, item_id);
                    model->setItem(count, 1, item_name);
                }
            }
            QApplication::postEvent(m_form, new SendModel(m_form, model));
        }
        else
        {
            for (quint32 i = 0; i < sSpellStore.GetNumRows(); i++)
            {
                SpellEntry const *m_spellInfo = sSpellStore.LookupEntry(i);
                if (m_spellInfo)
                {
                    count++;
                    QString sRank(QString::fromUtf8(m_spellInfo->Rank[Locale]));
                    QString sFullName(QString::fromUtf8(m_spellInfo->SpellName[Locale]));

                    QStandardItem *item_id = new QStandardItem(QString("%0").arg(m_spellInfo->Id));
                    QStandardItem *item_name;

                    if (!sRank.isEmpty())
                        sFullName.append(QString(" (%0)").arg(QString::fromUtf8(m_spellInfo->Rank[Locale])));

                    item_name = new QStandardItem(sFullName);

                    model->setItem(count, 0, item_id);
                    model->setItem(count, 1, item_name);
                }
            }
            QApplication::postEvent(m_form, new SendModel(m_form, model));
        }
    }
    m_sw->ThreadUnset(THREAD_SEARCH);
}

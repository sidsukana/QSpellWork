#include "SWSearch.h"

MetaSpell::MetaSpell(SpellEntry const *spellInfo)
    : m_spellInfo(spellInfo)
{
}

MetaSpell::~MetaSpell()
{
}

SWSearch::SWSearch(SWObject* sw)
: m_sw(sw), m_form(sw->getForm())
{
}

SWSearch::~SWSearch()
{
}

bool SWSearch::hasValue(QString name, QString value, SpellEntry const* spellInfo)
{
    MetaSpell metaSpell(spellInfo);

    QVariant spellValue = metaSpell.property(name.toAscii().data());

    QString typeName(spellValue.typeName());

    value.remove(QChar(32));

    switch (value.at(0).toAscii())
    {
        case '=':
        {
            value.remove(0, 1);

            if (typeName == "uarray2")
            {
                uarray2 var = spellValue.value<uarray2>();
                for (quint8 i = 0; i < 2; i++)
                    if (var.value[i] == value.toULong())
                        return true;
            }
            else if (typeName == "iarray2")
            {
                iarray2 var = spellValue.value<iarray2>();
                for (quint8 i = 0; i < 2; i++)
                    if (var.value[i] == value.toLong())
                        return true;
            }
            else if (typeName == "farray2")
            {
                farray2 var = spellValue.value<farray2>();
                for (quint8 i = 0; i < 2; i++)
                    if (var.value[i] == value.toFloat())
                        return true;
            }
            else if (typeName == "uarray3")
            {
                uarray3 var = spellValue.value<uarray3>();
                for (quint8 i = 0; i < 3; i++)
                    if (var.value[i] == value.toULong())
                        return true;
            }
            else if (typeName == "iarray3")
            {
                iarray3 var = spellValue.value<iarray3>();
                for (quint8 i = 0; i < 3; i++)
                    if (var.value[i] == value.toLong())
                        return true;
            }
            else if (typeName == "farray3")
            {
                farray3 var = spellValue.value<farray3>();
                for (quint8 i = 0; i < 3; i++)
                    if (var.value[i] == value.toFloat())
                        return true;
            }
            else if (typeName == "uarray8")
            {
                uarray8 var = spellValue.value<uarray8>();
                for (quint8 i = 0; i < 8; i++)
                    if (var.value[i] == value.toULong())
                        return true;
            }
            else if (typeName == "iarray8")
            {
                iarray8 var = spellValue.value<iarray8>();
                for (quint8 i = 0; i < 8; i++)
                    if (var.value[i] == value.toLong())
                        return true;
            }
            else if (typeName == "farray8")
            {
                farray8 var = spellValue.value<farray8>();
                for (quint8 i = 0; i < 8; i++)
                    if (var.value[i] == value.toFloat())
                        return true;
            }
            else
            {
                if (spellValue.toLongLong() == value.toLongLong())
                    return true;
            }
        }
        break;
        case '>':
        {
            value.remove(0, 1);
            if (typeName == "uarray2")
            {
                uarray2 var = spellValue.value<uarray2>();
                for (quint8 i = 0; i < 2; i++)
                    if (var.value[i] > value.toULong())
                        return true;
            }
            else if (typeName == "iarray2")
            {
                iarray2 var = spellValue.value<iarray2>();
                for (quint8 i = 0; i < 2; i++)
                    if (var.value[i] > value.toLong())
                        return true;
            }
            else if (typeName == "farray2")
            {
                farray2 var = spellValue.value<farray2>();
                for (quint8 i = 0; i < 2; i++)
                    if (var.value[i] > value.toFloat())
                        return true;
            }
            else if (typeName == "uarray3")
            {
                uarray3 var = spellValue.value<uarray3>();
                for (quint8 i = 0; i < 3; i++)
                    if (var.value[i] > value.toULong())
                        return true;
            }
            else if (typeName == "iarray3")
            {
                iarray3 var = spellValue.value<iarray3>();
                for (quint8 i = 0; i < 3; i++)
                    if (var.value[i] > value.toLong())
                        return true;
            }
            else if (typeName == "farray3")
            {
                farray3 var = spellValue.value<farray3>();
                for (quint8 i = 0; i < 3; i++)
                    if (var.value[i] > value.toFloat())
                        return true;
            }
            else if (typeName == "uarray8")
            {
                uarray8 var = spellValue.value<uarray8>();
                for (quint8 i = 0; i < 8; i++)
                    if (var.value[i] > value.toULong())
                        return true;
            }
            else if (typeName == "iarray8")
            {
                iarray8 var = spellValue.value<iarray8>();
                for (quint8 i = 0; i < 8; i++)
                    if (var.value[i] > value.toLong())
                        return true;
            }
            else if (typeName == "farray8")
            {
                farray8 var = spellValue.value<farray8>();
                for (quint8 i = 0; i < 8; i++)
                    if (var.value[i] > value.toFloat())
                        return true;
            }
            else
            {
                if (spellValue.toLongLong() > value.toLongLong())
                    return true;
            }
        }
        break;
        case '<':
        {
            value.remove(0, 1);
            if (typeName == "uarray2")
            {
                uarray2 var = spellValue.value<uarray2>();
                for (quint8 i = 0; i < 2; i++)
                    if (var.value[i] < value.toULong())
                        return true;
            }
            else if (typeName == "iarray2")
            {
                iarray2 var = spellValue.value<iarray2>();
                for (quint8 i = 0; i < 2; i++)
                    if (var.value[i] < value.toLong())
                        return true;
            }
            else if (typeName == "farray2")
            {
                farray2 var = spellValue.value<farray2>();
                for (quint8 i = 0; i < 2; i++)
                    if (var.value[i] < value.toFloat())
                        return true;
            }
            else if (typeName == "uarray3")
            {
                uarray3 var = spellValue.value<uarray3>();
                for (quint8 i = 0; i < 3; i++)
                    if (var.value[i] < value.toULong())
                        return true;
            }
            else if (typeName == "iarray3")
            {
                iarray3 var = spellValue.value<iarray3>();
                for (quint8 i = 0; i < 3; i++)
                    if (var.value[i] < value.toLong())
                        return true;
            }
            else if (typeName == "farray3")
            {
                farray3 var = spellValue.value<farray3>();
                for (quint8 i = 0; i < 3; i++)
                    if (var.value[i] < value.toFloat())
                        return true;
            }
            else if (typeName == "uarray8")
            {
                uarray8 var = spellValue.value<uarray8>();
                for (quint8 i = 0; i < 8; i++)
                    if (var.value[i] < value.toULong())
                        return true;
            }
            else if (typeName == "iarray8")
            {
                iarray8 var = spellValue.value<iarray8>();
                for (quint8 i = 0; i < 8; i++)
                    if (var.value[i] < value.toLong())
                        return true;
            }
            else if (typeName == "farray8")
            {
                farray8 var = spellValue.value<farray8>();
                for (quint8 i = 0; i < 8; i++)
                    if (var.value[i] < value.toFloat())
                        return true;
            }
            else
            {
                if (spellValue.toLongLong() < value.toLongLong())
                    return true;
            }
        }
        break;
        case '&':
        {
            value.remove(0, 1);
            if (typeName == "uarray2")
            {
                uarray2 var = spellValue.value<uarray2>();
                for (quint8 i = 0; i < 2; i++)
                    if (var.value[i] & value.toULong())
                        return true;
            }
            else if (typeName == "iarray2")
            {
                iarray2 var = spellValue.value<iarray2>();
                for (quint8 i = 0; i < 2; i++)
                    if (var.value[i] & value.toLong())
                        return true;
            }
            else if (typeName == "uarray3")
            {
                uarray3 var = spellValue.value<uarray3>();
                for (quint8 i = 0; i < 3; i++)
                    if (var.value[i] & value.toULong())
                        return true;
            }
            else if (typeName == "iarray3")
            {
                iarray3 var = spellValue.value<iarray3>();
                for (quint8 i = 0; i < 3; i++)
                    if (var.value[i] & value.toLong())
                        return true;
            }
            else if (typeName == "uarray8")
            {
                uarray8 var = spellValue.value<uarray8>();
                for (quint8 i = 0; i < 8; i++)
                    if (var.value[i] & value.toULong())
                        return true;
            }
            else if (typeName == "iarray8")
            {
                iarray8 var = spellValue.value<iarray8>();
                for (quint8 i = 0; i < 8; i++)
                    if (var.value[i] & value.toLong())
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
            if (typeName == "uarray2")
            {
                uarray2 var = spellValue.value<uarray2>();
                for (quint8 i = 0; i < 2; i++)
                    if (~var.value[i] & value.toULong())
                        return true;
            }
            else if (typeName == "iarray2")
            {
                iarray2 var = spellValue.value<iarray2>();
                for (quint8 i = 0; i < 2; i++)
                    if (~var.value[i] & value.toLong())
                        return true;
            }
            else if (typeName == "uarray3")
            {
                uarray3 var = spellValue.value<uarray3>();
                for (quint8 i = 0; i < 3; i++)
                    if (~var.value[i] & value.toULong())
                        return true;
            }
            else if (typeName == "iarray3")
            {
                iarray3 var = spellValue.value<iarray3>();
                for (quint8 i = 0; i < 3; i++)
                    if (~var.value[i] & value.toLong())
                        return true;
            }
            else if (typeName == "uarray8")
            {
                uarray8 var = spellValue.value<uarray8>();
                for (quint8 i = 0; i < 8; i++)
                    if (~var.value[i] & value.toULong())
                        return true;
            }
            else if (typeName == "iarray8")
            {
                iarray8 var = spellValue.value<iarray8>();
                for (quint8 i = 0; i < 8; i++)
                    if (~var.value[i] & value.toLong())
                        return true;
            }
            else
            {
                if (~spellValue.toLongLong() & value.toLongLong())
                    return true;
            }
        }
        break;
        case '!':
        {
            value.remove(0, 1);
            if (typeName == "uarray2")
            {
                uarray2 var = spellValue.value<uarray2>();
                for (quint8 i = 0; i < 2; i++)
                    if (var.value[i] == value.toULong())
                        return false;
            }
            else if (typeName == "iarray2")
            {
                iarray2 var = spellValue.value<iarray2>();
                for (quint8 i = 0; i < 2; i++)
                    if (var.value[i] == value.toLong())
                        return false;
            }
            else if (typeName == "farray2")
            {
                farray2 var = spellValue.value<farray2>();
                for (quint8 i = 0; i < 2; i++)
                    if (var.value[i] == value.toFloat())
                        return false;
            }
            else if (typeName == "uarray3")
            {
                uarray3 var = spellValue.value<uarray3>();
                for (quint8 i = 0; i < 3; i++)
                    if (var.value[i] == value.toULong())
                        return false;
            }
            else if (typeName == "iarray3")
            {
                iarray3 var = spellValue.value<iarray3>();
                for (quint8 i = 0; i < 3; i++)
                    if (var.value[i] == value.toLong())
                        return false;
            }
            else if (typeName == "farray3")
            {
                farray3 var = spellValue.value<farray3>();
                for (quint8 i = 0; i < 3; i++)
                    if (var.value[i] == value.toFloat())
                        return false;
            }
            else if (typeName == "uarray8")
            {
                uarray8 var = spellValue.value<uarray8>();
                for (quint8 i = 0; i < 8; i++)
                    if (var.value[i] == value.toULong())
                        return false;
            }
            else if (typeName == "iarray8")
            {
                iarray8 var = spellValue.value<iarray8>();
                for (quint8 i = 0; i < 8; i++)
                    if (var.value[i] == value.toLong())
                        return false;
            }
            else if (typeName == "farray8")
            {
                farray8 var = spellValue.value<farray8>();
                for (quint8 i = 0; i < 8; i++)
                    if (var.value[i] == value.toFloat())
                        return false;
            }
            else
            {
                if (spellValue.toLongLong() != value.toLongLong())
                    return true;
            }

            return true;
        }
        break;
        default:
        {
            if (typeName == "uarray2")
            {
                uarray2 var = spellValue.value<uarray2>();
                for (quint8 i = 0; i < 2; i++)
                    if (var.value[i] == value.toULong())
                        return true;
            }
            else if (typeName == "iarray2")
            {
                iarray2 var = spellValue.value<iarray2>();
                for (quint8 i = 0; i < 2; i++)
                    if (var.value[i] == value.toLong())
                        return true;
            }
            else if (typeName == "farray2")
            {
                farray2 var = spellValue.value<farray2>();
                for (quint8 i = 0; i < 2; i++)
                    if (var.value[i] == value.toFloat())
                        return true;
            }
            else if (typeName == "uarray3")
            {
                uarray3 var = spellValue.value<uarray3>();
                for (quint8 i = 0; i < 3; i++)
                    if (var.value[i] == value.toULong())
                        return true;
            }
            else if (typeName == "iarray3")
            {
                iarray3 var = spellValue.value<iarray3>();
                for (quint8 i = 0; i < 3; i++)
                    if (var.value[i] == value.toLong())
                        return true;
            }
            else if (typeName == "farray3")
            {
                farray3 var = spellValue.value<farray3>();
                for (quint8 i = 0; i < 3; i++)
                    if (var.value[i] == value.toFloat())
                        return true;
            }
            else if (typeName == "uarray8")
            {
                uarray8 var = spellValue.value<uarray8>();
                for (quint8 i = 0; i < 8; i++)
                    if (var.value[i] == value.toULong())
                        return true;
            }
            else if (typeName == "iarray8")
            {
                iarray8 var = spellValue.value<iarray8>();
                for (quint8 i = 0; i < 8; i++)
                    if (var.value[i] == value.toLong())
                        return true;
            }
            else if (typeName == "farray8")
            {
                farray8 var = spellValue.value<farray8>();
                for (quint8 i = 0; i < 8; i++)
                    if (var.value[i] == value.toFloat())
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
    m_sw->threadSet(THREAD_SEARCH);
    bool isString = false;

    SpellListModel *model = new SpellListModel;

    if (m_sw->getType() == 1)
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

            SpellEntry const* m_spellInfo = sSpellStore.LookupEntry(i);

            if (m_spellInfo)
            {
                m_sw->setMetaEnum("SpellFamilyNames");
                if (m_form->comboBox->currentIndex() < m_sw->getMetaEnum().keyCount())
                {
                    if (m_spellInfo->SpellFamilyName == m_sw->getMetaEnum().value(m_form->comboBox->currentIndex()))
                        family = true;
                }
                else
                    family = true;

                m_sw->setMetaEnum("AuraType");
                if (m_form->comboBox_2->currentIndex() < m_sw->getMetaEnum().keyCount())
                {
                    for (quint8 i = EFFECT_INDEX_0; i < MAX_EFFECT_INDEX; i++)
                    {
                        if (m_spellInfo->EffectApplyAuraName.value[i] == m_sw->getMetaEnum().value(m_form->comboBox_2->currentIndex()))
                        {
                            aura = true;
                            break;
                        }
                    }
                }
                else
                    aura = true;

                m_sw->setMetaEnum("Effects");
                if (m_form->comboBox_3->currentIndex() < m_sw->getMetaEnum().keyCount())
                {
                    for (quint8 i = EFFECT_INDEX_0; i < MAX_EFFECT_INDEX; i++)
                    {
                        if (m_spellInfo->Effect.value[i] == m_sw->getMetaEnum().value(m_form->comboBox_3->currentIndex()))
                        {
                            effect = true;
                            break;
                        }
                    }
                }
                else
                    effect = true;

                m_sw->setMetaEnum("Targets");
                if (m_form->comboBox_4->currentIndex() < m_sw->getMetaEnum().keyCount())
                {
                    for (quint8 i = EFFECT_INDEX_0; i < MAX_EFFECT_INDEX; i++)
                    {
                        if (m_spellInfo->EffectImplicitTargetA.value[i] == m_sw->getMetaEnum().value(m_form->comboBox_4->currentIndex()))
                        {
                            targetA = true;
                            break;
                        }
                    }
                }
                else
                    targetA = true;

                if (m_form->comboBox_5->currentIndex() < m_sw->getMetaEnum().keyCount())
                {
                    for (quint8 i = EFFECT_INDEX_0; i < MAX_EFFECT_INDEX; i++)
                    {
                        if (m_spellInfo->EffectImplicitTargetB.value[i] == m_sw->getMetaEnum().value(m_form->comboBox_5->currentIndex()))
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
                    QString sRank(QString::fromUtf8(m_spellInfo->Rank[Locale]));
                    QString sFullName(QString::fromUtf8(m_spellInfo->SpellName[Locale]));

                    if (!sRank.isEmpty())
                        sFullName.append(QString(" (%0)").arg(QString::fromUtf8(m_spellInfo->Rank[Locale])));

                    QStringList spellRecord;
                    spellRecord << QString("%0").arg(m_spellInfo->Id) << sFullName;

                    model->appendRecord(spellRecord);
                }
            }
        }
        QApplication::postEvent(m_form, new SendModel(model));
    }
    else if (m_sw->getType() == 2)
    {
        if (!m_form->compareSpell_1->text().isEmpty() && !m_form->compareSpell_2->text().isEmpty())
        {
            SpellEntry const* sInfo1 = sSpellStore.LookupEntry(m_form->compareSpell_1->text().toInt());
            SpellEntry const* sInfo2 = sSpellStore.LookupEntry(m_form->compareSpell_2->text().toInt());

            if (sInfo1 && sInfo2)
            {
                QApplication::postEvent(m_form, new SendCompareSpell(sInfo1, 0));
                QApplication::postEvent(m_form, new SendCompareSpell(sInfo2, 1));
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
                    SpellEntry const* m_spellInfo = sSpellStore.LookupEntry(i);
                    if (m_spellInfo && QString(QString::fromUtf8(m_spellInfo->SpellName[Locale])).contains(m_form->findLine_e1->text(), Qt::CaseInsensitive))
                    {
                        QString sRank(QString::fromUtf8(m_spellInfo->Rank[Locale]));
                        QString sFullName(QString::fromUtf8(m_spellInfo->SpellName[Locale]));

                        if (!sRank.isEmpty())
                            sFullName.append(QString(" (%0)").arg(QString::fromUtf8(m_spellInfo->Rank[Locale])));

                        QStringList spellRecord;
                        spellRecord << QString("%0").arg(m_spellInfo->Id) << sFullName;

                        model->appendRecord(spellRecord);
                    }
                }
                QApplication::postEvent(m_form, new SendModel(model));
            }
            else
            {
                SpellEntry const* m_spellInfo = sSpellStore.LookupEntry(m_form->findLine_e1->text().toInt());

                if (m_spellInfo)
                {
                    QString sRank(QString::fromUtf8(m_spellInfo->Rank[Locale]));
                    QString sFullName(QString::fromUtf8(m_spellInfo->SpellName[Locale]));

                    if (!sRank.isEmpty())
                        sFullName.append(QString(" (%0)").arg(QString::fromUtf8(m_spellInfo->Rank[Locale])));

                    QStringList spellRecord;
                    spellRecord << QString("%0").arg(m_spellInfo->Id) << sFullName;

                    model->appendRecord(spellRecord);
                    QApplication::postEvent(m_form, new SendModel(model));
                    QApplication::postEvent(m_form, new SendSpell(m_spellInfo));
                }
            }
        }
        else if (!m_form->findLine_e2->text().isEmpty())
        {
            for (quint32 i = 0; i < sSpellStore.GetNumRows(); i++)
            {
                SpellEntry const* m_spellInfo = sSpellStore.LookupEntry(i);
                if (m_spellInfo && m_spellInfo->SpellIconID == m_form->findLine_e2->text().toInt())
                {
                    QString sRank(QString::fromUtf8(m_spellInfo->Rank[Locale]));
                    QString sFullName(QString::fromUtf8(m_spellInfo->SpellName[Locale]));

                    if (!sRank.isEmpty())
                        sFullName.append(QString(" (%0)").arg(QString::fromUtf8(m_spellInfo->Rank[Locale])));

                    QStringList spellRecord;
                    spellRecord << QString("%0").arg(m_spellInfo->Id) << sFullName;

                    model->appendRecord(spellRecord);
                }
            }
            QApplication::postEvent(m_form, new SendModel(model));
        }
        else if (!m_form->findLine_e3->text().isEmpty())
        {
            for (quint32 i = 0; i < sSpellStore.GetNumRows(); i++)
            {
                SpellEntry const* m_spellInfo = sSpellStore.LookupEntry(i);
                if (m_spellInfo && QString(QString::fromUtf8(m_spellInfo->Description[Locale])).contains(m_form->findLine_e3->text(), Qt::CaseInsensitive))
                {
                    QString sRank(QString::fromUtf8(m_spellInfo->Rank[Locale]));
                    QString sFullName(QString::fromUtf8(m_spellInfo->SpellName[Locale]));

                    if (!sRank.isEmpty())
                        sFullName.append(QString(" (%0)").arg(QString::fromUtf8(m_spellInfo->Rank[Locale])));

                    QStringList spellRecord;
                    spellRecord << QString("%0").arg(m_spellInfo->Id) << sFullName;

                    model->appendRecord(spellRecord);
                }
            }
            QApplication::postEvent(m_form, new SendModel(model));
        }
        else
        {
            for (quint32 i = 0; i < sSpellStore.GetNumRows(); i++)
            {
                SpellEntry const* m_spellInfo = sSpellStore.LookupEntry(i);
                if (m_spellInfo)
                {
                    QString sRank(QString::fromUtf8(m_spellInfo->Rank[Locale]));
                    QString sFullName(QString::fromUtf8(m_spellInfo->SpellName[Locale]));

                    if (!sRank.isEmpty())
                        sFullName.append(QString(" (%0)").arg(QString::fromUtf8(m_spellInfo->Rank[Locale])));

                    QStringList spellRecord;
                    spellRecord << QString("%0").arg(m_spellInfo->Id) << sFullName;

                    model->appendRecord(spellRecord);
                }
            }
            QApplication::postEvent(m_form, new SendModel(model));
        }
    }
    m_sw->threadUnset(THREAD_SEARCH);
}

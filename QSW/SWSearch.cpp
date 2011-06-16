#include "SWSearch.h"
#include "QtGui/QStandardItemModel"

MetaSpell::MetaSpell(quint8 index, SpellEntry const *spellInfo, quint8 locale)
{
    switch (index)
    {
        case 1: Id = spellInfo->Id; break;
        case 2: School = spellInfo->School; break;
        case 3: Category = spellInfo->Category; break;
        case 4: CastUI = spellInfo->CastUI; break;
        case 5: Dispel = spellInfo->Dispel; break;
        case 6: Mechanic = spellInfo->Mechanic; break;
        case 7: Attributes = spellInfo->Attributes; break;
        case 8: AttributesEx = spellInfo->AttributesEx; break;
        case 9: AttributesEx2 = spellInfo->AttributesEx2; break;
        case 10: AttributesEx3 = spellInfo->AttributesEx3; break;
        case 11: AttributesEx4 = spellInfo->AttributesEx4; break;
        case 12: Stances = spellInfo->Stances; break;
        case 13: StancesNot = spellInfo->StancesNot; break;
        case 14: Targets = spellInfo->Targets; break;
        case 15: TargetCreatureType = spellInfo->TargetCreatureType; break;
        case 16: RequiresSpellFocus = spellInfo->RequiresSpellFocus; break;
        case 17: CasterAuraState = spellInfo->CasterAuraState; break;
        case 18: TargetAuraState = spellInfo->TargetAuraState; break;
        case 19: CastingTimeIndex = spellInfo->CastingTimeIndex; break;
        case 20: RecoveryTime = spellInfo->RecoveryTime; break;
        case 21: CategoryRecoveryTime = spellInfo->CategoryRecoveryTime; break;
        case 22: InterruptFlags = spellInfo->InterruptFlags; break;
        case 23: AuraInterruptFlags = spellInfo->AuraInterruptFlags; break;
        case 24: ChannelInterruptFlags = spellInfo->ChannelInterruptFlags; break;
        case 25: ProcFlags = spellInfo->ProcFlags; break;
        case 26: ProcChance = spellInfo->ProcChance; break;
        case 27: ProcCharges = spellInfo->ProcCharges; break;
        case 28: MaxLevel = spellInfo->MaxLevel; break;
        case 29: BaseLevel = spellInfo->BaseLevel; break;
        case 30: SpellLevel = spellInfo->SpellLevel; break;
        case 31: DurationIndex = spellInfo->DurationIndex; break;
        case 32: PowerType = spellInfo->PowerType; break;
        case 33: ManaCost = spellInfo->ManaCost; break;
        case 34: ManaCostPerlevel = spellInfo->ManaCostPerlevel; break;
        case 35: ManaPerSecond = spellInfo->ManaPerSecond; break;
        case 36: ManaPerSecondPerLevel = spellInfo->ManaPerSecondPerLevel; break;
        case 37: RangeIndex = spellInfo->RangeIndex; break;
        case 38: Speed = spellInfo->Speed; break;
        case 39: ModalNextSpell = spellInfo->ModalNextSpell; break;
        case 40: StackAmount = spellInfo->StackAmount; break;
        case 41: for (quint8 i = 0; i < MAX_SPELL_TOTEMS; i++) { Totem.append(spellInfo->Totem[i]); } break;
        case 42: for (quint8 i = 0; i < MAX_SPELL_REAGENTS; i++) { Reagent.append(spellInfo->Reagent[i]); } break;
        case 43: for (quint8 i = 0; i < MAX_SPELL_REAGENTS; i++) { ReagentCount.append(spellInfo->ReagentCount[i]); } break;
        case 44: EquippedItemClass = spellInfo->EquippedItemClass;
        case 45: EquippedItemSubClassMask = spellInfo->EquippedItemSubClassMask;
        case 46: EquippedItemInventoryTypeMask = spellInfo->EquippedItemInventoryTypeMask;
        case 47: for (quint8 i = 0; i < MAX_EFFECT_INDEX; i++) { Effect.append(spellInfo->Effect[i]); } break;
        case 48: for (quint8 i = 0; i < MAX_EFFECT_INDEX; i++) { EffectDieSides.append(spellInfo->EffectDieSides[i]); } break;
        case 49: for (quint8 i = 0; i < MAX_EFFECT_INDEX; i++) { EffectBaseDice.append(spellInfo->EffectBaseDice[i]); } break;
        case 50: for (quint8 i = 0; i < MAX_EFFECT_INDEX; i++) { EffectDicePerLevel.append(spellInfo->EffectDicePerLevel[i]); } break;
        case 51: for (quint8 i = 0; i < MAX_EFFECT_INDEX; i++) { EffectRealPointsPerLevel.append(spellInfo->EffectRealPointsPerLevel[i]); } break;
        case 52: for (quint8 i = 0; i < MAX_EFFECT_INDEX; i++) { EffectBasePoints.append(spellInfo->EffectBasePoints[i]); } break;
        case 53: for (quint8 i = 0; i < MAX_EFFECT_INDEX; i++) { EffectMechanic.append(spellInfo->EffectMechanic[i]); } break;
        case 54: for (quint8 i = 0; i < MAX_EFFECT_INDEX; i++) { EffectImplicitTargetA.append(spellInfo->EffectImplicitTargetA[i]); } break;
        case 55: for (quint8 i = 0; i < MAX_EFFECT_INDEX; i++) { EffectImplicitTargetB.append(spellInfo->EffectImplicitTargetB[i]); } break;
        case 56: for (quint8 i = 0; i < MAX_EFFECT_INDEX; i++) { EffectRadiusIndex.append(spellInfo->EffectRadiusIndex[i]); } break;
        case 57: for (quint8 i = 0; i < MAX_EFFECT_INDEX; i++) { EffectApplyAuraName.append(spellInfo->EffectApplyAuraName[i]); } break;
        case 58: for (quint8 i = 0; i < MAX_EFFECT_INDEX; i++) { EffectAmplitude.append(spellInfo->EffectAmplitude[i]); } break;
        case 59: for (quint8 i = 0; i < MAX_EFFECT_INDEX; i++) { EffectMultipleValue.append(spellInfo->EffectMultipleValue[i]); } break;
        case 60: for (quint8 i = 0; i < MAX_EFFECT_INDEX; i++) { EffectChainTarget.append(spellInfo->EffectChainTarget[i]); } break;
        case 61: for (quint8 i = 0; i < MAX_EFFECT_INDEX; i++) { EffectItemType.append(spellInfo->EffectItemType[i]); } break;
        case 62: for (quint8 i = 0; i < MAX_EFFECT_INDEX; i++) { EffectMiscValue.append(spellInfo->EffectMiscValue[i]); } break;
        case 63: for (quint8 i = 0; i < MAX_EFFECT_INDEX; i++) { EffectTriggerSpell.append(spellInfo->EffectTriggerSpell[i]); } break;
        case 64: for (quint8 i = 0; i < MAX_EFFECT_INDEX; i++) { EffectPointsPerComboPoint.append(spellInfo->EffectPointsPerComboPoint[i]); } break;
        case 65: for (quint8 i = 0; i < 2; i++) { SpellVisual.append(spellInfo->SpellVisual[i]); } break;
        case 66: SpellIconID = spellInfo->SpellIconID; break;
        case 67: ActiveIconID = spellInfo->ActiveIconID; break;
        case 68: SpellPriority = spellInfo->SpellPriority; break;
        case 69: SpellName = QString::fromUtf8(spellInfo->SpellName[locale]); break;
        case 70: SpellNameFlag = spellInfo->SpellNameFlag; break;
        case 71: Rank = QString::fromUtf8(spellInfo->Rank[locale]); break;
        case 72: RankFlags = spellInfo->RankFlags; break;
        case 73: Description = QString::fromUtf8(spellInfo->Description[locale]); break;
        case 74: DescriptionFlags = spellInfo->DescriptionFlags; break;
        case 75: ToolTip = QString::fromUtf8(spellInfo->ToolTip[locale]); break;
        case 76: ToolTipFlags = spellInfo->ToolTipFlags; break;
        case 77: ManaCostPercentage = spellInfo->ManaCostPercentage; break;
        case 78: StartRecoveryCategory = spellInfo->StartRecoveryCategory; break;
        case 79: StartRecoveryTime = spellInfo->StartRecoveryTime; break;
        case 80: MaxTargetLevel = spellInfo->MaxTargetLevel; break;
        case 81: SpellFamilyName = spellInfo->SpellFamilyName; break;
        case 82: SpellFamilyFlags = spellInfo->SpellFamilyFlags; break;
        case 83: MaxAffectedTargets = spellInfo->MaxAffectedTargets; break;
        case 84: DmgClass = spellInfo->DmgClass; break;
        case 85: PreventionType = spellInfo->PreventionType; break;
        case 86: StanceBarOrder = spellInfo->StanceBarOrder; break;
        case 87: for (quint8 i = 0; i < MAX_EFFECT_INDEX; i++) { DmgMultiplier.append(spellInfo->DmgMultiplier[i]); } break;
        case 88: MinFactionId = spellInfo->MinFactionId; break;
        case 89: MinReputation = spellInfo->MinReputation; break;
        case 90: RequiredAuraVision = spellInfo->RequiredAuraVision; break;
    }
}

MetaSpell::~MetaSpell()
{
}

SWSearch::SWSearch(SWObject *sw)
: m_sw(sw), m_locale(sw->GetLocale()), m_form(sw->GetForm())
{
}

SWSearch::~SWSearch()
{
}

bool SWSearch::hasValue(quint8 index, QString name, QString value, SpellEntry const *spellInfo)
{
    MetaSpell metaSpell(index, spellInfo, m_locale);

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
                    if (hasValue(m_form->adBox1->currentIndex(), m_form->adBox1->itemText(m_form->adBox1->currentIndex()), m_form->adLine1->text(), m_spellInfo))
                        adFilter1 = true;
                }
                else
                    adFilter1 = true;

                if (m_form->adBox2->currentIndex() > 0)
                {
                    if (hasValue(m_form->adBox2->currentIndex(), m_form->adBox2->itemText(m_form->adBox2->currentIndex()), m_form->adLine2->text(), m_spellInfo))
                        adFilter2 = true;
                }
                else
                    adFilter2 = true;

                if (family && aura && effect && adFilter1 && adFilter2 && targetA && targetB)
                {
                    count++;
                    QString sRank(QString::fromUtf8(m_spellInfo->Rank[m_locale]));
                    QString sFullName(QString::fromUtf8(m_spellInfo->SpellName[m_locale]));

                    QStandardItem *item_id = new QStandardItem(QString("%0").arg(m_spellInfo->Id));
                    QStandardItem *item_name;

                    if (!sRank.isEmpty())
                        sFullName.append(QString(" (%0)").arg(QString::fromUtf8(m_spellInfo->Rank[m_locale])));

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
                    if (m_spellInfo && QString(QString::fromUtf8(m_spellInfo->SpellName[m_locale])).contains(m_form->findLine_e1->text(), Qt::CaseInsensitive))
                    {
                        count++;
                        QString sRank(QString::fromUtf8(m_spellInfo->Rank[m_locale]));
                        QString sFullName(QString::fromUtf8(m_spellInfo->SpellName[m_locale]));

                        QStandardItem *item_id = new QStandardItem(QString("%0").arg(m_spellInfo->Id));
                        QStandardItem *item_name;

                        if (!sRank.isEmpty())
                            sFullName.append(QString(" (%0)").arg(QString::fromUtf8(m_spellInfo->Rank[m_locale])));

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
                    QString sRank(QString::fromUtf8(m_spellInfo->Rank[m_locale]));
                    QString sFullName(QString::fromUtf8(m_spellInfo->SpellName[m_locale]));

                    QStandardItem  *item_id = new QStandardItem (QString("%0").arg(m_spellInfo->Id));
                    QStandardItem  *item_name;

                    if (!sRank.isEmpty())
                        sFullName.append(QString(" (%0)").arg(QString::fromUtf8(m_spellInfo->Rank[m_locale])));

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
                    QString sRank(QString::fromUtf8(m_spellInfo->Rank[m_locale]));
                    QString sFullName(QString::fromUtf8(m_spellInfo->SpellName[m_locale]));

                    QStandardItem *item_id = new QStandardItem(QString("%0").arg(m_spellInfo->Id));
                    QStandardItem *item_name;

                    if (!sRank.isEmpty())
                        sFullName.append(QString(" (%0)").arg(QString::fromUtf8(m_spellInfo->Rank[m_locale])));

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
                if (m_spellInfo && QString(QString::fromUtf8(m_spellInfo->Description[m_locale])).contains(m_form->findLine_e3->text(), Qt::CaseInsensitive))
                {
                    count++;
                    QString sRank(QString::fromUtf8(m_spellInfo->Rank[m_locale]));
                    QString sFullName(QString::fromUtf8(m_spellInfo->SpellName[m_locale]));

                    QStandardItem *item_id = new QStandardItem(QString("%0").arg(m_spellInfo->Id));
                    QStandardItem *item_name;

                    if (!sRank.isEmpty())
                        sFullName.append(QString(" (%0)").arg(QString::fromUtf8(m_spellInfo->Rank[m_locale])));

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
                    QString sRank(QString::fromUtf8(m_spellInfo->Rank[m_locale]));
                    QString sFullName(QString::fromUtf8(m_spellInfo->SpellName[m_locale]));

                    QStandardItem *item_id = new QStandardItem(QString("%0").arg(m_spellInfo->Id));
                    QStandardItem *item_name;

                    if (!sRank.isEmpty())
                        sFullName.append(QString(" (%0)").arg(QString::fromUtf8(m_spellInfo->Rank[m_locale])));

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

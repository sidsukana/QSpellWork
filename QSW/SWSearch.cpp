#include "SWSearch.h"
#include "QtGui/QStandardItemModel"

SWSearch::SWSearch(SWObject *sw)
    : m_sw(sw)
{
}

SWSearch::~SWSearch()
{
}

bool SWSearch::HasValue(quint8 index, QString str, SpellEntry const *m_spellInfo, quint8 state)
{
    if (!m_spellInfo)
        return false;

    switch (index)
    {
        case 1:
            if (m_spellInfo->Id == str.toUInt())
                return true;
            break;
        case 2:
            if (m_spellInfo->Category == str.toUInt())
                return true;
            break;
        case 3:
            if (m_spellInfo->CastUI == str.toUInt())
                return true;
            break;
        case 4:
            if (m_spellInfo->Dispel == str.toUInt())
                return true;
            break;
        case 5:
            if (m_spellInfo->Mechanic == str.toUInt())
                return true;
            break;
        case 6:
            if (state == STATE_NONE)
            {
                if (m_spellInfo->Attributes == str.toUInt())
                    return true;
            }
            else if (state == STATE_CONTAIN)
            {
                if (m_spellInfo->Attributes & str.toUInt())
                    return true;
            }
            else if (state == STATE_NOT_CONTAIN)
            {
                if (~m_spellInfo->Attributes & str.toUInt())
                    return true;
            }
            break;
        case 7:
            if (state == STATE_NONE)
            {
                if (m_spellInfo->AttributesEx == str.toUInt())
                    return true;
            }
            else if (state == STATE_CONTAIN)
            {
                if (m_spellInfo->AttributesEx & str.toUInt())
                    return true;
            }
            else if (state == STATE_NOT_CONTAIN)
            {
                if (~m_spellInfo->AttributesEx & str.toUInt())
                    return true;
            }
            break;
        case 8:
            if (state == STATE_NONE)
            {
                if (m_spellInfo->AttributesEx2 == str.toUInt())
                    return true;
            }
            else if (state == STATE_CONTAIN)
            {
                if (m_spellInfo->AttributesEx2 & str.toUInt())
                    return true;
            }
            else if (state == STATE_NOT_CONTAIN)
            {
                if (~m_spellInfo->AttributesEx2 & str.toUInt())
                    return true;
            }
            break;
        case 9:
            if (state == STATE_NONE)
            {
                if (m_spellInfo->AttributesEx3 == str.toUInt())
                    return true;
            }
            else if (state == STATE_CONTAIN)
            {
                if (m_spellInfo->AttributesEx3 & str.toUInt())
                    return true;
            }
            else if (state == STATE_NOT_CONTAIN)
            {
                if (~m_spellInfo->AttributesEx3 & str.toUInt())
                    return true;
            }
            break;
        case 10:
            if (state == STATE_NONE)
            {
                if (m_spellInfo->AttributesEx4 == str.toUInt())
                    return true;
            }
            else if (state == STATE_CONTAIN)
            {
                if (m_spellInfo->AttributesEx4 & str.toUInt())
                    return true;
            }
            else if (state == STATE_NOT_CONTAIN)
            {
                if (~m_spellInfo->AttributesEx4 & str.toUInt())
                    return true;
            }
            break;
        case 11:
            if (state == STATE_NONE)
            {
                if (m_spellInfo->AttributesEx5 == str.toUInt())
                    return true;
            }
            else if (state == STATE_CONTAIN)
            {
                if (m_spellInfo->AttributesEx5 & str.toUInt())
                    return true;
            }
            else if (state == STATE_NOT_CONTAIN)
            {
                if (~m_spellInfo->AttributesEx5 & str.toUInt())
                    return true;
            }
            break;
        case 12:
            if (state == STATE_NONE)
            {
                if (m_spellInfo->AttributesEx6 == str.toUInt())
                    return true;
            }
            else if (state == STATE_CONTAIN)
            {
                if (m_spellInfo->AttributesEx6 & str.toUInt())
                    return true;
            }
            else if (state == STATE_NOT_CONTAIN)
            {
                if (~m_spellInfo->AttributesEx6 & str.toUInt())
                    return true;
            }
            break;
        case 13:
            if (state == STATE_NONE)
            {
                if (m_spellInfo->Stances == str.toUInt())
                    return true;
            }
            else if (state == STATE_CONTAIN)
            {
                if (m_spellInfo->Stances & str.toUInt())
                    return true;
            }
            else if (state == STATE_NOT_CONTAIN)
            {
                if (~m_spellInfo->Stances & str.toUInt())
                    return true;
            }
            break;
        case 14:
            if (state == STATE_NONE)
            {
                if (m_spellInfo->StancesNot == str.toUInt())
                    return true;
            }
            else if (state == STATE_CONTAIN)
            {
                if (m_spellInfo->StancesNot & str.toUInt())
                    return true;
            }
            else if (state == STATE_NOT_CONTAIN)
            {
                if (~m_spellInfo->StancesNot & str.toUInt())
                    return true;
            }
            break;
        case 15:
            if (state == STATE_NONE)
            {
                if (m_spellInfo->Targets == str.toUInt())
                    return true;
            }
            else if (state == STATE_CONTAIN)
            {
                if (m_spellInfo->Targets & str.toUInt())
                    return true;
            }
            else if (state == STATE_NOT_CONTAIN)
            {
                if (~m_spellInfo->Targets & str.toUInt())
                    return true;
            }
            break;
        case 16:
            if (state == STATE_NONE)
            {
                if (m_spellInfo->TargetCreatureType == str.toUInt())
                    return true;
            }
            else if (state == STATE_CONTAIN)
            {
                if (m_spellInfo->TargetCreatureType & str.toUInt())
                    return true;
            }
            else if (state == STATE_NOT_CONTAIN)
            {
                if (~m_spellInfo->TargetCreatureType & str.toUInt())
                    return true;
            }
            break;
        case 17:
            if (m_spellInfo->RequiresSpellFocus == str.toUInt())
                return true;
            break;
        case 18:
            if (m_spellInfo->FacingCasterFlags == str.toUInt())
                return true;
            break;
        case 19:
            if (m_spellInfo->CasterAuraState == str.toUInt())
                return true;
            break;
        case 20:
            if (m_spellInfo->TargetAuraState == str.toUInt())
                return true;
            break;
        case 21:
            if (m_spellInfo->CasterAuraStateNot == str.toUInt())
                return true;
            break;
        case 22:
            if (m_spellInfo->TargetAuraStateNot == str.toUInt())
                return true;
            break;
        case 23:
            if (m_spellInfo->CastingTimeIndex == str.toUInt())
                return true;
            break;
        case 24:
            if (m_spellInfo->RecoveryTime == str.toUInt())
                return true;
            break;
        case 25:
            if (m_spellInfo->CategoryRecoveryTime == str.toUInt())
                return true;
            break;
        case 26:
            if (state == STATE_NONE)
            {
                if (m_spellInfo->InterruptFlags == str.toUInt())
                    return true;
            }
            else if (state == STATE_CONTAIN)
            {
                if (m_spellInfo->InterruptFlags & str.toUInt())
                    return true;
            }
            else if (state == STATE_NOT_CONTAIN)
            {
                if (~m_spellInfo->InterruptFlags & str.toUInt())
                    return true;
            }
            break;
        case 27:
            if (state == STATE_NONE)
            {
                if (m_spellInfo->AuraInterruptFlags == str.toUInt())
                    return true;
            }
            else if (state == STATE_CONTAIN)
            {
                if (m_spellInfo->AuraInterruptFlags & str.toUInt())
                    return true;
            }
            else if (state == STATE_NOT_CONTAIN)
            {
                if (~m_spellInfo->AuraInterruptFlags & str.toUInt())
                    return true;
            }
            break;
        case 28:
            if (state == STATE_NONE)
            {
                if (m_spellInfo->ChannelInterruptFlags == str.toUInt())
                    return true;
            }
            else if (state == STATE_CONTAIN)
            {
                if (m_spellInfo->ChannelInterruptFlags & str.toUInt())
                    return true;
            }
            else if (state == STATE_NOT_CONTAIN)
            {
                if (~m_spellInfo->ChannelInterruptFlags & str.toUInt())
                    return true;
            }
            break;
        case 29:
            if (state == STATE_NONE)
            {
                if (m_spellInfo->ProcFlags == str.toUInt())
                    return true;
            }
            else if (state == STATE_CONTAIN)
            {
                if (m_spellInfo->ProcFlags & str.toUInt())
                    return true;
            }
            else if (state == STATE_NOT_CONTAIN)
            {
                if (~m_spellInfo->ProcFlags & str.toUInt())
                    return true;
            }
            break;
        case 30:
            if (m_spellInfo->ProcChance == str.toUInt())
                return true;
            break;
        case 31:
            if (m_spellInfo->ProcCharges == str.toUInt())
                return true;
            break;
        case 32:
            if (m_spellInfo->MaxLevel == str.toUInt())
                return true;
            break;
        case 33:
            if (m_spellInfo->BaseLevel == str.toUInt())
                return true;
            break;
        case 34:
            if (m_spellInfo->SpellLevel == str.toUInt())
                return true;
            break;
        case 35:
            if (m_spellInfo->DurationIndex == str.toUInt())
                return true;
            break;
        case 36:
            if (m_spellInfo->PowerType == str.toInt())
                return true;
            break;
        case 37:
            if (m_spellInfo->ManaCost == str.toUInt())
                return true;
            break;
        case 38:
            if (m_spellInfo->ManaCostPerlevel == str.toUInt())
                return true;
            break;
        case 39:
            if (m_spellInfo->ManaPerSecond == str.toUInt())
                return true;
            break;
        case 40:
            if (m_spellInfo->ManaPerSecondPerLevel == str.toUInt())
                return true;
            break;
        case 41:
            if (m_spellInfo->RangeIndex == str.toUInt())
                return true;
            break;
        case 42:
            if (m_spellInfo->Speed == str.toFloat())
                return true;
            break;
        case 43:
            if (m_spellInfo->ModalNextSpell == str.toUInt())
                return true;
            break;
        case 44:
            if (m_spellInfo->StackAmount == str.toUInt())
                return true;
            break;
        case 45:
            for (quint8 i = 0; i < MAX_SPELL_TOTEMS; i++)
            {
                if (m_spellInfo->Totem[i] == str.toUInt())
                    return true;
            }
            break;
        case 46:
            for (quint8 i = 0; i < MAX_SPELL_REAGENTS; i++)
            {
                if (m_spellInfo->Reagent[i] == str.toInt())
                    return true;
            }
            break;
        case 47:
            for (quint8 i = 0; i < MAX_SPELL_REAGENTS; i++)
            {
                if (m_spellInfo->ReagentCount[i] == str.toUInt())
                    return true;
            }
            break;
        case 48:
            if (m_spellInfo->EquippedItemClass == str.toInt())
                return true;
            break;
        case 49:
            if (state == STATE_NONE)
            {
                if (m_spellInfo->EquippedItemSubClassMask == str.toUInt())
                    return true;
            }
            else if (state == STATE_CONTAIN)
            {
                if (m_spellInfo->EquippedItemSubClassMask & str.toUInt())
                    return true;
            }
            else if (state == STATE_NOT_CONTAIN)
            {
                if (~m_spellInfo->EquippedItemSubClassMask & str.toUInt())
                    return true;
            }
            break;
        case 50:
            if (state == STATE_NONE)
            {
                if (m_spellInfo->EquippedItemInventoryTypeMask == str.toUInt())
                    return true;
            }
            else if (state == STATE_CONTAIN)
            {
                if (m_spellInfo->EquippedItemInventoryTypeMask & str.toUInt())
                    return true;
            }
            else if (state == STATE_NOT_CONTAIN)
            {
                if (~m_spellInfo->EquippedItemInventoryTypeMask & str.toUInt())
                    return true;
            }
            break;
        case 51:
            for (quint8 i = 0; i < MAX_EFFECT_INDEX; i++)
            {
                if (m_spellInfo->Effect[i] == str.toUInt())
                    return true;
            }
            break;
        case 52:
            for (quint8 i = 0; i < MAX_EFFECT_INDEX; i++)
            {
                if (m_spellInfo->EffectDieSides[i] == str.toInt())
                    return true;
            }
            break;
        case 53:
            for (quint8 i = 0; i < MAX_EFFECT_INDEX; i++)
            {
                if (m_spellInfo->EffectBaseDice[i] == str.toUInt())
                    return true;
            }
            break;
        case 54:
            for (quint8 i = 0; i < MAX_EFFECT_INDEX; i++)
            {
                if (m_spellInfo->EffectDicePerLevel[i] == str.toFloat())
                    return true;
            }
            break;
        case 55:
            for (quint8 i = 0; i < MAX_EFFECT_INDEX; i++)
            {
                if (m_spellInfo->EffectRealPointsPerLevel[i] == str.toFloat())
                    return true;
            }
            break;
        case 56:
            for (quint8 i = 0; i < MAX_EFFECT_INDEX; i++)
            {
                if (m_spellInfo->EffectBasePoints[i] == str.toInt())
                    return true;
            }
            break;
        case 57:
            for (quint8 i = 0; i < MAX_EFFECT_INDEX; i++)
            {
                if (m_spellInfo->EffectMechanic[i] == str.toUInt())
                    return true;
            }
            break;
        case 58:
            for (quint8 i = 0; i < MAX_EFFECT_INDEX; i++)
            {
                if (m_spellInfo->EffectImplicitTargetA[i] == str.toUInt())
                    return true;
            }
            break;
        case 59:
            for (quint8 i = 0; i < MAX_EFFECT_INDEX; i++)
            {
                if (m_spellInfo->EffectImplicitTargetB[i] == str.toUInt())
                    return true;
            }
            break;
        case 60:
            for (quint8 i = 0; i < MAX_EFFECT_INDEX; i++)
            {
                if (m_spellInfo->EffectRadiusIndex[i] == str.toUInt())
                    return true;
            }
            break;
        case 61:
            for (quint8 i = 0; i < MAX_EFFECT_INDEX; i++)
            {
                if (m_spellInfo->EffectApplyAuraName[i] == str.toUInt())
                    return true;
            }
            break;
        case 62:
            for (quint8 i = 0; i < MAX_EFFECT_INDEX; i++)
            {
                if (m_spellInfo->EffectAmplitude[i] == str.toUInt())
                    return true;
            }
            break;
        case 63:
            for (quint8 i = 0; i < MAX_EFFECT_INDEX; i++)
            {
                if (m_spellInfo->EffectMultipleValue[i] == str.toFloat())
                    return true;
            }
            break;
        case 64:
            for (quint8 i = 0; i < MAX_EFFECT_INDEX; i++)
            {
                if (m_spellInfo->EffectChainTarget[i] == str.toUInt())
                    return true;
            }
            break;
        case 65:
            for (quint8 i = 0; i < MAX_EFFECT_INDEX; i++)
            {
                if (m_spellInfo->EffectItemType[i] == str.toUInt())
                    return true;
            }
            break;
        case 66:
            for (quint8 i = 0; i < MAX_EFFECT_INDEX; i++)
            {
                if (m_spellInfo->EffectMiscValue[i] == str.toInt())
                    return true;
            }
            break;
        case 67:
            for (quint8 i = 0; i < MAX_EFFECT_INDEX; i++)
            {
                if (m_spellInfo->EffectMiscValueB[i] == str.toInt())
                    return true;
            }
            break;
        case 68:
            for (quint8 i = 0; i < MAX_EFFECT_INDEX; i++)
            {
                if (m_spellInfo->EffectTriggerSpell[i] == str.toUInt())
                    return true;
            }
            break;
        case 69:
            for (quint8 i = 0; i < MAX_EFFECT_INDEX; i++)
            {
                if (m_spellInfo->EffectPointsPerComboPoint[i] == str.toFloat())
                    return true;
            }
            break;
        case 70:
            if (m_spellInfo->SpellVisual[0] == str.toUInt() || m_spellInfo->SpellVisual[1] == str.toUInt())
                return true;
            break;
        case 71:
            if (m_spellInfo->SpellIconID == str.toUInt())
                return true;
            break;
        case 72:
            if (m_spellInfo->ActiveIconID == str.toUInt())
                return true;
            break;
        case 73:
            if (m_spellInfo->SpellPriority == str.toUInt())
                return true;
            break;
        case 74:
            if (QString(m_spellInfo->SpellName[0]) == str)
                return true;
            break;
        case 75:
            if (m_spellInfo->SpellNameFlag == str.toUInt())
                return true;
            break;
        case 76:
            if (QString(m_spellInfo->Rank[0]) == str)
                return true;
            break;
        case 77:
            if (m_spellInfo->RankFlags == str.toUInt())
                return true;
            break;
        case 78:
            if (QString(m_spellInfo->Description[0]) == str)
                return true;
            break;
        case 79:
            if (m_spellInfo->DescriptionFlags == str.toUInt())
                return true;
            break;
        case 80:
            if (QString(m_spellInfo->ToolTip[0]) == str)
                return true;
            break;
        case 81:
            if (m_spellInfo->ToolTipFlags == str.toUInt())
                return true;
            break;
        case 82:
            if (m_spellInfo->ManaCostPercentage == str.toUInt())
                return true;
            break;
        case 83:
            if (m_spellInfo->StartRecoveryCategory == str.toUInt())
                return true;
            break;
        case 84:
            if (m_spellInfo->StartRecoveryTime == str.toUInt())
                return true;
            break;
        case 85:
            if (m_spellInfo->MaxTargetLevel == str.toUInt())
                return true;
            break;
        case 86:
            if (m_spellInfo->SpellFamilyName == str.toUInt())
                return true;
            break;
        case 87:
            if (state == STATE_NONE)
            {
                if (m_spellInfo->SpellFamilyFlags == str.toULongLong())
                    return true;
            }
            else if (state == STATE_CONTAIN)
            {
                if (m_spellInfo->SpellFamilyFlags & str.toULongLong())
                    return true;
            }
            else if (state == STATE_NOT_CONTAIN)
            {
                if (~m_spellInfo->SpellFamilyFlags & str.toULongLong())
                    return true;
            }
            break;
        case 88:
            if (m_spellInfo->MaxAffectedTargets == str.toUInt())
                return true;
            break;
        case 89:
            if (m_spellInfo->DmgClass == str.toUInt())
                return true;
            break;
        case 90:
            if (m_spellInfo->PreventionType == str.toUInt())
                return true;
            break;
        case 91:
            if (m_spellInfo->StanceBarOrder == str.toFloat())
                return true;
            break;
        case 92:
            for (quint8 i = 0; i < MAX_EFFECT_INDEX; i++)
            {
                if (m_spellInfo->DmgMultiplier[i] == str.toFloat())
                    return true;
            }
            break;
        case 93:
            if (m_spellInfo->MinFactionId == str.toUInt())
                return true;
            break;
        case 94:
            if (m_spellInfo->MinReputation == str.toUInt())
                return true;
            break;
        case 95:
            if (m_spellInfo->RequiredAuraVision == str.toUInt())
                return true;
            break;
        case 96:
            for (quint8 i = 0; i < MAX_SPELL_TOTEM_CATEGORIES; i++)
            {
                if (m_spellInfo->TotemCategory[i] == str.toUInt())
                    return true;
            }
            break;
        case 97:
            if (m_spellInfo->AreaId == str.toUInt())
                return true;
            break;
        case 98:
            if (state == STATE_NONE)
            {
                if (m_spellInfo->SchoolMask == str.toUInt())
                    return true;
            }
            else if (state == STATE_CONTAIN)
            {
                if (m_spellInfo->SchoolMask & str.toUInt())
                    return true;
            }
            else if (state == STATE_NOT_CONTAIN)
            {
                if (~m_spellInfo->SchoolMask & str.toUInt())
                    return true;
            }
            break;
    }
    return false;
}

void SWSearch::Search()
{
    m_sw->ThreadSet(THREAD_SEARCH);
    SWForm *form = m_sw->GetForm();
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
                if (form->comboBox->currentIndex() < m_sw->GetMetaEnum().keyCount())
                {
                    if (m_spellInfo->SpellFamilyName == m_sw->GetMetaEnum().value(form->comboBox->currentIndex()))
                        family = true;
                }
                else
                    family = true;

                m_sw->SetMetaEnum("AuraType");
                if (form->comboBox_2->currentIndex() < m_sw->GetMetaEnum().keyCount())
                {
                    for (quint8 i = EFFECT_INDEX_0; i < MAX_EFFECT_INDEX; i++)
                    {
                        if (m_spellInfo->EffectApplyAuraName[i] == m_sw->GetMetaEnum().value(form->comboBox_2->currentIndex()))
                        {
                            aura = true;
                            break;
                        }
                    }
                }
                else
                    aura = true;

                m_sw->SetMetaEnum("Effects");
                if (form->comboBox_3->currentIndex() < m_sw->GetMetaEnum().keyCount())
                {
                    for (quint8 i = EFFECT_INDEX_0; i < MAX_EFFECT_INDEX; i++)
                    {
                        if (m_spellInfo->Effect[i] == m_sw->GetMetaEnum().value(form->comboBox_3->currentIndex()))
                        {
                            effect = true;
                            break;
                        }
                    }
                }
                else
                    effect = true;

                m_sw->SetMetaEnum("Targets");
                if (form->comboBox_4->currentIndex() < m_sw->GetMetaEnum().keyCount())
                {
                    for (quint8 i = EFFECT_INDEX_0; i < MAX_EFFECT_INDEX; i++)
                    {
                        if (m_spellInfo->EffectImplicitTargetA[i] == m_sw->GetMetaEnum().value(form->comboBox_4->currentIndex()))
                        {
                            targetA = true;
                            break;
                        }
                    }
                }
                else
                    targetA = true;

                if (form->comboBox_5->currentIndex() < m_sw->GetMetaEnum().keyCount())
                {
                    for (quint8 i = EFFECT_INDEX_0; i < MAX_EFFECT_INDEX; i++)
                    {
                        if (m_spellInfo->EffectImplicitTargetB[i] == m_sw->GetMetaEnum().value(form->comboBox_5->currentIndex()))
                        {
                            targetB = true;
                            break;
                        }
                    }
                }
                else
                    targetB = true;

                if (form->adBox1->currentIndex() > 0 && form->adBox1->currentIndex() < MAX_STRUCT)
                {
                    if (HasValue(form->adBox1->currentIndex(), form->adLine1->text(), m_spellInfo, form->GetToolState(TOOL_ONE)))
                        adFilter1 = true;
                }
                else
                    adFilter1 = true;

                if (form->adBox2->currentIndex() > 0 && form->adBox2->currentIndex() < MAX_STRUCT)
                {
                    if (HasValue(form->adBox2->currentIndex(), form->adLine2->text(), m_spellInfo, form->GetToolState(TOOL_TWO)))
                        adFilter2 = true;
                }
                else
                    adFilter2 = true;

                if (family && aura && effect && adFilter1 && adFilter2 && targetA && targetB)
                {
                    count++;
                    QString sRank(m_spellInfo->Rank[0]);

                    QStandardItem *item_id = new QStandardItem(QString("%0").arg(m_spellInfo->Id));
                    QStandardItem *item_name;

                    if (sRank.isEmpty())
                        item_name = new QStandardItem(QString("%0").arg(m_spellInfo->SpellName[0]));
                    else
                        item_name = new QStandardItem(QString("%0 (%1)").arg(m_spellInfo->SpellName[0]).arg(m_spellInfo->Rank[0]));

                    model->setItem(count, 0, item_id);
                    model->setItem(count, 1, item_name);
                }
            }
        }
        QApplication::postEvent(form, new SendModel(form, model));
    }
    else if (m_sw->GetType() == 2)
    {
        if (!form->compareSpell_1->text().isEmpty() && !form->compareSpell_2->text().isEmpty())
        {
            SpellEntry const *sInfo1 = sSpellStore.LookupEntry(form->compareSpell_1->text().toInt());
            SpellEntry const *sInfo2 = sSpellStore.LookupEntry(form->compareSpell_2->text().toInt());

            if (sInfo1 && sInfo2)
            {
                QApplication::postEvent(form, new SendCompareSpell(form, sInfo1, 0));
                QApplication::postEvent(form, new SendCompareSpell(form, sInfo2, 1));
            }
        }
    }
    else
    {
        if (!form->findLine_e1->text().isEmpty())
        {
            for (quint8 i = 0; i < form->findLine_e1->text().size(); ++i)
            {
                if (form->findLine_e1->text().at(i) > QChar('9'))
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
                    if (m_spellInfo && QString(m_spellInfo->SpellName[0]).contains(form->findLine_e1->text(), Qt::CaseInsensitive))
                    {
                        count++;
                        QString sRank(m_spellInfo->Rank[0]);

                        QStandardItem *item_id = new QStandardItem(QString("%0").arg(m_spellInfo->Id));
                        QStandardItem *item_name;

                        if (sRank.isEmpty())
                            item_name = new QStandardItem(QString("%0").arg(m_spellInfo->SpellName[0]));
                        else
                            item_name = new QStandardItem(QString("%0 (%1)").arg(m_spellInfo->SpellName[0]).arg(m_spellInfo->Rank[0]));

                        model->setItem(count, 0, item_id);
                        model->setItem(count, 1, item_name);
                    }
                }
                QApplication::postEvent(form, new SendModel(form, model));
            }
            else
            {
                SpellEntry const *m_spellInfo = sSpellStore.LookupEntry(form->findLine_e1->text().toInt());

                if (m_spellInfo)
                {
                    QString sRank(m_spellInfo->Rank[0]);

                    QStandardItem  *item_id = new QStandardItem (QString("%0").arg(m_spellInfo->Id));
                    QStandardItem  *item_name;

                    if (sRank.isEmpty())
                        item_name = new QStandardItem (QString("%0").arg(m_spellInfo->SpellName[0]));
                    else
                        item_name = new QStandardItem (QString("%0 (%1)").arg(m_spellInfo->SpellName[0]).arg(m_spellInfo->Rank[0]));

                    model->setItem(0, 0, item_id);
                    model->setItem(0, 1, item_name);
                    QApplication::postEvent(form, new SendModel(form, model));
                    QApplication::postEvent(form, new SendSpell(form, m_spellInfo));
                }
            }
        }
        else if (!form->findLine_e2->text().isEmpty())
        {
            for (quint32 i = 0; i < sSpellStore.GetNumRows(); i++)
            {
                SpellEntry const *m_spellInfo = sSpellStore.LookupEntry(i);
                if (m_spellInfo && m_spellInfo->SpellIconID == form->findLine_e2->text().toInt())
                {
                    count++;
                    QString sRank(m_spellInfo->Rank[0]);

                    QStandardItem *item_id = new QStandardItem(QString("%0").arg(m_spellInfo->Id));
                    QStandardItem *item_name;

                    if (sRank.isEmpty())
                        item_name = new QStandardItem(QString("%0").arg(m_spellInfo->SpellName[0]));
                    else
                        item_name = new QStandardItem(QString("%0 (%1)").arg(m_spellInfo->SpellName[0]).arg(m_spellInfo->Rank[0]));

                    model->setItem(count, 0, item_id);
                    model->setItem(count, 1, item_name);
                }
            }
            QApplication::postEvent(form, new SendModel(form, model));
        }
        else if (!form->findLine_e3->text().isEmpty())
        {
            for (quint32 i = 0; i < sSpellStore.GetNumRows(); i++)
            {
                SpellEntry const *m_spellInfo = sSpellStore.LookupEntry(i);
                if (m_spellInfo && QString(m_spellInfo->Description[0]).contains(form->findLine_e3->text(), Qt::CaseInsensitive))
                {
                    count++;
                    QString sRank(m_spellInfo->Rank[0]);

                    QStandardItem *item_id = new QStandardItem(QString("%0").arg(m_spellInfo->Id));
                    QStandardItem *item_name;

                    if (sRank.isEmpty())
                        item_name = new QStandardItem(QString("%0").arg(m_spellInfo->SpellName[0]));
                    else
                        item_name = new QStandardItem(QString("%0 (%1)").arg(m_spellInfo->SpellName[0]).arg(m_spellInfo->Rank[0]));

                    model->setItem(count, 0, item_id);
                    model->setItem(count, 1, item_name);
                }
            }
            QApplication::postEvent(form, new SendModel(form, model));
        }
        else
        {
            for (quint32 i = 0; i < sSpellStore.GetNumRows(); i++)
            {
                SpellEntry const *m_spellInfo = sSpellStore.LookupEntry(i);
                if (m_spellInfo)
                {
                    count++;
                    QString sRank(m_spellInfo->Rank[0]);

                    QStandardItem *item_id = new QStandardItem(QString("%0").arg(m_spellInfo->Id));
                    QStandardItem *item_name;

                    if (sRank.isEmpty())
                        item_name = new QStandardItem(QString("%0").arg(m_spellInfo->SpellName[0]));
                    else
                        item_name = new QStandardItem(QString("%0 (%1)").arg(m_spellInfo->SpellName[0]).arg(m_spellInfo->Rank[0]));

                    model->setItem(count, 0, item_id);
                    model->setItem(count, 1, item_name);
                }
            }
            QApplication::postEvent(form, new SendModel(form, model));
        }
    }
    m_sw->ThreadUnset(THREAD_SEARCH);
}

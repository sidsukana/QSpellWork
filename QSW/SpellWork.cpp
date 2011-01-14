#include "SpellWork.h"
#include "QDefines.h"

SpellWork::SpellWork(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);

    m_spellInfo = NULL;

    LoadDBCStores();
    LoadComboBoxes();

    connect(SpellList, SIGNAL(clicked(QModelIndex)), this, SLOT(SlotSearchFromList(QModelIndex)));

    connect(findButton, SIGNAL(clicked()), this, SLOT(SlotSearch()));
    connect(actionAbout, SIGNAL(triggered()), this, SLOT(SlotAbout()));
    connect(actionExit, SIGNAL(triggered()), this, SLOT(close()));
}

SpellWork::~SpellWork()
{
}

About::About(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);
}

About::~About()
{
}

ObjectSearch::ObjectSearch(SpellWork *obj)
    : iFace(obj)
{
    Search();
}

ObjectSearch::~ObjectSearch()
{
}

void SpellWork::LoadComboBoxes()
{
    comboBox->clear();
    comboBox->insertItem(-1, "SpellFamilyName");
    for (uint16 i = 0; i < MAX_SPELLFAMILY; i++)
        comboBox->insertItem(i, SpellFamilyString[i]);

    comboBox_2->clear();
    comboBox_2->insertItem(-1, "Aura");
    for (uint16 i = 0; i < MAX_AURA; i++)
        comboBox_2->insertItem(i, AuraString[i]);

    comboBox_3->clear();
    comboBox_3->insertItem(-1, "Effect");
    for (uint16 i = 0; i < MAX_EFFECT; i++)
        comboBox_3->insertItem(i, EffectString[i]);
}

void SpellWork::SlotAbout()
{
    About *about = new About;
    about->show();
}

bool SpellWork::event(QEvent* t_event)
{
    switch (t_event->type())
    {
        case _Event::TypeId:
        {
            _Event* ev = (_Event*)t_event;
            
            switch (ev->GetId())
            {
                case EVENT_SETMODEL:
                {
                    SpellList->setModel(ev->GetmObj());
                    if (ev->GetsObj())
                    {
                        m_spellInfo = ev->GetsObj();
                        ShowInfo();
                    }
                    return true;
                }
                break;
            }
            break;
        }
    }

    return QWidget::event(t_event);
}

_Event::_Event(int id, QStandardItemModel* m, SpellEntry const* s)
        : QEvent(QEvent::Type(_Event::TypeId)), op_id(id), mObj(m), sObj(s)
{
}

_Event::~_Event()
{
}
void ObjectSearch::Search()
{
    bool isString = false;

    QStandardItemModel *model;
    SpellEntry const *spellInfo;
    
    model = new QStandardItemModel(1, 2);
    model->setHorizontalHeaderItem(0, new QStandardItem("ID"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Name"));

    if (!iFace->findLine_e1->text().isEmpty())
    {
        for (int i = 0; i < iFace->findLine_e1->text().size(); ++i)
        {
            if (iFace->findLine_e1->text().at(i) > QChar('9'))
            {
                isString = true;
                break;
            }
        }

        if (isString)
        {
            int count = -1;
            for (int i = 0; i < sSpellStore.GetNumRows(); i++)
            {
                spellInfo = sSpellStore.LookupEntry(i);
				if (spellInfo && QString(spellInfo->SpellName[0]).contains(iFace->findLine_e1->text(), Qt::CaseInsensitive))
                {
                    count++;
                    QString sRank((char*)spellInfo->Rank[0]);

                    QStandardItem *item_id = new QStandardItem(QString("%0").arg(spellInfo->Id));
                    QStandardItem *item_name;

                    if (sRank.isEmpty())
                        item_name = new QStandardItem(QString("%0").arg((char*)spellInfo->SpellName[0]));
                    else
                        item_name = new QStandardItem(QString("%0 (%1)").arg((char*)spellInfo->SpellName[0]).arg((char*)spellInfo->Rank[0]));

                    model->setItem(count, 0, item_id);
                    model->setItem(count, 1, item_name);
                }
            }
            QApplication::postEvent(iFace, new _Event(EVENT_SETMODEL, model));
        }
        else
        {
            spellInfo = sSpellStore.LookupEntry(iFace->findLine_e1->text().toInt());

            if (spellInfo)
            {
                QString sRank((char*)spellInfo->Rank[0]);

                QStandardItem  *item_id = new QStandardItem (QString("%0").arg(spellInfo->Id));
                QStandardItem  *item_name;

                if (sRank.isEmpty())
                    item_name = new QStandardItem (QString("%0").arg((char*)spellInfo->SpellName[0]));
                else
                    item_name = new QStandardItem (QString("%0 (%1)").arg((char*)spellInfo->SpellName[0]).arg((char*)spellInfo->Rank[0]));

                model->setItem(0, 0, item_id);
                model->setItem(0, 1, item_name);
                QApplication::postEvent(iFace, new _Event(EVENT_SETMODEL, model, spellInfo));
            }
        }
    }
    else if (!iFace->findLine_e2->text().isEmpty())
    {
        int count = -1;
        for (int i = 0; i < sSpellStore.GetNumRows(); i++)
        {
            spellInfo = sSpellStore.LookupEntry(i);
            if (spellInfo && spellInfo->SpellIconID == iFace->findLine_e2->text().toInt())
            {
                count++;
                QString sRank((char*)spellInfo->Rank[0]);

                QStandardItem *item_id = new QStandardItem(QString("%0").arg(spellInfo->Id));
                QStandardItem *item_name;

                if (sRank.isEmpty())
                    item_name = new QStandardItem(QString("%0").arg((char*)spellInfo->SpellName[0]));
                else
                    item_name = new QStandardItem(QString("%0 (%1)").arg((char*)spellInfo->SpellName[0]).arg((char*)spellInfo->Rank[0]));

                model->setItem(count, 0, item_id);
                model->setItem(count, 1, item_name);
            }
        }
        QApplication::postEvent(iFace, new _Event(EVENT_SETMODEL, model));
    }
    else if (!iFace->findLine_e3->text().isEmpty())
    {
        int count = -1;
        for (int i = 0; i < sSpellStore.GetNumRows(); i++)
        {
            spellInfo = sSpellStore.LookupEntry(i);
            if (spellInfo && QString(spellInfo->Description[0]).contains(iFace->findLine_e3->text(), Qt::CaseInsensitive))
            {
                count++;
                QString sRank((char*)spellInfo->Rank[0]);

                QStandardItem *item_id = new QStandardItem(QString("%0").arg(spellInfo->Id));
                QStandardItem *item_name;

                if (sRank.isEmpty())
                    item_name = new QStandardItem(QString("%0").arg((char*)spellInfo->SpellName[0]));
                else
                    item_name = new QStandardItem(QString("%0 (%1)").arg((char*)spellInfo->SpellName[0]).arg((char*)spellInfo->Rank[0]));

                model->setItem(count, 0, item_id);
                model->setItem(count, 1, item_name);
            }
        }
        QApplication::postEvent(iFace, new _Event(EVENT_SETMODEL, model));
    }
}

void SpellWork::BeginThread(int id)
{
    for (ThreadList::iterator itr = threads.begin(); itr != threads.end(); ++itr)
    {
        if ((*itr) && (*itr)->isFinished())
            delete (*itr);
        else return;
    }

    threads.clear();

    threads.push_back(new ObjThread(id, this));
    
    for (ThreadList::iterator itr = threads.begin(); itr != threads.end(); ++itr)
    {
        if ((*itr) && !(*itr)->isFinished())
            (*itr)->start();
    }
}

void SpellWork::SlotSearch()
{
    BeginThread(THREAD_SEARCH);
}

void SpellWork::SlotSearchFromList(const QModelIndex &index)
{
    QVariant var = SpellList->model()->data(SpellList->model()->index(index.row(), 0));

    m_spellInfo = sSpellStore.LookupEntry(var.toInt());
    if (m_spellInfo)
        ShowInfo();
}

float SpellWork::GetRadius(SpellEntry const *spellInfo, uint8 effIndex)
{
    if (!spellInfo)
        return 0.0f;

    SpellRadiusEntry const *spellRadius = sSpellRadiusStore.LookupEntry(spellInfo->EffectRadiusIndex[effIndex]);
    if (spellRadius)
        return spellRadius->Radius;

    return 0.0f;
}

int SpellWork::GetRealDuration(SpellEntry const *spellInfo, uint8 effIndex)
{
    if (!spellInfo)
        return 1;

    return int(GetDuration(spellInfo) / int(spellInfo->EffectAmplitude[effIndex] / 1000));
}

QString SpellWork::GetDescription(QString str, SpellEntry const *spellInfo)
{
    QRegExp rx("\\$+(/([1-9]?[0-9]);)?([d+\\;)(\\d*)?([1-9]*)([a-zA-Z])([1-3]*)([a-zA-z ]*\\:([a-zA-z ]*)\\;)?");
    while (str.contains(rx))
    {
        if (rx.indexIn(str) != -1)
        {
            switch (rx.cap(4)[0].toAscii())
            {
                case 'a':
                {
                    if (!rx.cap(2).isEmpty())
                    {
                        if (!rx.cap(3).isEmpty())
                        {
                            SpellEntry const *tSpell = sSpellStore.LookupEntry(rx.cap(3).toInt());
                            if (tSpell)
                            {
                                str.replace(rx.cap(0), QString("%0")
                                    .arg(int(GetRadius(tSpell, rx.cap(5).toInt()-1)/rx.cap(2).toInt())));
                            }
                        }
                        else
                        {
                            str.replace(rx.cap(0), QString("%0")
                                .arg(int(GetRadius(spellInfo, rx.cap(5).toInt()-1)/rx.cap(2).toInt())));
                        }
                    }
                    else if (!rx.cap(3).isEmpty())
                    {
                        SpellEntry const *tSpell = sSpellStore.LookupEntry(rx.cap(3).toInt());
                        if (tSpell)
                        {
                            str.replace(rx.cap(0), QString("%0")
                                .arg(GetRadius(tSpell, rx.cap(5).toInt()-1)));
                        }
                    }
                    else
                    {
                        str.replace(rx.cap(0), QString("%0")
                            .arg(GetRadius(spellInfo, rx.cap(5).toInt()-1)));
                    }
                }
                case 'd':
                {
                    if (!rx.cap(2).isEmpty())
                    {
                        if (!rx.cap(3).isEmpty())
                        {
                            SpellEntry const *tSpell = sSpellStore.LookupEntry(rx.cap(3).toInt());
                            if (tSpell)
                            {
                                str.replace(rx.cap(0), QString("%0")
                                    .arg(int(GetDuration(tSpell)/rx.cap(2).toInt())));
                            }
                        }
                        else
                        {
                            str.replace(rx.cap(0), QString("%0")
                                .arg(int(GetDuration(spellInfo)/rx.cap(2).toInt())));
                        }
                    }
                    else if (!rx.cap(3).isEmpty())
                    {
                        SpellEntry const *tSpell = sSpellStore.LookupEntry(rx.cap(3).toInt());
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
                break;
                case 'o':
                {
                    if (!rx.cap(2).isEmpty())
                    {
                        if (!rx.cap(3).isEmpty())
                        {
                            SpellEntry const *tSpell = sSpellStore.LookupEntry(rx.cap(3).toInt());
                            if (tSpell)
                            {
                                str.replace(rx.cap(0), QString("%0")
                                .arg(int((GetRealDuration(tSpell, rx.cap(5).toInt()-1) * (tSpell->EffectBasePoints[rx.cap(5).toInt()-1] + 1))/rx.cap(2).toInt())));
                            }
                        }
                        else
                        {
                            str.replace(rx.cap(0), QString("%0")
                                .arg(int((GetRealDuration(spellInfo, rx.cap(5).toInt()-1) * (spellInfo->EffectBasePoints[rx.cap(5).toInt()-1] + 1))/rx.cap(2).toInt())));
                        }
                    }
                    else if (!rx.cap(3).isEmpty())
                    {
                        SpellEntry const *tSpell = sSpellStore.LookupEntry(rx.cap(3).toInt());
                        if (tSpell)
                        {
                            str.replace(rx.cap(0), QString("%0")
                                .arg(GetRealDuration(tSpell, rx.cap(5).toInt()-1) * (tSpell->EffectBasePoints[rx.cap(5).toInt()-1] + 1)));
                        }
                    }
                    else
                    {
                        str.replace(rx.cap(0), QString("%0")
                            .arg(GetRealDuration(spellInfo, rx.cap(5).toInt()-1) * (spellInfo->EffectBasePoints[rx.cap(5).toInt()-1] + 1)));
                    }
                }
                break;
                case 's':
                {
                    if (!rx.cap(2).isEmpty())
                    {
                        if (!rx.cap(3).isEmpty())
                        {
                            SpellEntry const *tSpell = sSpellStore.LookupEntry(rx.cap(3).toInt());
                            if (tSpell)
                            {
                                str.replace(rx.cap(0), QString("%0")
                                    .arg(abs(int((tSpell->EffectBasePoints[rx.cap(5).toInt()-1] + 1)/rx.cap(2).toInt()))));
                            }
                        }
                        else
                        {
                            str.replace(rx.cap(0), QString("%0")
                                .arg(abs(int((spellInfo->EffectBasePoints[rx.cap(5).toInt()-1] + 1)/rx.cap(2).toInt()))));
                        }
                    }
                    else if (!rx.cap(3).isEmpty())
                    {
                        SpellEntry const *tSpell = sSpellStore.LookupEntry(rx.cap(3).toInt());
                        if (tSpell)
                        {
                            str.replace(rx.cap(0), QString("%0")
                                .arg(abs(tSpell->EffectBasePoints[rx.cap(5).toInt()-1] + 1)));
                        }
                    }
                    else
                    {
                        str.replace(rx.cap(0), QString("%0")
                            .arg(abs(spellInfo->EffectBasePoints[rx.cap(5).toInt()-1] + 1)));
                    }
                }
                break;
                case 't':
                {
                    if (!rx.cap(2).isEmpty())
                    {
                        if (!rx.cap(3).isEmpty())
                        {
                            SpellEntry const *tSpell = sSpellStore.LookupEntry(rx.cap(3).toInt());
                            if (tSpell)
                            {
                                str.replace(rx.cap(0), QString("%0")
                                    .arg(int(int(tSpell->EffectAmplitude[rx.cap(5).toInt()-1] / 1000)/rx.cap(2).toInt())));
                            }
                        }
                        else
                        {
                            str.replace(rx.cap(0), QString("%0")
                                .arg(int(int(spellInfo->EffectAmplitude[rx.cap(5).toInt()-1] / 1000)/rx.cap(2).toInt())));
                        }
                    }
                    else if (!rx.cap(3).isEmpty())
                    {
                        SpellEntry const *tSpell = sSpellStore.LookupEntry(rx.cap(3).toInt());
                        if (tSpell)
                        {
                            str.replace(rx.cap(0), QString("%0")
                                .arg(int(tSpell->EffectAmplitude[rx.cap(5).toInt()-1] / 1000)));
                        }
                    }
                    else
                    {
                        str.replace(rx.cap(0), QString("%0")
                            .arg(int(spellInfo->EffectAmplitude[rx.cap(5).toInt()-1] / 1000)));
                    }
                }
                break;
                case 'l':
                {
                    str.replace(rx.cap(0), rx.cap(7));
                }
                break;
                case 'n':
                {
                    if (!rx.cap(3).isEmpty())
                    {
                        SpellEntry const *tSpell = sSpellStore.LookupEntry(rx.cap(3).toInt());
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
                break;
                default:
                    return str;
            }
        }
    }
    return str;
}

void SpellWork::ShowInfo()
{
    if (!m_spellInfo)
        return;

    SpellInfoBrowser->clear();
    QTextCursor cur = SpellInfoBrowser->textCursor();
    cur.clearSelection();
    SpellInfoBrowser->setTextCursor(cur);

    QString line("==================================================");

    QString sName((char*)m_spellInfo->SpellName[0]);
    QString sDescription((char*)m_spellInfo->Description[0]);
    QString sRank((char*)m_spellInfo->Rank[0]);
    QString sToolTip((char*)m_spellInfo->ToolTip[0]);
    QString sSpellFamilyFlags(QString("%0").arg(m_spellInfo->SpellFamilyFlags, 16, 16, QChar('0')));
    QString sAttributes(QString("%0").arg(m_spellInfo->Attributes, 8, 16, QChar('0')));
    QString sAttributesEx(QString("%0").arg(m_spellInfo->AttributesEx, 8, 16, QChar('0')));
    QString sAttributesEx2(QString("%0").arg(m_spellInfo->AttributesEx2, 8, 16, QChar('0')));
    QString sAttributesEx3(QString("%0").arg(m_spellInfo->AttributesEx3, 8, 16, QChar('0')));
    QString sAttributesEx4(QString("%0").arg(m_spellInfo->AttributesEx4, 8, 16, QChar('0')));
    QString sTargetMask(QString("%0").arg(m_spellInfo->Targets, 8, 16, QChar('0')));
    QString sCreatureTypeMask(QString("%0").arg(m_spellInfo->TargetCreatureType, 8, 16, QChar('0')));
    QString sFormMask(QString("%0").arg(m_spellInfo->Stances, 8, 16, QChar('0')));
    QString sIF(QString("%0").arg(m_spellInfo->InterruptFlags, 8, 16, QChar('0')));
    QString sAIF(QString("%0").arg(m_spellInfo->AuraInterruptFlags, 8, 16, QChar('0')));
    QString sCIF(QString("%0").arg(m_spellInfo->ChannelInterruptFlags, 8, 16, QChar('0')));

    SpellInfoBrowser->append(QString("<b>ID:</b> %0").arg(m_spellInfo->Id));

    if (sRank.isEmpty())
        SpellInfoBrowser->append(QString("<b>Name:</b> %0").arg(sName));
    else
        SpellInfoBrowser->append(QString("<b>Name:</b> %0 (%1)")
            .arg(sName)
            .arg(sRank));

    if (!sDescription.isEmpty())
        SpellInfoBrowser->append(QString("<b>Description:</b> %0").arg(GetDescription(sDescription, m_spellInfo)));

    if (!sToolTip.isEmpty())
        SpellInfoBrowser->append(QString("<b>ToolTip:</b> %0").arg(GetDescription(sToolTip, m_spellInfo)));

    SpellInfoBrowser->append(line);

     if (m_spellInfo->ModalNextSpell)
        SpellInfoBrowser->append(QString("ModalNextSpell: %0").arg(m_spellInfo->ModalNextSpell));

    SpellInfoBrowser->append(QString("Category = %0, SpellIconID = %1, ActiveIconID = %2, SpellVisual = %3")
        .arg(m_spellInfo->Category)
        .arg(m_spellInfo->SpellIconID)
        .arg(m_spellInfo->ActiveIconID)
        .arg(m_spellInfo->SpellVisual));

    SpellInfoBrowser->append(QString("SpellFamilyName = %0, SpellFamilyFlags = 0x%1\n")
        .arg(SpellFamilyString[m_spellInfo->SpellFamilyName])
        .arg(sSpellFamilyFlags.toUpper()));

    SpellInfoBrowser->append(QString("SpellSchool = %0 (%1)")
        .arg(m_spellInfo->School)
        .arg(SchoolString[m_spellInfo->School]));

    SpellInfoBrowser->append(QString("DamageClass = %0 (%1)")
        .arg(m_spellInfo->DmgClass)
        .arg(DmgClassString[m_spellInfo->DmgClass]));

    SpellInfoBrowser->append(QString("PreventionType = %0 (%1)")
        .arg(m_spellInfo->PreventionType)
        .arg(PreventionTypeString[m_spellInfo->PreventionType]));
    
    if (m_spellInfo->Attributes || m_spellInfo->AttributesEx || m_spellInfo->AttributesEx2 ||
        m_spellInfo->AttributesEx3 || m_spellInfo->AttributesEx4)
        SpellInfoBrowser->append(line);

    if (m_spellInfo->Attributes)
        SpellInfoBrowser->append(QString("Attributes: 0x%0 (%1)")
            .arg(sAttributes.toUpper())
            .arg(CompareAttributes(TYPE_ATTR)));

    if (m_spellInfo->AttributesEx)
        SpellInfoBrowser->append(QString("AttributesEx: 0x%0 (%1)")
            .arg(sAttributesEx.toUpper())
            .arg(CompareAttributes(TYPE_ATTR_EX)));

    if (m_spellInfo->AttributesEx2)
        SpellInfoBrowser->append(QString("AttributesEx2: 0x%0 (%1)")
            .arg(sAttributesEx2.toUpper())
            .arg(CompareAttributes(TYPE_ATTR_EX2)));

    if (m_spellInfo->AttributesEx3)
        SpellInfoBrowser->append(QString("AttributesEx3: 0x%0 (%1)")
            .arg(sAttributesEx3.toUpper())
            .arg(CompareAttributes(TYPE_ATTR_EX3)));

    if (m_spellInfo->AttributesEx4)
        SpellInfoBrowser->append(QString("AttributesEx4: 0x%0 (%1)")
            .arg(sAttributesEx4.toUpper())
            .arg(CompareAttributes(TYPE_ATTR_EX4)));

    SpellInfoBrowser->append(line);

    if (m_spellInfo->Targets)
        SpellInfoBrowser->append(QString("Targets Mask = 0x%0 (%1)")
            .arg(sTargetMask.toUpper())
            .arg(CompareAttributes(TYPE_TARGETS)));

    if (m_spellInfo->TargetCreatureType)
        SpellInfoBrowser->append(QString("Creature Type Mask = 0x%0 (%1)")
            .arg(sCreatureTypeMask.toUpper())
            .arg(CompareAttributes(TYPE_CREATURE)));

    if (m_spellInfo->Stances)
        SpellInfoBrowser->append(QString("Stances: 0x%0 (%1)")
            .arg(sFormMask.toUpper())
            .arg(CompareAttributes(TYPE_FORMS)));

    if (m_spellInfo->StancesNot)
        SpellInfoBrowser->append(QString("Stances not: 0x%0 (%1)")
            .arg(sFormMask.toUpper())
            .arg(CompareAttributes(TYPE_FORMS_NOT)));

    AppendSkillLine();

    SpellInfoBrowser->append(QString("Spell Level = %0, BaseLevel %1, MaxLevel %2, MaxTargetLevel %3")
        .arg(m_spellInfo->SpellLevel)
        .arg(m_spellInfo->BaseLevel)
        .arg(m_spellInfo->MaxLevel)
        .arg(m_spellInfo->MaxTargetLevel));

    if (m_spellInfo->EquippedItemClass != -1)
    {
        SpellInfoBrowser->append(QString("EquippedItemClass = %0 (%1)")
            .arg(m_spellInfo->EquippedItemClass)
            .arg(ItemClassString[m_spellInfo->EquippedItemClass]));

        if (m_spellInfo->EquippedItemSubClassMask)
        {
            QString sItemSubClassMask(QString("%0").arg(m_spellInfo->EquippedItemSubClassMask, 8, 16, QChar('0')));
            switch (m_spellInfo->EquippedItemClass)
            {
                case 2: // WEAPON
                SpellInfoBrowser->append(QString("  SubClass mask 0x%0 (%1)")
                    .arg(sItemSubClassMask.toUpper())
                    .arg(CompareAttributes(TYPE_ITEM_WEAPON)));
                    break;
                case 4: // ARMOR
                SpellInfoBrowser->append(QString("  SubClass mask 0x%0 (%1)")
                    .arg(sItemSubClassMask.toUpper())
                    .arg(CompareAttributes(TYPE_ITEM_ARMOR)));
                    break;
                case 15: // MISC
                SpellInfoBrowser->append(QString("  SubClass mask 0x%0 (%1)")
                    .arg(sItemSubClassMask.toUpper())
                    .arg(CompareAttributes(TYPE_ITEM_MISC)));
                    break;
            }
        }

        if (m_spellInfo->EquippedItemInventoryTypeMask)
        {
            QString sItemInventoryMask(QString("%0").arg(m_spellInfo->EquippedItemInventoryTypeMask, 8, 16, QChar('0')));
            SpellInfoBrowser->append(QString("  InventoryType mask = 0x%0 (%1)")
                .arg(sItemInventoryMask.toUpper())
                .arg(CompareAttributes(TYPE_ITEM_INVENTORY)));
        }
    }

    SpellInfoBrowser->append(QString());

    SpellInfoBrowser->append(QString("Category = %0").arg(m_spellInfo->Category));

    SpellInfoBrowser->append(QString("DispelType = %0 (%1)")
        .arg(m_spellInfo->Dispel)
        .arg(DispelTypeString[m_spellInfo->Dispel]));

    SpellInfoBrowser->append(QString("Mechanic = %0 (%1)")
        .arg(m_spellInfo->Mechanic)
        .arg(MechanicString[m_spellInfo->Mechanic]));

    AppendRangeInfo();

    if (m_spellInfo->Speed)
        SpellInfoBrowser->append(QString("Speed: %0").arg(m_spellInfo->Speed, 0, 'f', 2));

    if (m_spellInfo->StackAmount)
        SpellInfoBrowser->append(QString("Stackable up to %0").arg(m_spellInfo->StackAmount));

    AppendCastTimeLine();

    if (m_spellInfo->RecoveryTime || m_spellInfo->CategoryRecoveryTime || m_spellInfo->StartRecoveryCategory)
    {
        SpellInfoBrowser->append(QString("RecoveryTime: %0 ms, CategoryRecoveryTime: %1 ms")
            .arg(m_spellInfo->RecoveryTime)
            .arg(m_spellInfo->CategoryRecoveryTime));

        SpellInfoBrowser->append(QString("StartRecoveryCategory = %0, StartRecoveryTime = %1 ms")
            .arg(m_spellInfo->StartRecoveryCategory)
            .arg(float(m_spellInfo->StartRecoveryTime), 0, 'f', 2));
    }

    AppendDurationLine();

    if (m_spellInfo->ManaCost || m_spellInfo->ManaCostPercentage)
    {
        SpellInfoBrowser->append(QString("Power Type = %0, Cost %1")
            .arg(PowerString())
            .arg(m_spellInfo->ManaCost));

        if (m_spellInfo->ManaCostPerlevel)
            SpellInfoBrowser->append(QString("  + lvl * %0").arg(m_spellInfo->ManaCostPerlevel));

        if (m_spellInfo->ManaPerSecond)
            SpellInfoBrowser->append(QString("  + %0 Per Second").arg(m_spellInfo->ManaPerSecond));

        if (m_spellInfo->ManaPerSecondPerLevel)
            SpellInfoBrowser->append(QString("  + lvl * %0").arg(m_spellInfo->ManaPerSecondPerLevel));
    }

    SpellInfoBrowser->append(QString());

    SpellInfoBrowser->append(QString("Interrupt Flags: 0x%0, AuraIF 0x%1, ChannelIF 0x%2")
        .arg(sIF.toUpper())
        .arg(sAIF.toUpper())
        .arg(sCIF.toUpper()));

    if (m_spellInfo->CasterAuraState)
        SpellInfoBrowser->append(QString("CasterAuraState = %0 (%1)")
            .arg(m_spellInfo->CasterAuraState)
            .arg(AuraStateString[m_spellInfo->CasterAuraState]));

    if (m_spellInfo->TargetAuraState)
        SpellInfoBrowser->append(QString("TargetAuraState = %0 (%1)")
            .arg(m_spellInfo->TargetAuraState)
            .arg(AuraStateString[m_spellInfo->TargetAuraState]));

    if (m_spellInfo->RequiresSpellFocus)
        SpellInfoBrowser->append(QString("Requires Spell Focus %0").arg(m_spellInfo->RequiresSpellFocus));

    if (m_spellInfo->ProcFlags)
    {
        QString sProcFlags(QString("%0").arg(m_spellInfo->ProcFlags, 8, 16, QChar('0')));
        SpellInfoBrowser->append(QString("<b>Proc flag 0x%0, chance = %1, charges - %2</b>")
            .arg(sProcFlags.toUpper())
            .arg(m_spellInfo->ProcChance)
            .arg(m_spellInfo->ProcCharges));
        SpellInfoBrowser->append(line);

        AppendProcInfo(m_spellInfo);
    }
    else
    {
        SpellInfoBrowser->append(QString("Chance = %0, charges - %1")
            .arg(m_spellInfo->ProcChance)
            .arg(m_spellInfo->ProcCharges));
    }

    SpellInfoBrowser->append(line);

    AppendSpellEffectInfo();
}

void SpellWork::AppendRangeInfo()
{
    if (!m_spellInfo)
        return;

    SpellRangeEntry const *range = sSpellRangeStore.LookupEntry(m_spellInfo->RangeIndex);
    if (range)
    {
        SpellInfoBrowser->append(QString("SpellRange: (Id %0) \"%1\": MinRange = %2, MaxRange = %3")
            .arg(range->Id)
            .arg((char*)range->Name[0])
            .arg(range->MinRange)
            .arg(range->MaxRange));
    }
}

void SpellWork::AppendProcInfo(SpellEntry const *spellInfo)
{
    if (!spellInfo)
        return;

    int i = 0;
    uint64 proc = spellInfo->ProcFlags;
    while (proc != 0)
    {
        if ((proc & 1) != 0)
            SpellInfoBrowser->append(QString("  %0").arg(ProcFlagDesc[i]));
        i++;
        proc >>= 1;
    }
}

void SpellWork::AppendSpellEffectInfo()
{
    if (!m_spellInfo)
        return;

    for (uint8 i = EFFECT_INDEX_0; i < MAX_EFFECT_INDEX; i++)
    {
        if (!m_spellInfo->Effect[i])
        {
            SpellInfoBrowser->append(QString("<b>Effect %0:  NO EFFECT</b>").arg(i));
            SpellInfoBrowser->append(QString());
        }
        else
        {
            QString _BasePoints(QString("BasePoints = %0").arg(m_spellInfo->EffectBasePoints[i] + 1));
            
            QString _RealPoints;
            if (m_spellInfo->EffectRealPointsPerLevel[i] != 0)
                _RealPoints = QString(" + Level * %0").arg(m_spellInfo->EffectRealPointsPerLevel[i], 0, 'f', 2);

            QString _DieSides;
            if (1 < m_spellInfo->EffectDieSides[i])
            {
                if (m_spellInfo->EffectRealPointsPerLevel[i] != 0)
                    _DieSides = QString(" to %0 + lvl * %1")
                        .arg(m_spellInfo->EffectBasePoints[i] + 1 + m_spellInfo->EffectDieSides[i])
                        .arg(m_spellInfo->EffectRealPointsPerLevel[i], 0, 'f', 2);
                else
                    _DieSides = QString(" to %0").arg(m_spellInfo->EffectBasePoints[i] + 1 + m_spellInfo->EffectDieSides[i]);
            }

            QString _PointsPerCombo;
            if (m_spellInfo->EffectPointsPerComboPoint[i] != 0)
                _PointsPerCombo = QString(" + combo * %0").arg(m_spellInfo->EffectPointsPerComboPoint[i], 0, 'f', 2);

            QString _DmgMultiplier;
            if (m_spellInfo->DmgMultiplier[i] != 1.0f)
                _DmgMultiplier = QString(" * %0").arg(m_spellInfo->DmgMultiplier[i], 0, 'f', 2);

            QString _Multiple;
            if (m_spellInfo->EffectMultipleValue[i] != 0)
                _Multiple = QString(", Multiple = %0").arg(m_spellInfo->EffectMultipleValue[i], 0, 'f', 2);
                
            QString _Result = _BasePoints + _RealPoints + _DieSides + _PointsPerCombo + _DmgMultiplier + _Multiple;
            SpellInfoBrowser->append(QString("<b>Effect %0: Id %1 (%2)</b>")
                .arg(i)
                .arg(m_spellInfo->Effect[i])
                .arg(EffectString[m_spellInfo->Effect[i]]));

            SpellInfoBrowser->append(_Result);

            SpellInfoBrowser->append(QString("Targets (%0, %1) (%2, %3)")
                .arg(m_spellInfo->EffectImplicitTargetA[i])
                .arg(m_spellInfo->EffectImplicitTargetB[i])
                .arg(EffectTargetString[m_spellInfo->EffectImplicitTargetA[i]])
                .arg(EffectTargetString[m_spellInfo->EffectImplicitTargetB[i]]));
            
            AppendAuraInfo(i);

            AppendRadiusInfo(i);

            AppendTriggerInfo(i);

            if (m_spellInfo->EffectChainTarget[i] != 0)
                SpellInfoBrowser->append(QString("EffectChainTarget = %0").arg(m_spellInfo->EffectChainTarget[i]));

            if (m_spellInfo->EffectItemType[i] != 0)
                SpellInfoBrowser->append(QString("EffectItemType = %0").arg(m_spellInfo->EffectItemType[i]));

            if (m_spellInfo->EffectMechanic[i] != 0)
                SpellInfoBrowser->append(QString("Effect Mechanic = %0 (%1)")
                    .arg(m_spellInfo->EffectMechanic[i])
                    .arg(MechanicString[m_spellInfo->EffectMechanic[i]]));

            SpellInfoBrowser->append(QString());
        }
    }
}

void SpellWork::AppendTriggerInfo(int index)
{
    if (!m_spellInfo)
        return;

    uint32 trigger = m_spellInfo->EffectTriggerSpell[index];
    if (trigger != 0)
    {
        SpellEntry const *triggerSpell = sSpellStore.LookupEntry(trigger);
        if (triggerSpell)
        {
            SpellInfoBrowser->append(QString("<b><font color='blue'>   Trigger spell (%0) %1. Chance = %2</font></b>")
                .arg(trigger)
                .arg(QString("%0 (%1)").arg((char*)triggerSpell->SpellName[0]).arg((char*)triggerSpell->Rank[0]))
                .arg(triggerSpell->ProcChance));

                QString sDescription((char*)triggerSpell->Description[0]);
                QString sTooltip((char*)triggerSpell->ToolTip[0]);

                if (!sDescription.isEmpty())
                    SpellInfoBrowser->append(QString("   Description: %0").arg(GetDescription(sDescription, triggerSpell)));

                if (!sTooltip.isEmpty())
                    SpellInfoBrowser->append(QString("   ToolTip: %0").arg(GetDescription(sTooltip, triggerSpell)));

                if (triggerSpell->ProcFlags != 0)
                {
                    SpellInfoBrowser->append(QString("Charges - %0").arg(triggerSpell->ProcCharges));
                    SpellInfoBrowser->append(QString());
                        
                    AppendProcInfo(triggerSpell);

                    SpellInfoBrowser->append(QString());
                }
        }
        else
        {
            SpellInfoBrowser->append(QString("Trigger spell (%0) Not found").arg(trigger));
        }
    }
}

void SpellWork::AppendRadiusInfo(int index)
{
    if (!m_spellInfo)
        return;

    uint32 rIndex = m_spellInfo->EffectRadiusIndex[index];
    if (rIndex != 0)
    {
        SpellRadiusEntry const *spellRadius = sSpellRadiusStore.LookupEntry(rIndex);
        if (spellRadius)
            SpellInfoBrowser->append(QString("Radius (Id %0) %1")
                .arg(rIndex)
                .arg(spellRadius->Radius, 0, 'f', 2));
        else
            SpellInfoBrowser->append(QString("Radius (Id %0) Not found").arg(rIndex));
    }
}

void SpellWork::AppendAuraInfo(int index)
{
    if (!m_spellInfo)
        return;

    QString sAura(AuraString[m_spellInfo->EffectApplyAuraName[index]]);
    int misc = m_spellInfo->EffectMiscValue[index];

    if (m_spellInfo->EffectApplyAuraName[index] == 0)
    {
        if (m_spellInfo->EffectMiscValue[index] != 0)
            SpellInfoBrowser->append(QString("EffectMiscValue = %0").arg(m_spellInfo->EffectMiscValue[index]));

        if (m_spellInfo->EffectAmplitude[index] != 0)
            SpellInfoBrowser->append(QString("EffectAmplitude = %0").arg(m_spellInfo->EffectAmplitude[index]));
                
        return;
    }

    QString _BaseAuraInfo;
    _BaseAuraInfo = QString("Aura Id %0 (%1), value = %2, misc = %3 ")
        .arg(m_spellInfo->EffectApplyAuraName[index])
        .arg(sAura)
        .arg(m_spellInfo->EffectBasePoints[index] + 1)
        .arg(misc);

    QString _SpecialAuraInfo;
    switch (m_spellInfo->EffectApplyAuraName[index])
    {
        case 29:
            _SpecialAuraInfo = QString("(%0").arg(UnitMods[misc]);
            break;
        case 189:
            _SpecialAuraInfo = QString("(%0").arg(CompareAttributes(TYPE_CR, index));
            break;
        case 107:
        case 108:
            _SpecialAuraInfo = QString("(%0").arg(SpellModOp[misc]);
            break;
        // todo: more case
        default:
            _SpecialAuraInfo = QString("(%0").arg(misc);
            break;
    }

    QString _Periodic = QString(", periodic = %0)").arg(m_spellInfo->EffectAmplitude[index]);
    QString _Result = _BaseAuraInfo + _SpecialAuraInfo + _Periodic;
    SpellInfoBrowser->append(_Result);
}

QString SpellWork::PowerString()
{
    if (!m_spellInfo)
        return QString();

    switch (m_spellInfo->PowerType)
    {
        case POWER_MANA:
            return QString("POWER_MANA");
        case POWER_RAGE:
            return QString("POWER_RAGE");
        case POWER_FOCUS:
            return QString("POWER_FOCUS");
        case POWER_ENERGY:
            return QString("POWER_ENERGY");
        case POWER_HAPPINESS:
            return QString("POWER_HAPPINESS");
        case POWER_RUNES:
            return QString("POWER_RUNES");
        case POWER_HEALTH:
            return QString("POWER_HEALTH");
        default:
            return QString("POWER_UNKNOWN");
    }
    return QString();
}

QString SpellWork::CompareAttributes(AttrType attr, int index)
{
    if (!m_spellInfo)
        return QString();

    QString str("");
    switch (attr)
    {
        case TYPE_ATTR:
        {
            uint8 Max = sizeof(AttributesVal) / sizeof(AttributesVal[0]);
            for (uint8 i = 0; i < Max; i++)
            {
                if (m_spellInfo->Attributes & AttributesVal[i])
                {   
                    QString tstr(QString("%0, ").arg(AttributesString[i]));
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
            uint8 Max = sizeof(AttributesVal) / sizeof(AttributesVal[0]);
            for (uint8 i = 0; i < Max; i++)
            {
                if (m_spellInfo->AttributesEx & AttributesVal[i])
                {   
                    QString tstr(QString("%0, ").arg(AttributesExString[i]));
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
            uint8 Max = sizeof(AttributesVal) / sizeof(AttributesVal[0]);
            for (uint8 i = 0; i < Max; i++)
            {
                if (m_spellInfo->AttributesEx2 & AttributesVal[i])
                {   
                    QString tstr(QString("%0, ").arg(AttributesEx2String[i]));
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
            uint8 Max = sizeof(AttributesVal) / sizeof(AttributesVal[0]);
            for (uint8 i = 0; i < Max; i++)
            {
                if (m_spellInfo->AttributesEx3 & AttributesVal[i])
                {   
                    QString tstr(QString("%0, ").arg(AttributesEx3String[i]));
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
            uint8 Max = sizeof(AttributesVal) / sizeof(AttributesVal[0]);
            for (uint8 i = 0; i < Max; i++)
            {
                if (m_spellInfo->AttributesEx4 & AttributesVal[i])
                {   
                    QString tstr(QString("%0, ").arg(AttributesEx4String[i]));
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
            uint8 Max = sizeof(TargetFlags) / sizeof(TargetFlags[0]);
            for (uint8 i = 0; i < Max; i++)
            {
                if (m_spellInfo->Targets & TargetFlags[i])
                {   
                    QString tstr(QString("%0, ").arg(TargetFlagsString[i]));
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
            uint8 Max = sizeof(CreatureTypeFlags) / sizeof(CreatureTypeFlags[0]);
            for (uint8 i = 0; i < Max; i++)
            {
                if (m_spellInfo->TargetCreatureType & CreatureTypeFlags[i])
                {   
                    QString tstr(QString("%0, ").arg(CreatureTypeString[i]));
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
            uint8 Max = sizeof(FormMask) / sizeof(FormMask[0]);
            for (uint8 i = 0; i < Max; i++)
            {
                if (m_spellInfo->Stances & FormMask[i])
                {   
                    QString tstr(QString("%0, ").arg(FormString[i]));
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
            uint8 Max = sizeof(FormMask) / sizeof(FormMask[0]);
            for (uint8 i = 0; i < Max; i++)
            {
                if (m_spellInfo->StancesNot & FormMask[i])
                {   
                    QString tstr(QString("%0, ").arg(FormString[i]));
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
            uint8 Max = sizeof(ItemSubWeaponMask) / sizeof(ItemSubWeaponMask[0]);
            for (uint8 i = 0; i < Max; i++)
            {
                if (m_spellInfo->EquippedItemSubClassMask & ItemSubWeaponMask[i])
                {   
                    QString tstr(QString("%0, ").arg(ItemSubWeaponString[i]));
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
            uint8 Max = sizeof(ItemSubArmorMask) / sizeof(ItemSubArmorMask[0]);
            for (uint8 i = 0; i < Max; i++)
            {
                if (m_spellInfo->EquippedItemSubClassMask & ItemSubArmorMask[i])
                {   
                    QString tstr(QString("%0, ").arg(ItemSubArmorString[i]));
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
            uint8 Max = sizeof(ItemSubMiscMask) / sizeof(ItemSubMiscMask[0]);
            for (uint8 i = 0; i < Max; i++)
            {
                if (m_spellInfo->EquippedItemSubClassMask & ItemSubMiscMask[i])
                {   
                    QString tstr(QString("%0, ").arg(ItemSubMiscString[i]));
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
            uint8 Max = sizeof(InventoryTypeMask) / sizeof(InventoryTypeMask[0]);
            for (uint8 i = 0; i < Max; i++)
            {
                if (m_spellInfo->EquippedItemInventoryTypeMask & InventoryTypeMask[i])
                {   
                    QString tstr(QString("%0, ").arg(InventoryTypeString[i]));
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
            uint8 Max = sizeof(CombatRating) / sizeof(CombatRating[0]);
            for (uint8 i = 0; i < Max; i++)
            {
                if (m_spellInfo->EffectMiscValue[index] & CombatRating[i])
                {   
                    QString tstr(QString("%0, ").arg(CombatRatingString[i]));
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

void SpellWork::AppendSkillLine()
{
    if (!m_spellInfo)
        return;

    for (int i = 0; i < sSkillLineAbilityStore.GetNumRows(); i++)
    {
        SkillLineAbilityEntry const *skillInfo = sSkillLineAbilityStore.LookupEntry(i);
        if (skillInfo && skillInfo->SpellId == m_spellInfo->Id)
        {
            SkillLineEntry const *skill = sSkillLineStore.LookupEntry(skillInfo->SkillId);
            SpellInfoBrowser->append(QString("Skill (Id %0) \"%1\", ReqSkillValue = %2, Forward Spell = %3, MinMaxValue (%4, %5), CharacterPoints (%6, %7)")
                .arg(skill->Id)
                .arg((char*)skill->Name[0])
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

void SpellWork::AppendCastTimeLine()
{
    if (!m_spellInfo)
        return;

    SpellCastTimesEntry const *castInfo = sSpellCastTimesStore.LookupEntry(m_spellInfo->CastingTimeIndex);
    if (castInfo)
    {
        SpellInfoBrowser->append(QString("CastingTime (Id %0) = %1")
            .arg(castInfo->Id)
            .arg(float(castInfo->CastTime) / 1000, 0, 'f', 2));
    }
}

int SpellWork::GetDuration(SpellEntry const *spellInfo)
{
    if (!spellInfo)
        return 1;

    SpellDurationEntry const *durationInfo = sSpellDurationStore.LookupEntry(spellInfo->DurationIndex);
    if (durationInfo)
        return int(durationInfo->Duration[0] / 1000);

    return 1;
}
void SpellWork::AppendDurationLine()
{
    if (!m_spellInfo)
        return;

    SpellDurationEntry const *durationInfo = sSpellDurationStore.LookupEntry(m_spellInfo->DurationIndex);
    if (durationInfo)
    {
        SpellInfoBrowser->append(QString("Duration: ID (%0)  %1, %2, %3")
            .arg(durationInfo->Id)
            .arg(durationInfo->Duration[0])
            .arg(durationInfo->Duration[1])
            .arg(durationInfo->Duration[2]));
    }
}
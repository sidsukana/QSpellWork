#include "SWForm.h"
#include "AboutForm.h"

SWForm::SWForm(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);

    sw = new SWObject(this);
    layoutWidget1->hide();
    slabel1->hide();
    compareSpell_1->hide();

    LoadComboBoxes();
    LoadToolButtons();
    DetectLocale();

    // List search connection
    connect(SpellList, SIGNAL(clicked(QModelIndex)), this, SLOT(SlotSearchFromList(QModelIndex)));

    // Main search connections
    connect(findLine_e1, SIGNAL(returnPressed()), this, SLOT(SlotButtonSearch()));
    connect(findLine_e2, SIGNAL(returnPressed()), this, SLOT(SlotButtonSearch()));
    connect(findLine_e3, SIGNAL(returnPressed()), this, SLOT(SlotButtonSearch()));

    // Menu connections
    connect(actionAbout, SIGNAL(triggered()), this, SLOT(SlotAbout()));
    connect(actionExit, SIGNAL(triggered()), this, SLOT(close()));

    // RegExp connection
    connect(actionRegExp, SIGNAL(triggered()), this, SLOT(SlotRegExp()));

    // Filter search connections
    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(SlotFilterSearch()));
    connect(comboBox_2, SIGNAL(currentIndexChanged(int)), this, SLOT(SlotFilterSearch()));
    connect(comboBox_3, SIGNAL(currentIndexChanged(int)), this, SLOT(SlotFilterSearch()));
    connect(comboBox_4, SIGNAL(currentIndexChanged(int)), this, SLOT(SlotFilterSearch()));
    connect(comboBox_5, SIGNAL(currentIndexChanged(int)), this, SLOT(SlotFilterSearch()));
    connect(adLine1, SIGNAL(returnPressed()), this, SLOT(SlotFilterSearch()));
    connect(adLine2, SIGNAL(returnPressed()), this, SLOT(SlotFilterSearch()));

    // Search connection
    connect(this, SIGNAL(SignalSearch(quint8)), this, SLOT(SlotSearch(quint8)));

    connect(menuMode, SIGNAL(triggered(QAction*)), this, SLOT(SlotSetMode(QAction*)));
    connect(compareSpell_1, SIGNAL(returnPressed()), this, SLOT(SlotCompareSearch()));
    connect(compareSpell_2, SIGNAL(returnPressed()), this, SLOT(SlotCompareSearch()));
}

SWForm::~SWForm()
{
}

void SWForm::DetectLocale()
{
    SpellEntry const *spellInfo = sSpellStore.LookupEntry(1);

    if (!spellInfo)
        return;

    sw->SetMetaEnum("LocalesDBC");
    for (quint8 i = 0; i < sw->me.keyCount(); i++)
    {
        if (!QString::fromUtf8(spellInfo->SpellName[i]).isEmpty())
        {
            sw->SetLocale(i);
            QLabel *label = new QLabel;
            label->setText(QString("%0<b>DBC Locale: <font color=green>%1</font><b>")
                .arg(QChar(QChar::Nbsp), 2, QChar(QChar::Nbsp))
                .arg(sw->me.valueToKey(sw->me.value(i))));
            mainToolBar->addWidget(label);
            break;
        }
    }
}

void SWForm::SlotSetMode(QAction *ac)
{
    modeStandart->setChecked(false);
    modeCompare->setChecked(false);

    ac->setChecked(true);

    if (modeCompare->isChecked())
    {
        groupBox->hide();
        groupBox_2->hide();
        groupBox_3->hide();
        SpellList->hide();
        SpellInfoBrowser->clear();
        SpellInfoBrowser2->clear();
        layoutWidget1->show();
        slabel1->show();
        compareSpell_1->show();
    }
    else
    {
        groupBox->show();
        groupBox_2->show();
        groupBox_3->show();
        SpellList->show();
        SpellInfoBrowser->clear();
        SpellInfoBrowser2->clear();
        layoutWidget1->hide();
        slabel1->hide();
        compareSpell_1->hide();
    }
}

void SWForm::LoadToolButtons()
{
    for (quint8 i = 0; i < 3; i++)
    {
        actionA[i] = new QAction(this);
        actionB[i] = new QAction(this);
    }

    actionA[0]->setText(QString("None"));
    actionA[1]->setText(QString("Contain"));
    actionA[2]->setText(QString("Not Contain"));

    actionB[0]->setText(QString("None"));
    actionB[1]->setText(QString("Contain"));
    actionB[2]->setText(QString("Not Contain"));

    for (quint8 i = 0; i < 3; i++)
    {
        actionA[i]->setCheckable(true);
        actionB[i]->setCheckable(true);
        toolButton->addAction(actionA[i]);
        toolButton_2->addAction(actionB[i]);
    }

    actionA[0]->setChecked(true);
    actionB[0]->setChecked(true);

    connect(toolButton, SIGNAL(triggered(QAction*)), this, SLOT(SlotSetCheckedA(QAction*)));
    connect(toolButton_2, SIGNAL(triggered(QAction*)), this, SLOT(SlotSetCheckedB(QAction*)));
}

void SWForm::SlotSetCheckedA(QAction *ac)
{
    for (quint8 i = 0; i < 3; i++)
        actionA[i]->setChecked(false);

    ac->setChecked(true);
}

void SWForm::SlotSetCheckedB(QAction *ac)
{
    for (quint8 i = 0; i < 3; i++)
        actionB[i]->setChecked(false);

    ac->setChecked(true);
}

void SWForm::LoadComboBoxes()
{
    comboBox->clear();
    comboBox->insertItem(-1, "SpellFamilyName");
    sw->SetMetaEnum("SpellFamilyNames");
    for (quint16 i = 0; i < sw->me.keyCount(); i++)
        comboBox->insertItem(i, QString("(%0) %1").arg(i, 3, 10, QChar('0')).arg(sw->me.valueToKey(sw->me.value(i))));

    comboBox_2->clear();
    comboBox_2->insertItem(-1, "Aura");
    sw->SetMetaEnum("AuraType");
    for (quint16 i = 0; i < sw->me.keyCount(); i++)
        comboBox_2->insertItem(i, QString("(%0) %1").arg(i, 3, 10, QChar('0')).arg(sw->me.valueToKey(sw->me.value(i))));

    comboBox_3->clear();
    comboBox_3->insertItem(-1, "Effect");
    sw->SetMetaEnum("Effects");
    for (quint16 i = 0; i < sw->me.keyCount(); i++)
        comboBox_3->insertItem(i, QString("(%0) %1").arg(i, 3, 10, QChar('0')).arg(sw->me.valueToKey(sw->me.value(i))));

    comboBox_4->clear();
    sw->SetMetaEnum("Targets");
    comboBox_4->insertItem(-1, "Target A");
    for (quint16 i = 0; i < sw->me.keyCount(); i++)
        comboBox_4->insertItem(i, QString("(%0) %1").arg(i, 3, 10, QChar('0')).arg(sw->me.key(i)));

    comboBox_5->clear();
    comboBox_5->insertItem(-1, "Target B");
    for (quint16 i = 0; i < sw->me.keyCount(); i++)
        comboBox_5->insertItem(i, QString("(%0) %1").arg(i, 3, 10, QChar('0')).arg(sw->me.key(i)));

    adBox1->clear();
    adBox2->clear();
    for (quint16 i = 0; i < MAX_STRUCT; i++)
    {
        adBox1->insertItem(i, QString("%0").arg(SpellStruct[i]));
        adBox2->insertItem(i, QString("%0").arg(SpellStruct[i]));
    }
}

void SWForm::SlotRegExp()
{
    if (!sw->IsRegExp())
        sw->SetRegExp(true);
    else
        sw->SetRegExp(false);

    if (!SpellList->model())
        return;

    if (SpellEntry const *spellInfo = sSpellStore.LookupEntry(SpellList->model()->data(SpellList->model()->index(SpellList->currentIndex().row(), 0)).toInt()))
        sw->ShowInfo(spellInfo);
}

void SWForm::SlotAbout()
{
    new AboutForm;
}

void SWForm::SlotButtonSearch()
{
    emit SignalSearch(0);
}

void SWForm::SlotFilterSearch()
{
    emit SignalSearch(1);
}

void SWForm::SlotCompareSearch()
{
    emit SignalSearch(2);
}

void SWForm::SlotSearch(quint8 type)
{
    if (type != 2)
        delete SpellList->model();

    sw->SetType(type);
    sw->ThreadBegin(THREAD_SEARCH);
}

void SWForm::SlotSearchFromList(const QModelIndex &index)
{
    QVariant var = SpellList->model()->data(SpellList->model()->index(index.row(), 0));

    if (SpellEntry const *spellInfo = sSpellStore.LookupEntry(var.toInt()))
        sw->ShowInfo(spellInfo);
}

bool SWForm::event(QEvent *ev)
{
    switch (ev->type())
    {
        case SendModel::TypeId:
        {
            SendModel* m_ev = (SendModel*)ev;
            SpellList->setModel(m_ev->GetObject());
            return true;
        }
        break;
        case SendSpell::TypeId:
        {
            SendSpell* m_ev = (SendSpell*)ev;
            sw->ShowInfo(m_ev->GetObject());
            return true;
        }
        break;
        case SendCompareSpell::TypeId:
        {
            SendCompareSpell* m_ev = (SendCompareSpell*)ev;
            sw->ShowInfo(m_ev->GetObject(), m_ev->GetNum());
            return true;
        }
        break;
        default:
            break;
    }
    

    return QWidget::event(ev);
}

quint8 SWForm::GetToolState(quint8 Tool)
{
    if (Tool == TOOL_ONE)
    {
        if (actionA[STATE_NONE]->isChecked())
            return STATE_NONE;
        else if (actionA[STATE_CONTAIN]->isChecked())
            return STATE_CONTAIN;
        else if (actionA[STATE_NOT_CONTAIN]->isChecked())
            return STATE_NOT_CONTAIN;
    }
    else if (Tool == TOOL_TWO)
    {
        if (actionB[STATE_NONE]->isChecked())
            return STATE_NONE;
        else if (actionB[STATE_CONTAIN]->isChecked())
            return STATE_CONTAIN;
        else if (actionB[STATE_NOT_CONTAIN]->isChecked())
            return STATE_NOT_CONTAIN;
    }

    return STATE_NONE;
}

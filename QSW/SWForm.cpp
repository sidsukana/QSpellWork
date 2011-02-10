#include "SWForm.h"
#include "AboutForm.h"

SWForm::SWForm(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);

    sw = new SWObject(this);

    LoadComboBoxes();

    // List search connection
    connect(SpellList, SIGNAL(clicked(QModelIndex)), this, SLOT(SlotSearchFromList(QModelIndex)));

    // Main search connections
    connect(findLine_e1, SIGNAL(returnPressed()), this, SLOT(SlotButtonSearch()));
    connect(findLine_e2, SIGNAL(returnPressed()), this, SLOT(SlotButtonSearch()));
    connect(findLine_e3, SIGNAL(returnPressed()), this, SLOT(SlotButtonSearch()));
    connect(findButton, SIGNAL(clicked()), this, SLOT(SlotButtonSearch()));

    // Menu connections
    connect(actionAbout, SIGNAL(triggered()), this, SLOT(SlotAbout()));
    connect(actionExit, SIGNAL(triggered()), this, SLOT(close()));

    // RegExp connection
    connect(regexpButton, SIGNAL(clicked()), this, SLOT(SlotRegExp()));

    // Filter search connections
    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(SlotFilterSearch()));
    connect(comboBox_2, SIGNAL(currentIndexChanged(int)), this, SLOT(SlotFilterSearch()));
    connect(comboBox_3, SIGNAL(currentIndexChanged(int)), this, SLOT(SlotFilterSearch()));
    connect(comboBox_4, SIGNAL(currentIndexChanged(int)), this, SLOT(SlotFilterSearch()));
    connect(comboBox_5, SIGNAL(currentIndexChanged(int)), this, SLOT(SlotFilterSearch()));
    connect(adLine1, SIGNAL(returnPressed()), this, SLOT(SlotFilterSearch()));
    connect(adLine2, SIGNAL(returnPressed()), this, SLOT(SlotFilterSearch()));

    // Search connection
    connect(this, SIGNAL(SignalSearch(bool)), this, SLOT(SlotSearch(bool)));
}

SWForm::~SWForm()
{
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
    {
        sw->SetRegExp(true);
        regexpButton->setStyleSheet("background-color: qlineargradient(spread:pad, x1:1, y1:0.00568182, x2:0, y2:0, stop:0 rgba(0, 255, 28, 255), stop:1 rgba(255, 255, 255, 255));");
    }
    else
    {
        sw->SetRegExp(false);
        regexpButton->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(255, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));");
    }
}

void SWForm::SlotAbout()
{
    AboutForm *aform = new AboutForm;
}

void SWForm::SlotButtonSearch()
{
    emit SignalSearch(false);
}

void SWForm::SlotFilterSearch()
{
    emit SignalSearch(true);
}

void SWForm::SlotSearch(bool filter)
{
    sw->SetFilter(filter);
    delete SpellList->model();
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
    }

    return QWidget::event(ev);
}

#include "SpellWork.h"

SpellWork::SpellWork(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);

    model = NULL;
    m_spellInfo = NULL;

    LoadDBCStores();

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

void SpellWork::SlotAbout()
{
    About *about = new About;
    about->show();
}

void SpellWork::SlotSearch()
{
    bool isString = false;

    SpellInfoBrowser->clear();

    if (model)
        model->clear();

    if (!findLine_e1->text().isEmpty())
    {
        for (int i = 0; i < findLine_e1->text().size(); ++i)
        {
            if (findLine_e1->text().at(i) > QChar('9'))
            {
                isString = true;
                break;
            }
        }

        if (isString)
        {
            model = new QStandardItemModel(1, 2);
            int count = -1;
            for (int i = 0; i < sSpellStore.GetNumRows(); i++)
            {
                m_spellInfo = sSpellStore.LookupEntry(i);
				if (m_spellInfo && QString(m_spellInfo->SpellName[0]).contains(findLine_e1->text(), Qt::CaseInsensitive))
                {
                    count++;
                    QString sRank((char*)m_spellInfo->Rank[0]);

                    QStandardItem *item_id = new QStandardItem(QString("%0").arg(m_spellInfo->Id));
                    QStandardItem *item_name;
                    if (sRank.isEmpty())
                        item_name = new QStandardItem(QString("%0").arg((char*)m_spellInfo->SpellName[0]));
                    else
                        item_name = new QStandardItem(QString("%0 (%1)").arg((char*)m_spellInfo->SpellName[0]).arg((char*)m_spellInfo->Rank[0]));

                    model->setItem(count, 0, item_id);
                    model->setItem(count, 1, item_name);
                }
            }
            model->setHorizontalHeaderItem(0, new QStandardItem("ID"));
            model->setHorizontalHeaderItem(1, new QStandardItem("Name"));
            SpellList->setModel(model);
        }
        else
        {
            model = new QStandardItemModel(1, 2);

            m_spellInfo = sSpellStore.LookupEntry(findLine_e1->text().toInt());

            if (m_spellInfo)
            {
                QString sRank((char*)m_spellInfo->Rank[0]);

                QStandardItem *item_id = new QStandardItem(QString("%0").arg(m_spellInfo->Id));
                QStandardItem *item_name;
                if (sRank.isEmpty())
                    item_name = new QStandardItem(QString("%0").arg((char*)m_spellInfo->SpellName[0]));
                else
                    item_name = new QStandardItem(QString("%0 (%1)").arg((char*)m_spellInfo->SpellName[0]).arg((char*)m_spellInfo->Rank[0]));

                model->setItem(0, 0, item_id);
                model->setItem(0, 1, item_name);
                model->setHorizontalHeaderItem(0, new QStandardItem("ID"));
                model->setHorizontalHeaderItem(1, new QStandardItem("Name"));
                SpellList->setModel(model);
                ShowInfo(m_spellInfo);
            }
        }
    }
    else if (!findLine_e2->text().isEmpty())
    {
        model = new QStandardItemModel(1, 2);
        int count = -1;
        for (int i = 0; i < sSpellStore.GetNumRows(); i++)
        {
            m_spellInfo = sSpellStore.LookupEntry(i);
            if (m_spellInfo && m_spellInfo->SpellIconID == findLine_e2->text().toInt())
            {
                count++;
                QString sRank((char*)m_spellInfo->Rank[0]);

                QStandardItem *item_id = new QStandardItem(QString("%0").arg(m_spellInfo->Id));
                QStandardItem *item_name;
                if (sRank.isEmpty())
                    item_name = new QStandardItem(QString("%0").arg((char*)m_spellInfo->SpellName[0]));
                else
                    item_name = new QStandardItem(QString("%0 (%1)").arg((char*)m_spellInfo->SpellName[0]).arg((char*)m_spellInfo->Rank[0]));

                model->setItem(count, 0, item_id);
                model->setItem(count, 1, item_name);
            }
        }
        model->setHorizontalHeaderItem(0, new QStandardItem("ID"));
        model->setHorizontalHeaderItem(1, new QStandardItem("Name"));
        SpellList->setModel(model);
    }
}

void SpellWork::SlotSearchFromList(const QModelIndex &index)
{
    QStandardItem *spellItem = model->item(index.row());
    
    QString value(spellItem->text());

    uint32 id = value.toInt();

    SpellInfoBrowser->clear();

    m_spellInfo = sSpellStore.LookupEntry(id);
    if (m_spellInfo)
        ShowInfo(m_spellInfo);
        
}

void SpellWork::ShowInfo(SpellEntry const* spellInfo)
{
    if (!spellInfo)
        return;

    QString sRank((char*)spellInfo->Rank[0]);

    SpellInfoBrowser->append(QString("ID: %0").arg(spellInfo->Id));

    if (sRank.isEmpty())
        SpellInfoBrowser->append(QString("Name: %0").arg((char*)spellInfo->SpellName[0]));
    else
        SpellInfoBrowser->append(QString("Name: %0 (%1)").arg((char*)spellInfo->SpellName[0]).arg((char*)m_spellInfo->Rank[0]));

    SpellInfoBrowser->append(QString("Description: %0").arg((char*)spellInfo->Description[0]));
    SpellInfoBrowser->append(QString("=================================================="));
    SpellInfoBrowser->append(QString("Category = %0, SpellIconID = %1, activeIconID = %2, SpellVisual = %3")
        .arg(spellInfo->Category)
        .arg(spellInfo->SpellIconID)
        .arg(spellInfo->activeIconID)
        .arg(spellInfo->SpellVisual));
}

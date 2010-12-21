#include "SpellWork.h"
#include "DBC/DBCStores.h"

SpellWork::SpellWork(QWidget *parent)
	: QMainWindow(parent)
{
	setupUi(this);

    LoadDBCStores();

	connect(findButton, SIGNAL(clicked()), this, SLOT(SlotFind()));
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

void SpellWork::SlotFind()
{
    bool isString = false;

    SpellEntry const* spellInfo = NULL;

    SpellInfoBrowser->clear();

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
        for (int i = 0; i < sSpellStore.GetNumRows(); i++)
        {
            spellInfo = sSpellStore.LookupEntry(i);
            if (spellInfo && spellInfo->SpellName[0] == findLine_e1->text())
            {
                SpellInfoBrowser->append(QString("Spell ID: %1").arg(spellInfo->Id));
                SpellInfoBrowser->append(QString("Spell name: %1").arg((char*)spellInfo->SpellName[0]));
                SpellInfoBrowser->append(QString("Spell description: %1").arg((char*)spellInfo->Description[0]));
            }
        }
    }
    else
    {
        spellInfo = sSpellStore.LookupEntry(findLine_e1->text().toInt());
        if (spellInfo)
        {
            SpellInfoBrowser->append(QString("Spell ID: %1").arg(spellInfo->Id));
            SpellInfoBrowser->append(QString("Spell name: %1").arg((char*)spellInfo->SpellName[0]));
            SpellInfoBrowser->append(QString("Spell description: %1").arg((char*)spellInfo->Description[0]));
        }
    }
}

#include "SpellWork.h"
#include "DBC/DBCStores.h"

SpellWork::SpellWork(QWidget *parent)
	: QMainWindow(parent)
{
	setupUi(this);

    LoadDBCStores();

	connect(findButton, SIGNAL(clicked()), this, SLOT(SlotFind()));
    connect(actionAbout, SIGNAL(triggered()), this, SLOT(SlotAbout()));
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
    SpellEntry const* spellInfo = sSpellStore.LookupEntry(findLine_e1->text().toInt());

    if (spellInfo)
    {
        SpellInfoBrowser->clear();
        SpellInfoBrowser->append(QString("Spell ID: %1").arg(spellInfo->Id));
        SpellInfoBrowser->append(QString("Spell name: %1").arg((char*)spellInfo->SpellName[0]));
        SpellInfoBrowser->append(QString("Spell description: %1").arg((char*)spellInfo->Description[0]));
    }
}

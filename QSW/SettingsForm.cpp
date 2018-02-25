#include <QFileDialog>
#include <QDir>

#include "SettingsForm.h"
#include "mpq/MPQ.h"
#include "dbc/DBC.h"

SettingsForm::SettingsForm(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    connect(mpqDir, SIGNAL(editingFinished()), this, SLOT(slotEditMPQ()));
    connect(mpqButton, SIGNAL(clicked()), this, SLOT(slotMPQ()));
    connect(dbcButton, SIGNAL(clicked()), this, SLOT(slotDBC()));

    mpqDir->setText(MPQ::mpqDir());
    dbcDir->setText(DBC::dbcDir());

    slotEditMPQ();

    mpqLocale->setCurrentIndex(mpqLocale->findText(MPQ::localeDir()));

    show();
}

void SettingsForm::slotEditMPQ()
{
    if (!mpqDir->text().isEmpty())
    {
        QDir dir(mpqDir->text());
        if (dir.exists())
        {
            mpqDir->setText(dir.absolutePath());
            dbcDir->setText("DBFilesClient");
            mpqLocale->clear();
            QStringList localeDirs = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
            for (QString& str : localeDirs)
            {
                QString localeDir = str.section("\\", -1);
                if (localeDir.size() == 4)
                {
                    mpqLocale->addItem(localeDir);
                }
            }
            mpqLocale->addItem("");
        }
    }
    else
    {
        mpqLocale->clear();
    }
}

void SettingsForm::slotMPQ()
{
    QDir dir(QFileDialog::getExistingDirectory(this, "Set MPQ directory", mpqDir->text()));
    if (dir.exists())
    {
        mpqDir->setText(dir.absolutePath());
        dbcDir->setText("DBFilesClient");
        mpqLocale->clear();
        QStringList localeDirs = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
        for (QString& str : localeDirs)
        {
            QString localeDir = str.section("\\", -1);
            if (localeDir.size() == 4)
            {
                mpqLocale->addItem(localeDir);
            }
        }
        mpqLocale->addItem("");
    }
}

void SettingsForm::slotDBC()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Set DBC directory", dbcDir->text());
    if (!dir.isEmpty())
        dbcDir->setText(dir);
}


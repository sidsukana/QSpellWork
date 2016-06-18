#include <QFileDialog>
#include <QDir>

#include "SettingsForm.h"
#include "Defines.h"
#include "mpq/MPQ.h"

SettingsForm::SettingsForm(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    connect(mpqDir, SIGNAL(editingFinished()), this, SLOT(slotEditMPQ()));
    connect(mpqButton, SIGNAL(clicked()), this, SLOT(slotMPQ()));
    connect(dbcButton, SIGNAL(clicked()), this, SLOT(slotDBC()));

    show();
}

void SettingsForm::slotEditMPQ()
{
    if (!mpqDir->text().isEmpty()) {
        QDir dir(mpqDir->text());
        if (dir.exists()) {
            mpqDir->setText(dir.absolutePath());
            dbcDir->setText("DBFilesClient");
            mpqLocale->clear();
            QStringList localeDirs = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
            foreach (QString str, localeDirs) {
                mpqLocale->addItem(str.section("\\", -1));
            }
            mpqLocale->addItem("");
        }
    } else {
        mpqLocale->clear();
        dbcDir->setText("");
    }
}

void SettingsForm::slotMPQ()
{
    QDir dir(QFileDialog::getExistingDirectory(this, "Set MPQ directory", mpqDir->text()));
    if (dir.exists()) {
        mpqDir->setText(dir.absolutePath());
        dbcDir->setText("DBFilesClient");
        mpqLocale->clear();
        QStringList localeDirs = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
        foreach (QString str, localeDirs) {
            mpqLocale->addItem(str.section("\\", -1));
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

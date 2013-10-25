#include <QFileDialog>
#include <QDir>

#include "SWSettingsForm.h"
#include "SWDefines.h"
#include "mpq/MPQ.h"

SWSettingsForm::SWSettingsForm(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    connect(buttonDir, SIGNAL(clicked()), this, SLOT(slotDir()));
    connect(this, SIGNAL(accepted()), this, SLOT(slotAccept()));

    editDir->setText(QSW::settings().value("Directories/WoW1", "").toString());

    show();
}

void SWSettingsForm::slotDir()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Set WoW 1.12.x directory", editDir->text());
    if (!dir.isEmpty())
    {
        dir.append(QDir::separator());
        editDir->setText(dir);
    }
}

void SWSettingsForm::slotAccept()
{
    if (!editDir->text().isEmpty())
    {
        QSW::settings().setValue("Directories/WoW1", editDir->text());
        MPQ::gameDir() = QDir::fromNativeSeparators(editDir->text());
    }
}

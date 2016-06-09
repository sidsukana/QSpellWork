#include <QFileDialog>
#include <QDir>

#include "SettingsForm.h"
#include "Defines.h"
#include "mpq/MPQ.h"

SettingsForm::SettingsForm(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    connect(buttonDir, SIGNAL(clicked()), this, SLOT(slotDir()));

    show();
}

void SettingsForm::slotDir()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Set MPQ directory", editDir->text());
    if (!dir.isEmpty())
    {
        dir.append("/");
        editDir->setText(dir);
    }
}

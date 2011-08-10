#include "AboutForm.h"

AboutForm::AboutForm(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    versionLabel->setText(QString("<b>Qt SpellWork %0 (%1) for WoW %2 (%3)</b>")
        .arg(QSW_VERSION)
        .arg(QSW_BUILD)
        .arg(CLIENT_VERSION)
        .arg(CLIENT_BUILD));

    show();
}

AboutForm::~AboutForm()
{
}

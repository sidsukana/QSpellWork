#include "AboutForm.h"

AboutForm::AboutForm(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);
    show();
}

AboutForm::~AboutForm()
{
}

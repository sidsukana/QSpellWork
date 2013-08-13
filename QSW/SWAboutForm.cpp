#include "SWAboutForm.h"

SWAboutForm::SWAboutForm(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    QString versionString = label->text();

    label->setText(versionString.arg(CLIENT_VERSION).arg(CLIENT_BUILD).arg(QSW_BUILD));

    connect(pushButton_2, SIGNAL(clicked()), qApp, SLOT(aboutQt()));

    show();
}

SWAboutForm::~SWAboutForm()
{
}

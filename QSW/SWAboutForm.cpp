#include "SWAboutForm.h"

SWAboutForm::SWAboutForm(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    QString versionString = label->text();

    label->setText(versionString.arg(QSW_VERSION).arg(QSW_BUILD).arg(CLIENT_VERSION).arg(CLIENT_BUILD));

    connect(pushButton_2, SIGNAL(clicked()), qApp, SLOT(aboutQt()));

    show();
}

SWAboutForm::~SWAboutForm()
{
}

#include "AboutForm.h"
#include "version.h"

AboutForm::AboutForm(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    QString versionString = label->text();

    label->setText(versionString.arg(APP_VERSION.toString()));

    connect(pushButton_2, SIGNAL(clicked()), qApp, SLOT(aboutQt()));

    show();
}

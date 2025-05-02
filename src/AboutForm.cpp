#include "AboutForm.h"
#include "qsw.h"

AboutForm::AboutForm(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    QString versionString = label->text();

    label->setText(versionString.arg(QSW::VERSION));

    connect(pushButton_2, SIGNAL(clicked()), qApp, SLOT(aboutQt()));

    show();
}

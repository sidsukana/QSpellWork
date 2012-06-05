#ifndef SW_ABOUT_FORM_H
#define SW_ABOUT_FORM_H

#include <QtGui/QDialog>
#include "SWDefines.h"
#include "ui_SWAboutUI.h"

class SWAboutForm : public QDialog, public Ui::SWAboutUI
{
    Q_OBJECT

public:
    SWAboutForm(QWidget *parent = 0);
    ~SWAboutForm();

private:
    Ui::SWAboutUI ui;
};

#endif // SW_ABOUT_FORM_H

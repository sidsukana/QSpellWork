#ifndef ABOUTFORM_H
#define ABOUTFORM_H

#include <QtGui/QDialog>
#include "SWDefines.h"
#include "ui_AboutFormUI.h"

class AboutForm : public QDialog, public Ui::AboutFormUI
{
    Q_OBJECT

public:
    AboutForm(QWidget *parent = 0);
    ~AboutForm();

private:
    Ui::AboutFormUI ui;
};

#endif // ABOUTFORM_H

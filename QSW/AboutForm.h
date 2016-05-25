#ifndef ABOUT_FORM_H
#define ABOUT_FORM_H

#include <QDialog>

#include "ui_about.h"

class AboutForm : public QDialog, public Ui::about
{
    Q_OBJECT

    public:
        AboutForm(QWidget *parent = nullptr);
        ~AboutForm() {}

    private:
        Ui::about ui;
};

#endif // ABOUT_FORM_H

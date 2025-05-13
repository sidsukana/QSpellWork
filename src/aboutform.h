#pragma once

#include <QtWidgets/QDialog>

#include "ui_aboutform.h"

class AboutForm : public QDialog, public Ui::AboutForm
{
    Q_OBJECT

    public:
        AboutForm(QWidget *parent = nullptr);
        ~AboutForm() {}

    private:
        Ui::AboutForm ui;
};

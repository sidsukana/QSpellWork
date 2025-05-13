#pragma once

#include <QtWidgets/QDialog>

#include "ui_settingsform.h"

class SettingsForm : public QDialog, public Ui::SettingsForm
{
    Q_OBJECT

    public:
        SettingsForm(QWidget *parent = nullptr);
        ~SettingsForm() {}

    public slots:
        void slotEditMPQ();
        void slotMPQ();
        void slotDBC();

    private:
        Ui::SettingsForm ui;
};

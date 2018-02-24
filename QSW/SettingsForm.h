#pragma once

#include <QDialog>

#include "ui_settings.h"

class SettingsForm : public QDialog, public Ui::settings
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
        Ui::settings ui;
};

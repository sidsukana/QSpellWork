#ifndef SETTINGS_FORM_H
#define SETTINGS_FORM_H

#include <QDialog>

#include "ui_settings.h"

class SettingsForm : public QDialog, public Ui::settings
{
    Q_OBJECT

    public:
        SettingsForm(QWidget *parent = 0);
        ~SettingsForm() {}

    public slots:
        void slotDir();
        void slotAccept();

    private:
        Ui::settings ui;
};

#endif // SETTINGS_FORM_H
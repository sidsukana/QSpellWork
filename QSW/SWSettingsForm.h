#ifndef SW_SETTINGS_FORM_H
#define SW_SETTINGS_FORM_H

#include <QDialog>

#include "ui_SWSettingsUI.h"

class SWSettingsForm : public QDialog, public Ui::SWSettingsUI
{
    Q_OBJECT

    public:
        SWSettingsForm(QWidget *parent = 0);
        ~SWSettingsForm() {}

    public slots:
        void slotDir();
        void slotAccept();

    private:
        Ui::SWSettingsUI ui;
};

#endif // SW_SETTINGS_FORM_H
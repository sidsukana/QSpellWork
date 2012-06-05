#ifndef SW_UPDATE_FORM_H
#define SW_UPDATE_FORM_H

#include <QtGui/QDialog>

#include <QtXml/QDomDocument>
#include "SWDefines.h"
#include "ui_SWUpdateUI.h"

class SWUpdateForm : public QDialog, public Ui::SWUpdateUI
{
    Q_OBJECT

    public:
        SWUpdateForm(QWidget *parent = 0);
        ~SWUpdateForm();

        void checkForUpdates();
        void updateSoftware();

        bool event(QEvent* ev);

    public slots:
        void slotUpdateProgress(qint64 bytes, qint64 total);
        void slotStartUpdate();

    private:
        Ui::SWUpdateUI ui;
        QDomDocument m_xmlData;
        QStringList m_updateFiles;
};

#endif // SW_UPDATE_FORM_H
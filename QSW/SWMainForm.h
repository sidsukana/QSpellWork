#ifndef SWFORM_H
#define SWFORM_H

#include <QtCore/QSettings>

#include <QtGui/QTextBrowser>
#include <QtGui/QMainWindow>
#include <QtGui/QToolButton>
#include <QtGui/QCompleter>
#include <QtGui/QIcon>

#include <QtWebKit/QWebView>
#include <QtWebKit/QWebFrame>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlTableModel>

#include "SWEnums.h"
#include "SWObject.h"
#include "ui_SWMainUI.h"

class SWObject;
class SpellListSortedModel;

class SWMainForm : public QMainWindow, public Ui::SWMainUI
{
    Q_OBJECT

    public:
        SWMainForm(QWidget* parent = 0);
        ~SWMainForm();

        void saveSettings();
        void loadSettings();

        bool isRegExp() const { return m_regExp->isChecked(); }
        void setRegExp(bool enable) { m_regExp->setChecked(enable); }
        SWEnums* getEnums() const { return m_enums; }

        QWebView* getBrowser(quint8 num) const
        {
            switch (num)
            {
                case 1: return webView1;
                case 2: return webView2;
                case 3: return webView3;
                default: return webView1;
            }
        }

    signals:
        void signalSearch(quint8 type);

    private slots:
        void slotAbout();
        void slotFilterSearch();
        void slotButtonSearch();
        void slotCompareSearch();
        void slotSearch(quint8 type);
        void slotSearchFromList(const QModelIndex &index);
        void slotLinkClicked(const QUrl &url);
        void slotRegExp();
        void slotModeDatabase();
        void slotModeShow();
        void slotModeCompare();
        void slotPrevRow();
        void slotNextRow();
        
        void slotConnectToDatabase();
        void slotSpellTable();
        void slotAutoRelate();
        void slotResetRelate();

        bool event(QEvent* ev);

    private:
        void loadComboBoxes();
        void detectLocale();
        void createModeButton();
        void initializeCompleter();

        SWEnums* m_enums;

        QSettings* m_settings;
        SpellListSortedModel* m_sortedModel;
        Ui::SWMainUI m_ui;
        SWObject* m_sw;
        QToolButton* m_modeButton;
        QAction* m_regExp;
        QAction* m_about;
        QAction* m_update;
};

class Enums : public QObject
{
    Q_OBJECT
    public:

        enum LocalesDBC
        {
            enUS,
            koKR,
            frFR,
            deDE,
            zhCN,
            zhTW,
            esES,
            esMX,
            ruRU
        };

        Q_ENUMS(LocalesDBC)
};


#endif

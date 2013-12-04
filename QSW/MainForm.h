#ifndef MAIN_FORM_H
#define MAIN_FORM_H

#include <QSettings>
#include <QFutureWatcher>
#include <QTextBrowser>
#include <QMainWindow>
#include <QToolButton>
#include <QIcon>
#include <QWebView>
#include <QWebFrame>

#include "SWEnums.h"
#include "SWObject.h"

#include "ui_main.h"
#include "ui_advancedFilter.h"

class SWObject;
class SpellListSortedModel;

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
        esMX
    };

    Q_ENUMS(LocalesDBC)
};

class AdvancedFilterWidget : public QWidget, public Ui::advancedFilter
{
    Q_OBJECT

public:
    AdvancedFilterWidget(QWidget* parent = NULL);
    ~AdvancedFilterWidget() {}
};

class MainForm : public QMainWindow, public Ui::main
{
    Q_OBJECT

    public:
        MainForm(QWidget* parent = NULL);
        ~MainForm();

        void saveSettings();
        void loadSettings();

        bool isRegExp() const { return m_actionRegExp->isChecked(); }
        void setRegExp(bool enable) { m_actionRegExp->setChecked(enable); }
        SWEnums* getEnums() const { return m_enums; }
        QString getFilterText() const { return m_advancedFilterWidget->textEdit->toPlainText(); }

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
        void slotAdvancedFilter();
        void slotAdvancedApply();
        void slotFilterSearch();
        void slotButtonSearch();
        void slotCompareSearch();
        void slotSearch(quint8 type);
        void slotSearchResult();
        void slotSearchFromList(const QModelIndex &index);
        void slotLinkClicked(const QUrl &url);
        void slotRegExp();
        void slotSettings();
        void slotModeShow();
        void slotModeCompare();
        void slotPrevRow();
        void slotNextRow();

        bool event(QEvent* ev);
        void resizeEvent (QResizeEvent* event);

    private:
        void loadComboBoxes();
        void detectLocale();
        void createModeButton();
        void initializeCompleter();

        SWEnums* m_enums;

        SpellListSortedModel* m_sortedModel;
        Ui::main m_ui;
        SWObject* m_sw;
        QToolButton* m_modeButton;
        QAction* m_actionRegExp;
        QAction* m_actionAbout;
        QAction* m_actionSettings;

        typedef QList<QEvent*> EventList;
        typedef QFutureWatcher<EventList> SearchResultWatcher;
        SearchResultWatcher* m_watcher;

        AdvancedFilterWidget* m_advancedFilterWidget;
};

#endif // MAIN_FORM_H
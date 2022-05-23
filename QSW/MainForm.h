#pragma once

#include <QSettings>
#include <QFutureWatcher>
#include <QMainWindow>
#include <QToolButton>
#include <QIcon>
#include <QStringListModel>

#include "events.h"
#include "models.h"
#include "qsw.h"
#include "spellwork.h"

#include "ui_main.h"
#include "ui_scriptFilter.h"

class SpellWork;
class SpellListSortedModel;

class ScriptFilter : public QWidget, public Ui::scriptFilter
{
    Q_OBJECT

    public:
        ScriptFilter(QWidget* parent = nullptr);
        ~ScriptFilter() {}

        void addBookmark(QString str) {
            str =  str.trimmed();
            if (!m_bookmarks.contains(str))
                m_bookmarks << str;
            m_model->setStringList(m_bookmarks);
        }
        void addBookmarks(QStringList bookmarks) {
            m_bookmarks = bookmarks;
            m_model->setStringList(m_bookmarks);
        }

        void removeBookmark(int index) {
            if (index < m_bookmarks.size())
                m_bookmarks.removeAt(index);
            m_model->setStringList(m_bookmarks);
        }

        void clearBookmarks() {
            m_bookmarks.clear();
            m_model->setStringList(m_bookmarks);
        }

        QStringList getBookmarks() const { return m_bookmarks; }

    public slots:
        void slotAdd();
        void slotRemove();
        void slotClear();

    private:
        QStringList m_bookmarks;
        QStringListModel* m_model;
};

class QSWPage : public QWebEnginePage
{
    Q_OBJECT
    public:
        QSWPage(QSW::Pages pageId, QObject* parent = nullptr)
            : QWebEnginePage(parent), m_pageId(pageId), m_spellId(0) {}

        QSW::Pages getPageId() const { return m_pageId; }
        quint32 getSpellId() const { return m_spellId; }
        QString getSourceHtml() const { return m_sourceHtml; }

        bool acceptNavigationRequest(const QUrl& url, QWebEnginePage::NavigationType type, bool)
        {
            if (type == QWebEnginePage::NavigationTypeLinkClicked)
            {
                emit linkClicked(url);
                return false;
            }
            return true;
        }

        void setCompareInfo(const QString &html)
        {
            setHtml(html, QUrl(QString("http://spellwork/%0").arg(m_spellId)));
        }

        void setInfo(const QString &html, quint32 spellId = 0)
        {
            if (spellId)
                m_spellId = spellId;

            m_sourceHtml = html;

            setHtml(html, QUrl(QString("http://spellwork/%0").arg(m_spellId)));
        }

    signals:
        void linkClicked(const QUrl&);

    private:
        quint32 m_spellId;
        QSW::Pages m_pageId;
        QString m_sourceHtml;

};

class MainForm : public QMainWindow, public Ui::main
{
    Q_OBJECT

    public:
        MainForm(QWidget* parent = nullptr);
        ~MainForm();

        QString getFilterText() const { return m_scriptFilter->scriptEdit->toPlainText(); }
        void setFilterText(QString str) { m_scriptFilter->scriptEdit->setText(str); }

        ScriptFilter* getScriptFilter() const { return m_scriptFilter; }

        QWebEngineView* getBrowser(quint8 num) const
        {
            switch (num)
            {
                case 1: return webView1;
                case 2: return webView2;
                case 3: return webView3;
                default: return webView1;
            }
        }

        QSWPage* getPage(QSW::Pages pageId) const
        {
            return m_pages[pageId];
        }

        void setLocale(QString locale);
        void loadComboBoxes(EnumHash enums);
        void loadCompleter(QStringList names);
        void createModeButton();
        void createPluginButton();
        void updatePlguinButton();

    public slots:
        void saveSettings();
        void loadSettings(bool overridenLastActivePlugin, QString activePlugin);

    signals:
        void signalSearch(quint8 type);

    private slots:
        void slotAbout();
        void slotScriptFilter();
        void slotScriptApply();
        void slotFilterSearch();
        void slotButtonSearch();
        void slotCompareSearch();
        void slotSearch(quint8 type);
        void slotSearchResult();
        void slotSearchFromList(const QModelIndex &index);
        void slotLinkClicked(const QUrl &url);
        void slotWov();
        void slotSettings();
        void slotModeShow();
        void slotModeCompare();
        void slotPrevRow();
        void slotNextRow();
        void slotCopyAll();
        void slotChangeActivePlugin();

        void onPluginLoaded();
        void onPluginLoadingFail();
        void onPluginLoadingInit();

        void showProgressBar(int maximum);
        void hideProgressBar();

        bool event(QEvent* ev);

    private:

        SpellListSortedModel* m_sortedModel;
        Ui::main m_ui;
        SpellWork* m_sw;
        QToolButton* m_modeButton;
        QToolButton* m_pluginButton;
        QAction* m_actionAbout;
        QAction* m_actionSettings;
        QAction* m_actionWov;

        QVector<QFontComboBox*> m_comboBoxes;
        QVector<ComboBoxModel*> m_comboBoxModels;

        typedef QFutureWatcher<EventList> SearchResultWatcher;
        SearchResultWatcher* m_watcher;

        QCompleter* m_completer;
        QStringListModel* m_completerModel;

        ScriptFilter* m_scriptFilter;

        QSWPage* m_pages[QSW::PAGE_MAX];

        bool m_pluginLoading;
};

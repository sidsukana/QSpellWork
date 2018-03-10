#pragma once

#include <QJSEngine>
#include <QJSValue>
#include <QJSValueList>
#include <QJsonObject>

#include "MainForm.h"
#include "qsw.h"
#include "events.h"
#include "blp/BLP.h"

#include "plugins/spellinfo/interface.h"

typedef QPair<QJsonObject, SpellInfoInterface*> SpellInfoPluginPair;
typedef QHash<QString, SpellInfoPluginPair> SpellInfoPlugins;

class MainForm;
class SpellWork : public QObject
{
    Q_OBJECT

    public:
        SpellWork(MainForm *form);
        ~SpellWork() {}

        void loadPlugins();
        void setActivePlugin(QString name);
        SpellInfoPlugins getPlugins() const { return m_spellInfoPlugins; }
        SpellInfoInterface* getActivePlugin() const { return m_activeSpellInfoPlugin; }
        QString getActivePluginName() const { return m_activeSpellInfoPluginName; }

        void showInfo(quint32 id, QSW::Pages pageId = QSW::PAGE_MAIN);
        void compare();
        EventList search(quint8 type);

        MainForm* getForm() { return m_form; }

    signals:
        void pluginLoadingInit();
        void pluginLoadingFail();
        void pluginLoaded();
        void progressShow(int maximum);
        void progressStep(int value);
        void progressHide();

    private:
        MainForm *m_form;

        QByteArray m_templateHtml;
        QByteArray m_styleCss;

        QMutex _pluginLoaderMutex;
        SpellInfoPlugins m_spellInfoPlugins;
        SpellInfoInterface* m_activeSpellInfoPlugin;
        QString m_activeSpellInfoPluginName;
};

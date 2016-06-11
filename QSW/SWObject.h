#ifndef SWOBJECT_H
#define SWOBJECT_H

#include <QMetaEnum>
#include <QJSEngine>
#include <QJSValue>
#include <QJSValueList>
#include <QJsonObject>

#include "MainForm.h"
#include "shared.h"
#include "events.h"
#include "Defines.h"
#include "blp/BLP.h"

#include "plugins/spellinfo/interface.h"

typedef QPair<QJsonObject, SpellInfoInterface*> SpellInfoPluginPair;
typedef QHash<QString, SpellInfoPluginPair> SpellInfoPlugins;

class MainForm;
class SWObject : public QObject
{
    Q_OBJECT

    public:
        SWObject(MainForm *form);
        ~SWObject() {}

        void loadPlugins();
        void setActivePlugin(QString name);
        SpellInfoPlugins getPlugins() const { return m_spellInfoPlugins; }
        SpellInfoInterface* getActivePlugin() const { return m_activeSpellInfoPlugin; }
        QString getActivePluginName() const { return m_activeSpellInfoPluginName; }

        void showInfo(quint32 id, QSW::Pages pageId = QSW::PAGE_MAIN);
        void compare();
        EventList search();

        QMetaEnum getMetaEnum() { return m_metaEnum; }
        void setMetaEnum(const char* enumName);

        quint8 getType() const { return m_type; }
        void setType(quint8 type) { m_type = type; }

        MainForm* getForm() { return m_form; }

    private:
        MainForm *m_form;

        QMetaEnum m_metaEnum;

        quint8 m_type;

        QByteArray m_templateHtml;
        QByteArray m_styleCss;

        SpellInfoPlugins m_spellInfoPlugins;
        SpellInfoInterface* m_activeSpellInfoPlugin;
        QString m_activeSpellInfoPluginName;
};

#endif // SWOBJECT_H

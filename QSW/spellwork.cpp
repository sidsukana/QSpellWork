#include <QBuffer>
#include <QThread>
#include <QResource>
#include <QDir>
#include <QPluginLoader>
#include <QMessageBox>
#include <QSqlQuery>

#include "spellwork.h"
#include "models.h"
#include "blp/BLP.h"
#include "mpq/MPQ.h"

#include "mustache/mustache.h"

SpellWork::SpellWork(MainForm* form)
    : QObject(form), m_form(form), m_activeSpellInfoPlugin(nullptr)
{
    loadPlugins();
}

void SpellWork::setActivePlugin(QString name)
{
    m_activeSpellInfoPlugin = nullptr;

    // load new plugin
    if (m_spellInfoPlugins.contains(name)) {

        SpellInfoInterface* plugin = m_spellInfoPlugins[name].second;
        m_activeSpellInfoPluginName = name;
        m_form->loadSettings();

        MPQ::setMpqFiles(plugin->getMPQFiles());

        if (!plugin->init()) {
            qCritical("Plugin '%s' is not loaded!", qPrintable(name));
            QMessageBox::warning(m_form, "Warning", "Please check directories settings!", QMessageBox::StandardButton::Ok);
            return;
        }

        // Modified SQL data
        QStringList queries = plugin->getModifiedSqlDataQueries();
        quint8 queryIndex = 0;
        for (QString& query : queries)
        {
            QSqlQuery result = QSW::database().exec(query);
            plugin->setModifiedSqlDataResult(queryIndex++, result);
        }

        QJsonObject metaData = m_spellInfoPlugins[name].first;

        QFile templateFile("plugins/spellinfo/" + metaData.value("htmlFile").toString());
        if (templateFile.open(QFile::ReadOnly)) {
            m_templateHtml = templateFile.readAll();
            templateFile.close();
        }

        QFile styleFile("plugins/spellinfo/" + metaData.value("cssFile").toString());
        if (styleFile.open(QFile::ReadOnly)) {
            m_styleCss = styleFile.readAll();
            styleFile.close();
        }

        EnumHash enums = QSW::loadEnumFile("plugins/spellinfo/" + metaData.value("enumsFile").toString());
        plugin->setEnums(enums);

        m_form->getScriptFilter()->scriptEdit->setupCompleter(plugin->getMetaSpell(0));
        m_form->loadComboBoxes(enums);
        m_form->loadCompleter(plugin->getNames());
        m_form->setLocale(MPQ::localeDir());
        m_activeSpellInfoPlugin = plugin;
    }
}

void SpellWork::loadPlugins()
{
    QDir pluginsDir(qApp->applicationDirPath());
    pluginsDir.cd("plugins/spellinfo");
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();
        if (plugin) {
            SpellInfoInterface* spellInfoPlugin = qobject_cast<SpellInfoInterface *>(plugin);
            if (spellInfoPlugin) {
                QJsonObject metaData = pluginLoader.metaData().value("MetaData").toObject();
                m_spellInfoPlugins[metaData.value("name").toString()] = SpellInfoPluginPair(metaData, spellInfoPlugin);
            }
        }
    }
}

EventList SpellWork::search(quint8 type)
{
    EventList eventList;
    if (!m_activeSpellInfoPlugin)
        return eventList;

    SpellListModel *model = new SpellListModel();

    if (type == 1)
    {
        for (quint32 i = 0; i < m_activeSpellInfoPlugin->getSpellsCount(); ++i)
        {
            bool family = true;
            bool aura = true;
            bool effect = true;
            bool targetA = true;
            bool targetB = true;

            if (QObject* m_spellInfo = m_activeSpellInfoPlugin->getMetaSpell(i))
            {
                if (m_form->comboBox->currentIndex() > 0)
                    family = (m_spellInfo->property("SpellFamilyName").toUInt() == m_form->comboBox->currentData().toUInt());

                if (m_form->comboBox_2->currentIndex() > 0)
                    QMetaObject::invokeMethod(m_spellInfo, "hasAura", Qt::DirectConnection,
                                              Q_RETURN_ARG(bool, aura), Q_ARG(quint32, m_form->comboBox_2->currentData().toUInt()));

                if (m_form->comboBox_3->currentIndex() > 0)
                    QMetaObject::invokeMethod(m_spellInfo, "hasEffect", Qt::DirectConnection,
                                              Q_RETURN_ARG(bool, effect), Q_ARG(quint32, m_form->comboBox_3->currentData().toUInt()));


                if (m_form->comboBox_4->currentIndex() > 0)
                    QMetaObject::invokeMethod(m_spellInfo, "hasTargetA", Qt::DirectConnection,
                                              Q_RETURN_ARG(bool, targetA), Q_ARG(quint32, m_form->comboBox_4->currentData().toUInt()));


                if (m_form->comboBox_5->currentIndex() > 0)
                    QMetaObject::invokeMethod(m_spellInfo, "hasTargetB", Qt::DirectConnection,
                                              Q_RETURN_ARG(bool, targetB), Q_ARG(quint32, m_form->comboBox_5->currentData().toUInt()));


                if (family && aura && effect && targetA && targetB)
                {
                    QStringList spellRecord;
                    spellRecord << QString("%0").arg(m_spellInfo->property("Id").toUInt()) << m_spellInfo->property("NameWithRank").toString();

                    model->appendRecord(spellRecord);
                }
            }
        }
        Event* ev = new Event(Event::Type(Event::EVENT_SEND_MODEL));
        ev->addValue(QVariant::fromValue(model));
        eventList << ev;
    }
    else if (type == 3)
    {
        QJSEngine engine;

        EnumHash enums = m_activeSpellInfoPlugin->getEnums();

        for (EnumHash::const_iterator itr = enums.begin(); itr != enums.end(); ++itr)
            for (Enumerator::const_iterator itr2 = itr->begin(); itr2 != itr->end(); ++itr2)
                engine.globalObject().setProperty(itr2.value(), qreal(itr2.key()));

        QString text = m_form->getFilterText();
        QJSValue script = engine.evaluate(text.contains("function()") ? "(" + text + ")" : "(function() { return (" + text + "); })");

        for (quint32 i = 0; i < m_activeSpellInfoPlugin->getSpellsCount(); ++i)
        {
            QObject* m_spellInfo = m_activeSpellInfoPlugin->getMetaSpell(i);

            if (!m_spellInfo)
                continue;

            engine.globalObject().setProperty("spell", engine.toScriptValue(m_spellInfo));

            if (script.call().toBool())
            {
                QStringList spellRecord;
                spellRecord << QString("%0").arg(m_spellInfo->property("Id").toUInt()) << m_spellInfo->property("NameWithRank").toString();

                model->appendRecord(spellRecord);
            }
        }

        Event* ev = new Event(Event::Type(Event::EVENT_SEND_MODEL));
        ev->addValue(QVariant::fromValue(model));
        eventList << ev;
    }
    else
    {
        if (!m_form->findLine_e1->text().isEmpty())
        {
            if (!m_form->findLine_e1->text().toInt())
            {
                for (quint32 i = 0; i < m_activeSpellInfoPlugin->getSpellsCount(); ++i)
                {
                    QObject* m_spellInfo = m_activeSpellInfoPlugin->getMetaSpell(i);

                    if (m_spellInfo)
                    {
                        QString name = m_spellInfo->property("Name").toString();
                        if (name.contains(m_form->findLine_e1->text(), Qt::CaseInsensitive))
                        {
                            QStringList spellRecord;
                            spellRecord << QString("%0").arg(m_spellInfo->property("Id").toUInt()) << m_spellInfo->property("NameWithRank").toString();
                            model->appendRecord(spellRecord);
                        }
                    }
                }

                Event* ev = new Event(Event::Type(Event::EVENT_SEND_MODEL));
                ev->addValue(QVariant::fromValue(model));
                eventList << ev;
            }
            else
            {
                if (QObject* m_spellInfo = m_activeSpellInfoPlugin->getMetaSpell(m_form->findLine_e1->text().toInt(), true))
                {
                    QStringList spellRecord;
                    spellRecord << QString("%0").arg(m_spellInfo->property("Id").toUInt()) << m_spellInfo->property("NameWithRank").toString();

                    model->appendRecord(spellRecord);

                    Event* ev1 = new Event(Event::Type(Event::EVENT_SEND_MODEL));
                    ev1->addValue(QVariant::fromValue(model));
                    eventList << ev1;

                    Event* ev2 = new Event(Event::Type(Event::EVENT_SEND_SPELL));
                    ev2->addValue(m_spellInfo->property("Id").toUInt());
                    eventList << ev2;
                }
            }
        }
        else if (!m_form->findLine_e3->text().isEmpty())
        {
            for (quint32 i = 0; i < m_activeSpellInfoPlugin->getSpellsCount(); ++i)
            {
                QObject* m_spellInfo = m_activeSpellInfoPlugin->getMetaSpell(i);
                if (m_spellInfo)
                {
                    QString description = m_spellInfo->property("Description").toString();
                    if (description.contains(m_form->findLine_e3->text(), Qt::CaseInsensitive))
                    {
                        QStringList spellRecord;
                        spellRecord << QString("%0").arg(m_spellInfo->property("Id").toUInt()) << m_spellInfo->property("NameWithRank").toString();
                        model->appendRecord(spellRecord);
                    }
                }
            }

            Event* ev = new Event(Event::Type(Event::EVENT_SEND_MODEL));
            ev->addValue(QVariant::fromValue(model));
            eventList << ev;
        }
        else
        {
            for (quint32 i = 0; i < m_activeSpellInfoPlugin->getSpellsCount(); ++i)
            {
                if (QObject* m_spellInfo = m_activeSpellInfoPlugin->getMetaSpell(i))
                {
                    QStringList spellRecord;
                    spellRecord << QString("%0").arg(m_spellInfo->property("Id").toUInt()) << m_spellInfo->property("NameWithRank").toString();

                    model->appendRecord(spellRecord);
                }
            }

            Event* ev = new Event(Event::Type(Event::EVENT_SEND_MODEL));
            ev->addValue(QVariant::fromValue(model));
            eventList << ev;
        }
    }

    return eventList;
}

void SpellWork::showInfo(quint32 id, QSW::Pages pageId)
{
    QVariantHash values = m_activeSpellInfoPlugin->getValues(id);
    values["style"] = m_styleCss;

    Mustache::Renderer renderer;
    Mustache::QtVariantContext context(values);

    QString html;
    QTextStream stream(&html);
    stream << renderer.render(m_templateHtml, &context);

    html = html.simplified();
    html.replace("> <", ">\n<");

    m_form->getPage(pageId)->setInfo(html, id);
}

void SpellWork::compare()
{
    QStringList list1 = m_form->getPage(QSW::PAGE_CLEFT)->getSourceHtml().split("\n");
    QStringList list2 = m_form->getPage(QSW::PAGE_CRIGHT)->getSourceHtml().split("\n");

    QString html1, html2;

    QRegExp rx("(<[A-Za-z_0-9]*>)+([A-Za-z_0-9-!\"#$%&'()*+,./:;=?@[\\]_`{|}~\\s]*)+(</[A-Za-z_0-9]*>)");

    for (QStringList::iterator itr1 = list1.begin(); itr1 != list1.end(); ++itr1)
    {
        bool yes = false;

        for (QStringList::iterator itr2 = list2.begin(); itr2 != list2.end(); ++itr2)
        {
            if ((*itr1) == (*itr2))
            {
                yes = true;
                break;
            }
        }

        if (yes)
        {
            if (rx.indexIn((*itr1)) != -1)
            {
                // QString r1 = rx.cap(0); // Full
                QString r2 = rx.cap(1); // <xxx>
                QString r3 = rx.cap(2); // <>xxx</>
                QString r4 = rx.cap(3); // </xxx>

                if (r2 == "<b>")
                    html1.append(QString("<span style='background-color: cyan'>%0</span>").arg((*itr1)));
                else if (r2 == "<style>")
                {
                    html1.append((*itr1));
                }
                else
                {
                    r3 = QString("<span style='background-color: cyan'>%0</span>").arg(r3);
                    r3.prepend(r2);
                    r3.append(r4);
                    html1.append(r3);
                }
            }
            else
                html1.append((*itr1));
        }
        else
        {
            if (rx.indexIn((*itr1)) != -1)
            {
                // QString r1 = rx.cap(0); // Full
                QString r2 = rx.cap(1); // <xxx>
                QString r3 = rx.cap(2); // <>xxx</>
                QString r4 = rx.cap(3); // </xxx>

                if (r2 == "<b>")
                    html1.append(QString("<span style='background-color: salmon'>%0</span>").arg((*itr1)));
                else if (r2 == "<style>")
                {
                    html1.append((*itr1));
                }
                else
                {
                    r3 = QString("<span style='background-color: salmon'>%0</span>").arg(r3);
                    r3.prepend(r2);
                    r3.append(r4);
                    html1.append(r3);
                }
            }
            else
                html1.append((*itr1));
        }
    }

    // second
    for (QStringList::iterator itr2 = list2.begin(); itr2 != list2.end(); ++itr2)
    {
        bool yes = false;

        for (QStringList::iterator itr1 = list1.begin(); itr1 != list1.end(); ++itr1)
        {
            if ((*itr2) == (*itr1))
            {
                yes = true;
                break;
            }
        }

        if (yes)
        {
            if (rx.indexIn((*itr2)) != -1)
            {
                // QString r1 = rx.cap(0); // Full
                QString r2 = rx.cap(1); // <xxx>
                QString r3 = rx.cap(2); // <>xxx</>
                QString r4 = rx.cap(3); // </xxx>

                if (r2 == "<b>")
                    html2.append(QString("<span style='background-color: cyan'>%0</span>").arg((*itr2)));
                else if (r2 == "<style>")
                {
                    html2.append((*itr2));
                }
                else
                {
                    r3 = QString("<span style='background-color: cyan'>%0</span>").arg(r3);
                    r3.prepend(r2);
                    r3.append(r4);
                    html2.append(r3);
                }
            }
            else
                html2.append((*itr2));
        }
        else
        {
            if (rx.indexIn((*itr2)) != -1)
            {
                // QString r1 = rx.cap(0); // Full
                QString r2 = rx.cap(1); // <xxx>
                QString r3 = rx.cap(2); // <>xxx</>
                QString r4 = rx.cap(3); // </xxx>

                if (r2 == "<b>")
                    html2.append(QString("<span style='background-color: salmon'>%0</span>").arg((*itr2)));
                else if (r2 == "<style>")
                {
                    html2.append((*itr2));
                }
                else
                {
                    r3 = QString("<span style='background-color: salmon'>%0</span>").arg(r3);
                    r3.prepend(r2);
                    r3.append(r4);
                    html2.append(r3);
                }
            }
            else
                html2.append((*itr2));
        }
    }

    m_form->getPage(QSW::PAGE_CLEFT)->setCompareInfo(html1);
    m_form->getPage(QSW::PAGE_CRIGHT)->setCompareInfo(html2);
}



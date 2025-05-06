#include <QBuffer>
#include <QThread>
#include <QResource>
#include <QDir>
#include <QDirIterator>
#include <QPluginLoader>
#include <QMessageBox>
#include <QSqlQuery>

#include <fstream>
#include <mustache.h>

#include "spellwork.h"
#include "models.h"
#include "mpq.h"


SpellWork::SpellWork(MainForm* form)
    : QObject(form), m_form(form), m_activeSpellInfoPlugin(nullptr)
{
    loadPlugins();
}

void SpellWork::setActivePlugin(QString name)
{
    if (!_pluginLoaderMutex.tryLock())
        return;

    emit pluginLoadingInit();
    m_activeSpellInfoPlugin = nullptr;

    // load new plugin
    if (m_spellInfoPlugins.contains(name))
    {
        SpellInfoInterface* plugin = m_spellInfoPlugins[name].second;
        m_activeSpellInfoPluginName = name;
        m_form->loadSettings(false, QString());

        MPQ::setMpqFiles(plugin->getMPQFiles());

        if (!plugin->init())
        {
            qCritical("Plugin '%s' is not loaded!", qPrintable(name));
            emit pluginLoadingFail();
            _pluginLoaderMutex.unlock();
            return;
        }

        // Modified SQL data
        QStringList queries = plugin->getModifiedSqlDataQueries();
        quint8 queryIndex = 0;
        for (QString& query : queries)
        {
            QSqlQuery result(QSW::database());
            result.setForwardOnly(true);
            result.prepare(query);
            result.exec();
            plugin->setModifiedSqlDataResult(queryIndex++, result);
        }

        QJsonObject metaData = m_spellInfoPlugins[name].first;

        QString filePathTemplate = QString("plugins/spellinfo/%0/%1").arg(name);
        QFile templateFile(filePathTemplate.arg(metaData.value("htmlFile").toString()));
        if (templateFile.open(QFile::ReadOnly))
        {
            m_templateHtml = templateFile.readAll();
            templateFile.close();
        }

        QFile styleFile(filePathTemplate.arg(metaData.value("cssFile").toString()));
        if (styleFile.open(QFile::ReadOnly))
        {
            m_styleCss = styleFile.readAll();
            styleFile.close();
        }

        EnumHash enums = QSW::loadEnumFile(filePathTemplate.arg(metaData.value("enumsFile").toString()));
        plugin->setEnums(enums);

        m_form->getScriptFilter()->scriptEdit->setupCompleter(plugin->getMetaSpell(0));
        m_form->loadComboBoxes(enums);
        m_form->loadCompleter(plugin->getNames());
        m_form->setLocale(MPQ::localeDir());
        m_activeSpellInfoPlugin = plugin;
    }

    emit pluginLoaded();
    _pluginLoaderMutex.unlock();
}

void SpellWork::loadPlugins()
{
    QDir dir = QDir::current();

    if (!dir.cd("plugins/spellinfo")) {
        return;
    }

    dir.setNameFilters({"*.dll"});

    QDirIterator itr(dir, QDirIterator::Subdirectories);

    while (itr.hasNext())
    {
        QPluginLoader pluginLoader(itr.next());
        QObject *plugin = pluginLoader.instance();
        if (plugin)
        {
            SpellInfoInterface* spellInfoPlugin = qobject_cast<SpellInfoInterface *>(plugin);
            if (spellInfoPlugin)
            {
                connect(plugin, SIGNAL(progressShow(int)), this, SIGNAL(progressShow(int)));
                connect(plugin, SIGNAL(progressStep(int)), this, SIGNAL(progressStep(int)));
                connect(plugin, SIGNAL(progressHide()), this, SIGNAL(progressHide()));

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

    std::ofstream MyFile("filename.txt");

    // Write to the file
    MyFile << html.toStdString();

    // Close the file
    MyFile.close();

    m_form->getPage(pageId)->setInfo(html, id);
}

// COPILOT AI GENERATED FOR QUICK FIX COMPARE FUNCTION
void SpellWork::compare()
{
    static const QRegularExpression reSplit(R"((<[^>]+>)|([^<]+))");
    static const QRegularExpression reStripTags(R"(<[^>]+>)");

    auto stripText = [&](const QString &html) {
        QString t = html;
        t.remove(reStripTags);
        return t.simplified();
    };

    auto highlightText = [&](const QString &text, const QString &bg) {
        return QString("<span style=\"background-color:%1;\">%2</span>")
        .arg(bg, text.toHtmlEscaped());
    };

    auto renderLine = [&](const QString &line, const QString &bg) {
        QString out;
        auto it = reSplit.globalMatch(line);
        while (it.hasNext()) {
            auto m = it.next();
            if (!m.captured(1).isEmpty())
                out += m.captured(1);
            else if (!m.captured(2).isEmpty())
                out += highlightText(m.captured(2), bg);
        }
        return out;
    };


    QStringList rawL = m_form->getPage(QSW::PAGE_CLEFT )->getSourceHtml().split('\n');
    QStringList rawR = m_form->getPage(QSW::PAGE_CRIGHT)->getSourceHtml().split('\n');
    int n = rawL.size(), m = rawR.size();

    QVector<QString> L(n), R(m);
    for (int i = 0; i < n; ++i) L[i] = stripText(rawL[i]);
    for (int j = 0; j < m; ++j) R[j] = stripText(rawR[j]);

    QVector<QVector<int>> dp(n+1, QVector<int>(m+1, 0));
    for (int i = n-1; i >= 0; --i) {
        for (int j = m-1; j >= 0; --j) {
            if (!L[i].isEmpty() && L[i] == R[j])
                dp[i][j] = dp[i+1][j+1] + 1;
            else
                dp[i][j] = qMax(dp[i+1][j], dp[i][j+1]);
        }
    }

    QVector<QPair<int,int>> matches;
    int i = 0, j = 0;
    while (i < n && j < m) {
        if (!L[i].isEmpty() && L[i] == R[j]) {
            matches.append(qMakePair(i, j));
            ++i; ++j;
        }
        else if (dp[i+1][j] >= dp[i][j+1]) ++i;
        else ++j;
    }

    matches.prepend(qMakePair(-1, -1));
    matches.append(qMakePair(n, m));

    const QString COL_CHANGED = "#FFA500"; // orange
    const QString COL_ONLY    = "#90EE90"; // lightgreen

    QString outL, outR;
    for (int k = 0; k+1 < matches.size(); ++k) {
        int i1 = matches[k].first,  j1 = matches[k].second;
        int i2 = matches[k+1].first, j2 = matches[k+1].second;

        int countL = i2 - i1 - 1;
        int countR = j2 - j1 - 1;

        if (countL > 0 && countR > 0) {
            for (int x = i1+1; x < i2; ++x)
                outL += renderLine(rawL[x], COL_CHANGED) + '\n';
            for (int y = j1+1; y < j2; ++y)
                outR += renderLine(rawR[y], COL_CHANGED) + '\n';
        }
        else {
            for (int x = i1+1; x < i2; ++x)
                outL += renderLine(rawL[x], COL_ONLY) + '\n';
            for (int y = j1+1; y < j2; ++y)
                outR += renderLine(rawR[y], COL_ONLY) + '\n';
        }

        if (i2 >= 0 && i2 < n && j2 >= 0 && j2 < m) {
            outL += rawL[i2] + '\n';
            outR += rawR[j2] + '\n';
        }
    }

    m_form->getPage(QSW::PAGE_CLEFT )->setCompareInfo(outL);
    m_form->getPage(QSW::PAGE_CRIGHT)->setCompareInfo(outR);
}

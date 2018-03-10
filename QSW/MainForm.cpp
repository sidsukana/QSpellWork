#include <QtConcurrentRun>
#include <QFuture>
#include <QTime>
#include <QStandardItemModel>
#include <QStringListModel>
#include <QDir>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QClipboard>
#include <QShortcut>
#include <QSqlError>
#include <QStatusBar>

#include "MainForm.h"
#include "AboutForm.h"
#include "SettingsForm.h"
#include "wov/wov.h"
#include "mpq/MPQ.h"

MainForm::MainForm(QWidget* parent)
    : QMainWindow(parent)
{
    QTime m_time;
    m_time.start();

    setupUi(this);

    m_scriptFilter = new ScriptFilter(page);
    gridLayout_4->addWidget(m_scriptFilter, 0, 1, 2, 1);
    m_scriptFilter->hide();

    m_sw = new SpellWork(this);
    m_watcher = new SearchResultWatcher();
    connect(m_watcher, SIGNAL(finished()), this, SLOT(slotSearchResult()));

    m_sortedModel = new SpellListSortedModel(this);
    m_sortedModel->setDynamicSortFilter(true);
    SpellList->setModel(m_sortedModel);

    setLocale(MPQ::localeDir());
    createModeButton();
    createPluginButton();

    mainToolBar->addSeparator();
    mainToolBar->addWidget(m_modeButton);
    mainToolBar->addSeparator();
    mainToolBar->addWidget(m_pluginButton);
    mainToolBar->addSeparator();
    m_actionSettings = mainToolBar->addAction(QIcon(":/qsw/resources/cog.png"), "Settings");
    mainToolBar->addSeparator();
    m_actionWov = mainToolBar->addAction(QIcon(":/qsw/resources/wand.png"), "Wov");
    mainToolBar->addSeparator();
    m_actionAbout = mainToolBar->addAction(QIcon(":/qsw/resources/information.png"), "About");

    QShortcut* shortcut = new QShortcut(QKeySequence(QKeySequence::MoveToPreviousLine), this, SLOT(slotPrevRow()));
    shortcut = new QShortcut(QKeySequence(QKeySequence::MoveToNextLine), this, SLOT(slotNextRow()));

    QAction* copyAction = new QAction("Copy all", this);
    connect(copyAction, SIGNAL(triggered()), this, SLOT(slotCopyAll()));
    SpellList->addAction(copyAction);

    m_completer = new QCompleter(this);
    m_completerModel = new QStringListModel(this);
    m_completer->setModel(m_completerModel);
    m_completer->setCaseSensitivity(Qt::CaseInsensitive);
    findLine_e1->setCompleter(m_completer);

    connect(adFilterButton, SIGNAL(clicked()), this, SLOT(slotScriptFilter()));

    // List search connection
    connect(SpellList, SIGNAL(clicked(QModelIndex)), this, SLOT(slotSearchFromList(QModelIndex)));

    // Main search connections
    connect(findLine_e1, SIGNAL(returnPressed()), this, SLOT(slotButtonSearch()));
    connect(findLine_e3, SIGNAL(returnPressed()), this, SLOT(slotButtonSearch()));

    // Menu connections
    connect(m_actionAbout, SIGNAL(triggered()), this, SLOT(slotAbout()));

    // Settings form connection
    connect(m_actionSettings, SIGNAL(triggered()), this, SLOT(slotSettings()));

    // Wov form connection
    connect(m_actionWov, SIGNAL(triggered()), this, SLOT(slotWov()));

    m_comboBoxes = { comboBox, comboBox_2, comboBox_3, comboBox_4, comboBox_5 };
    m_comboBoxModels.resize(5);
    for (quint8 i = 0; i < 5; ++i)
    {
        m_comboBoxModels[i] = new ComboBoxModel(this);
        m_comboBoxes[i]->setModel(m_comboBoxModels[i]);
        connect(m_comboBoxes[i], SIGNAL(currentIndexChanged(int)), this, SLOT(slotFilterSearch()));
    }

    // Search connection
    connect(this, SIGNAL(signalSearch(quint8)), this, SLOT(slotSearch(quint8)));

    connect(m_scriptFilter->pushButton, SIGNAL(clicked()), this, SLOT(slotScriptApply()));

    connect(compareSpell_1, SIGNAL(returnPressed()), this, SLOT(slotCompareSearch()));
    connect(compareSpell_2, SIGNAL(returnPressed()), this, SLOT(slotCompareSearch()));

    for (quint8 i = QSW::PAGE_MAIN; i < QSW::PAGE_MAX; ++i)
    {
        m_pages[i] = new QSWPage(QSW::Pages(i));
        connect(m_pages[i], SIGNAL(linkClicked(QUrl)), this, SLOT(slotLinkClicked(QUrl)));

        switch (i)
        {
            case QSW::PAGE_MAIN: webView1->setPage(m_pages[i]); break;
            case QSW::PAGE_CLEFT: webView2->setPage(m_pages[i]); break;
            case QSW::PAGE_CRIGHT: webView3->setPage(m_pages[i]); break;
            default: break;
        }

    }

    getPage(QSW::PAGE_MAIN)->setInfo(QString("Load time: %0 ms").arg(m_time.elapsed()));

    // Save settings on exit
    connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(saveSettings()));

    progressBar->hide();

    // Load settings at end
    loadSettings();
}

MainForm::~MainForm()
{

}

void MainForm::slotSettings()
{
    QSharedPointer<SettingsForm> settingsForm = QSharedPointer<SettingsForm>(new SettingsForm(this));

    connect(settingsForm->buttonConnect, &QPushButton::clicked, [=](){
        if (QSW::database().isOpen())
        {
            QSW::database().close();
            settingsForm->buttonConnect->setText("Connect");
        }
        else
        {
            QSW::database().setHostName(settingsForm->hostname->text());
            QSW::database().setPort(settingsForm->port->text().toUInt());
            QSW::database().setUserName(settingsForm->username->text());
            QSW::database().setPassword(settingsForm->password->text());
            QSW::database().setDatabaseName(settingsForm->database->text());

            if (QSW::database().open())
            {
                settingsForm->buttonConnect->setText("Disconnect");
            }
            else
            {
                qDebug() << QSW::database().lastError().text();
            }
        }
    });

    // Database
    settingsForm->buttonConnect->setText(QSW::database().isOpen() ? "Disconnect" : "Connect");
    settingsForm->hostname->setText(QSW::database().hostName());
    settingsForm->port->setText(QString::number(QSW::database().port()));
    settingsForm->username->setText(QSW::database().userName());
    settingsForm->password->setText(QSW::database().password());
    settingsForm->database->setText(QSW::database().databaseName());

    if (settingsForm->exec() == QDialog::Accepted) {
        MPQ::mpqDir() = "";
        MPQ::localeDir() = "";
        DBC::dbcDir() = "";
        if (!settingsForm->mpqDir->text().isEmpty()) {
            MPQ::mpqDir() = QDir::fromNativeSeparators(QDir::cleanPath(settingsForm->mpqDir->text())) + "/";
            MPQ::localeDir() = settingsForm->mpqLocale->itemText(settingsForm->mpqLocale->currentIndex());
        }
        if (!settingsForm->dbcDir->text().isEmpty()) {
            DBC::dbcDir() = QDir::fromNativeSeparators(QDir::cleanPath(settingsForm->dbcDir->text())) + "/";
        }
    }

    saveSettings();
}

void MainForm::slotScriptFilter()
{
    if (m_scriptFilter->isVisible())
    {
        webView1->show();
        m_scriptFilter->hide();
    }
    else
    {
        webView1->hide();
        m_scriptFilter->show();
    }
}

void MainForm::slotScriptApply()
{
    emit signalSearch(3);
}

void MainForm::loadSettings()
{
    QString pluginName = m_sw->getActivePluginName();

    if (pluginName.isEmpty())
    {
        QSW::settings().beginGroup("Global");
        pluginName = QSW::settings().value("lastActivePlugin", QString()).toString();
        QSW::settings().endGroup();

        if (!pluginName.isEmpty())
        {
            QtConcurrent::run(m_sw, &SpellWork::setActivePlugin, pluginName);
        }
        return;
    }

    if (!pluginName.isEmpty())
    {
        QSW::settings().beginGroup("Plugin/" + pluginName);

        MPQ::mpqDir() = QSW::settings().value("mpqDir", "").toString();
        MPQ::localeDir() = QSW::settings().value("mpqLocaleDir", "").toString();
        DBC::dbcDir() = QSW::settings().value("dbcDir", "").toString();

        QSW::settings().beginGroup("Database");
        QSW::database().setHostName(QSW::settings().value("hostname").toString());
        QSW::database().setPort(QSW::settings().value("port").toUInt());
        QSW::database().setUserName(QSW::settings().value("username").toString());
        QSW::database().setPassword(QSW::settings().value("password").toString());
        QSW::database().setDatabaseName(QSW::settings().value("database").toString());
        QSW::database().open();
        QSW::settings().endGroup();

        QSW::settings().beginGroup("FastFilter");
        findLine_e1->setText(QSW::settings().value("IdOrName", "").toString());
        findLine_e3->setText(QSW::settings().value("Description", "").toString());
        comboBox->setCurrentIndex(QSW::settings().value("SpellFamilyIndex", 0).toInt());
        comboBox_2->setCurrentIndex(QSW::settings().value("EffectIndex", 0).toInt());
        comboBox_3->setCurrentIndex(QSW::settings().value("AuraIndex", 0).toInt());
        comboBox_4->setCurrentIndex(QSW::settings().value("TargetAIndex", 0).toInt());
        comboBox_5->setCurrentIndex(QSW::settings().value("TargetBIndex", 0).toInt());
        QSW::settings().endGroup();

        QSW::settings().beginGroup("ScriptFilter");
        m_scriptFilter->addBookmarks(QSW::settings().value("Bookmarks").toStringList());
        QSW::settings().endGroup();
        QSW::settings().endGroup();
    }
}

void MainForm::saveSettings()
{
    QString pluginName = m_sw->getActivePluginName();

    if (!pluginName.isEmpty())
    {
        QSW::settings().beginGroup("Global");
        QSW::settings().setValue("lastActivePlugin", pluginName);
        QSW::settings().endGroup();

        QSW::settings().beginGroup("Plugin/" + pluginName);
        QSW::settings().setValue("mpqDir", MPQ::mpqDir());
        QSW::settings().setValue("mpqLocaleDir", MPQ::localeDir());
        QSW::settings().setValue("dbcDir", DBC::dbcDir());

        if (QSW::database().isOpen())
        {
            QSW::settings().beginGroup("Database");
            QSW::settings().setValue("hostname", QSW::database().hostName());
            QSW::settings().setValue("port", QSW::database().port());
            QSW::settings().setValue("username", QSW::database().userName());
            QSW::settings().setValue("password", QSW::database().password());
            QSW::settings().setValue("database", QSW::database().databaseName());
            QSW::settings().endGroup();
        }

        QSW::settings().beginGroup("FastFilter");
        QSW::settings().setValue("IdOrName", findLine_e1->text());
        QSW::settings().setValue("Description", findLine_e3->text());
        QSW::settings().setValue("SpellFamilyIndex", comboBox->currentIndex());
        QSW::settings().setValue("EffectIndex", comboBox_2->currentIndex());
        QSW::settings().setValue("AuraIndex", comboBox_3->currentIndex());
        QSW::settings().setValue("TargetAIndex", comboBox_4->currentIndex());
        QSW::settings().setValue("TargetBIndex", comboBox_5->currentIndex());
        QSW::settings().endGroup();

        QSW::settings().beginGroup("ScriptFilter");
        QStringList bookmarks = m_scriptFilter->getBookmarks();
        QSW::settings().setValue("Bookmarks", bookmarks);
        QSW::settings().endGroup();
        QSW::settings().endGroup();
    }

    QSW::settings().sync();
}

void MainForm::slotPrevRow()
{
    if (!SpellList->hasFocus())
        return;

    SpellList->selectRow(SpellList->currentIndex().row() - 1);

    QVariant var = SpellList->model()->data(SpellList->model()->index(SpellList->currentIndex().row(), 0));
    m_sw->showInfo(var.toInt());
    SpellList->setFocus();
}

void MainForm::slotNextRow()
{
    if (!SpellList->hasFocus())
        return;

    SpellList->selectRow(SpellList->currentIndex().row() + 1);

    QVariant var = SpellList->model()->data(SpellList->model()->index(SpellList->currentIndex().row(), 0));
    m_sw->showInfo(var.toInt());
    SpellList->setFocus();
}

void MainForm::slotCopyAll()
{
    QClipboard *clipboard = QApplication::clipboard();

    auto spellList = ((SpellListModel*)m_sortedModel->sourceModel())->getSpellList();

    QString str;
    for (auto itr = spellList.begin(); itr != spellList.end(); ++itr)
        str.append(itr->at(0) + " | " + itr->at(1) + "\n");
    clipboard->setText(str);
}

void MainForm::loadCompleter(QStringList names)
{
    m_completerModel->setStringList(names);
}

void MainForm::createModeButton()
{
    QAction* actionShow = new QAction(QIcon(":/qsw/resources/application.png"), "Show", this);
    QAction* actionCompare = new QAction(QIcon(":/qsw/resources/application_tile_horizontal.png"), "Compare", this);

    connect(actionShow, SIGNAL(triggered()), this, SLOT(slotModeShow()));
    connect(actionCompare, SIGNAL(triggered()), this, SLOT(slotModeCompare()));

    m_modeButton = new QToolButton(this);
    m_modeButton->setText("Mode");
    m_modeButton->setIcon(actionShow->icon());
    m_modeButton->setPopupMode(QToolButton::InstantPopup);

    m_modeButton->addAction(actionShow);
    m_modeButton->addAction(actionCompare);
}

void MainForm::createPluginButton()
{
    connect(m_sw, &SpellWork::progressShow, this, &MainForm::showProgressBar);
    connect(m_sw, &SpellWork::progressStep, progressBar, &QProgressBar::setValue);
    connect(m_sw, &SpellWork::progressHide, this, &MainForm::hideProgressBar);
    connect(m_sw, &SpellWork::pluginLoadingInit, this, &MainForm::onPluginLoadingInit);
    connect(m_sw, &SpellWork::pluginLoadingFail, this, &MainForm::onPluginLoadingFail);
    connect(m_sw, &SpellWork::pluginLoaded, this, &MainForm::onPluginLoaded);

    m_pluginButton = new QToolButton(this);
    m_pluginButton->setText("Plugins");
    m_pluginButton->setPopupMode(QToolButton::InstantPopup);

    SpellInfoPlugins plugins = m_sw->getPlugins();
    for (SpellInfoPlugins::iterator itr = plugins.begin(); itr != plugins.end(); ++itr)
    {
        QAction* actionPlugin = new QAction(itr.value().first.value("fullName").toString(), this);
        actionPlugin->setCheckable(true);
        actionPlugin->setData(itr.key());
        m_pluginButton->addAction(actionPlugin);
        connect(actionPlugin, SIGNAL(triggered()), this, SLOT(slotChangeActivePlugin()));
    }
}

void MainForm::updatePlguinButton()
{
    for (QAction* action : m_pluginButton->actions())
    {
        action->setChecked(action->data().toString() == m_sw->getActivePluginName());
    }
}

void MainForm::slotChangeActivePlugin()
{
    QAction* actionPlugin = static_cast<QAction*>(sender());

    // save current plugin settings
    saveSettings();

    QtConcurrent::run(m_sw, &SpellWork::setActivePlugin, actionPlugin->data().toString());
}

void MainForm::showProgressBar(int maximum)
{
    progressBar->show();
    progressBar->setMaximum(maximum);

    updatePlguinButton();
}

void MainForm::hideProgressBar()
{
    if (!progressBar->isHidden())
    {
        progressBar->reset();
        progressBar->hide();
    }
}

void MainForm::onPluginLoadingInit()
{
    setEnabled(false);
    updatePlguinButton();
}

void MainForm::onPluginLoadingFail()
{
    onPluginLoaded();

    QMessageBox::warning(this, "Warning", "Please check directories settings!", QMessageBox::StandardButton::Ok);
}

void MainForm::onPluginLoaded()
{
    setEnabled(true);
    updatePlguinButton();
    update();
}

void MainForm::setLocale(QString locale)
{
    QLabel* label = mainToolBar->findChild<QLabel*>("localeLable");

    if (!label)
    {
        label = new QLabel;
        label->setObjectName("localeLable");
        mainToolBar->addWidget(label);
    }

    locale = locale.isEmpty() ? QStringLiteral("enUS") : locale;

    label->setText(QString("%0<b>Locale: <font color=green>%1 </font><b>")
        .arg(QChar(QChar::Nbsp), 2, QChar(QChar::Nbsp))
        .arg(locale));
}

void MainForm::slotLinkClicked(const QUrl &url)
{
    QSWPage* page = static_cast<QSWPage*>(sender());

    qint32 id = url.toString().section('/', -1).toUInt();

    m_sw->showInfo(id, page->getPageId());

    switch (page->getPageId())
    {
        case QSW::PAGE_CLEFT:
        {
            m_sw->showInfo(getPage(QSW::PAGE_CRIGHT)->getSpellId(), QSW::PAGE_CRIGHT);
            m_sw->compare();
            break;
        }
        case QSW::PAGE_CRIGHT:
        {
            m_sw->showInfo(getPage(QSW::PAGE_CLEFT)->getSpellId(), QSW::PAGE_CLEFT);
            m_sw->compare();
            break;
        }
        default: break;
    }
}

void MainForm::slotModeShow()
{
    m_modeButton->setIcon(m_modeButton->actions().at(0)->icon());
    stackedWidget->setCurrentIndex(0);
}

void MainForm::slotModeCompare()
{
    m_modeButton->setIcon(m_modeButton->actions().at(1)->icon());
    stackedWidget->setCurrentIndex(1);
}

void MainForm::loadComboBoxes(EnumHash enums)
{
    ComboBoxHash items;

    quint32 i = 0;
    items[i] = ComboBoxPair(-1, "SpellFamilyName");
    Enumerator enumerator = enums["SpellFamily"];
    for (auto itr = enumerator.begin(); itr != enumerator.end(); ++itr)
        items[++i] = ComboBoxPair(itr.key(), QString("(%0) %1").arg(itr.key(), 3, 10, QChar('0')).arg(itr.value()));
    m_comboBoxModels[0]->setItems(items);

    i = 0;
    items.clear();
    items[i] = ComboBoxPair(-1, "SpellAura");
    
    enumerator = enums["SpellAura"];
    for (auto itr = enumerator.begin(); itr != enumerator.end(); ++itr)
        items[++i] = ComboBoxPair(itr.key(), QString("(%0) %1").arg(itr.key(), 3, 10, QChar('0')).arg(itr.value()));
    m_comboBoxModels[1]->setItems(items);

    i = 0;
    items.clear();
    items[i] = ComboBoxPair(-1, "SpellEffect");
    
    enumerator = enums["SpellEffect"];
    for (auto itr = enumerator.begin(); itr != enumerator.end(); ++itr)
        items[++i] = ComboBoxPair(itr.key(), QString("(%0) %1").arg(itr.key(), 3, 10, QChar('0')).arg(itr.value()));
    m_comboBoxModels[2]->setItems(items);

    i = 0;
    items.clear();
    items[i] = ComboBoxPair(-1, "Target A");

    enumerator = enums["Target"];
    for (auto itr = enumerator.begin(); itr != enumerator.end(); ++itr)
        items[++i] = ComboBoxPair(itr.key(), QString("(%0) %1").arg(itr.key(), 3, 10, QChar('0')).arg(itr.value()));
    m_comboBoxModels[3]->setItems(items);

    items[0] = ComboBoxPair(-1, "Target B");
    m_comboBoxModels[4]->setItems(items);
}

void MainForm::slotWov()
{
    WovWidget* wov = new WovWidget();
    wov->setWindowIcon(QIcon(":/qsw/resources/mangos.ico"));
    wov->setWindowTitle("WoW object view");
    wov->show();
}

void MainForm::slotAbout()
{
    AboutForm aboutView(this);
    aboutView.exec();
}

void MainForm::slotButtonSearch()
{
    emit signalSearch(0);
}

void MainForm::slotFilterSearch()
{
    emit signalSearch(1);
}

void MainForm::slotCompareSearch()
{
    if (!compareSpell_1->text().isEmpty() && !compareSpell_2->text().isEmpty())
    {
        m_sw->showInfo(compareSpell_1->text().toInt(), QSW::PAGE_CLEFT);
        m_sw->showInfo(compareSpell_2->text().toInt(), QSW::PAGE_CRIGHT);
        m_sw->compare();
    }
}

void MainForm::slotSearch(quint8 type)
{
    SpellListSortedModel* smodel = static_cast<SpellListSortedModel*>(SpellList->model());
    SpellListModel* model = static_cast<SpellListModel*>(smodel->sourceModel());
    delete model;
    model = nullptr;

    m_watcher->setFuture(QtConcurrent::run(m_sw, &SpellWork::search, type));
}

void MainForm::slotSearchResult()
{
    SearchResultWatcher* watcher = (SearchResultWatcher*)QObject::sender();

    EventList eventList = watcher->future().result();
    for (EventList::iterator itr = eventList.begin(); itr != eventList.end(); ++itr)
        QApplication::postEvent(this, *itr);
}

void MainForm::slotSearchFromList(const QModelIndex &index)
{
    QVariant var = SpellList->model()->data(SpellList->model()->index(index.row(), 0));
    m_sw->showInfo(var.toInt());
    SpellList->setFocus();
}

bool MainForm::event(QEvent* ev)
{
    switch (Event::Events(ev->type()))
    {
        case Event::EVENT_SEND_MODEL:
            {
                Event* m_ev = (Event*)ev;
                m_sortedModel->setSourceModel(m_ev->getValue(0).value<SpellListModel*>());
                SpellList->setColumnWidth(0, 40);
                SpellList->setColumnWidth(1, 150);
                return true;
            }
            break;
        case Event::EVENT_SEND_SPELL:
            {
                Event* m_ev = (Event*)ev;
                m_sw->showInfo(m_ev->getValue(0).toUInt());
                return true;
            }
            break;
        default:
            break;
    }

    return QWidget::event(ev);
}

ScriptFilter::ScriptFilter(QWidget* parent /* = nullptr */)
    : QWidget(parent)
{
    setupUi(this);
    setAutoFillBackground(true);

    connect(buttonAdd, SIGNAL(clicked(bool)), this, SLOT(slotAdd()));
    connect(buttonRemove, SIGNAL(clicked(bool)), this, SLOT(slotRemove()));
    connect(buttonClear, SIGNAL(clicked(bool)), this, SLOT(slotClear()));

    m_model = new QStringListModel(m_bookmarks);
    listView->setModel(m_model);
}

void ScriptFilter::slotAdd()
{
    addBookmark(scriptEdit->toPlainText());
}

void ScriptFilter::slotRemove()
{
    removeBookmark(listView->currentIndex().row());
}

void ScriptFilter::slotClear()
{
    clearBookmarks();
}

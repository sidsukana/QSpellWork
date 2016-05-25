#include <QtConcurrentRun>
#include <QFuture>
#include <QTime>
#include <QStandardItemModel>
#include <QStringListModel>
#include <QDir>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QClipboard>

#include "MainForm.h"
#include "AboutForm.h"
#include "SettingsForm.h"
#include "SWModels.h"
#include "Defines.h"
#include "WovWidget.h"

MainForm::MainForm(QWidget* parent)
    : QMainWindow(parent)
{
    QTime m_time;
    m_time.start();

    setupUi(this);

    m_advancedFilterWidget = new AdvancedFilterWidget(page);
    gridLayout_4->addWidget(m_advancedFilterWidget, 0, 1, 2, 1);
    m_advancedFilterWidget->hide();

    m_enums = new SWEnums();
    m_sw = new SWObject(this);
    m_watcher = new SearchResultWatcher();
    connect(m_watcher, SIGNAL(finished()), this, SLOT(slotSearchResult()));

    m_sortedModel = new SpellListSortedModel(this);
    m_sortedModel->setDynamicSortFilter(true);
    SpellList->setModel(m_sortedModel);

    loadComboBoxes();
    detectLocale();
    createModeButton();
    initializeCompleter();

    mainToolBar->addSeparator();
    mainToolBar->addWidget(m_modeButton);
    mainToolBar->addSeparator();
    m_actionRegExp = mainToolBar->addAction(QIcon(":/qsw/resources/regExp.png"), "<font color=red>Off</font>");
    m_actionRegExp->setCheckable(true);
    mainToolBar->addSeparator();
    m_actionSettings = mainToolBar->addAction(QIcon(":/qsw/resources/cog.png"), "Settings");
    mainToolBar->addSeparator();
    m_actionWov = mainToolBar->addAction(QIcon(":/qsw/resources/wand.png"), "Wov");
    mainToolBar->addSeparator();
    m_actionAbout = mainToolBar->addAction(QIcon(":/qsw/resources/information.png"), "About");

    QAction* selectedAction = new QAction(this);
    selectedAction->setShortcut(QKeySequence::MoveToPreviousLine);
    selectedAction->setVisible(false);
    connect(selectedAction, SIGNAL(triggered()), this, SLOT(slotPrevRow()));
    SpellList->addAction(selectedAction);

    selectedAction = new QAction(this);
    selectedAction->setShortcut(QKeySequence::MoveToNextLine);
    selectedAction->setVisible(false);
    connect(selectedAction, SIGNAL(triggered()), this, SLOT(slotNextRow()));
    SpellList->addAction(selectedAction);

    QAction* copyAction = new QAction("Copy all", this);
    connect(copyAction, SIGNAL(triggered()), this, SLOT(slotCopyAll()));
    SpellList->addAction(copyAction);

    connect(adFilterButton, SIGNAL(clicked()), this, SLOT(slotAdvancedFilter()));

    // List search connection
    connect(SpellList, SIGNAL(clicked(QModelIndex)), this, SLOT(slotSearchFromList(QModelIndex)));

    // Main search connections
    connect(findLine_e1, SIGNAL(returnPressed()), this, SLOT(slotButtonSearch()));
    connect(findLine_e3, SIGNAL(returnPressed()), this, SLOT(slotButtonSearch()));

    // Menu connections
    connect(m_actionAbout, SIGNAL(triggered()), this, SLOT(slotAbout()));

    // RegExp connection
    connect(m_actionRegExp, SIGNAL(triggered()), this, SLOT(slotRegExp()));

    // Settings form connection
    connect(m_actionSettings, SIGNAL(triggered()), this, SLOT(slotSettings()));

    // Wov form connection
    connect(m_actionWov, SIGNAL(triggered()), this, SLOT(slotWov()));

    // Filter search connections
    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotFilterSearch()));
    connect(comboBox_2, SIGNAL(currentIndexChanged(int)), this, SLOT(slotFilterSearch()));
    connect(comboBox_3, SIGNAL(currentIndexChanged(int)), this, SLOT(slotFilterSearch()));
    connect(comboBox_4, SIGNAL(currentIndexChanged(int)), this, SLOT(slotFilterSearch()));
    connect(comboBox_5, SIGNAL(currentIndexChanged(int)), this, SLOT(slotFilterSearch()));

    // Search connection
    connect(this, SIGNAL(signalSearch(quint8)), this, SLOT(slotSearch(quint8)));

    connect(m_advancedFilterWidget->pushButton, SIGNAL(clicked()), this, SLOT(slotAdvancedApply()));

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

    // Load settings at end
    loadSettings();
}

MainForm::~MainForm()
{
    saveSettings();
}

void MainForm::slotSettings()
{
    SettingsForm settingsForm(this);
    settingsForm.exec();
}

void MainForm::slotAdvancedFilter()
{
    if (m_advancedFilterWidget->isVisible())
    {
        webView1->show();
        m_advancedFilterWidget->hide();
    }
    else
    {
        webView1->hide();
        m_advancedFilterWidget->show();
    }
}

void MainForm::slotAdvancedApply()
{
    emit signalSearch(3);
}

void MainForm::loadSettings()
{
    QSW::settings().beginGroup("Global");
    setRegExp(QSW::settings().value("RegExp", false).toBool());
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
    int size = QSW::settings().beginReadArray("Bookmarks");
    for (auto i = 0; i < size; ++i) {
        QSW::settings().setArrayIndex(i);
        m_advancedFilterWidget->addBookmark(QSW::settings().value("filter").toString());
    }
    QSW::settings().endArray();
    QSW::settings().endGroup();
}

void MainForm::saveSettings()
{
    QSW::settings().beginGroup("Global");
    QSW::settings().setValue("RegExp", isRegExp());
    QSW::settings().endGroup();

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
    QStringList bookmarks = m_advancedFilterWidget->getBookmarks();
    QSW::settings().beginWriteArray("Bookmarks", bookmarks.size());
    for (auto i = 0; i < bookmarks.size(); ++i) {
        QSW::settings().setArrayIndex(i);
        QSW::settings().setValue("filter", bookmarks.at(i));
    }
    QSW::settings().endArray();
    QSW::settings().endGroup();
}

void MainForm::slotPrevRow()
{
    SpellList->selectRow(SpellList->currentIndex().row() - 1);

    QVariant var = SpellList->model()->data(SpellList->model()->index(SpellList->currentIndex().row(), 0));
    m_sw->showInfo(Spell::getRecord(var.toInt(), true));
}

void MainForm::slotNextRow()
{
    SpellList->selectRow(SpellList->currentIndex().row() + 1);

    QVariant var = SpellList->model()->data(SpellList->model()->index(SpellList->currentIndex().row(), 0));
    m_sw->showInfo(Spell::getRecord(var.toInt(), true));
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

void MainForm::initializeCompleter()
{
    QSet<QString> names;

    for (quint32 i = 0; i < Spell::getHeader()->recordCount; ++i)
    {
        if (const Spell::entry* spellInfo = Spell::getRecord(i))
        {
            QString sName = spellInfo->name();
            if (names.find(sName) == names.end())
                names << sName;
        }
    }

    QCompleter* completer = new QCompleter(names.toList(), this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    findLine_e1->setCompleter(completer);
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

void MainForm::detectLocale()
{
    if (const Spell::entry* spellInfo = Spell::getRecord(1, true))
    {
        m_sw->setMetaEnum("LocalesDBC");
        for (quint8 i = 0; i < m_sw->getMetaEnum().keyCount(); ++i)
        {
            if (spellInfo->nameOffset[i])
            {
                QSW::Locale = i;
                QLabel* label = new QLabel;
                label->setText(QString("%0<b>DBC Locale: <font color=green>%1 </font><b>")
                    .arg(QChar(QChar::Nbsp), 2, QChar(QChar::Nbsp))
                    .arg(m_sw->getMetaEnum().valueToKey(m_sw->getMetaEnum().value(i))));
                mainToolBar->addWidget(label);
                break;
            }
        }
    }
}

void MainForm::slotLinkClicked(const QUrl &url)
{
    QSWPage* page = static_cast<QSWPage*>(sender());

    qint32 id = url.toString().section('/', -1).toUInt();

    m_sw->showInfo(Spell::getRecord(id, true), page->getPageId());

    switch (page->getPageId())
    {
        case QSW::PAGE_CLEFT:
        {
            m_sw->showInfo(Spell::getRecord(getPage(QSW::PAGE_CRIGHT)->getSpellId(), true), QSW::PAGE_CRIGHT);
            m_sw->compare();
            break;
        }
        case QSW::PAGE_CRIGHT:
        {
            m_sw->showInfo(Spell::getRecord(getPage(QSW::PAGE_CLEFT)->getSpellId(), true), QSW::PAGE_CLEFT);
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

void MainForm::loadComboBoxes()
{
    comboBox->clear();
    comboBox->setModel(new QStandardItemModel);
    comboBox->insertItem(0, "SpellFamilyName", 0);

    EnumIterator itr(m_enums->getSpellFamilies());
    quint32 i = 0;
    while (itr.hasNext())
    {
        ++i;
        itr.next();
        comboBox->insertItem(i, QString("(%0) %1")
            .arg(itr.key(), 3, 10, QChar('0'))
            .arg(itr.value()), itr.key());
    }

    comboBox_2->clear();
    comboBox_2->setModel(new QStandardItemModel);
    comboBox_2->insertItem(0, "Aura", 0);
    
    itr = EnumIterator(m_enums->getSpellAuras());
    i = 0;
    while (itr.hasNext())
    {
        ++i;
        itr.next();
        comboBox_2->insertItem(i, QString("(%0) %1")
            .arg(itr.key(), 3, 10, QChar('0'))
            .arg(itr.value()), itr.key());
    }

    comboBox_3->clear();
    comboBox_3->setModel(new QStandardItemModel);
    comboBox_3->insertItem(0, "Effect", 0);
    
    itr = EnumIterator(m_enums->getSpellEffects());
    i = 0;
    while (itr.hasNext())
    {
        ++i;
        itr.next();
        comboBox_3->insertItem(i, QString("(%0) %1")
            .arg(itr.key(), 3, 10, QChar('0'))
            .arg(itr.value()), itr.key());
    }

    comboBox_4->clear();
    comboBox_4->setModel(new QStandardItemModel);
    comboBox_4->insertItem(0, "Target A", 0);

    comboBox_5->clear();
    comboBox_5->setModel(new QStandardItemModel);
    comboBox_5->insertItem(0, "Target B", 0);

    itr = EnumIterator(m_enums->getTargets());
    i = 0;
    while (itr.hasNext())
    {
        ++i;
        itr.next();
        comboBox_4->insertItem(i, QString("(%0) %1")
            .arg(itr.key(), 3, 10, QChar('0'))
            .arg(itr.value()), itr.key());

        comboBox_5->insertItem(i, QString("(%0) %1")
            .arg(itr.key(), 3, 10, QChar('0'))
            .arg(itr.value()), itr.key());
    }
}

void MainForm::slotRegExp()
{
    if (isRegExp())
    {
        m_actionRegExp->setChecked(true);
        m_actionRegExp->setIcon(QIcon(":/qsw/resources/regExp.png"));
        m_actionRegExp->setText("<font color=green>On</font>");
    }
    else
    {
        m_actionRegExp->setChecked(false);
        m_actionRegExp->setIcon(QIcon(":/qsw/resources/regExp.png"));
        m_actionRegExp->setText("<font color=red>Off</font>");
    }

    m_sw->showInfo(Spell::getRecord(webView1->url().path().remove(0, 1).toInt(), true));

    bool compared[2] = { false, false };
    if (const Spell::entry* spellInfo = Spell::getRecord(webView2->url().path().remove(0, 1).toInt(), true))
    {
        m_sw->showInfo(spellInfo, QSW::PAGE_CLEFT);
        compared[0] = true;
    }

    if (const Spell::entry* spellInfo = Spell::getRecord(webView3->url().path().remove(0, 1).toInt(), true))
    {
        m_sw->showInfo(spellInfo, QSW::PAGE_CRIGHT);
        compared[1] = true;
    }

    if (compared[0] || compared[1])
        m_sw->compare();
}

void MainForm::slotWov()
{
    WovWidget* wov = new WovWidget();
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
        m_sw->showInfo(Spell::getRecord(compareSpell_1->text().toInt(), true), QSW::PAGE_CLEFT);
        m_sw->showInfo(Spell::getRecord(compareSpell_2->text().toInt(), true), QSW::PAGE_CRIGHT);
        m_sw->compare();
    }
}

void MainForm::slotSearch(quint8 type)
{
    SpellListSortedModel* smodel = static_cast<SpellListSortedModel*>(SpellList->model());
    SpellListModel* model = static_cast<SpellListModel*>(smodel->sourceModel());
    delete model;
    model = nullptr;

    m_sw->setType(type);

    m_watcher->setFuture(QtConcurrent::run<EventList, SWObject>(m_sw, &SWObject::search));
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
    m_sw->showInfo(Spell::getRecord(var.toInt(), true));
}

bool MainForm::event(QEvent* ev)
{
    switch (Event::Events(ev->type()))
    {
        case Event::EVENT_SEND_MODEL:
            {
                Event* m_ev = (Event*)ev;
                m_sortedModel->sourceModel()->deleteLater();
                m_sortedModel->setSourceModel(m_ev->getValue(0).value<SpellListModel*>());
                SpellList->setColumnWidth(0, 40);
                SpellList->setColumnWidth(1, 150);
                return true;
            }
            break;
        case Event::EVENT_SEND_SPELL:
            {
                Event* m_ev = (Event*)ev;
                m_sw->showInfo(Spell::getRecord(m_ev->getValue(0).toUInt(), true));
                return true;
            }
            break;
        default:
            break;
    }

    return QWidget::event(ev);
}

AdvancedFilterWidget::AdvancedFilterWidget(QWidget* parent /* = nullptr */)
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

void AdvancedFilterWidget::slotAdd()
{
    addBookmark(textEdit->toPlainText());
}

void AdvancedFilterWidget::slotRemove()
{
    removeBookmark(listView->currentIndex().row());
}

void AdvancedFilterWidget::slotClear()
{
    clearBookmarks();
}

#include "SWMainForm.h"
#include "SWAboutForm.h"
#include "SWUpdateForm.h"

#include <QtCore/QtConcurrentRun>
#include <QtCore/QTime>

#include <QtGui/QMessageBox>

SWMainForm::SWMainForm(QWidget* parent)
    : QMainWindow(parent)
{
    QTime m_time;
    m_time.start();

    setupUi(this);

    m_sw = new SWObject(this);

    m_sortedModel = new SpellListSortedModel(this);
    m_sortedModel->setDynamicSortFilter(true);
    SpellList->setModel(m_sortedModel);

    loadComboBoxes();
    detectLocale();
    createModeButton();

    mainToolBar->addSeparator();
    mainToolBar->addWidget(m_modeButton);
    mainToolBar->addSeparator();
    m_regExp = mainToolBar->addAction(QIcon(":/SpellWork/Recources/regExp.png"), "<font color=red>Off</font>");
    mainToolBar->addSeparator();
    m_about = mainToolBar->addAction(QIcon(":/SpellWork/Recources/about.png"), "About");
    mainToolBar->addSeparator();
    m_update = mainToolBar->addAction(QIcon(":/SpellWork/Recources/update.png"), "Update");

    webView1->pageAction(QWebPage::Copy)->setShortcut(QKeySequence::Copy);
    webView2->pageAction(QWebPage::Copy)->setShortcut(QKeySequence::Copy);
    webView3->pageAction(QWebPage::Copy)->setShortcut(QKeySequence::Copy);

    initializeCompleter();

    QAction* selectedAction = new QAction(this);
    selectedAction->setShortcut(QKeySequence::MoveToPreviousLine);
    connect(selectedAction, SIGNAL(triggered()), this, SLOT(slotPrevRow()));
    SpellList->addAction(selectedAction);

    selectedAction = new QAction(this);
    selectedAction->setShortcut(QKeySequence::MoveToNextLine);
    connect(selectedAction, SIGNAL(triggered()), this, SLOT(slotNextRow()));
    SpellList->addAction(selectedAction);

    // List search connection
    connect(SpellList, SIGNAL(clicked(QModelIndex)), this, SLOT(slotSearchFromList(QModelIndex)));

    // Main search connections
    connect(findLine_e1, SIGNAL(returnPressed()), this, SLOT(slotButtonSearch()));
    connect(findLine_e2, SIGNAL(returnPressed()), this, SLOT(slotButtonSearch()));
    connect(findLine_e3, SIGNAL(returnPressed()), this, SLOT(slotButtonSearch()));

    // Update connect
    connect(m_update, SIGNAL(triggered()), this, SLOT(slotUpdate()));

    // Menu connections
    connect(m_about, SIGNAL(triggered()), this, SLOT(slotAbout()));

    // RegExp connection
    connect(m_regExp, SIGNAL(triggered()), this, SLOT(slotRegExp()));

    // Filter search connections
    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotFilterSearch()));
    connect(comboBox_2, SIGNAL(currentIndexChanged(int)), this, SLOT(slotFilterSearch()));
    connect(comboBox_3, SIGNAL(currentIndexChanged(int)), this, SLOT(slotFilterSearch()));
    connect(comboBox_4, SIGNAL(currentIndexChanged(int)), this, SLOT(slotFilterSearch()));
    connect(comboBox_5, SIGNAL(currentIndexChanged(int)), this, SLOT(slotFilterSearch()));
    connect(adLine1, SIGNAL(returnPressed()), this, SLOT(slotFilterSearch()));
    connect(adLine2, SIGNAL(returnPressed()), this, SLOT(slotFilterSearch()));

    // Search connection
    connect(this, SIGNAL(signalSearch(quint8)), this, SLOT(slotSearch(quint8)));

    connect(compareSpell_1, SIGNAL(returnPressed()), this, SLOT(slotCompareSearch()));
    connect(compareSpell_2, SIGNAL(returnPressed()), this, SLOT(slotCompareSearch()));

    connect(webView1, SIGNAL(linkClicked(QUrl)), this, SLOT(slotLinkClicked(QUrl)));
    connect(webView2, SIGNAL(linkClicked(QUrl)), this, SLOT(slotLinkClicked(QUrl)));
    connect(webView3, SIGNAL(linkClicked(QUrl)), this, SLOT(slotLinkClicked(QUrl)));

    webView1->setHtml(QString("Load time: %0 ms").arg(m_time.elapsed()));
}

SWMainForm::~SWMainForm()
{
}

void SWMainForm::slotUpdate()
{
    SWUpdateForm* updateForm = new SWUpdateForm();
}

void SWMainForm::slotPrevRow()
{
    SpellList->selectRow(SpellList->currentIndex().row() - 1);

    QVariant var = SpellList->model()->data(SpellList->model()->index(SpellList->currentIndex().row(), 0));

    if (SpellEntry const* spellInfo = sSpellStore.LookupEntry(var.toInt()))
        m_sw->showInfo(spellInfo);
}

void SWMainForm::slotNextRow()
{
    SpellList->selectRow(SpellList->currentIndex().row() + 1);

    QVariant var = SpellList->model()->data(SpellList->model()->index(SpellList->currentIndex().row(), 0));

    if (SpellEntry const* spellInfo = sSpellStore.LookupEntry(var.toInt()))
        m_sw->showInfo(spellInfo);
}

void SWMainForm::initializeCompleter()
{
    QStringList names;

    for (quint32 i = 0; i < sSpellStore.GetNumRows(); i++)
    {
        SpellEntry const* spellInfo = sSpellStore.LookupEntry(i);
        if (spellInfo)
        {
            QString sName = QString::fromUtf8(spellInfo->SpellName[Locale]);
            if (!names.contains(sName, Qt::CaseInsensitive))
                names << sName;
        }
    }

    QCompleter* completer = new QCompleter(names, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    findLine_e1->setCompleter(completer);
}

void SWMainForm::createModeButton()
{   
    QAction* actionShow = new QAction(QIcon(":/SpellWork/Recources/show.png"), "Show", this);
    QAction* actionCompare = new QAction(QIcon(":/SpellWork/Recources/compare.png"), "Compare", this);
    QAction* actionDatabaase = new QAction(QIcon(":/SpellWork/Recources/database.png"), "Database", this);

    connect(actionShow, SIGNAL(triggered()), this, SLOT(slotModeShow()));
    connect(actionCompare, SIGNAL(triggered()), this, SLOT(slotModeCompare()));
    connect(actionDatabaase, SIGNAL(triggered()), this, SLOT(slotModeDatabase()));

    m_modeButton = new QToolButton(this);
    m_modeButton->setText("Mode");
    m_modeButton->setIcon(actionShow->icon());
    m_modeButton->setPopupMode(QToolButton::InstantPopup);

    m_modeButton->addAction(actionShow);
    m_modeButton->addAction(actionCompare);
    m_modeButton->addAction(actionDatabaase);
}

void SWMainForm::detectLocale()
{
    SpellEntry const* spellInfo = sSpellStore.LookupEntry(1);

    if (!spellInfo)
        return;

    m_sw->setMetaEnum("LocalesDBC");
    for (quint8 i = 0; i < m_sw->getMetaEnum().keyCount(); i++)
    {
        if (!QString::fromUtf8(spellInfo->SpellName[i]).isEmpty())
        {
            Locale = i;
            QLabel* label = new QLabel;
            label->setText(QString("%0<b>DBC Locale: <font color=green>%1 </font><b>")
                .arg(QChar(QChar::Nbsp), 2, QChar(QChar::Nbsp))
                .arg(m_sw->getMetaEnum().valueToKey(m_sw->getMetaEnum().value(i))));
            mainToolBar->addWidget(label);
            break;
        }
    }
}

void SWMainForm::slotLinkClicked(const QUrl &url)
{
    QWebView* webView = static_cast<QWebView*>(sender());

    qint32 browserId = webView->objectName().at(7).digitValue();
    qint32 id = url.toString().section('/', -1).toInt();

    switch (browserId)
    {
        case 1:
        {
            if (SpellEntry const* spellInfo = sSpellStore.LookupEntry(id))
                m_sw->showInfo(spellInfo, browserId);
            break;
        }
        case 2:
        {
            if (SpellEntry const* spellInfo = sSpellStore.LookupEntry(id))
                m_sw->showInfo(spellInfo, browserId);

            qint32 id3 = webView3->url().toString().section('/', -1).toInt();
            if (SpellEntry const* spellInfo = sSpellStore.LookupEntry(id3))
                m_sw->showInfo(spellInfo, 3);

            m_sw->compare();
            break;
        }
        case 3:
        {
            if (SpellEntry const* spellInfo = sSpellStore.LookupEntry(id))
                m_sw->showInfo(spellInfo, browserId);

            qint32 id2 = webView2->url().toString().section('/', -1).toInt();
            if (SpellEntry const* spellInfo = sSpellStore.LookupEntry(id2))
                m_sw->showInfo(spellInfo, 2);

            m_sw->compare();
            break;
        }
        default: break;
    }
}

void SWMainForm::slotModeShow()
{
    stackedWidget->setCurrentIndex(0);
}

void SWMainForm::slotModeCompare()
{
    stackedWidget->setCurrentIndex(1);
}

void SWMainForm::slotModeDatabase()
{
    stackedWidget->setCurrentIndex(2);

    connect(dbConnectButton, SIGNAL(clicked()), this, SLOT(slotConnectToDatabase()));
    connect(nextButton2, SIGNAL(clicked()), this, SLOT(slotSpellTable()));
}

void SWMainForm::slotSpellTable()
{
    QSqlTableModel* sqlModel = new QSqlTableModel(this, QSqlDatabase::database("DB"));

    sqlModel->setTable("spell_dbc");
    sqlModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    sqlModel->select();

    spellDbcView->setModel(sqlModel);

    stackedWidget->setCurrentIndex(4);
}

void SWMainForm::slotConnectToDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", "DB");
    db.setHostName(hostname->text());
    db.setUserName(username->text());
    db.setPassword(password->text());
    db.setDatabaseName(database->text());
    
    if (!db.open())
    {
        QMessageBox::warning(this, "MySQL Error!", db.lastError().text());
        return;
    }

    QSqlQuery result(QSqlDatabase::database("DB"));
    result.exec("SHOW FULL FIELDS FROM `spell_dbc`");

    DNDModel* sqlModel = new DNDModel();
    DNDModel* dbcModel = new DNDModel();
    
    connect(sqlModel, SIGNAL(signalDataDropped(const QString&, const QString&)), this, SLOT(slotDataDropped(const QString &, const QString&)));
    connect(dbcModel, SIGNAL(signalDataDropped(const QString&, const QString&)), this, SLOT(slotDataDropped(const QString &, const QString&)));

    sqlModel->setViewerName("sql");
    dbcModel->setViewerName("dbc");

    while (result.next())
    {
        sqlModel->append(result.value(0).toString());
    }

    sqlFieldsView->setModel(sqlModel);

    SpellEntry const* spellInfo = sSpellStore.LookupEntry(1);

    for (quint8 i = 0; i < MAX_STRUCT; i++)
        dbcModel->append(SpellStruct[i]);

    dbcFieldsView->setModel(dbcModel);

    stackedWidget->setCurrentIndex(3);
}

void SWMainForm::loadComboBoxes()
{
    comboBox->clear();
    comboBox->insertItem(-1, "SpellFamilyName");
    m_sw->setMetaEnum("SpellFamilyNames");
    for (quint16 i = 0; i < m_sw->getMetaEnum().keyCount(); i++)
        comboBox->insertItem(i, QString("(%0) %1")
            .arg(m_sw->getMetaEnum().value(i), 3, 10, QChar('0'))
            .arg(m_sw->getMetaEnum().valueToKey(m_sw->getMetaEnum().value(i))));

    comboBox_2->clear();
    comboBox_2->insertItem(-1, "Aura");
    m_sw->setMetaEnum("AuraType");
    for (quint16 i = 0; i < m_sw->getMetaEnum().keyCount(); i++)
        comboBox_2->insertItem(i, QString("(%0) %1")
            .arg(m_sw->getMetaEnum().value(i), 3, 10, QChar('0'))
            .arg(m_sw->getMetaEnum().valueToKey(m_sw->getMetaEnum().value(i))));

    comboBox_3->clear();
    comboBox_3->insertItem(-1, "Effect");
    m_sw->setMetaEnum("Effects");
    for (quint16 i = 0; i < m_sw->getMetaEnum().keyCount(); i++)
        comboBox_3->insertItem(i, QString("(%0) %1")
            .arg(m_sw->getMetaEnum().value(i), 3, 10, QChar('0'))
            .arg(m_sw->getMetaEnum().valueToKey(m_sw->getMetaEnum().value(i))));

    comboBox_4->clear();
    m_sw->setMetaEnum("Targets");
    comboBox_4->insertItem(-1, "Target A");
    for (quint16 i = 0; i < m_sw->getMetaEnum().keyCount(); i++)
        comboBox_4->insertItem(i, QString("(%0) %1")
            .arg(m_sw->getMetaEnum().value(i), 3, 10, QChar('0'))
            .arg(m_sw->getMetaEnum().key(i)));

    comboBox_5->clear();
    comboBox_5->insertItem(-1, "Target B");
    for (quint16 i = 0; i < m_sw->getMetaEnum().keyCount(); i++)
        comboBox_5->insertItem(i, QString("(%0) %1")
            .arg(m_sw->getMetaEnum().value(i), 3, 10, QChar('0'))
            .arg(m_sw->getMetaEnum().key(i)));

    adBox1->clear();
    adBox2->clear();
    for (quint16 i = 0; i < MAX_STRUCT; i++)
    {
        adBox1->insertItem(i, QString("%0").arg(SpellStruct[i]));
        adBox2->insertItem(i, QString("%0").arg(SpellStruct[i]));
    }
}

void SWMainForm::slotRegExp()
{
    if (!m_sw->isRegExp())
    {
        m_sw->setRegExp(true);
        m_regExp->setIcon(QIcon(":/SpellWork/Recources/regExp.png"));
        m_regExp->setText("<font color=green>On</font>");
    }
    else
    {
        m_sw->setRegExp(false);
        m_regExp->setIcon(QIcon(":/SpellWork/Recources/regExp.png"));
        m_regExp->setText("<font color=red>Off</font>");
    }

    if (SpellEntry const* spellInfo = sSpellStore.LookupEntry(webView1->url().path().remove(0, 1).toInt()))
        m_sw->showInfo(spellInfo);
}

void SWMainForm::slotAbout()
{
    new SWAboutForm;
}

void SWMainForm::slotButtonSearch()
{
    emit signalSearch(0);
}

void SWMainForm::slotFilterSearch()
{
    emit signalSearch(1);
}

void SWMainForm::slotCompareSearch()
{
    emit signalSearch(2);
}

void SWMainForm::slotSearch(quint8 type)
{
    if (type != 2)
    {
        SpellListSortedModel* smodel = static_cast<SpellListSortedModel*>(SpellList->model());
        SpellListModel* model = static_cast<SpellListModel*>(smodel->sourceModel());
        if (model)
            delete model;
    }

    m_sw->setType(type);

    QtConcurrent::run(m_sw, &SWObject::search);
}

void SWMainForm::slotSearchFromList(const QModelIndex &index)
{
    QVariant var = SpellList->model()->data(SpellList->model()->index(index.row(), 0));

    if (SpellEntry const* spellInfo = sSpellStore.LookupEntry(var.toInt()))
        m_sw->showInfo(spellInfo);
}

bool SWMainForm::event(QEvent* ev)
{
    switch (ev->type())
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
            m_sw->showInfo(m_ev->getValue(0).value<const SpellEntry*>());
            return true;
        }
        break;
        case Event::EVENT_SEND_CSPELL:
        {
            Event* m_ev = (Event*)ev;
            m_sw->showInfo(m_ev->getValue(0).value<const SpellEntry*>(), 2);
            m_sw->showInfo(m_ev->getValue(1).value<const SpellEntry*>(), 3);
            m_sw->compare();
            return true;
        }
        break;
        default:
            break;
    }
    

    return QWidget::event(ev);
}

void SWMainForm::slotDataDropped(const QString &curData, const QString &newData)
{
    if (curData.contains('=') || newData.contains('='))
        return;

    DNDModel* receiveModel = static_cast<DNDModel*>(sender());

    if (receiveModel)
    {
        // dropped to sql viewer
        if (receiveModel->getViewerName() == "sql")
        {
            receiveModel->setData(receiveModel->index(receiveModel->getDataRow(curData), 0, QModelIndex()), curData + " = " + newData);
            if (DNDModel* dbcModel = (DNDModel*)dbcFieldsView->model())
                dbcModel->setData(dbcModel->index(dbcModel->getDataRow(newData), 0, QModelIndex()), newData + " = " + curData);
            m_relations[curData] = newData;
        }
        // dropped to dbc viewer
        else
        {
            receiveModel->setData(receiveModel->index(receiveModel->getDataRow(curData), 0, QModelIndex()), curData + " = " + newData);
            if (DNDModel* sqlModel = (DNDModel*)sqlFieldsView->model())
                sqlModel->setData(sqlModel->index(sqlModel->getDataRow(newData), 0, QModelIndex()), newData + " = " + curData);
            m_relations[newData] = curData;
        }
    }
}
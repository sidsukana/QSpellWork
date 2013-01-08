#include "SWMainForm.h"
#include "SWAboutForm.h"
#include "SWModels.h"
#include "SWSearch.h"

#include <QtConcurrent/QtConcurrentRun>
#include <QtCore/QTime>
#include <QtGui/QStandardItemModel>

#include <QtWidgets/QMessageBox>

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
    createModeButton();
    initializeCompleter();

    mainToolBar->addSeparator();
    mainToolBar->addWidget(m_modeButton);
    mainToolBar->addSeparator();
    m_regExp = mainToolBar->addAction(QIcon(":/SpellWork/Recources/regExp.png"), "<font color=red>Off</font>");
    m_regExp->setCheckable(true);
    mainToolBar->addSeparator();
    m_about = mainToolBar->addAction(QIcon(":/SpellWork/Recources/about.png"), "About");
    
    webView1->pageAction(QWebPage::Copy)->setShortcut(QKeySequence::Copy);
    webView2->pageAction(QWebPage::Copy)->setShortcut(QKeySequence::Copy);
    webView3->pageAction(QWebPage::Copy)->setShortcut(QKeySequence::Copy);

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

    // Load settings at end
    loadSettings();
}

SWMainForm::~SWMainForm()
{
    saveSettings();
}

void SWMainForm::loadSettings()
{
    m_settings = new QSettings("QSW.ini", QSettings::IniFormat, this);
    m_settings->sync();

    // Global
    setRegExp(m_settings->value("Global/RegExp", false).toBool());

    // Search and filters
    findLine_e1->setText(m_settings->value("Search/IdOrName", "").toString());
    findLine_e2->setText(m_settings->value("Search/Description", "").toString());
    findLine_e3->setText(m_settings->value("Search/IconId", "").toString());
    comboBox->setCurrentIndex(m_settings->value("Search/SpellFamilyIndex", 0).toInt());
    comboBox_2->setCurrentIndex(m_settings->value("Search/EffectIndex", 0).toInt());
    comboBox_3->setCurrentIndex(m_settings->value("Search/AuraIndex", 0).toInt());
    comboBox_4->setCurrentIndex(m_settings->value("Search/TargetAIndex", 0).toInt());
    comboBox_5->setCurrentIndex(m_settings->value("Search/TargetBIndex", 0).toInt());

    // Database
    hostname->setText(m_settings->value("Database/Hostname", "localhost").toString());
    database->setText(m_settings->value("Database/Database", "").toString());
    username->setText(m_settings->value("Database/Username", "root").toString());
    password->setText(m_settings->value("Database/Password", "").toString());

    if (!findLine_e1->text().isEmpty())
        slotButtonSearch();
}

void SWMainForm::saveSettings()
{
    // Global
    m_settings->setValue("Global/RegExp", isRegExp());

    // Search and filters
    m_settings->setValue("Search/IdOrName", findLine_e1->text());
    m_settings->setValue("Search/Description", findLine_e2->text());
    m_settings->setValue("Search/IconId", findLine_e3->text());
    m_settings->setValue("Search/SpellFamilyIndex", comboBox->currentIndex());
    m_settings->setValue("Search/EffectIndex", comboBox_2->currentIndex());
    m_settings->setValue("Search/AuraIndex", comboBox_3->currentIndex());
    m_settings->setValue("Search/TargetAIndex", comboBox_4->currentIndex());
    m_settings->setValue("Search/TargetBIndex", comboBox_5->currentIndex());

    // Database
    m_settings->setValue("Database/Hostname", hostname->text());
    m_settings->setValue("Database/Database", database->text());
    m_settings->setValue("Database/Username", username->text());
    m_settings->setValue("Database/Password", password->text());
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
    QSet<QString> names;

    for (quint32 i = 0; i < sSpellStore.GetNumRows(); ++i)
    {
        SpellEntry const* spellInfo = sSpellStore.LookupEntry(i);
        if (spellInfo)
        {
            QString sName = QString::fromUtf8(spellInfo->SpellName);
            if (names.find(sName) == names.end())
                names << sName;
        }
    }

    QCompleter* completer = new QCompleter(names.toList(), this);
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

    connect(m_modeButton, SIGNAL(triggered(QAction*)), this, SLOT(slotSetMode(QAction*)));
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
    m_modeButton->setIcon(m_modeButton->actions().at(0)->icon());
    stackedWidget->setCurrentIndex(0);
}

void SWMainForm::slotModeCompare()
{
    m_modeButton->setIcon(m_modeButton->actions().at(1)->icon());
    stackedWidget->setCurrentIndex(1);
}

void SWMainForm::slotModeDatabase()
{
    m_modeButton->setIcon(m_modeButton->actions().at(2)->icon());
    stackedWidget->setCurrentIndex(2);

    connect(nextButton3, SIGNAL(clicked()), this, SLOT(slotConnectToDatabase()));
    connect(nextButton4, SIGNAL(clicked()), this, SLOT(slotSpellTable()));
}

void SWMainForm::slotSpellTable()
{
    QSqlTableModel* sqlModel = new QSqlTableModel(this, QSqlDatabase::database("DB"));

    sqlModel->setTable("spell_dbc");
    sqlModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    sqlModel->select();

    spellDbcView->setItemDelegate(new SpellDelegate(this));
    spellDbcView->setModel(sqlModel);

    for (qint32 i = 0; i < sqlModel->columnCount(); ++i)
        spellDbcView->hideColumn(i);

    RelationList relationList = ((RelationModel*)fieldsView->model())->getRelations();
    for (RelationList::iterator itr = relationList.begin(); itr != relationList.end(); ++itr)
        if (!(*itr)->dbcField.isEmpty())
            spellDbcView->showColumn(sqlModel->fieldIndex((*itr)->sqlField));

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

    RelationModel* model = new RelationModel(fieldsView);
    connect(relateButton4, SIGNAL(clicked()), this, SLOT(slotAutoRelate()));
    connect(resetButton4, SIGNAL(clicked()), this, SLOT(slotResetRelate()));

    while (result.next())
    {
        RelationItem* item = new RelationItem();
        item->sqlField = result.value(0).toString();
        model->appendRelation(item);
    }

    model->appendDbcField("");
    for (qint32 i = 1; i < adBox1->count(); ++i)
        model->appendDbcField(adBox1->itemText(i));

    fieldsView->setItemDelegate(new RelationDelegate);
    fieldsView->setModel(model);

    stackedWidget->setCurrentIndex(3);
}

void SWMainForm::loadComboBoxes()
{
    comboBox->clear();
    comboBox->setModel(new QStandardItemModel);
    comboBox->insertItem(0, "SpellFamilyName", 0);
    m_sw->setMetaEnum("SpellFamilyNames");
    for (quint16 i = 0; i < m_sw->getMetaEnum().keyCount(); ++i)
        comboBox->insertItem(i + 1, QString("(%0) %1")
            .arg(m_sw->getMetaEnum().value(i), 3, 10, QChar('0'))
            .arg(m_sw->getMetaEnum().valueToKey(m_sw->getMetaEnum().value(i))), m_sw->getMetaEnum().value(i));

    comboBox_2->clear();
    comboBox_2->setModel(new QStandardItemModel);
    comboBox_2->insertItem(0, "Aura", 0);
    m_sw->setMetaEnum("AuraType");
    for (quint16 i = 0; i < m_sw->getMetaEnum().keyCount(); ++i)
    {
        comboBox_2->insertItem(i + 1, QString("(%0) %1")
            .arg(m_sw->getMetaEnum().value(i), 3, 10, QChar('0'))
            .arg(m_sw->getMetaEnum().valueToKey(m_sw->getMetaEnum().value(i))), m_sw->getMetaEnum().value(i));
    }

    comboBox_3->clear();
    comboBox_3->setModel(new QStandardItemModel);
    comboBox_3->insertItem(0, "Effect", 0);
    m_sw->setMetaEnum("Effects");
    for (quint16 i = 0; i < m_sw->getMetaEnum().keyCount(); ++i)
        comboBox_3->insertItem(i + 1, QString("(%0) %1")
            .arg(m_sw->getMetaEnum().value(i), 3, 10, QChar('0'))
            .arg(m_sw->getMetaEnum().valueToKey(m_sw->getMetaEnum().value(i))), m_sw->getMetaEnum().value(i));

    comboBox_4->clear();
    comboBox_4->setModel(new QStandardItemModel);
    m_sw->setMetaEnum("Targets");
    comboBox_4->insertItem(0, "Target A", 0);
    for (quint16 i = 0; i < m_sw->getMetaEnum().keyCount(); ++i)
        comboBox_4->insertItem(i + 1, QString("(%0) %1")
            .arg(m_sw->getMetaEnum().value(i), 3, 10, QChar('0'))
            .arg(m_sw->getMetaEnum().key(i)), m_sw->getMetaEnum().value(i));

    comboBox_5->clear();
    comboBox_5->setModel(new QStandardItemModel);
    comboBox_5->insertItem(0, "Target B", 0);
    for (quint16 i = 0; i < m_sw->getMetaEnum().keyCount(); ++i)
        comboBox_5->insertItem(i + 1, QString("(%0) %1")
            .arg(m_sw->getMetaEnum().value(i), 3, 10, QChar('0'))
            .arg(m_sw->getMetaEnum().key(i)), m_sw->getMetaEnum().value(i));

    adBox1->clear();
    adBox2->clear();
    MetaSpell metaSpell;
    quint32 offset = metaSpell.metaObject()->methodOffset();
    quint32 count = metaSpell.metaObject()->methodCount();
    QStandardItemModel* model = new QStandardItemModel();
    model->setItem(0, new QStandardItem("None"));
    for (quint16 i = offset; i < count; ++i)
    {
        QString signature = metaSpell.metaObject()->method(i).methodSignature().data();
        QRegExp rx("(\\D.*)(\\(.*\\))");
        if (rx.indexIn(signature) != -1)
        {
            QStandardItem* item = new QStandardItem(rx.cap(1));
            item->setData(signature, 33);

            QVariant arraySize = metaSpell.property(rx.cap(1).toLatin1().data());
            if (arraySize.isValid())
                item->setData(arraySize.toUInt(), 34);
            else
                item->setData(0, 34);

            model->setItem(i - offset + 1, item);
        }
    }

    adBox1->setModel(model);
    adBox2->setModel(model);
}

void SWMainForm::slotRegExp()
{
    if (isRegExp())
    {
        m_regExp->setChecked(true);
        m_regExp->setIcon(QIcon(":/SpellWork/Recources/regExp.png"));
        m_regExp->setText("<font color=green>On</font>");
    }
    else
    {
        m_regExp->setChecked(false);
        m_regExp->setIcon(QIcon(":/SpellWork/Recources/regExp.png"));
        m_regExp->setText("<font color=red>Off</font>");
    }

    if (SpellEntry const* spellInfo = sSpellStore.LookupEntry(webView1->url().path().remove(0, 1).toInt()))
        m_sw->showInfo(spellInfo);

    bool compared[2] = { false, false };
    if (SpellEntry const* spellInfo = sSpellStore.LookupEntry(webView2->url().path().remove(0, 1).toInt()))
    {
        m_sw->showInfo(spellInfo, 2);
        compared[0] = true;
    }

    if (SpellEntry const* spellInfo = sSpellStore.LookupEntry(webView3->url().path().remove(0, 1).toInt()))
    {
        m_sw->showInfo(spellInfo, 3);
        compared[1] = true;
    }

    if (compared[0] || compared[1])
        m_sw->compare();
}

void SWMainForm::slotAbout()
{
    SWAboutForm* aboutForm = new SWAboutForm(this);
    connect(aboutForm, SIGNAL(destroyed()), aboutForm, SLOT(deleteLater()));
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

void SWMainForm::slotResetRelate()
{
    ((RelationModel*)fieldsView->model())->resetRelate();
}

void SWMainForm::slotAutoRelate()
{
    ((RelationModel*)fieldsView->model())->autoRelate();
}

bool SWMainForm::event(QEvent* ev)
{
    switch (ev->type())
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

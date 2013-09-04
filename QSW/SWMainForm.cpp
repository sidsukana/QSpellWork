#include "SWMainForm.h"
#include "SWAboutForm.h"
#include "SWModels.h"
#include "SWSearch.h"

#include <QtCore/QtConcurrentRun>
#include <QtCore/QTime>
#include <QtGui/QStandardItemModel>
#include <QtGui/QMessageBox>
#include <QtGui/QStringListModel>

SWMainForm::SWMainForm(QWidget* parent)
    : QMainWindow(parent)
{
    QTime m_time;
    m_time.start();

    setupUi(this);
    
    m_advancedTextEdit = new TextEdit(page);
    gridLayout_4->addWidget(m_advancedTextEdit, 0, 0, 4, 1);
    m_advancedTextEdit->hide();

    m_enums = new SWEnums();
    m_sw = new SWObject(this);

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
    
    connect(adFilterButton, SIGNAL(clicked()), this, SLOT(slotAdvancedFilter()));
    connect(adApplyButton, SIGNAL(clicked()), this, SLOT(slotAdvancedApply()));

    selectedAction = new QAction(this);
    selectedAction->setShortcut(QKeySequence::MoveToNextLine);
    connect(selectedAction, SIGNAL(triggered()), this, SLOT(slotNextRow()));
    SpellList->addAction(selectedAction);

    // List search connection
    connect(SpellList, SIGNAL(clicked(QModelIndex)), this, SLOT(slotSearchFromList(QModelIndex)));

    // Main search connections
    connect(findLine_e1, SIGNAL(returnPressed()), this, SLOT(slotButtonSearch()));
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

void SWMainForm::slotAdvancedFilter()
{
    if (m_advancedTextEdit->isVisible())
    {
        webView1->show();
        m_advancedTextEdit->hide();
    }
    else
    {
        webView1->hide();
        m_advancedTextEdit->show();
    }
}

void SWMainForm::slotAdvancedApply()
{
    emit signalSearch(3);
}

void SWMainForm::loadSettings()
{
    m_settings = new QSettings("QSW.ini", QSettings::IniFormat, this);
    m_settings->sync();

    // Global
    setRegExp(m_settings->value("Global/RegExp", false).toBool());

    // Search and filters
    findLine_e1->setText(m_settings->value("Search/IdOrName", "").toString());
    findLine_e3->setText(m_settings->value("Search/Description", "").toString());
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
    m_settings->setValue("Search/Description", findLine_e3->text());
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
            QString sName = QString::fromUtf8(spellInfo->SpellName[Locale]);
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
}

void SWMainForm::detectLocale()
{
    SpellEntry const* spellInfo = sSpellStore.LookupEntry(1);

    if (!spellInfo)
        return;

    m_sw->setMetaEnum("LocalesDBC");
    for (quint8 i = 0; i < m_sw->getMetaEnum().keyCount(); ++i)
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

    fieldsView->setItemDelegate(new RelationDelegate);
    fieldsView->setModel(model);

    stackedWidget->setCurrentIndex(3);
}

void SWMainForm::loadComboBoxes()
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
        delete model;
        model = NULL;
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

TextEdit::TextEdit(QWidget *parent)
    : QTextEdit(parent), m_completer(NULL)
{
    m_completer = new QCompleter(parent);
    m_completer->setModel(setupModel());
    m_completer->setModelSorting(QCompleter::UnsortedModel);
    m_completer->setCaseSensitivity(Qt::CaseInsensitive);
    m_completer->setWrapAround(false);
    m_completer->setWidget(this);
    m_completer->setCompletionMode(QCompleter::PopupCompletion);

    QObject::connect(m_completer, SIGNAL(activated(QString)), this, SLOT(insertCompletion(QString)));
}

TextEdit::~TextEdit()
{
}

QCompleter *TextEdit::completer() const
{
    return m_completer;
}

void TextEdit::insertCompletion(const QString& completion)
{
    if (m_completer->widget() != this)
        return;

    QTextCursor tc = textCursor();
    tc.select(QTextCursor::WordUnderCursor);
    tc.insertText(completion);
    setTextCursor(tc);
}

QString TextEdit::textUnderCursor() const
{
    QTextCursor tc = textCursor();
    tc.select(QTextCursor::BlockUnderCursor);
    return tc.selectedText();
}

void TextEdit::focusInEvent(QFocusEvent *e)
{
    if (m_completer)
        m_completer->setWidget(this);
    QTextEdit::focusInEvent(e);
}

void TextEdit::keyPressEvent(QKeyEvent *e)
{
    if (m_completer && m_completer->popup()->isVisible())
    {
        // The following keys are forwarded by the completer to the widget
        switch (e->key()) {
        case Qt::Key_Enter:
        case Qt::Key_Return:
        case Qt::Key_Escape:
        case Qt::Key_Tab:
        case Qt::Key_Backtab:
            e->ignore();
            return; // let the completer do default behavior
        default:
            break;
        }
    }

    bool isShortcut = ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_Space); // CTRL+E
    if (!m_completer || !isShortcut) // do not process the shortcut when we have a completer
        QTextEdit::keyPressEvent(e);

    const bool ctrlOrShift = e->modifiers() & (Qt::ControlModifier | Qt::ShiftModifier);
    if (!m_completer || (ctrlOrShift && e->text().isEmpty()))
        return;

    static QString eow(" ~!@#$%^&*_+{}|:\"<>?,/;'[]()\\-="); // end of word
    bool hasModifier = (e->modifiers() != Qt::NoModifier) && !ctrlOrShift;
    QString completionPrefix = textUnderCursor();

    int pos = textCursor().positionInBlock();
    bool complete = false;
    
    // Check autocomplete
    if (completionPrefix.size() >= 6 && pos >= 6 && completionPrefix.contains("spell."))
    {
        // Remove all after first right whitespace about cursor position
        for (qint32 i = pos; i < completionPrefix.size(); ++i)
        {
            if (completionPrefix.at(i) == ' ')
            {
                completionPrefix.remove(i, completionPrefix.size() - i);
                break;
            }
        }
        
        // Remove all before first dot about cursor position
        // and contains 'spell.'
        for (qint32 i = pos - 1; i != -1; --i)
        {
            if (completionPrefix.at(i) == '.')
            {
                if (completionPrefix.mid(i - 5, 6).startsWith("spell."))
                {
                    completionPrefix.remove(0, i + 1);
                    complete = true;
                    break;
                }
            }
        }
    }

    if (!isShortcut && e->key() != Qt::Key_Period && (hasModifier || e->text().isEmpty() || !complete || eow.contains(e->text().right(1))))
    {
        m_completer->popup()->hide();
        return;
    }

    if (completionPrefix != m_completer->completionPrefix())
    {
        m_completer->setCompletionPrefix(completionPrefix);
        m_completer->popup()->setCurrentIndex(m_completer->completionModel()->index(0, 0));
    }

    if (completionPrefix == m_completer->currentCompletion())
    {
        m_completer->popup()->hide();
        return;
    }
    QRect cr = cursorRect();
    cr.setWidth(m_completer->popup()->sizeHintForColumn(0) + m_completer->popup()->verticalScrollBar()->sizeHint().width());
    m_completer->complete(cr);
}

QAbstractItemModel* TextEdit::setupModel()
{
    QSet<QString> fields;

    MetaSpell spell;

    qint32 propertyCount = spell.metaObject()->propertyCount();
    qint32 methodCount = spell.metaObject()->methodCount();

    for (qint32 i = 1; i < propertyCount; ++i)
        fields << spell.metaObject()->property(i).name();

    for (qint32 i = 0; i < methodCount; ++i)
    {
        QString methodName = spell.metaObject()->method(i).signature();
        if (methodName.contains("(quint8)"))
            fields << methodName.replace("(quint8)", "(index)");
    }

    return new QStringListModel(fields.toList(), m_completer);
}

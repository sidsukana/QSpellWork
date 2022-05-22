#include <QMetaProperty>
#include <QMetaObject>
#include <QScrollBar>

#include "ScriptEdit.h"

ScriptEdit::ScriptEdit(QWidget *parent)
    : QTextEdit(parent), m_completer(nullptr), m_completerModel(nullptr)
{
    m_completer = new QCompleter(this);
    m_completerModel = new QStringListModel(m_completer);
    m_completer->setModel(m_completerModel);
    m_completer->setCaseSensitivity(Qt::CaseInsensitive);
    m_completer->setWrapAround(false);
    m_completer->setWidget(this);
    m_completer->setCompletionMode(QCompleter::PopupCompletion);

    QObject::connect(m_completer, SIGNAL(activated(QString)), this, SLOT(insertCompletion(QString)));
}

ScriptEdit::~ScriptEdit()
{
}

QCompleter *ScriptEdit::completer() const
{
    return m_completer;
}

void ScriptEdit::insertCompletion(const QString& completion)
{
    if (m_completer->widget() != this)
        return;

    QTextCursor tc = textCursor();
    tc.select(QTextCursor::WordUnderCursor);
    tc.insertText(completion);
    setTextCursor(tc);
}

QString ScriptEdit::textUnderCursor() const
{
    QTextCursor tc = textCursor();
    tc.select(QTextCursor::BlockUnderCursor);
    return tc.selectedText();
}

void ScriptEdit::focusInEvent(QFocusEvent *e)
{
    if (m_completer)
        m_completer->setWidget(this);
    QTextEdit::focusInEvent(e);
}

void ScriptEdit::keyPressEvent(QKeyEvent *e)
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

void ScriptEdit::setupCompleter(QObject* metaSpell)
{
    QSet<QString> fields;

    qint32 propertyCount = metaSpell->metaObject()->propertyCount();
    qint32 methodCount = metaSpell->metaObject()->methodCount();

    for (qint32 i = 1; i < propertyCount; ++i)
        fields << metaSpell->metaObject()->property(i).name();

    for (qint32 i = 0; i < methodCount; ++i)
    {
        QString methodName = metaSpell->metaObject()->method(i).methodSignature();
        if (methodName.contains("(uchar)"))
            fields << methodName.replace("(uchar)", "(index)");
        else if (methodName.contains("(uint)"))
            fields << methodName.replace("(uint)", "(id)");
        else if (methodName.contains("(qulonglong)"))
            fields << methodName.replace("(qulonglong)", "(flags)");
    }

    m_completerModel->setStringList(fields.values());
    m_completerModel->sort(0);
}

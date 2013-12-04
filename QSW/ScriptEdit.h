#ifndef SCRIPTEDIT_H
#define SCRIPTEDIT_H

#include <QAbstractItemView>
#include <QCompleter>
#include <QKeyEvent>
#include <QScrollBar>
#include <QTextEdit>

class ScriptEdit : public QTextEdit
{
    Q_OBJECT

    public:
        ScriptEdit(QWidget *parent = NULL);
        ~ScriptEdit();

        QAbstractItemModel* setupModel();
        QCompleter *completer() const;

    protected:
        void keyPressEvent(QKeyEvent *e);
        void focusInEvent(QFocusEvent *e);

        private slots:
            void insertCompletion(const QString &completion);

    private:
        QString textUnderCursor() const;

    private:
        QCompleter *m_completer;
};

#endif
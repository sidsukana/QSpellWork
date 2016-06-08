#ifndef SCRIPTEDIT_H
#define SCRIPTEDIT_H

#include <QAbstractItemView>
#include <QStringListModel>
#include <QCompleter>
#include <QKeyEvent>
#include <QTextEdit>

class ScriptEdit : public QTextEdit
{
    Q_OBJECT

    public:
        ScriptEdit(QWidget *parent = nullptr);
        ~ScriptEdit();

        void setupCompleter(QObject* metaSpell);
        QCompleter *completer() const;

    protected:
        void keyPressEvent(QKeyEvent *e);
        void focusInEvent(QFocusEvent *e);

        private slots:
            void insertCompletion(const QString &completion);

    private:
        QString textUnderCursor() const;

    private:
        QCompleter* m_completer;
        QStringListModel* m_completerModel;

};

#endif

#ifndef SPELLWORK_H
#define SPELLWORK_H

#include <QtGui/QMainWindow>
#include <QtGui/QDialog>
#include <QtGui/QStandardItem>
#include <QtGui/QStandardItemModel>
#include "ui_SpellWorkUI.h"
#include "ui_AboutUI.h"

class SpellWork : public QMainWindow, public Ui::SpellWorkUI
{
    Q_OBJECT

    public:
        SpellWork(QWidget *parent = 0);
        ~SpellWork();

    private slots:
        void SlotAbout();
        void SlotFind();
        void SlotFindFromList(const QModelIndex &index);

    private:
        Ui::SpellWorkUI ui;
        QStandardItemModel *model;
};

class About : public QDialog, public Ui::AboutUI
{
    Q_OBJECT

public:
    About(QWidget *parent = 0);
    ~About();

private:
    Ui::AboutUI ui;
};

#endif

#ifndef SPELLWORK_H
#define SPELLWORK_H

#include <QtGui/QMainWindow>
#include <QtGui/QDialog>
#include <QtGui/QStandardItem>
#include <QtGui/QStandardItemModel>
#include "ui_SpellWorkUI.h"
#include "ui_AboutUI.h"

#include "DBC/DBCStores.h"

class SpellWork : public QMainWindow, public Ui::SpellWorkUI
{
    Q_OBJECT

    public:
        SpellWork(QWidget *parent = 0);
        ~SpellWork();

        void ShowInfo();
        void AppendSkillLine();
        void AppendCastTimeLine();
        void AppendDurationLine();
        void AppendRangeInfo();
        void AppendSpellEffectInfo();
        void AppendAuraInfo(int index);
        void AppendProcInfo(SpellEntry const *spellInfo);
        QString PowerString();
        QString CompareAttributes(AttrType attr, int index = 0);

    private slots:
        void SlotAbout();
        void SlotSearch();
        void SlotSearchFromList(const QModelIndex &index);

    private:
        Ui::SpellWorkUI ui;
        QStandardItemModel *model;
        SpellEntry const* m_spellInfo;
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

#ifndef SPELLWORK_H
#define SPELLWORK_H

#include <QtGui/QMainWindow>
#include <QtGui/QDialog>
#include <QtGui/QStandardItem>
#include <QtGui/QStandardItemModel>
#include <QtCore/QThread>
#include <QtCore/QEvent>
#include "ui_SpellWorkUI.h"
#include "ui_AboutUI.h"

#include "DBC/DBCStores.h"
#include "ThreadObject.h"

class SpellWork : public QMainWindow, public Ui::SpellWorkUI
{
    Q_OBJECT

        friend class ObjThread;
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
        void AppendRadiusInfo(int index);
        void AppendTriggerInfo(int index);
        void AppendProcInfo(SpellEntry const *spellInfo);
        QString PowerString();
        QString CompareAttributes(AttrType attr, int index = 0);
        QString GetDescription(QString str);
        int GetDuration(SpellEntry const *spellInfo);
        int GetRealDuration(SpellEntry const *spellInfo, uint8 effIndex);
        float GetRadius(SpellEntry const *spellInfo, uint8 effIndex);
        void BeginThread(int id);

        bool event(QEvent* e);

    private slots:
        void SlotAbout();
        void SlotSearch();
        void SlotSearchFromList(const QModelIndex &index);

    private:
        Ui::SpellWorkUI ui;
        SpellEntry const* m_spellInfo;

        typedef QList<ObjThread*> ThreadList;
        ThreadList threads;
};

class ObjectSearch
{
    friend class SpellWork;
public:
    ObjectSearch(SpellWork *obj = NULL);
    ~ObjectSearch();

    void Search();

private:
    SpellWork *iFace;
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

class _Event : public QEvent
{
public:
    enum 
    {
        TypeId = QEvent::User + 1
    };
    _Event(int id = 0, QStandardItemModel* m = NULL, SpellEntry const* s = NULL);
    ~_Event();

    int GetId() const { return op_id; }
    QStandardItemModel* GetmObj() const { return mObj; }
    SpellEntry const* GetsObj() const { return sObj; }
private:
    int op_id;
    QStandardItemModel* mObj;
    SpellEntry const* sObj;
};

#endif

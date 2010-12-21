#ifndef SPELLWORK_H
#define SPELLWORK_H

#include <QtGui/QMainWindow>
#include <QtGui/QDialog>
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

	private:
		Ui::SpellWorkUI ui;
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

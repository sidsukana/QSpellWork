#include "SpellWork.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	SpellWork *sw = new SpellWork;
	sw->show();
	return app.exec();
}

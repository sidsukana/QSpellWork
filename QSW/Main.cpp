#include "SWForm.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    SWForm *form = new SWForm;
    form->show();
    return app.exec();
}

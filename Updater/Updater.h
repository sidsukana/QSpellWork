#ifndef UPDATER_H
#define UPDATER_H

#include <QtCore/QObject>

class Updater : public QObject
{
    Q_OBJECT

    public:
        Updater(QObject* parent = 0);
        ~Updater();

        void start();
};

#endif // UPDATER_H

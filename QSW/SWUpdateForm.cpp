#include "SWUpdateForm.h"

#include "SWEvent.h"

#include <QtCore/QtConcurrentRun>
#include <QtCore/QProcess>
#include <QtCore/QFile>
#include <QtCore/QDir>

#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

SWUpdateForm::SWUpdateForm(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    connect(updateButton, SIGNAL(clicked()), this, SLOT(slotStartUpdate()));

    updateButton->setEnabled(false);
    progressBar->hide();
    fileLabel->hide();

    QtConcurrent::run(this, &SWUpdateForm::checkForUpdates);

    show();
}

SWUpdateForm::~SWUpdateForm()
{
}

void SWUpdateForm::checkForUpdates()
{
    QNetworkAccessManager qnam;
    QNetworkReply *reply = qnam.get(QNetworkRequest(QUrl(QString("http://valkyrie-wow.ru/uploads/QSW/") + QString("Updates.xml"))));
    QEventLoop loop;
    connect(this, SIGNAL(rejected()), &loop, SLOT(quit()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), &loop, SLOT(quit()));
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    if (!reply->isFinished())
    {
        Event* clearEvent = new Event(Event::Type(Event::EVENT_SEND_ACTION));
        clearEvent->addValue(0);
        QApplication::postEvent(this, clearEvent);

        Event* textEvent = new Event(Event::Type(Event::EVENT_SEND_TEXT));
        textEvent->addValue(reply->errorString());
        QApplication::postEvent(this, textEvent);
        return;
    }

    m_xmlData.setContent(reply->readAll());

    QString softwareName = "QSW1";
    quint32 currentBuild = QSW_BUILD.toUInt();
    quint32 newBuild = currentBuild;

    QDomNodeList softwareNodes = m_xmlData.childNodes();
    for (quint8 soft = 0; soft < softwareNodes.count(); soft++)
    {
        QDomElement software = softwareNodes.at(soft).toElement();
        if (software.tagName() == softwareName)
        {
            Event* clearEvent = new Event(Event::Type(Event::EVENT_SEND_ACTION));
            clearEvent->addValue(0);
            QApplication::postEvent(this, clearEvent);

            QDomNodeList updateNodes = software.childNodes();
            for (quint32 upd = 0; upd < updateNodes.count(); upd++)
            {
                QDomElement update = updateNodes.at(upd).toElement();
                if (update.attribute("build").toUInt() > newBuild)
                {
                    newBuild = update.attribute("build").toUInt();

                    QDomNodeList descriptionNodes = update.childNodes();
                    for (quint32 desc = 0; desc < descriptionNodes.count(); desc++)
                    {
                        QDomElement description = descriptionNodes.at(desc).toElement();
                        if (description.tagName() == "Description")
                        {
                            Event* textEvent = new Event(Event::Type(Event::EVENT_SEND_TEXT));
                            textEvent->addValue(QVariant(description.text()));
                            QApplication::postEvent(this, textEvent);
                        }

                        if (upd == updateNodes.count() - 1 && description.tagName() == "Files")
                        {
                            QDomNodeList fileNodes = description.childNodes();
                            for (quint32 f = 0; f < fileNodes.count(); f++)
                            {
                                QDomElement file = fileNodes.at(f).toElement();
                                m_updateFiles << file.attribute("name");
                            }

                            Event* enableEvent = new Event(Event::Type(Event::EVENT_SEND_ACTION));
                            enableEvent->addValue(1);
                            QApplication::postEvent(this, enableEvent);
                        }
                    }
                }
            }
        }
    }

    if (newBuild == currentBuild)
    {
        Event* textEvent = new Event(Event::Type(Event::EVENT_SEND_TEXT));
        textEvent->addValue(QVariant("No updates available."));
        QApplication::postEvent(this, textEvent);
    }
}

void SWUpdateForm::slotUpdateProgress(qint64 bytes, qint64 total)
{
    progressBar->setMaximum(total);
    progressBar->setValue(bytes);
}

void SWUpdateForm::slotStartUpdate()
{
    progressBar->show();
    fileLabel->show();

    QtConcurrent::run(this, &SWUpdateForm::updateSoftware);
}

void SWUpdateForm::updateSoftware()
{
    QNetworkAccessManager qnam;

    for (QStringList::const_iterator itr = m_updateFiles.begin(); itr != m_updateFiles.end(); ++itr)
    {
        Event* ev = new Event(QEvent::Type(Event::EVENT_SEND_ACTION));
        ev->addValue(2);
        ev->addValue((*itr));
        QApplication::postEvent(this, ev);

        QNetworkReply *reply = qnam.get(QNetworkRequest(QUrl(QString("http://valkyrie-wow.ru/uploads/QSW/QSW1/") + (*itr))));
        QEventLoop loop;
        connect(this, SIGNAL(rejected()), &loop, SLOT(quit()));
        connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), &loop, SLOT(quit()));
        connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        connect(reply, SIGNAL(finished()), progressBar, SLOT(reset()));
        connect(reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(slotUpdateProgress(qint64, qint64)));
        loop.exec();

        if (!reply->isFinished())
        {
            Event* clearEvent = new Event(Event::Type(Event::EVENT_SEND_ACTION));
            clearEvent->addValue(0);
            QApplication::postEvent(this, clearEvent);

            Event* textEvent = new Event(Event::Type(Event::EVENT_SEND_TEXT));
            textEvent->addValue(reply->errorString());
            QApplication::postEvent(this, textEvent);
            return;
        }

        QDir path;
        path.setCurrent(QApplication::applicationDirPath());
        
        if (path.mkdir("Temp"))
        {
            QFile file("Temp/" + (*itr));
            if (file.open(QIODevice::WriteOnly))
            {
                file.write(reply->readAll());
                file.flush();
                file.close();
            }
        }
    }

    qint32 index = m_updateFiles.indexOf("Updater.exe");

    if (index != -1)
    {
        QDir path;
        path.setCurrent(QApplication::applicationDirPath());

        if (path.exists("Temp"))
        {
            if (path.exists("Updater.exe"))
            {
                while (!path.remove("Updater.exe")) {}
                while (!path.rename("Temp/Updater.exe", "Updater.exe")) {}
            }
        }

        m_updateFiles.removeAt(index);
    }

    QProcess::startDetached("Updater.exe", m_updateFiles);
    QApplication::quit();
}

bool SWUpdateForm::event(QEvent* ev)
{
    switch (ev->type())
    {
        case Event::EVENT_SEND_TEXT:
        {
            Event* m_ev = (Event*)ev;

            for (quint32 i = 0; i < m_ev->getCount(); i++)
                textEdit->append(m_ev->getValue(i).toString());

            return true;
        }
        break;
        case Event::EVENT_SEND_ACTION:
        {
            Event* m_ev = (Event*)ev;

            for (quint32 i = 0; i < m_ev->getCount(); i++)
            {
                switch (m_ev->getValue(i).toUInt())
                {
                    case 0:
                    {
                        textEdit->clear();
                        return true;
                    }
                    case 1:
                    {
                        updateButton->setEnabled(true);
                        return true;
                    }
                    case 2:
                    {
                        fileLabel->setText(m_ev->getValue(i+1).toString());
                        return true;
                    }
                    default: break;
                }
            }
        }
        break;
    }

    return QWidget::event(ev);
}
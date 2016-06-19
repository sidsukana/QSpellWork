#include <QDomDocument>
#include <QFile>

#include "qsw.h"

QSettings& QSW::settings()
{
    static QSettings m_settings("QSW.ini", QSettings::IniFormat);
    m_settings.sync();
    return m_settings;
}

EnumHash QSW::loadEnumFile(QString fileName)
{
    QFile xmlFile(fileName);
    xmlFile.open(QIODevice::ReadOnly);

    QDomDocument xmlData;
    xmlData.setContent(&xmlFile);
    xmlFile.close();

    EnumHash enums;

    QDomNodeList enumNodes = xmlData.firstChild().childNodes();
    for (qint32 i = 0; i < enumNodes.count(); ++i)
    {
        QDomNodeList valuesNodes = enumNodes.item(i).toElement().childNodes();
        Enumerator enumerator;
        for (qint32 j = 0; j < valuesNodes.count(); ++j)
        {
            QDomElement valueElement = valuesNodes.item(j).toElement();
            if (valueElement.attribute("key").contains("0x"))
            {
                bool ok;
                enumerator[valueElement.attribute("key").toLongLong(&ok, 16)]= valueElement.attribute("value");
            }
            else
                enumerator[valueElement.attribute("key").toLongLong()]= valueElement.attribute("value");
        }
        enums[enumNodes.item(i).toElement().tagName()] = enumerator;
    }

    return enums;
}

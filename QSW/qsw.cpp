#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

#include "qsw.h"

QJsonSettings &QSW::settings()
{
    static QJsonSettings m_settings(QStringLiteral("config.json"), jsonFormat);
    return m_settings;
}

EnumHash QSW::loadEnumFile(QString fileName)
{
    QFile jsonFile(fileName);
    jsonFile.open(QIODevice::ReadOnly);
    
    QJsonDocument json = QJsonDocument::fromJson(jsonFile.readAll());

    jsonFile.close();

    EnumHash enums;

    if (json.isObject())
    {
        QJsonObject object = json.object();
        for (auto itr = object.begin(); itr != object.end(); ++itr)
        {
            QJsonValue v1 = itr.value();
            // v1 - first level must be array type
            if (v1.isArray())
            {
                QJsonArray vArray = v1.toArray();
                Enumerator enumerator;
                for (QJsonValue v2 : vArray)
                {
                    // v2 - second level must be object type
                    if (v2.isObject())
                    {
                        QJsonObject vObject = v2.toObject();
                        QString key = vObject["key"].toString();
                        QString value  = vObject["value"].toVariant().toString();

                        enumerator[value.startsWith("0x") ? value.toLongLong(nullptr, 16) : value.toLongLong()]= key;
                    }
                }
                enums[itr.key()] = enumerator;
            }
        }
   }

   return enums;
}

QSqlDatabase& QSW::database()
{
    static QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", "qsw");
    return db;
}

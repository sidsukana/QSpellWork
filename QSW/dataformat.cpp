#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "dataformat.h"

DataFormat::DataFormat(const QString& fileName)
    : _fileName(fileName)
{
    QFile jsonFile(fileName);
    jsonFile.open(QIODevice::ReadOnly);

    QJsonDocument json = QJsonDocument::fromJson(jsonFile.readAll());

    jsonFile.close();

    if (json.isObject())
    {
        QJsonObject formatObject = json.object();
        for (auto itr = formatObject.begin(); itr != formatObject.end(); ++itr)
        {
            QJsonObject sourceObject = itr.value().toObject();
            FormatSource formatSource;
            formatSource.type = sourceObject.value("type").toInt();
            formatSource.name = sourceObject.value("name").toString();

            QJsonArray fieldsArray = sourceObject.value("fields").toArray();

            for (QJsonValue fieldValue : fieldsArray)
            {
                QJsonObject fieldObject = fieldValue.toObject();
                FormatField formatField;
                formatField.type = fieldObject.value("type").toInt();
                formatField.name = fieldObject.value("name").toString();
                formatField.load = fieldObject.value("load").toBool();
                formatSource.fields << formatField;
            }
            _data[itr.key()] = formatSource;
        }
    }
}

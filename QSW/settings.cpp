#include <QDebug>

#include "settings.h"

bool readSettingsJson(QIODevice &device, QSettings::SettingsMap &map)
{
    QJsonDocument json = QJsonDocument::fromJson(device.readAll());
    if (!json.isEmpty())
    {
        QJsonObject object = json.object();
        if (!object.isEmpty())
        {
            map = object.toVariantMap();
            return true;
        }
    }

    qDebug() << "Can't read JSON file settings!";
    return false;
}

bool writeSettingsJson(QIODevice &device, const QSettings::SettingsMap &map)
{
    QJsonObject object = QJsonObject::fromVariantMap(map);

    if (!object.isEmpty())
    {
        QJsonDocument json(object);
        if (!json.isEmpty())
        {
            device.write(json.toJson());
            return true;
        }
    }

    qDebug() << "Can't write JSON file settings!";
    return false;
}

#pragma once

#include <QJsonDocument>
#include <QJsonObject>
#include <QIODevice>
#include <QSettings>
#include <QQueue>

#include "qsw_export.h"

bool QSW_EXPORT readSettingsJson(QIODevice &device, QSettings::SettingsMap &map);
bool QSW_EXPORT writeSettingsJson(QIODevice &device, const QSettings::SettingsMap &map);

static const QSettings::Format jsonFormat = QSettings::registerFormat("json", &readSettingsJson, &writeSettingsJson);

class QJsonSettings : public QObject
{
    Q_OBJECT
    public:
        QJsonSettings(const QString &fileName, QSettings::Format format, QObject* parent = nullptr)
            : QObject(parent), _settings(fileName, format)
        {
            _values = _settings.value("qsw").toMap();
            _current = _values;
            _groupQueue.push_back(JsonGroup("qsw", _current));
        }
        ~QJsonSettings()
        {
           sync();
        }

        void beginGroup(const QString& name)
        {
            _groupQueue.last().second = _current;
            if (_current.contains(name))
            {
                _current = _current.value(name).toMap();
            }
            else
            {
                _current[name] = QVariantMap();
                _groupQueue.last().second = _current;
                _current = _current[name].toMap();
            }

            _groupQueue.push_back(JsonGroup(name, _current));
        }

        void endGroup()
        {
            _groupQueue.last().second = _current;
            JsonGroup lastGroup = _groupQueue.last();
            _groupQueue.pop_back();
            _current = _groupQueue.last().second;
            _current[lastGroup.first] = lastGroup.second;

            if (_groupQueue.size() <= 1)
            {
                _values = _current;
            }
        }

        void setValue(const QString& key, const QVariant& value)
        {
            _current[key] = value;
        }

        QVariant value(const QString& key, const QVariant& defaultValue = QVariant()) const
        {
            return _current.contains(key) ? _current[key] : defaultValue;
        }

    public slots:
        void sync()
        {
            _settings.setValue("qsw", _values);
            _settings.sync();
        }
    private:
        QVariantMap _current;
        typedef QPair<QString, QVariantMap> JsonGroup;
        QQueue<JsonGroup> _groupQueue;
        QSettings _settings;
        QVariantMap _values;
};

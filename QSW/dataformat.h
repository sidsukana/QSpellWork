#pragma once

#include <QObject>
#include <QVariantHash>
#include <QJsonObject>

enum FormatType
{
    TypeUint,
    TypeInt,
    TypeFloat,
    TypeString
};

struct FormatField
{
    FormatField() : type(0), load(true) {}
    quint8 type;
    QString name;
    bool load;
};

struct FormatSource
{
    FormatSource() : type(0) {}
    quint8 type;
    QString name;
    QList<FormatField> fields;
};

class DataFormat
{
    public:
        DataFormat(const QString& fileName);
        ~DataFormat() {}

        quint8 getSourceType(const QString& name) const
        {
            return _data.value(name).type;
        }

        QString getSourceName(const QString& name) const
        {
            return _data.value(name).name;
        }

        QList<FormatField> getSourceFields(const QString& name) const
        {
            return _data.value(name).fields;
        }

        QStringList getSourceList() const
        {
            return _data.keys();
        }

        FormatSource getSourceFormat(const QString& name) const
        {
            return _data.value(name);
        }

    private:
        QString _fileName;
        QHash<QString, FormatSource> _data;
};

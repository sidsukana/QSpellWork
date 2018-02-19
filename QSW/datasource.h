#pragma once

#include <QVariantHash>
#include "dataformat.h"

#include "DBC/DBC.h"

enum DataSourceType
{
    SourceDbc,
    SourceSql,
    SourceMax
};

class DataSource
{
public:
    virtual ~DataSource() {}
    virtual bool load() = 0;
    virtual QVariantHash getEntry(quint32 id) const = 0;
    virtual QVariantHash getRecord(quint32 id) const = 0;
    virtual quint32 getRecordCount() const = 0;
    virtual quint32 getIndex(quint32 id) const = 0;
    virtual QString getString(quint32 id) const = 0;
    virtual QSharedPointer<FormatSource> getFormat() const = 0;
};

class DBCSource : public DataSource
{
    public:
        explicit DBCSource(QSharedPointer<FormatSource> format);
        ~DBCSource() {}

        bool load();

        QVariantHash getEntry(quint32 id) const;

        QVariantHash getRecord(quint32 id) const;

        quint32 getRecordCount() const { return _header->recordCount; }
        quint32 getIndex(quint32 id) const { return _indexes.indexOf(id); }
        QString getString(quint32 id) const { return QString::fromUtf8(_strings + id); }
        QSharedPointer<FormatSource> getFormat() const { return _format; }

    private:

        QByteArray _rawData;
        const DBCFileHeader *_header;
        const char *_strings;
        Indexes _indexes;
        quint32 _maxId;
        quint32 _minId;
        QString _fileName;
        QSharedPointer<FormatSource> _format;
        QHash<quint32, QVariantHash> _data;
};


class SourceRecord : public QObject
{
    Q_OBJECT
    public:
        SourceRecord(DataSource* source, QVariantHash data, QObject* parent = nullptr) : QObject(parent), _source(source), _data(data) {}
        ~SourceRecord() {}

        Q_INVOKABLE QVariant value(const QString& name) const
        {
            if (_source->getFormat()->isString(name))
            {
                return _source->getString(_data.value(name).toUInt());
            }
            else
            {
                return _data.value(name);
            }
        }

    private:
        DataSource* _source;
        QVariantHash _data;

};

class SQLSource : public DataSource
{
    public:
        explicit SQLSource(QSharedPointer<FormatSource> format);
        ~SQLSource();

        bool load();

        QVariantHash getEntry(quint32 id) const;

        QVariantHash getRecord(quint32 id) const;

        SourceRecord* getEntry2(quint32 id) const;

        SourceRecord* getRecord2(quint32 id) const;

        quint32 getRecordCount() const { return _recordCount; }
        quint32 getIndex(quint32 id) const { return _indexes.indexOf(id); }
        QString getString(quint32 id) const { return _strings.at(id); }
        QSharedPointer<FormatSource> getFormat() const { return _format; }

    private:

        Indexes _indexes;
        quint32 _maxId;
        quint32 _minId;
        QString _tableName;
        QSharedPointer<FormatSource> _format;

        qint32 _recordCount;
        QHash<quint32, SourceRecord*> _data;
        QStringList _strings;
};

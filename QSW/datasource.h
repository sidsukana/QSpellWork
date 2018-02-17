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
    virtual bool load(FormatSource&& format) = 0;
    virtual QVariantHash getEntry(quint32 id) const = 0;
    virtual QVariantHash getRecord(quint32 id) const = 0;
    virtual quint32 getRecordCount() const = 0;
    virtual quint32 getIndex(quint32 id) const = 0;
};

class DBCSource : public DataSource
{
    public:
        explicit DBCSource(const QString &fileName);
        ~DBCSource() {}

        bool load(FormatSource &&format);

        QVariantHash getEntry(quint32 id) const;

        QVariantHash getRecord(quint32 id) const;

        quint32 getRecordCount() const { return _header->recordCount; }
        quint32 getIndex(quint32 id) const { return _indexes.indexOf(id); }

    private:

        QByteArray _rawData;
        const DBCFileHeader *_header;
        const char *_strings;
        Indexes _indexes;
        quint32 _maxId;
        quint32 _minId;
        QString _fileName;
        QHash<quint32, QVariantHash> _data;
};

class SQLSource : public DataSource
{
    public:
        explicit SQLSource(const QString &tableName);
        ~SQLSource() {}

        bool load(FormatSource&& format);

        QVariantHash getEntry(quint32 id) const;

        QVariantHash getRecord(quint32 id) const;

        quint32 getRecordCount() const { return _recordCount; }
        quint32 getIndex(quint32 id) const { return _indexes.indexOf(id); }

    private:

        Indexes _indexes;
        quint32 _maxId;
        quint32 _minId;
        QString _tableName;

        qint32 _recordCount;
        QHash<quint32, QVariantHash> _data;
};

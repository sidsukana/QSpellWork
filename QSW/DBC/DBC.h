#ifndef DBC_H_
#define DBC_H_

#include <QString>
#include <QList>
#include "qsw_export.h"

#define DBC_MAGIC "WDBC"

namespace DBC
{
    QString& dbcDir();
}

struct DBCFileHeader
{
    char magic[4];
    quint32 recordCount;
    quint32 fieldCount;
    quint32 recordSize;
    quint32 stringBlockSize;
};

typedef QList<quint32> Indexes;

class QSW_EXPORT DBCFile
{
    public:
        explicit DBCFile(const QString &fileName);
        ~DBCFile() {}

        bool load();

        template <typename T>
        const T* getEntry(quint32 id) const
        {
            qint32 index = m_indexes.indexOf(id);
            return (index == -1 ? nullptr : getRecord<T>(index));
        }

        template <typename T>
        const T* getRecord(quint32 id) const
        {
            return reinterpret_cast<const T*>(m_records + m_header->recordSize * id);
        }

        const quint32 getRecordCount() const { return m_header->recordCount; }
        const quint32 getIndex(quint32 id) const { return m_indexes.indexOf(id); }
        const Indexes getIndexes() const { return m_indexes; }
        const QString getString(quint32 offset) const { return QString::fromUtf8(m_strings + offset); }

    private:

        QByteArray m_data;
        const DBCFileHeader *m_header;
        const char *m_records;
        const char *m_strings;
        Indexes m_indexes;
        quint32 m_maxId;
        quint32 m_minId;
        QString m_fileName;
};


#endif

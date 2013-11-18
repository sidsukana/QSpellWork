#ifndef DBC_H_
#define DBC_H_

#include <QString>

#define DBC_MAGIC "WDBC"

struct DBCFileHeader
{
    char magic[4];
    quint32 recordCount;
    quint32 fieldCount;
    quint32 recordSize;
    quint32 stringBlockSize;
};

class DBCFile
{
    public:
        explicit DBCFile(const QString &fileName);
        ~DBCFile();

        template <typename T>
        const T* getEntry(quint32 id) const
        {
            return (id > m_maxId ? NULL : getRecord<T>(m_indexes[id]));
        }

        template <typename T>
        const T* getRecord(quint32 id) const
        {
            return reinterpret_cast<const T*>(m_records + m_header->recordSize * id);
        }

        const char* getStringBlock() const;
        const DBCFileHeader* getHeader() const { return m_header; }

    private:

        QByteArray m_data;
        const DBCFileHeader *m_header;
        const char *m_records;
        const char *m_strings;
        quint32 *m_indexes;
        quint32 m_maxId;
};

#endif

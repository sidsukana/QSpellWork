#include <QFile>

#include "mpq/MPQ.h"
#include "dbc/DBC.h"
#include "Defines.h"

DBCFile::DBCFile(const QString &fileName)
    : m_header(nullptr), m_records(nullptr), m_strings(nullptr),
      m_indexes(nullptr), m_maxId(0), m_fileName(fileName)
{

}

bool DBCFile::load()
{
    if (MPQ::mpqDir().isEmpty()) {
        QFile file(m_fileName);
        if (file.open(QFile::ReadOnly))
            m_data = file.readAll();
    } else {
        m_data = MPQ::readFile(m_fileName);
    }

    if (m_data.size() == 0) {
        qCritical("Cannot load DBC '%s'", qPrintable(m_fileName));
        return false;
    }

    m_header = reinterpret_cast<const DBCFileHeader *>(m_data.constData());

    if (qstrncmp(m_header->magic, DBC_MAGIC, 4) != 0) {
        qCritical("File '%s' is not a valid DBC file!", qPrintable(m_fileName));
        return false;
    }

    m_records = m_data.constData() + sizeof(DBCFileHeader);
    m_strings = m_records + m_header->recordCount * m_header->recordSize;

    m_maxId = *reinterpret_cast<const quint32*>(m_records + m_header->recordSize * (m_header->recordCount - 1));

    m_indexes = new quint32[m_maxId + 1];
    memset(m_indexes, 0, (m_maxId + 1) * 4);
    for (quint32 i = 0; i < m_header->recordCount; ++i)
    {
        quint32 id = *reinterpret_cast<const quint32*>(m_records + m_header->recordSize * i);
        m_indexes[id] = i;

        if (i == 0)
            m_minId = id;
    }

    return true;
}

const char* DBCFile::getStringBlock() const
{
    return m_strings;
}

DBCFile::~DBCFile()
{
    delete[] m_indexes;
}


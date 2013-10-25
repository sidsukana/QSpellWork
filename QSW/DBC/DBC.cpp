#include "DBC/DBC.h"
#include "mpq/MPQ.h"
#include "SWDefines.h"

#include <QDebug>

DBCFile::DBCFile(const QString &fileName) : m_header(0), m_records(0), m_strings(0)
{
    m_data = MPQ::readFile(fileName);

    if (m_data.size() == 0) {
        qCritical("Cannot load DBC '%s'", qPrintable(fileName));
        return;
    }

    m_header = reinterpret_cast<const DBCFileHeader *>(m_data.constData());

    if (qstrncmp(m_header->magic, DBC_MAGIC, 4) != 0) {
        qCritical("File '%s' is not a valid DBC file!", qPrintable(fileName));
        return;
    }

    m_records = m_data.constData() + sizeof(DBCFileHeader);
    m_strings = m_records + m_header->recordCount * m_header->recordSize;
}

const char * DBCFile::getStringBlock() const
{
    return m_strings;
}



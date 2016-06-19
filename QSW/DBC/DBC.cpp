#include <QFile>

#include "mpq/MPQ.h"
#include "dbc/DBC.h"

QString& DBC::dbcDir()
{
    static QString dbcDir;
    return dbcDir;
}

DBCFile::DBCFile(const QString &fileName) :
    m_header(nullptr), m_records(nullptr), m_strings(nullptr),
    m_maxId(0), m_fileName(fileName)
{
}

bool DBCFile::load()
{
    if (MPQ::mpqDir().isEmpty()) {
        QFile file(DBC::dbcDir() + m_fileName);
        if (file.open(QFile::ReadOnly)) {
            m_data = file.readAll();
            file.close();
        }
    } else {
        m_data = MPQ::readFile(DBC::dbcDir() + m_fileName);
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

    for (quint32 i = 0; i < m_header->recordCount; ++i)
        m_indexes << *reinterpret_cast<const quint32*>(m_records + m_header->recordSize * i);

    m_minId = *std::min_element(m_indexes.begin(), m_indexes.end());
    m_maxId = *std::max_element(m_indexes.begin(), m_indexes.end());

    return true;
}


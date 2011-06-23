#include "DBCFileLoader.h"
#include <QtCore/QFile>
#include <QtCore/QDataStream>

DBCFileLoader::DBCFileLoader()
{
    data = NULL;
    fieldsOffset = NULL;
}

bool DBCFileLoader::Load(const QString filename, const QString fmt)
{

    quint32 header;
    if (data)
    {
        delete []data;
        data = NULL;
    }

    QFile file(filename);
        
    if (!file.open(QIODevice::ReadOnly))
        return false;

    QDataStream stream(&file);
    stream.setByteOrder(QDataStream::ByteOrder(QSW_ENDIAN));

    file.seek(0);
    stream >> header >> recordCount >> fieldCount >> recordSize >> stringSize;

    // Check 'WDBC'
    if (header != 0x43424457)
        return false; 

    fieldsOffset = new quint32[fieldCount];
    fieldsOffset[0] = 0;
    for (quint32 i = 1; i < fieldCount; i++)
    {
        fieldsOffset[i] = fieldsOffset[i - 1];
        if (fmt[i - 1] == 'b' || fmt[i - 1] == 'X')
            fieldsOffset[i] += 1;
        else
            fieldsOffset[i] += 4;
    }

    data = new char[recordSize * recordCount + stringSize];
    stringTable = data + recordSize * recordCount;

    file.seek(20);
    file.read(data, recordSize * recordCount + stringSize);

    file.close();

    return true;
}

DBCFileLoader::~DBCFileLoader()
{
    if (data)
        delete []data;

    if (fieldsOffset)
        delete []fieldsOffset;
}

DBCFileLoader::Record DBCFileLoader::getRecord(size_t id)
{
    assert(data);
    return Record(*this, data + id * recordSize);
}

quint32 DBCFileLoader::GetFormatRecordSize(const QString format, qint32* index_pos)
{
    quint32 recordsize = 0;
    qint32 i = -1;
    for (quint32 x = 0; x < format.length(); ++x)
    {
        switch (format[x].toAscii())
        {
            case FT_FLOAT:
            case FT_INT:
            case FT_STRING:
                recordsize += 4;
                break;
            case FT_SORT:
                i = x;
                break;
            case FT_IND:
                i = x;
                recordsize += 4;
                break;
            case FT_BYTE:
                recordsize += 1;
                break;
        }
    }

    if (index_pos)
        *index_pos = i;

    return recordsize;
}

char* DBCFileLoader::AutoProduceData(const QString format, quint32& records, char**& indexTable)
{
    typedef char* ptr;

    if (format.length() != fieldCount)
        return NULL;

    // Get struct size and index pos
    qint32 i;
    quint32 recordsize = GetFormatRecordSize(format, &i);

    if (i >= 0)
    {
        quint32 maxi = 0;
        // Find max index
        for (quint32 y = 0; y < recordCount; y++)
        {
            quint32 ind = getRecord(y).getUInt(i);
            if (ind > maxi)
                maxi = ind;
        }

        ++maxi;
        records = maxi;
        indexTable = new ptr[maxi];
        memset(indexTable, 0, maxi * sizeof(ptr));
    }
    else
    {
        records = recordCount;
        indexTable = new ptr[recordCount];
    }

    char* dataTable = new char[recordCount * recordsize];

    quint32 offset = 0;

    for (quint32 y = 0; y < recordCount; y++)
    {
        if (i >= 0)
            indexTable[getRecord(y).getUInt(i)] = &dataTable[offset];
        else
            indexTable[y] = &dataTable[offset];

        for (quint32 x = 0; x < fieldCount; x++)
        {
            switch (format[x].toAscii())
            {
                case FT_FLOAT:
                    *((float*)(&dataTable[offset])) = getRecord(y).getFloat(x);
                    offset += 4;
                    break;
                case FT_IND:
                case FT_INT:
                    *((quint32*)(&dataTable[offset])) = getRecord(y).getUInt(x);
                    offset += 4;
                    break;
                case FT_BYTE:
                    *((quint8*)(&dataTable[offset])) = getRecord(y).getUInt8(x);
                    offset += 1;
                    break;
                case FT_STRING:
                    // Will be replaces non-empty or "" strings in AutoProduceStrings
                    *((char**)(&dataTable[offset])) = NULL;
                    offset += sizeof(char*);
                    break;
            }
        }
    }

    return dataTable;
}

char* DBCFileLoader::AutoProduceStrings(const QString format, char* dataTable)
{
    if (format.length() != fieldCount)
        return NULL;

    char* stringPool = new char[stringSize];
    memcpy(stringPool, stringTable, stringSize);

    quint32 offset = 0;

    for (quint32 y = 0; y < recordCount; y++)
    {
        for (quint32 x = 0; x < fieldCount; x++)
        {
            switch (format[x].toAscii())
            {
                case FT_FLOAT:
                case FT_IND:
                case FT_INT:
                    offset += 4;
                    break;
                case FT_BYTE:
                    offset += 1;
                    break;
                case FT_STRING:
                {
                    // Fill only not filled entries
                    char** slot = (char**)(&dataTable[offset]);
                    if (!*slot || !**slot)
                    {
                        const char* st = getRecord(y).getString(x);
                        *slot = stringPool + (st - (const char*)stringTable);
                    }
                    offset += sizeof(char*);
                    break;
                }
                case FT_NA:
                case FT_NA_BYTE:
                case FT_SORT:
                    break;
                default:
                    assert(false && "Unknown format character");
            }
        }
    }

    return stringPool;
}

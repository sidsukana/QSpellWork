#ifndef DBC_FILE_LOADER_H
#define DBC_FILE_LOADER_H

#include <QtCore/QtGlobal>
#include "Platform/Define.h"
#include "Utilities/ByteConverter.h"
#include <cassert>

enum
{
    FT_NA       = 'x',                                         // Not used or unknown, 4 byte size
    FT_NA_BYTE  = 'X',                                         // Not used or unknown, byte
    FT_STRING   = 's',                                         // char*
    FT_FLOAT    = 'f',                                         // float
    FT_INT      = 'i',                                         // uint32
    FT_BYTE     = 'b',                                         // uint8
    FT_SORT     = 'd',                                         // Sorted by this field, field is not included
    FT_IND      = 'n',                                         // The same, but parsed to data
    FT_LOGIC    = 'l'                                          // Logical (boolean)
};

class DBCFileLoader
{
    public:
        DBCFileLoader();
        ~DBCFileLoader();

        bool Load(const char* filename, const char* fmt);

        class Record
        {
            public:
                float getFloat(size_t field) const
                {
                    assert(field < file.fieldCount);
                    float val = *reinterpret_cast<float*>(offset + file.GetOffset(field));
                    EndianConvert(val);
                    return val;
                }
                quint32 getUInt(size_t field) const
                {
                    assert(field < file.fieldCount);
                    quint32 val = *reinterpret_cast<quint32*>(offset + file.GetOffset(field));
                    EndianConvert(val);
                    return val;
                }
                quint8 getUInt8(size_t field) const
                {
                    assert(field < file.fieldCount);
                    return *reinterpret_cast<quint8*>(offset + file.GetOffset(field));
                }
                const char* getString(size_t field) const
                {
                    assert(field < file.fieldCount);
                    size_t stringOffset = getUInt(field);
                    assert(stringOffset < file.stringSize);
                    return reinterpret_cast<char*>(file.stringTable + stringOffset);
                }

            private:
                Record(DBCFileLoader &file_,  char* offset_): offset(offset_), file(file_) {}
                char* offset;
                DBCFileLoader &file;

                friend class DBCFileLoader;
        };

        // Get record by id
        Record getRecord(size_t id);

        quint32 GetNumRows() const { return recordCount; }
        quint32 GetCols() const { return fieldCount; }
        quint32 GetOffset(size_t id) const { return ((fieldsOffset != NULL && id < fieldCount) ? fieldsOffset[id] : 0); }

        bool IsLoaded() { return (data != NULL); }
        char* AutoProduceData(const char* fmt, quint32& count, char**& indexTable);
        char* AutoProduceStrings(const char* fmt, char* dataTable);
        static quint32 GetFormatRecordSize(const char* format, qint32* index_pos = NULL);
    private:

        quint32 recordSize;
        quint32 recordCount;
        quint32 fieldCount;
        quint32 stringSize;
        quint32* fieldsOffset;
        char* data;
        char* stringTable;
};
#endif

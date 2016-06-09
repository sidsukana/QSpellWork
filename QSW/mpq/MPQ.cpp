#include <QHash>

#include "StormLib/StormLib.h"
#include "MPQ.h"

QString& MPQ::mpqDir()
{
    static QString mpqDir;
    return mpqDir;
}

QStringList& MPQ::mpqFiles()
{
    static QStringList mpqFiles;
    return mpqFiles;
}

HANDLE getHandle(const QString &mpq)
{
    static QHash<QString, HANDLE> archives;

    if (archives.contains(mpq))
        return archives[mpq];
    else {
        HANDLE hMPQ;

        if (!SFileOpenArchive(mpq.toUtf8().constData(), 0, STREAM_FLAG_READ_ONLY, &hMPQ)) {
            qCritical("Cannot open archive '%s'", qPrintable(mpq));
            hMPQ = 0;
        }

        return (archives[mpq] = hMPQ);
    }
}

QByteArray MPQ::readFile(const QString &fileName)
{
    HANDLE hMPQ = 0;

    for (QStringList::iterator mpq = mpqFiles().begin(); mpq != mpqFiles().end(); ++mpq) {
        QString path = mpqDir() + *mpq;

        hMPQ = getHandle(path);

        if (hMPQ && SFileHasFile(hMPQ, fileName.toUtf8().constData()))
            break;
        else
            hMPQ = 0;
    }

    if (!hMPQ) {
        qCritical("File '%s' not found", qPrintable(fileName));
        return QByteArray();
    }

    HANDLE hFile;

    if (!SFileOpenFileEx(hMPQ, fileName.toUtf8().constData(), SFILE_OPEN_FROM_MPQ, &hFile)) {
        qCritical("Cannot open file '%s' from archive", qPrintable(fileName));
        return QByteArray();
    }

    DWORD size = SFileGetFileSize(hFile, nullptr);

    if (size == SFILE_INVALID_SIZE) {
        qCritical("Cannot read file '%s' from archive", qPrintable(fileName));
        return QByteArray();
    }

    char *data = new char[size];

    if (!SFileReadFile(hFile, data, size, nullptr, nullptr)) {
        qCritical("Cannot read file '%s' from archive", qPrintable(fileName));
        SFileCloseFile(hFile);
        delete[] data;
        return QByteArray();
    }

    SFileCloseFile(hFile);

    QByteArray bytes = QByteArray(data, size);

    delete[] data;

    return bytes;
}

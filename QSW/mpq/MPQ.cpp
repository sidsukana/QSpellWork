#include <QHash>

#include "StormLib/StormLib.h"
#include "MPQ.h"

QString& MPQ::mpqDir()
{
    static QString mpqDir;
    return mpqDir;
}

QString& MPQ::localeDir()
{
    static QString localeDir;
    return localeDir;
}

MPQList &MPQ::mpqFiles()
{
    static MPQList mpqFiles;
    return mpqFiles;
}

void MPQ::setMpqFiles(const MPQList& files)
{
    MPQ::mpqFiles().clear();
    for (auto file = files.begin(); file != files.end(); ++file) {
        QString mpq = file->first;
        QStringList patches = file->second;
        QStringList mpqPatches;
        foreach (QString patch, patches) {
            mpqPatches << patch.replace("%locale%", MPQ::localeDir());
        }
        mpq = mpq.replace("%locale%", MPQ::localeDir());
        mpqFiles() << MPQPair(mpq, mpqPatches);

    }
}

HANDLE getHandle(const QString &mpq, const QStringList& patches)
{
    static QHash<QString, HANDLE> archives;

    if (!archives.contains(mpq)) {

        HANDLE hMPQ;

        QString tmpq = MPQ::mpqDir() + mpq;
        if (!SFileOpenArchive((const TCHAR*)(tmpq.toUtf8().constData()), 0, STREAM_FLAG_READ_ONLY, &hMPQ)) {
            qCritical("Cannot open archive '%s'", qPrintable(mpq));
            hMPQ = 0;
        }

        foreach (QString patch, patches) {
            tmpq = MPQ::mpqDir() + patch;
            if (!SFileOpenPatchArchive(hMPQ, (const TCHAR*)(tmpq.toUtf8().constData()), nullptr, 0)) {
                qCritical("Cannot open patch archive '%s'", qPrintable(patch));
            }
        }

        return (archives[mpq] = hMPQ);
    }

    return archives[mpq];

}

QByteArray MPQ::readFile(const QString &fileName)
{
    HANDLE hMPQ = 0;

    for (auto mpq = mpqFiles().begin(); mpq != mpqFiles().end(); ++mpq) {

        hMPQ = getHandle(mpq->first, mpq->second);

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

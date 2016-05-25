#include <QHash>

#include "StormLib/StormLib.h"
#include "MPQ.h"

QString & MPQ::gameDir()
{
    static QString gameDir;
    return gameDir;
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
    static QHash<QString, QByteArray> files;

    static const QString mpqs[] = {
		"ruRU/patch-3.MPQ",		// custom ruRU locale by Maus Team
        "patch-2.MPQ",
        "patch.MPQ",
        "dbc.MPQ",
        "model.MPQ",
        "interface.MPQ",
        "texture.MPQ",
        ""
    };

    if (files.contains(fileName))
        return files[fileName];

    const QString *mpq = mpqs;

    HANDLE hMPQ = 0;

    while (!mpq->isEmpty()) {
        QString path = gameDir() + "Data/" + *mpq;

        hMPQ = getHandle(path);

		if (hMPQ && SFileHasFile(hMPQ, fileName.toUtf8().constData()))
            break;
        else
            hMPQ = 0;
        mpq++;
    }

    if (!hMPQ) {
        qCritical("File '%s' not found", qPrintable(fileName));
        return files[fileName];
    }

    HANDLE hFile;

    if (!SFileOpenFileEx(hMPQ, fileName.toUtf8().constData(), SFILE_OPEN_FROM_MPQ, &hFile)) {
        qCritical("Cannot open file '%s' from archive", qPrintable(fileName));
        return files[fileName];
    }

    DWORD size = SFileGetFileSize(hFile, nullptr);

    if (size == SFILE_INVALID_SIZE) {
        qCritical("Cannot read file '%s' from archive", qPrintable(fileName));
        return files[fileName];
    }

    char *data = new char[size];

    if (!SFileReadFile(hFile, data, size, nullptr, nullptr)) {
        qCritical("Cannot read file '%s' from archive", qPrintable(fileName));
        SFileCloseFile(hFile);
        delete[] data;
        return files[fileName];
    }

    SFileCloseFile(hFile);

    files[fileName] = QByteArray(data, size);

    delete[] data;

    return files[fileName];
}

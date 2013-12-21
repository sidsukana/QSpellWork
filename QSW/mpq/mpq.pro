#-------------------------------------------------
#
# Project created by QtCreator 2013-12-17T11:42:36
#
#-------------------------------------------------

QT       -= gui

TARGET = mpq


TEMPLATE = lib

DEFINES += MPQ_LIBRARY __STORMLIB_SELF__

SOURCES += mpq.cpp

HEADERS += mpq.h\
        mpq_global.h

win32:CONFIG(release, debug|release): DLLDESTDIR = $$OUT_PWD/../../../bin/release/
else:win32:CONFIG(debug, debug|release): DLLDESTDIR = $$OUT_PWD/../../../bin/debug/

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/StormLib/release/ -lStormLib_dll
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/StormLib/debug/ -lStormLib_dll

INCLUDEPATH += $$PWD/StormLib
DEPENDPATH += $$PWD/StormLib

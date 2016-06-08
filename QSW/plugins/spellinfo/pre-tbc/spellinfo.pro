TEMPLATE        = lib
CONFIG         += plugin
HEADERS         = spellinfo.h \
    structure.h
SOURCES         = spellinfo.cpp \
    structure.cpp
TARGET          = pre-tbc

OTHER_FILES =

win32: {
    contains(QT_ARCH, i386) {
        PLATFORM = "Win32"
    } else {
        PLATFORM = "x64"
    }
    CONFIG(debug, debug|release) {
        BUILDTYPE = "Debug"
    } else {
        BUILDTYPE = "Release"
    }
}
DLLDESTDIR = $$PWD/../../../build-qsw/bin/$$PLATFORM/$$BUILDTYPE/plugins/spellinfo

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../build-qsw/bin/Win32/Release/ -lQSW
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../build-qsw/bin/Win32/Debug/ -lQSW

INCLUDEPATH += $$PWD/../../../
DEPENDPATH += $$PWD/../../../

RESOURCES +=

TEMPLATE        = lib
CONFIG         += plugin
HEADERS         = spellinfo.h \
    structure.h
SOURCES         = spellinfo.cpp \
    structure.cpp
TARGET          = cata

defineTest(copyToDestdir) {
    files = $$1

    for(FILE, files) {

        DDIR = $$DESTDIR\\$$2

        win32:FILE ~= s,/,\\,g
        win32:DDIR ~= s,/,\\,g

        QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$FILE) $$quote($$DDIR) $$escape_expand(\\n\\t)
    }

    export(QMAKE_POST_LINK)
}

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
DESTDIR = $$DLLDESTDIR

copyToDestdir($$PWD/cata.css)
copyToDestdir($$PWD/cata.html)
copyToDestdir($$PWD/cata.xml)

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../build-qsw/bin/Win32/Release/ -lQSW
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../build-qsw/bin/Win32/Debug/ -lQSW

INCLUDEPATH += $$PWD/../../../
DEPENDPATH += $$PWD/../../../

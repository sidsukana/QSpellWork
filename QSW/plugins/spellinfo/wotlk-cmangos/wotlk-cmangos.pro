TEMPLATE        = lib
CONFIG         += plugin
QT             += sql
HEADERS         = spellinfo.h \
    structure.h
SOURCES         = spellinfo.cpp \
    structure.cpp
TARGET          = wotlk-cmangos

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

    LIBS += -L$$PWD/../../../../build-qsw/bin/$$PLATFORM/$$BUILDTYPE/ -lQSW

    DLLDESTDIR = $$PWD/../../../../build-qsw/bin/$$PLATFORM/$$BUILDTYPE/plugins/spellinfo/$$TARGET
    DESTDIR = $$DLLDESTDIR

    copyToDestdir($$PWD/template.css)
    copyToDestdir($$PWD/template.html)
    copyToDestdir($$PWD/enums.json)
}

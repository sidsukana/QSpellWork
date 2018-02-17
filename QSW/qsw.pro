#-------------------------------------------------
#
# Project created by QtCreator 2013-12-21T16:05:53
#
#-------------------------------------------------

QT += core gui xml qml widgets webenginewidgets webengine webenginecore concurrent sql

TARGET = QSW
TEMPLATE = app
CONFIG -= debug_and_release
CONFIG += c++11
DEFINES += __STORMLIB_SELF__ QSW_LIB

INCLUDEPATH += $$PWD/mpq/StormLib
DEPENDPATH += $$PWD/mpq/StormLib

win32:RC_ICONS += resources/mangos.ico

SOURCES += \
    AboutForm.cpp \
    Alphanum.cpp \
    MainForm.cpp \
    ScriptEdit.cpp \
    SettingsForm.cpp \
    blp/blp.cpp \
    dbc/DBC.cpp \
    mpq/MPQ.cpp \
    wov/bone.cpp \
    wov/camerashake.cpp \
    wov/m2.cpp \
    wov/model.cpp \
    wov/modelscene.cpp \
    wov/mvp.cpp \
    wov/particleemitter.cpp \
    wov/ribbonemitter.cpp \
    wov/spellvisual.cpp \
    wov/spellvisualkit.cpp \
    wov/texture.cpp \
    wov/textureanimation.cpp \
    Main.cpp \
    wov/wovdbc.cpp \
    mustache/mustache.cpp \
    models.cpp \
    qsw.cpp \
    spellwork.cpp \
    wov/wov.cpp \
    settings.cpp \
    datasource.cpp \
    dataformat.cpp

HEADERS  += \
    AboutForm.h \
    Alphanum.h \
    MainForm.h \
    ScriptEdit.h \
    SettingsForm.h \
    blp/blp.h \
    dbc/DBC.h \
    mpq/MPQ.h \
    wov/animatedvalue.h \
    wov/bone.h \
    wov/camerashake.h \
    wov/m2.h \
    wov/m2structures.h \
    wov/model.h \
    wov/modelscene.h \
    wov/mvp.h \
    wov/particleemitter.h \
    wov/ribbonemitter.h \
    wov/spellvisual.h \
    wov/spellvisualkit.h \
    wov/texture.h \
    wov/textureanimation.h \
    wov/wovdbc.h \
    mustache/mustache.h \
    models.h \
    events.h \
    qsw.h \
    spellwork.h \
    wov/wov.h \
    settings.h \
    datasource.h \
    dataformat.h

FORMS += \
    about.ui \
    main.ui \
    settings.ui \
    scriptFilter.ui

OTHER_FILES += \
    wov/particle.fs \
    wov/particle.vs \
    wov/shader.fs \
    wov/shader.vs

RESOURCES += \
    qsw.qrc \
    wov/wov.qrc

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

    LIBS += -L$$PWD/mpq/StormLib/$$PLATFORM/$$BUILDTYPE/ -lStormLib
    LIBS += -L$$PWD/blp/squish/$$PLATFORM/$$BUILDTYPE/ -lsquish
    DLLDESTDIR = $$OUT_PWD/bin/$$PLATFORM/$$BUILDTYPE/
    DESTDIR = $$DLLDESTDIR

    copyToDestdir($$PWD/mpq/StormLib/$$PLATFORM/$$BUILDTYPE/StormLib.dll)

    QMAKE_POST_LINK += windeployqt --no-system-d3d-compiler --no-opengl-sw --no-svg --no-qmltooling $${DESTDIR}$${TARGET}.exe
}

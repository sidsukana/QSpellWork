#-------------------------------------------------
#
# Project created by QtCreator 2013-12-21T16:05:53
#
#-------------------------------------------------

QT += core gui xml qml widgets webenginewidgets webengine webenginecore concurrent

TARGET = QSW
TEMPLATE = app
CONFIG -= debug_and_release
CONFIG += c++11
DEFINES += __STORMLIB_SELF__

INCLUDEPATH += $$PWD/mpq/StormLib
DEPENDPATH += $$PWD/mpq/StormLib

win32:RC_ICONS += resources/mangos.ico

SOURCES += \
    AboutForm.cpp \
    Alphanum.cpp \
    Defines.cpp \
    MainForm.cpp \
    ScriptEdit.cpp \
    SettingsForm.cpp \
    SWEnums.cpp \
    SWModels.cpp \
    SWObject.cpp \
    WovWidget.cpp \
    blp/blp.cpp \
    dbc/DBC.cpp \
    dbc/DBCStructure.cpp \
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
    mustache/mustache.cpp

HEADERS  += \
    AboutForm.h \
    Alphanum.h \
    Defines.h \
    MainForm.h \
    ScriptEdit.h \
    SettingsForm.h \
    SWEnums.h \
    SWEvent.h \
    SWModels.h \
    SWObject.h \
    WovWidget.h \
    blp/blp.h \
    dbc/DBC.h \
    dbc/DBCStructure.h \
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
    mustache/mustache.h

FORMS += \
    about.ui \
    main.ui \
    settings.ui \
    advancedFilter.ui

OTHER_FILES += \
    wov/particle.fs \
    wov/particle.vs \
    wov/shader.fs \
    wov/shader.vs

RESOURCES += \
    qsw.qrc \
    wov/wov.qrc

win32:RELEASE_LIBS += \
    $(QTDIR)/bin/libEGL.dll \
    $(QTDIR)/bin/libGLESv2.dll \
    $(QTDIR)/bin/Qt5Core.dll \
    $(QTDIR)/bin/Qt5Gui.dll \
    $(QTDIR)/bin/Qt5Network.dll \
    $(QTDIR)/bin/Qt5Qml.dll \
    $(QTDIR)/bin/Qt5Quick.dll \
    $(QTDIR)/bin/Qt5WebChannel.dll \
    $(QTDIR)/bin/Qt5WebEngine.dll \
    $(QTDIR)/bin/Qt5WebEngineCore.dll \
    $(QTDIR)/bin/Qt5WebEngineWidgets.dll \
    $(QTDIR)/bin/Qt5Widgets.dll \
    $(QTDIR)/bin/Qt5Xml.dll

win32:DEBUG_LIBS += \
    $(QTDIR)/bin/libEGLd.dll \
    $(QTDIR)/bin/libGLESv2d.dll \
    $(QTDIR)/bin/Qt5Cored.dll \
    $(QTDIR)/bin/Qt5Guid.dll \
    $(QTDIR)/bin/Qt5Networkd.dll \
    $(QTDIR)/bin/Qt5Qmld.dll \
    $(QTDIR)/bin/Qt5Quickd.dll \
    $(QTDIR)/bin/Qt5WebChanneld.dll \
    $(QTDIR)/bin/Qt5WebEngined.dll \
    $(QTDIR)/bin/Qt5WebEngineCored.dll \
    $(QTDIR)/bin/Qt5WebEngineWidgetsd.dll \
    $(QTDIR)/bin/Qt5Widgetsd.dll \
    $(QTDIR)/bin/Qt5Xmld.dll

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

defineTest(createDir) {

    DIR = $$1
    win32:DIR ~= s,/,\\,g
    QMAKE_POST_LINK += $$sprintf($$QMAKE_MKDIR_CMD, $$DIR) $$escape_expand(\\n\\t) #$$QMAKE_MKDIR_CMD $$quote($$DIR) $$escape_expand(\\n\\t)
    export(QMAKE_POST_LINK)
}

defineTest(copyDirToDestdir) {

    DIR = $$1
    DDIR = $$DESTDIR\\$$2

    win32:DIR ~= s,/,\\,g
    win32:DDIR ~= s,/,\\,g

    QMAKE_POST_LINK += $$sprintf($$QMAKE_MKDIR_CMD, $$DDIR) $$escape_expand(\\n\\t)# $$QMAKE_MKDIR_CMD $$quote($$DDIR) $$escape_expand(\\n\\t)
    QMAKE_POST_LINK += $$QMAKE_COPY_DIR $$quote($$DIR) $$quote($$DDIR) $$escape_expand(\\n\\t)

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
    DLLDESTDIR = $$OUT_PWD/bin/$$PLATFORM/$$BUILDTYPE
    DESTDIR = $$DLLDESTDIR

    copyToDestdir($$PWD/mpq/StormLib/$$PLATFORM/$$BUILDTYPE/StormLib.dll)
    copyDirToDestdir($$PWD/data, data)

    createDir($$DESTDIR/imageformats)
    createDir($$DESTDIR/platforms)

    CONFIG(debug, debug|release) {
        copyToDestdir($$DEBUG_LIBS)
        copyToDestdir($(QTDIR)/plugins/imageformats/qicod.dll, imageformats)
        copyToDestdir($(QTDIR)/plugins/imageformats/qjpegd.dll, imageformats)
        copyToDestdir($(QTDIR)/plugins/platforms/qminimald.dll, platforms)
        copyToDestdir($(QTDIR)/plugins/platforms/qwindowsd.dll, platforms)
        copyToDestdir($(QTDIR)/plugins/platforms/qoffscreend.dll, platforms)
    } else {
        copyToDestdir($$RELEASE_LIBS)
        copyToDestdir($(QTDIR)/plugins/imageformats/qico.dll, imageformats)
        copyToDestdir($(QTDIR)/plugins/imageformats/qjpeg.dll, imageformats)
        copyToDestdir($(QTDIR)/plugins/platforms/qminimal.dll, platforms)
        copyToDestdir($(QTDIR)/plugins/platforms/qwindows.dll, platforms)
        copyToDestdir($(QTDIR)/plugins/platforms/qoffscreen.dll, platforms)
    }
}

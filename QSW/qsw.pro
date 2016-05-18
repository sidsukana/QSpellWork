#-------------------------------------------------
#
# Project created by QtCreator 2013-12-21T16:05:53
#
#-------------------------------------------------

QT += core gui xml qml widgets webenginewidgets webengine webenginecore concurrent

TARGET = qsw
TEMPLATE = app
CONFIG -= debug_and_release
CONFIG += c++11
DEFINES += __STORMLIB_SELF__

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
    wov/wovdbc.cpp

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
    wov/wovdbc.h

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

INCLUDEPATH += $$PWD/mpq/StormLib
DEPENDPATH += $$PWD/mpq/StormLib

win32: {
    contains(QT_ARCH, i386) {
        message("32-bit")
        CONFIG(debug, debug|release) {
            LIBS += -L$$PWD/mpq/StormLib/Win32/Debug -lStormLib
            LIBS += -L$$PWD/blp/squish/Win32/Debug -lsquish
            DLLDESTDIR = $$OUT_PWD/../bin/Win32/Debug/
        } else {
            LIBS += -L$$PWD/mpq/StormLib/Win32/Release/ -lStormLib
            LIBS += -L$$PWD/blp/squish/Win32/Release/ -lsquish
            DLLDESTDIR = $$OUT_PWD/../bin/Win32/Release/
        }
    } else {
        message("64-bit")
        CONFIG(debug, debug|release) {
            LIBS += -L$$PWD/mpq/StormLib/x64/Debug/ -lStormLib
            LIBS += -L$$PWD/blp/squish/x64/Debug/ -lsquish
            DLLDESTDIR = $$OUT_PWD/../bin/x64/Debug/
        } else {
            LIBS += -L$$PWD/mpq/StormLib/x64/Release/ -lStormLib
            LIBS += -L$$PWD/blp/squish/x64/Release/ -lsquish
            DLLDESTDIR = $$OUT_PWD/../bin/x64/Release/
        }
    }
}

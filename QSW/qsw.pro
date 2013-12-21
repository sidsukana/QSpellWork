#-------------------------------------------------
#
# Project created by QtCreator 2013-12-21T16:05:53
#
#-------------------------------------------------

QT       += core gui xml script opengl widgets webkitwidgets concurrent

TARGET = qsw
TEMPLATE = app
RC_FILE = icon.rc


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
    Main.cpp

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
    dbc/DBCStructure.h

FORMS    += \
    about.ui \
    advancedFilter.ui \
    main.ui \
    settings.ui

RESOURCES += \
    qsw.qrc

INCLUDEPATH += $$PWD

win32:CONFIG(release, debug|release): DLLDESTDIR = $$OUT_PWD/../../bin/release/
else:win32:CONFIG(debug, debug|release): DLLDESTDIR = $$OUT_PWD/../../bin/debug/

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/mpq/release/ -lmpq
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/mpq/debug/ -lmpq

INCLUDEPATH += $$PWD/mpq
DEPENDPATH += $$PWD/mpq

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/wov/release/ -lwov
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/wov/debug/ -lwov

INCLUDEPATH += $$PWD/wov
DEPENDPATH += $$PWD/wov

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/blp/squish/release/ -lsquish
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/blp/squish/debug/ -lsquish

INCLUDEPATH += $$PWD/blp/squish
DEPENDPATH += $$PWD/blp/squish

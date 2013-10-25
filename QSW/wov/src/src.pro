TEMPLATE = lib
TARGET = wov
QT += opengl

DEFINES += WOV_LIBRARY

HEADERS = \
    animatedvalue.h \
    bone.h \
    camerashake.h \
    dbc.h \
    global.h \
    m2.h \
    m2structures.h \
    model.h \
    modelscene.h \
    mpq.h \
    mvp.h \
    particleemitter.h \
    ribbonemitter.h \
    spellvisual.h \
    spellvisualkit.h \
    textureanimation.h \
    texture.h

SOURCES = \
    bone.cpp \
    camerashake.cpp \
    dbc.cpp \
    m2.cpp \
    model.cpp \
    modelscene.cpp \
    mpq.cpp \
    mvp.cpp \
    particleemitter.cpp \
    ribbonemitter.cpp \
    spellvisual.cpp \
    spellvisualkit.cpp \
    textureanimation.cpp \
    texture.cpp

unix:LIBS += -lstorm

win32:INCLUDEPATH += ../StormLib/src
win32:LIBS += -L$$PWD/../StormLib/stormlib_dll -lStormLib_dll

RESOURCES += src.qrc

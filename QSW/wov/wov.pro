#-------------------------------------------------
#
# Project created by QtCreator 2013-12-17T12:09:42
#
#-------------------------------------------------

QT       += opengl

QT       -= gui

TARGET = wov

TEMPLATE = lib

DEFINES += WOV_LIBRARY

SOURCES += \
    bone.cpp \
    camerashake.cpp \
    dbc.cpp \
    m2.cpp \
    model.cpp \
    modelscene.cpp \
    mvp.cpp \
    particleemitter.cpp \
    ribbonemitter.cpp \
    spellvisual.cpp \
    spellvisualkit.cpp \
    texture.cpp \
    textureanimation.cpp

HEADERS += \
    animatedvalue.h \
    bone.h \
    camerashake.h \
    dbc.h \
    m2.h \
    m2structures.h \
    model.h \
    modelscene.h \
    mvp.h \
    particleemitter.h \
    ribbonemitter.h \
    spellvisual.h \
    spellvisualkit.h \
    texture.h \
    textureanimation.h \
    wov_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

OTHER_FILES += \
    particle.fs \
    particle.vs \
    shader.fs \
    shader.vs

RESOURCES += \
    wov.qrc

win32:CONFIG(release, debug|release): DLLDESTDIR = $$OUT_PWD/../../../bin/release/
else:win32:CONFIG(debug, debug|release): DLLDESTDIR = $$OUT_PWD/../../../bin/debug/

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../mpq/release/ -lmpq
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../mpq/debug/ -lmpq

INCLUDEPATH += $$PWD/../mpq
DEPENDPATH += $$PWD/../mpq

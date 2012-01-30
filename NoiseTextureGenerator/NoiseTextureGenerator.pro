#-------------------------------------------------
#
# Project created by QtCreator 2012-01-26T20:19:30
#
#-------------------------------------------------

QT       += core gui

TARGET = NoiseTextureGenerator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    noisemodulescene.cpp \
    noisemodule.cpp \
    arrow.cpp

HEADERS  += mainwindow.h \
    noisemodulescene.h \
    noisemodule.h \
    arrow.h

FORMS    += mainwindow.ui

unix|win32: LIBS += -lnoise

INCLUDEPATH += /usr/local/include/noise

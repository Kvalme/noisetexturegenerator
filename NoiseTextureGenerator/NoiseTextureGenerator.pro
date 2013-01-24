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
    arrow.cpp \
    noiseoutput.cpp \
    tinyXml/tinyxml.cpp \
    tinyXml/tinystr.cpp \
    tinyXml/tinyxmlparser.cpp \
    tinyXml/tinyxmlerror.cpp \
    Generation/generation.cpp \
    PreviewRenderer/previewrenderer.cpp \
    Generation/noisexmlbuilder.cpp \
    Generation/ntgploader.cpp \
    GradientEditor/gradienteditor.cpp \
    libclnoise/src/clnoise.cpp \
    libclnoise/src/clnoisemodule.cpp \
    libclnoise/src/clnoiseoutput.cpp

HEADERS  += mainwindow.h \
    noisemodulescene.h \
    noisemodule.h \
    arrow.h \
    noiseoutput.h \
    tinyXml/tinystr.h \
    tinyXml/tinyxml.h \
    Generation/generation.h \
    PreviewRenderer/previewrenderer.h \
    Generation/noisexmlbuilder.h \
    Generation/ntgploader.h \
    GradientEditor/gradienteditor.h \
    libclnoise/src/clnoise.h \
    libclnoise/src/clnoiseerror.h \
    libclnoise/src/clnoisemodule.h \
    libclnoise/src/clnoisemoduleattribute.h \
    libclnoise/src/clnoiseoutput.h

FORMS    += mainwindow.ui \
    PreviewRenderer/previewrenderer.ui

INCLUDEPATH += libclnoise/src

RESOURCES += \
    base.qrc

LIBS += -lOpenCL

QMAKE_CXXFLAGS += -Wno-cpp -std=c++11
QMAKE_CXXFLAGS_RELEASE += -g0 -O3 -mfpmath=sse,387 -msse -msse2 -msse3
QMAKE_CXXFLAGS_DEBUG += -Wno-cpp -std=c++11 -g3 -O0

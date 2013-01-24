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
    libclnoisecl/src/clnoise.cpp \
    libclnoisecl/src/clnoisemodule.cpp \
    libclnoisecl/src/clnoiseoutput.cpp

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
    libclnoisecl/src/clnoisecl.h \
    libclnoisecl/src/clnoiseclerror.h \
    libclnoisecl/src/clnoisemodule.h \
    libclnoisecl/src/clnoisemoduleattribute.h \
    libclnoisecl/src/clnoiseoutput.h

FORMS    += mainwindow.ui \
    PreviewRenderer/previewrenderer.ui

INCLUDEPATH += .

RESOURCES += \
    base.qrc

QMAKE_CXXFLAGS += -Wno-cpp -std=c++11
QMAKE_CXXFLAGS_RELEASE += -O3 -mfpmath=sse,387 -msse -msse2 -msse3

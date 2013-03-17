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
    Generation/ntgploader.cpp \
    GradientEditor/gradienteditor.cpp \
    noisemoduleconnector.cpp \
    noisemodifier.cpp \
    oclutils.cpp \
    libclnoise/src/output.cpp \
    libclnoise/src/noisemap.cpp \
    libclnoise/src/noise.cpp \
    libclnoise/src/library.cpp \
    libclnoise/src/generator.cpp \
    libclnoise/src/function.cpp \
    libclnoise/src/filter.cpp \
    libclnoise/src/basemodule.cpp

HEADERS  += mainwindow.h \
    noisemodulescene.h \
    noisemodule.h \
    arrow.h \
    noiseoutput.h \
    tinyXml/tinystr.h \
    tinyXml/tinyxml.h \
    Generation/generation.h \
    PreviewRenderer/previewrenderer.h \
    Generation/ntgploader.h \
    GradientEditor/gradienteditor.h \
    noisemoduleconnector.h \
    noisemodifier.h \
    oclutils.h \
    libclnoise/src/output.h \
    libclnoise/src/noisemap.h \
    libclnoise/src/noise.h \
    libclnoise/src/library.h \
    libclnoise/src/generator.h \
    libclnoise/src/function.h \
    libclnoise/src/filter.h \
    libclnoise/src/error.h \
    libclnoise/src/basemodule.h \
    libclnoise/src/attribute.h

FORMS    += mainwindow.ui \
    PreviewRenderer/previewrenderer.ui

INCLUDEPATH += libclnoise/headers

RESOURCES += \
    base.qrc

LIBS += -lOpenCL

QMAKE_CXXFLAGS += -Wno-cpp -std=c++0x
QMAKE_CXXFLAGS_RELEASE += -g0 -O3 -mfpmath=sse,387 -msse -msse2 -msse3
QMAKE_CXXFLAGS_DEBUG += -g3 -O0 -DDEBUG

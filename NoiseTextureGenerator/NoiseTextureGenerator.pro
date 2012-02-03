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
    noisetransformer.cpp \
    noiseselector.cpp \
    noiseoutput.cpp \
    noisemodifier.cpp \
    noisegenerator.cpp \
    noisecombiner.cpp \
    NoiseGenerators/billowoptions.cpp \
    NoiseGenerators/checkerboardoptions.cpp \
    NoiseGenerators/constoptions.cpp \
    NoiseGenerators/cylindersoptions.cpp \
    NoiseGenerators/perlinoptions.cpp \
    NoiseGenerators/ridgedmultioptions.cpp \
    NoiseGenerators/spheresoptions.cpp \
    NoiseGenerators/voronoioptions.cpp \ 
    tinyXml/tinyxml.cpp \
    tinyXml/tinystr.cpp \
    tinyXml/tinyxmlparser.cpp \
    tinyXml/tinyxmlerror.cpp \
    NoiseOutput/planeoptions.cpp \
    NoiseOutput/sphereoptions.cpp \
    NoiseOutput/cylinderoutput.cpp \
    Generation/generation.cpp \
    PreviewRenderer/previewrenderer.cpp

HEADERS  += mainwindow.h \
    noisemodulescene.h \
    noisemodule.h \
    arrow.h \
    noisecombiner.h \
    noisetransformer.h \
    noiseselector.h \
    noiseoutput.h \
    noisemodifier.h \
    noisegenerator.h \
    NoiseGenerators/billowoptions.h \
    NoiseGenerators/checkerboardoptions.h \
    NoiseGenerators/constoptions.h \
    NoiseGenerators/cylindersoptions.h \
    NoiseGenerators/perlinoptions.h \
    NoiseGenerators/ridgedmultioptions.h \
    NoiseGenerators/spheresoptions.h \
    NoiseGenerators/voronoioptions.h \ 
    tinyXml/tinystr.h \
    tinyXml/tinyxml.h \
    NoiseOutput/planeoptions.h \
    NoiseOutput/sphereoptions.h \
    NoiseOutput/cylinderoutput.h \
    Generation/generation.h \
    PreviewRenderer/previewrenderer.h

FORMS    += mainwindow.ui \
    NoiseGenerators/billowoptions.ui \
    NoiseGenerators/checkerboardoptions.ui \
    NoiseGenerators/constoptions.ui \
    NoiseGenerators/cylindersoptions.ui \
    NoiseGenerators/perlinoptions.ui \
    NoiseGenerators/ridgedmultioptions.ui \
    NoiseGenerators/spheresoptions.ui \
    NoiseGenerators/voronoioptions.ui \
    NoiseOutput/planeoptions.ui \
    NoiseOutput/sphereoptions.ui \
    NoiseOutput/cylinderoutput.ui \
    PreviewRenderer/previewrenderer.ui

unix|win32: LIBS += -lnoise

INCLUDEPATH += /usr/local/include/noise

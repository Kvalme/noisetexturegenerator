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
    noiseutils.cpp \
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
    PreviewRenderer/previewrenderer.cpp \
    Generation/noisexmlbuilder.cpp \
    Generation/ntgploader.cpp \
    NoiseModifiers/modifierabs.cpp \
    NoiseModifiers/modifierclamp.cpp \
    NoiseModifiers/modifiercurve.cpp \
    NoiseModifiers/modifierexponent.cpp \
    NoiseModifiers/modifierinvert.cpp \
    NoiseModifiers/modifierscalebias.cpp \
    NoiseModifiers/modifierterrace.cpp \
    NoiseSelector/selectorblend.cpp \
    NoiseSelector/selectorselect.cpp \
    NoiseTransformer/transformerdisplace.cpp \
    NoiseTransformer/transformerrotatepoint.cpp \
    NoiseTransformer/transformerscalepoint.cpp \
    NoiseTransformer/transformertranslatepoint.cpp \
    NoiseTransformer/transformerturbulence.cpp \
    GradientEditor/gradienteditor.cpp

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
    PreviewRenderer/previewrenderer.h \
    Generation/noisexmlbuilder.h \
    Generation/ntgploader.h \
    NoiseModifiers/modifierabs.h \
    NoiseModifiers/modifierclamp.h \
    NoiseModifiers/modifiercurve.h \
    NoiseModifiers/modifierexponent.h \
    NoiseModifiers/modifierinvert.h \
    NoiseModifiers/modifierscalebias.h \
    NoiseModifiers/modifierterrace.h \
    NoiseSelector/selectorblend.h \
    NoiseSelector/selectorselect.h \
    NoiseTransformer/transformerdisplace.h \
    NoiseTransformer/transformerrotatepoint.h \
    NoiseTransformer/transformerscalepoint.h \
    NoiseTransformer/transformertranslatepoint.h \
    NoiseTransformer/transformerturbulence.h \
    GradientEditor/gradienteditor.h

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
    PreviewRenderer/previewrenderer.ui \
    NoiseModifiers/modifierabs.ui \
    NoiseModifiers/modifierclamp.ui \
    NoiseModifiers/modifiercurve.ui \
    NoiseModifiers/modifierexponent.ui \
    NoiseModifiers/modifierinvert.ui \
    NoiseModifiers/modifierscalebias.ui \
    NoiseModifiers/modifierterrace.ui \
    NoiseSelector/selectorblend.ui \
    NoiseSelector/selectorselect.ui \
    NoiseTransformer/transformerdisplace.ui \
    NoiseTransformer/transformerrotatepoint.ui \
    NoiseTransformer/transformerscalepoint.ui \
    NoiseTransformer/transformertranslatepoint.ui \
    NoiseTransformer/transformerturbulence.ui

unix|win32: LIBS += -lnoise

INCLUDEPATH += /usr/include/libnoise

RESOURCES += \
    base.qrc

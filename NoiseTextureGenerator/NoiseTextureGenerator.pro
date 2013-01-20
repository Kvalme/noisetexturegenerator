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
    GradientEditor/gradienteditor.cpp \
    libnoise/noise/src/latlon.cpp \
    libnoise/noise/src/noisegen.cpp \
    libnoise/noise/src/model/cylinder.cpp \
    libnoise/noise/src/model/line.cpp \
    libnoise/noise/src/model/plane.cpp \
    libnoise/noise/src/model/sphere.cpp \
    libnoise/noise/src/module/abs.cpp \
    libnoise/noise/src/module/add.cpp \
    libnoise/noise/src/module/billow.cpp \
    libnoise/noise/src/module/blend.cpp \
    libnoise/noise/src/module/cache.cpp \
    libnoise/noise/src/module/checkerboard.cpp \
    libnoise/noise/src/module/clamp.cpp \
    libnoise/noise/src/module/const.cpp \
    libnoise/noise/src/module/curve.cpp \
    libnoise/noise/src/module/cylinders.cpp \
    libnoise/noise/src/module/displace.cpp \
    libnoise/noise/src/module/exponent.cpp \
    libnoise/noise/src/module/invert.cpp \
    libnoise/noise/src/module/max.cpp \
    libnoise/noise/src/module/min.cpp \
    libnoise/noise/src/module/modulebase.cpp \
    libnoise/noise/src/module/multiply.cpp \
    libnoise/noise/src/module/perlin.cpp \
    libnoise/noise/src/module/power.cpp \
    libnoise/noise/src/module/ridgedmulti.cpp \
    libnoise/noise/src/module/rotatepoint.cpp \
    libnoise/noise/src/module/scalebias.cpp \
    libnoise/noise/src/module/scalepoint.cpp \
    libnoise/noise/src/module/select.cpp \
    libnoise/noise/src/module/spheres.cpp \
    libnoise/noise/src/module/terrace.cpp \
    libnoise/noise/src/module/translatepoint.cpp \
    libnoise/noise/src/module/turbulence.cpp \
    libnoise/noise/src/module/voronoi.cpp \
    libnoise/utils/noiseutils.cpp

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
    GradientEditor/gradienteditor.h \
    libnoise/noise/src/basictypes.h \
    libnoise/noise/src/exception.h \
    libnoise/noise/src/interp.h \
    libnoise/noise/src/latlon.h \
    libnoise/noise/src/mathconsts.h \
    libnoise/noise/src/misc.h \
    libnoise/noise/src/noise.h \
    libnoise/noise/src/noisegen.h \
    libnoise/noise/src/vectortable.h \
    libnoise/noise/src/model/cylinder.h \
    libnoise/noise/src/model/line.h \
    libnoise/noise/src/model/model.h \
    libnoise/noise/src/model/plane.h \
    libnoise/noise/src/model/sphere.h \
    libnoise/noise/src/module/abs.h \
    libnoise/noise/src/module/add.h \
    libnoise/noise/src/module/billow.h \
    libnoise/noise/src/module/blend.h \
    libnoise/noise/src/module/cache.h \
    libnoise/noise/src/module/checkerboard.h \
    libnoise/noise/src/module/clamp.h \
    libnoise/noise/src/module/const.h \
    libnoise/noise/src/module/curve.h \
    libnoise/noise/src/module/cylinders.h \
    libnoise/noise/src/module/displace.h \
    libnoise/noise/src/module/exponent.h \
    libnoise/noise/src/module/invert.h \
    libnoise/noise/src/module/max.h \
    libnoise/noise/src/module/min.h \
    libnoise/noise/src/module/module.h \
    libnoise/noise/src/module/modulebase.h \
    libnoise/noise/src/module/multiply.h \
    libnoise/noise/src/module/perlin.h \
    libnoise/noise/src/module/power.h \
    libnoise/noise/src/module/ridgedmulti.h \
    libnoise/noise/src/module/rotatepoint.h \
    libnoise/noise/src/module/scalebias.h \
    libnoise/noise/src/module/scalepoint.h \
    libnoise/noise/src/module/select.h \
    libnoise/noise/src/module/spheres.h \
    libnoise/noise/src/module/terrace.h \
    libnoise/noise/src/module/translatepoint.h \
    libnoise/noise/src/module/turbulence.h \
    libnoise/noise/src/module/voronoi.h \
    libnoise/utils/noiseutils.h

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

INCLUDEPATH += libnoise/noise \
    libnoise/noise/src \
    libnoise/utils

RESOURCES += \
    base.qrc

QMAKE_CXXFLAGS_RELEASE += -O3 -mfpmath=sse,387 -msse -msse2 -msse3

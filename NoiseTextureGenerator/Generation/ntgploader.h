#pragma once

#include "tinyXml/tinyxml.h"
#include "noisemodulescene.h"
#include "noisemodule.h"
#include "noiseoutput.h"
#include <map>

#include "noise.h"
#include "noiseutils.h"

class NTGPLoader
{
public:
    enum GeneratorType { Billow, Checkerboard, Const, Cylinders, Perlin, RidgedMulti, Spheres, Voronoi};
    enum OutputType { Cylinder, Plane, Sphere};
    enum ModifierType { Abs, Clamp, Curve, Exponent, Invert, ScaleBias, Terrace};
    enum CombinerType { Add, Max, Min, Multiply, Power};
    enum SelectorType { Blend, Select};

    NTGPLoader();
    void load(TiXmlDocument *doc, NoiseModuleScene *scene);

private:

    void readGenerators(TiXmlElement *src, NoiseModuleScene *scene);
    void readOutputs(TiXmlElement *src, NoiseModuleScene *scene);
    void readModifiers(TiXmlElement *src, NoiseModuleScene *scene);
    void readCombiners(TiXmlElement *src, NoiseModuleScene *scene);
    void readSelectors(TiXmlElement *src, NoiseModuleScene *scene);


    noise::module::Module* readGeneratorBillow(TiXmlElement *src);
    noise::module::Module* readGeneratorCheckerboard(TiXmlElement *src);
    noise::module::Module* readGeneratorConst(TiXmlElement *src);
    noise::module::Module* readGeneratorCylinders(TiXmlElement *src);
    noise::module::Module* readGeneratorPerlin(TiXmlElement *src);
    noise::module::Module* readGeneratorRidgedMulty(TiXmlElement *src);
    noise::module::Module* readGeneratorSpheres(TiXmlElement *src);
    noise::module::Module* readGeneratorVoronoi(TiXmlElement *src);

    noise::utils::NoiseMapBuilder* readOutputCylinder(TiXmlElement *src);
    noise::utils::NoiseMapBuilder* readOutputPlane(TiXmlElement *src);
    noise::utils::NoiseMapBuilder* readOutputSphere(TiXmlElement *src);

    noise::module::Module* readModifierAbs(TiXmlElement *src);
    noise::module::Module* readModifierClamp(TiXmlElement *src);
    noise::module::Module* readModifierCurve(TiXmlElement *src);
    noise::module::Module* readModifierExponent(TiXmlElement *src);
    noise::module::Module* readModifierInvert(TiXmlElement *src);
    noise::module::Module* readModifierScaleBias(TiXmlElement *src);
    noise::module::Module* readModifierTerrace(TiXmlElement *src);

    noise::module::Module* readCombinerAdd(TiXmlElement *src);
    noise::module::Module* readCombinerMax(TiXmlElement *src);
    noise::module::Module* readCombinerMin(TiXmlElement *src);
    noise::module::Module* readCombinerMultiply(TiXmlElement *src);
    noise::module::Module* readCombinerPower(TiXmlElement *src);

    noise::module::Module* readSelectorBlend(TiXmlElement *src);
    noise::module::Module* readSelectorSelect(TiXmlElement *src);

    void readLinks(TiXmlElement *src, NoiseModuleScene *scene);

    std::map<int, NoiseModule*> modules;

};

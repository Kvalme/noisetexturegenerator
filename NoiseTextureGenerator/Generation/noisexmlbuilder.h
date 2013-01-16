#ifndef NOISEXMLBUILDER_H
#define NOISEXMLBUILDER_H

#include "tinyXml/tinyxml.h"
#include <map>
#include <vector>

#include "noise.h"
#include "noiseutils.h"

class NoiseXMLBuilder
{
public:
    enum GeneratorType { Billow, Checkerboard, Const, Cylinders, Perlin, RidgedMulti, Spheres, Voronoi};
    enum OutputType { Cylinder, Plane, Sphere};
    enum ModifierType { Abs, Clamp, Curve, Exponent, Invert, ScaleBias, Terrace};
    enum CombinerType { Add, Max, Min, Multiply, Power};
    enum SelectorType { Blend, Select};

    struct GradientPoint
    {
        double pos;
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    };

    NoiseXMLBuilder();
    void load(TiXmlDocument *doc);
    noise::utils::Image* getImage(std::vector<GradientPoint> *gradient);

private:

    void readGenerators(TiXmlElement *src);
    void readOutputs(TiXmlElement *src);
    void readModifiers(TiXmlElement *src);
    void readCombiners(TiXmlElement *src);
    void readSelectors(TiXmlElement *src);


    noise::module::Module* readGeneratorBillow(TiXmlElement *src);
    noise::module::Module* readGeneratorCheckerboard(TiXmlElement *src);
    noise::module::Module* readGeneratorConst(TiXmlElement *src);
    noise::module::Module* readGeneratorCylinders(TiXmlElement *src);
    noise::module::Module* readGeneratorPerlin(TiXmlElement *src);
    noise::module::Module* readGeneratorRidgedMulty(TiXmlElement *src);
    noise::module::Module* readGeneratorSpheres(TiXmlElement *src);
    noise::module::Module* readGeneratorVoronoi(TiXmlElement *src);

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

    noise::utils::NoiseMapBuilder* readOutputCylinder(TiXmlElement *src);
    noise::utils::NoiseMapBuilder* readOutputPlane(TiXmlElement *src);
    noise::utils::NoiseMapBuilder* readOutputSphere(TiXmlElement *src);


    void readLinks(TiXmlElement *src);

    void connectOutputSources(noise::utils::NoiseMapBuilder *mod, int dstId);
    void connectSources(noise::module::Module *mod, int dstId);

    std::map<int, noise::module::Module*> modules;
    std::map<int, noise::utils::NoiseMapBuilder*> mapBuilders;
    std::map<noise::module::Module*, int> moduleIndexes;


};

#endif // NOISEXMLBUILDER_H

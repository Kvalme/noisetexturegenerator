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

    NTGPLoader();
    void load(TiXmlDocument *doc, NoiseModuleScene *scene);

private:

    void readGenerators(TiXmlElement *src, NoiseModuleScene *scene);
    void readOutputs(TiXmlElement *src, NoiseModuleScene *scene);


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
    void connectOutputSources(NoiseOutputModule *srcMod, TiXmlElement *src, NoiseModuleScene *scene);

    std::map<int, NoiseModule*> modules;

};

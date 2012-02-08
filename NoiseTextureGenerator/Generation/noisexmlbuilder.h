#ifndef NOISEXMLBUILDER_H
#define NOISEXMLBUILDER_H

#include "tinyXml/tinyxml.h"
#include <map>

#include "noise.h"
#include "noiseutils.h"

class NoiseXMLBuilder
{
public:
    enum GeneratorType { Billow, Checkerboard, Const, Cylinders, Perlin, RidgedMulti, Spheres, Voronoi};
    enum OutputType { Cylinder, Plane, Sphere};

    NoiseXMLBuilder();
    void load(TiXmlDocument *doc);
    noise::utils::Image* getImage();

private:

    void readGenerators(TiXmlElement *src);
    void readOutputs(TiXmlElement *src);


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
    void connectOutputSources(noise::utils::NoiseMapBuilder *mod, TiXmlElement *src);

    std::map<int, noise::module::Module*> modules;
    std::map<int, noise::utils::NoiseMapBuilder*> mapBuilders;


};

#endif // NOISEXMLBUILDER_H

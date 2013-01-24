#ifndef NOISEXMLBUILDER_H
#define NOISEXMLBUILDER_H

#include "tinyXml/tinyxml.h"
#include <map>
#include <vector>

class NoiseXMLBuilder
{
public:

    NoiseXMLBuilder();
    void load(TiXmlDocument *doc);
//    noise::utils::Image* getImage();

private:

    void readModules(TiXmlElement *src);
    void readGradient(TiXmlElement *src);
    void readLinks(TiXmlElement *src);

    /*void connectOutputSources(noise::utils::NoiseMapBuilder *mod, int dstId);
    void connectSources(noise::module::Module *mod, int dstId);*/

/*    std::map<int, noise::module::Module*> modules;
    std::map<noise::module::Module*, int> moduleIndexes;*/

    struct GradientPoint
    {
        double pos;
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    };
    std::vector<GradientPoint> gradient;
};

#endif // NOISEXMLBUILDER_H

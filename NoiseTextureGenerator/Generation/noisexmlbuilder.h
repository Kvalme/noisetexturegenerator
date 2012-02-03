#ifndef NOISEXMLBUILDER_H
#define NOISEXMLBUILDER_H

#include "tinyXml/tinyxml.h"
#include <map>

#include "noise.h"
#include "noiseutils.h"

class NoiseXMLBuilder
{
public:
    NoiseXMLBuilder();
    void load(TiXmlDocument *doc);

private:
    std::map<int, noise::module::Module*> modules;
    std::map<int, noise::utils::NoiseMapBuilder*> mapBuilders;


};

#endif // NOISEXMLBUILDER_H

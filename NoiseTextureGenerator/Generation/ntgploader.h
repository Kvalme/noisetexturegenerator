#pragma once

#include "tinyXml/tinyxml.h"
#include "noisemodulescene.h"
#include "noisemodule.h"
#include "noiseoutput.h"
#include "GradientEditor/gradienteditor.h"
#include <map>

class NTGPLoader
{
public:

    NTGPLoader();
    void load(TiXmlDocument *doc, NoiseModuleScene *scene, CLNoise::Noise *noise);

private:

    void readModules(TiXmlElement *src, NoiseModuleScene *scene, CLNoise::Noise *noise);
    NoiseModule* readModule(TiXmlElement *src, NoiseModuleScene *scene, CLNoise::Noise *noise);
    void readLinks(TiXmlElement *src, NoiseModuleScene *scene);

    std::map<int, NoiseModule*> modules;

};

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
    void load(TiXmlDocument *doc, NoiseModuleScene *scene, QVector<GradientEditor::GradientPoint> *gradientPoints);

private:

    void readModules(TiXmlElement *src, NoiseModuleScene *scene);
    void readGradient(TiXmlElement *src, QVector<GradientEditor::GradientPoint> *gradientPoints);
    void readLinks(TiXmlElement *src, NoiseModuleScene *);

    std::map<int, NoiseModule*> modules;

};

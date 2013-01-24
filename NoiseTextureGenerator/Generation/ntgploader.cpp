#include "ntgploader.h"
#include "noiseoutput.h"
#include "arrow.h"

NTGPLoader::NTGPLoader()
{
}
void NTGPLoader::load(TiXmlDocument *doc, NoiseModuleScene *scene, QVector<GradientEditor::GradientPoint> *gradientPoints)
{
    TiXmlElement *root = doc->RootElement();
    TiXmlElement *modules = root->FirstChildElement("Modules");
    TiXmlElement *xmlLinks = root->FirstChildElement("Links");
    TiXmlElement *gradient = root->FirstChildElement("Gradient");

    if(modules)readModules(modules, scene);
    if(xmlLinks)readLinks(xmlLinks, scene);

    if(gradient)readGradient(gradient, gradientPoints);
}

void NTGPLoader::readGradient(TiXmlElement *src, QVector<GradientEditor::GradientPoint> *gradientPoints)
{
    gradientPoints->clear();
    for(TiXmlElement *point = src->FirstChildElement("Point"); point; point = point->NextSiblingElement("Point"))
    {
        float pos = (float)atof(point->Attribute("pos"));
        int r = atoi(point->Attribute("r"));
        int g = atoi(point->Attribute("g"));
        int b = atoi(point->Attribute("b"));
        int a = atoi(point->Attribute("a"));

        gradientPoints->push_back(GradientEditor::GradientPoint(pos, QColor(r, g, b, a)));
    }
}

void NTGPLoader::readModules(TiXmlElement *src, NoiseModuleScene *scene)
{
    for(TiXmlElement *generator = src->FirstChildElement("Module"); generator; generator = generator->NextSiblingElement("Module"))
    {
    }
}

void NTGPLoader::readLinks(TiXmlElement *src, NoiseModuleScene *scene )
{
    for(TiXmlElement *xmlLink = src->FirstChildElement("Link"); xmlLink; xmlLink = xmlLink->NextSiblingElement("Link"))
    {
        int fromId = atoi(xmlLink->Attribute("source"));
        int toId = atoi(xmlLink->Attribute("destination"));

        NoiseModule *fromMod = modules[fromId];
        NoiseModule *toMod = modules[toId];
        if(!fromMod || !toMod)continue;

        Arrow *arrow = new Arrow(fromMod, toMod);
        fromMod->addArrow(arrow);
        toMod->addArrow(arrow);
        arrow->setZValue(-1000.0);
        arrow->updatePosition();
        scene->addItem(arrow);
    }
}


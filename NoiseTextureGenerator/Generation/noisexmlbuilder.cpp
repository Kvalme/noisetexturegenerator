#include <iostream>
#include "noisexmlbuilder.h"

NoiseXMLBuilder::NoiseXMLBuilder()
{
}
void NoiseXMLBuilder::load(TiXmlDocument *doc)
{
    TiXmlElement *root = doc->RootElement();
    TiXmlElement *modules = root->FirstChildElement("Modules");
    TiXmlElement *xmlLinks = root->FirstChildElement("Links");
    TiXmlElement *xmlGradient = root->FirstChildElement("Gradient");

    readModules(modules);
    readLinks(xmlLinks);

//    readGradient(xmlGradient);
}
void NoiseXMLBuilder::readModules(TiXmlElement *src)
{
    for(TiXmlElement *generator = src->FirstChildElement("Module"); generator; generator = generator->NextSiblingElement("Module"))
    {
    }
}
/*void NoiseXMLBuilder::connectOutputSources(noise::utils::NoiseMapBuilder *mod, int dstId)
{
    noise::module::Module *module = modules[dstId];
    if(!module)
    {
        std::cerr<<"ERROR! No module with id="<<dstId<<std::endl;
        return;
    }
    mod->SetSourceModule(*module);
}
void NoiseXMLBuilder::connectSources(noise::module::Module *mod, int dstId)
{
    noise::module::Module *module = modules[dstId];
    if(!module)
    {
        std::cerr<<"ERROR! No module with id="<<dstId<<std::endl;
        return;
    }
    int index = 0;
    std::map<noise::module::Module*, int>::iterator indexIt = moduleIndexes.find(mod);
    if(indexIt == moduleIndexes.end())
    {
        moduleIndexes.insert(std::make_pair(mod, index));
    }
    else
    {
        index = ++indexIt->second;
    }
    mod->SetSourceModule(index, *module);
}
*/
/*
noise::utils::Image* NoiseXMLBuilder::getImage()
{
    utils::NoiseMap noiseMap;
    noise::utils::NoiseMapBuilder *builder = mapBuilders.begin()->second;
    builder->SetDestNoiseMap(noiseMap);
    builder->Build();

    utils::Image *img = new utils::Image;
    utils::RendererImage renderer;
    renderer.SetSourceNoiseMap(noiseMap);
    renderer.SetDestImage(*img);
    if(!gradient.empty())
    {
        renderer.ClearGradient();
        for(std::vector<GradientPoint>::iterator it = gradient.begin(); it != gradient.end(); ++it)
        {

            noise::utils::Color color(it->r, it->g, it->b, it->a);
            renderer.AddGradientPoint(it->pos, color);
        }
    }
    else
    {
//        renderer.BuildGrayscaleGradient();
    }

    renderer.Render();
    return img;
}
*/


void NoiseXMLBuilder::readLinks(TiXmlElement *src)
{
/*    for(TiXmlElement *xmlLink = src->FirstChildElement("Link"); xmlLink; xmlLink = xmlLink->NextSiblingElement("Link"))
    {
        int fromId = atoi(xmlLink->Attribute("source"));
        int toId = atoi(xmlLink->Attribute("destination"));

        std::map<int, noise::utils::NoiseMapBuilder*>::iterator mapBuilderModule = mapBuilders.find(toId);

        if(mapBuilderModule != mapBuilders.end()) //Output module
        {
            connectOutputSources(mapBuilderModule->second, fromId);
        }
        else
        {
            std::map<int, noise::module::Module*>::iterator module = modules.find(toId);
            connectSources(module->second, fromId);
        }
    }*/
}

void NoiseXMLBuilder::readGradient(TiXmlElement *src)
{
    gradient.clear();
    for(TiXmlElement *point = src->FirstChildElement("Point"); point; point = point->NextSiblingElement("Point"))
    {
        float pos = (float)atof(point->Attribute("pos"));
        int r = atoi(point->Attribute("r"));
        int g = atoi(point->Attribute("g"));
        int b = atoi(point->Attribute("b"));
        int a = atoi(point->Attribute("a"));

        GradientPoint p = {pos, r, g, b, a};

        gradient.push_back(p);
    }
}


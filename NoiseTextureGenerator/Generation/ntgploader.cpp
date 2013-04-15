#include "ntgploader.h"
#include "noiseoutput.h"
#include "noisemodifier.h"
#include "arrow.h"
#include "clnoise/gradientattribute.h"

NTGPLoader::NTGPLoader()
{
}
void NTGPLoader::load(TiXmlDocument *doc, NoiseModuleScene *scene, CLNoise::Noise *noise)
{
    TiXmlElement *root = doc->RootElement();
    TiXmlElement *xmlModules = root->FirstChildElement("Modules");
    TiXmlElement *xmlLinks = root->FirstChildElement("Links");

    if(xmlModules)readModules(xmlModules, scene, noise);
    if(xmlLinks)readLinks(xmlLinks, scene);
}

void NTGPLoader::readModules(TiXmlElement *src, NoiseModuleScene *scene, CLNoise::Noise *noise)
{
    for(TiXmlElement *xmlModule = src->FirstChildElement("Module"); xmlModule; xmlModule = xmlModule->NextSiblingElement("Module"))
    {
        NoiseModule *module = readModule(xmlModule, scene, noise);
        if(!module) continue;

        int id = atol(xmlModule->Attribute("id"));
        float xpos = atof(xmlModule->Attribute("xpos"));
        float ypos = atof(xmlModule->Attribute("ypos"));

        modules.insert(std::make_pair(id, module));
        module->setPos(xpos, ypos);
    }
}

NoiseModule* NTGPLoader::readModule(TiXmlElement *src, NoiseModuleScene *scene, CLNoise::Noise *noise)
{
    int type = atol(src->Attribute("type"));
    const char *moduleName = src->Attribute("name");

    CLNoise::BaseModule *module;
    if(type == CLNoise::BaseModule::OUTPUT)
        module = dynamic_cast<CLNoise::Output*>(noise->createModule(moduleName, CLNoise::BaseModule::OUTPUT));
    else if(type == CLNoise::BaseModule::GENERATOR)
        module = dynamic_cast<CLNoise::BaseModule*>(noise->createModule(moduleName, CLNoise::BaseModule::GENERATOR));
    else if(type == CLNoise::BaseModule::FILTER)
        module = dynamic_cast<CLNoise::Filter*>(noise->createModule(moduleName, CLNoise::BaseModule::FILTER));

    if(!module)return 0;

    for(TiXmlElement *xmlAtt = src->FirstChildElement("Attribute"); xmlAtt; xmlAtt = xmlAtt->NextSiblingElement("Attribute"))
    {
        const char *attName = xmlAtt->Attribute("name");
        int type = atoi(xmlAtt->Attribute("type"));
        switch(type)
        {
            case CLNoise::Attribute::FLOAT:
            {
                CLNoise::Attribute att = module->getAttribute(std::string(attName));
                att.setValue((float)atof(xmlAtt->Attribute("value")));
                module->setAttribute(att);
                break;
            }
            case CLNoise::Attribute::INT:
            {
                CLNoise::Attribute att = module->getAttribute(std::string(attName));
                att.setValue(atoi(xmlAtt->Attribute("value")));
                module->setAttribute(att);
                break;
            }
            case CLNoise::Attribute::GRADIENT:
            {
                CLNoise::GradientAttribute g_a(attName);
                for(TiXmlElement *grad = xmlAtt->FirstChildElement("Gradient"); grad; grad = grad->NextSiblingElement("Gradient"))
                {
                    float pos = atof(grad->Attribute("pos"));
                    float r = atof(grad->Attribute("r"));
                    float g = atof(grad->Attribute("g"));
                    float b = atof(grad->Attribute("b"));
                    float a = atof(grad->Attribute("a"));
                    g_a.addPoint(pos, CLNoise::GradientAttribute::GradientPoint(r, g, b, a));
                }
                module->setAttribute(g_a);
                break;
            }
            default:
                break;
        }
    }
    return scene->addModule(noise, module, moduleName);
}

void NTGPLoader::readLinks(TiXmlElement *src, NoiseModuleScene * scene)
{
    for(TiXmlElement *xmlLink = src->FirstChildElement("Link"); xmlLink; xmlLink = xmlLink->NextSiblingElement("Link"))
    {
        int fromId = atoi(xmlLink->Attribute("source"));
        int toId = atoi(xmlLink->Attribute("destination"));
        int srcSlot = atoi(xmlLink->Attribute("sourceSlot"));
        int dstSlot = atoi(xmlLink->Attribute("destinationSlot"));

        NoiseModule *fromMod = modules[fromId];
        NoiseModule *toMod = modules[toId];
        if(!fromMod || !toMod)continue;
        NoiseModuleConnector *from = fromMod->getConnector(srcSlot, NoiseModuleConnector::OutputConnector);
        NoiseModuleConnector *to = toMod->getConnector(dstSlot, NoiseModuleConnector::InputConnector);
        if(!from || !to)continue;

        Arrow *arrow = new Arrow(from, to);
        from->addArrow(arrow);
        to->addArrow(arrow);
        arrow->setZValue(-1000.0);
        scene->addItem(arrow);
        arrow->updatePosition();
    }
}


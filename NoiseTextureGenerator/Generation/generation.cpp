#include "generation.h"
#include "noisemodulescene.h"
#include "clnoise/gradientattribute.h"

void NoiseXMLGenerator::prepareModules(const std::set<NoiseModule*> &modules)
{
    allModules.clear();

    int id=0;
    for (NoiseModule *module : modules)
    {
        allModules.insert(std::make_pair(module, id++));
    }
}

TiXmlDocument* NoiseXMLGenerator::generateExport(const std::set<NoiseModule*> &modules)
{
    doc = new TiXmlDocument();
    TiXmlElement *root = new TiXmlElement("NoiseMap");
    doc->LinkEndChild(root);

    generate(modules, root, false);

    return doc;
}
TiXmlDocument* NoiseXMLGenerator::generateSave(const std::set<NoiseModule*> &modules)
{
    doc = new TiXmlDocument();
    TiXmlElement *root = new TiXmlElement("NoiseTextureGeneratorProject");
    doc->LinkEndChild(root);

    generate(modules, root, true);

    return doc;
}

TiXmlDocument* NoiseXMLGenerator::generate(
        const std::set<NoiseModule*> &modules,
        TiXmlElement *root,
        bool isSave)
{
    xmlModules = new TiXmlElement("Modules");
    xmlLinks = new TiXmlElement("Links");

    root->LinkEndChild(xmlModules);
    root->LinkEndChild(xmlLinks);

    prepareModules(modules);

    writeModules(isSave);

    return 0;
}

void NoiseXMLGenerator::writeModules(bool savePosition)
{
    for (std::pair<NoiseModule*, int> mod : allModules)
    {
        int id = mod.second;
        TiXmlElement *xmlModule = new TiXmlElement("Module");
        xmlModules->LinkEndChild(xmlModule);

        xmlModule->SetAttribute("id", id);

        if(savePosition)
        {
            QPointF pos = mod.first->scenePos();
            xmlModule->SetAttribute("xpos", pos.x());
            xmlModule->SetAttribute("ypos", pos.y());
        }

        writeModule(mod.first, xmlModule);
        generateLinks(mod.first);
    }
}
void NoiseXMLGenerator::writeModule(NoiseModule *m, TiXmlElement *xmlModule)
{
    if(!m || !xmlModule)return;

    CLNoise::BaseModule*module = m->getNoiseModule();
    xmlModule->SetAttribute("name", module->getName().c_str());
    xmlModule->SetAttribute("type", module->getType());

    for(CLNoise::Attribute *att : module->getAttributes())
    {
        TiXmlElement *xmlAtt = new TiXmlElement("Attribute");
        xmlAtt->SetAttribute("name", att->getName().c_str());
        xmlAtt->SetAttribute("type", att->getType());
        switch(att->getType())
        {
            case CLNoise::Attribute::FLOAT:
                xmlAtt->SetDoubleAttribute("value", att->getFloat());
                break;
            case CLNoise::Attribute::INT:
                xmlAtt->SetAttribute("value", att->getInt());
                break;
            case CLNoise::Attribute::GRADIENT:
            {
                CLNoise::GradientAttribute *grad = static_cast<CLNoise::GradientAttribute*>(att);
                for (int a = 0; a < grad->getPointCount(); ++a)
                {
                    TiXmlElement *gradient = new TiXmlElement("Gradient");
                    float pos;
                    CLNoise::GradientAttribute::GradientPoint point(0, 0, 0, 0);
                    grad->getPoint(a, &pos, &point);
                    gradient->SetDoubleAttribute("pos", pos);
                    gradient->SetDoubleAttribute("r", point.r);
                    gradient->SetDoubleAttribute("g", point.g);
                    gradient->SetDoubleAttribute("b", point.b);
                    gradient->SetDoubleAttribute("a", point.a);
                    xmlAtt->LinkEndChild(gradient);
                }
                break;
            }
            default:
                break;
        }
        xmlModule->LinkEndChild(xmlAtt);
    }
}

void NoiseXMLGenerator::generateLinks(NoiseModule *module)
{
    auto childs = module->childItems();
    foreach( QGraphicsItem *child, childs)
    {
        if(child->type() != NoiseModuleScene::ConnectorModule)continue;
        NoiseModuleConnector *connector = dynamic_cast<NoiseModuleConnector*>(child);
        if(!connector)continue;
        if(connector->getConnectorType() != NoiseModuleConnector::InputConnector) continue;

        QList<Arrow*> arrows = connector->getArrows();
        int destId = allModules[module];
        int dstSlot = connector->getConnectorId();

        foreach(Arrow *arrow, arrows)
        {
            if(arrow->endItem() != connector) continue;
            int srcId = allModules[arrow->startItem()->getModule()];
            int srcSlot = arrow->startItem()->getConnectorId();

            writeLink(srcId, destId, srcSlot, dstSlot, connector->getConnectorType());
        }
    }
}


void NoiseXMLGenerator::writeLink(int src, int dst, int srcSlot, int dstSlot, NoiseModuleConnector::ConnectorType type)
{
    TiXmlElement *xmlLink = new TiXmlElement("Link");
    xmlLink->SetAttribute("source", src);
    xmlLink->SetAttribute("destination", dst);
    xmlLink->SetAttribute("sourceSlot", srcSlot);
    xmlLink->SetAttribute("destinationSlot", dstSlot);
    xmlLinks->LinkEndChild(xmlLink);
}


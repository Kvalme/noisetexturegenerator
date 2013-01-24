#include "generation.h"
#include <iostream>
void NoiseXMLGenerator::prepareModules(const std::set<NoiseModule*> &modules)
{
    std::cerr<<"Modules count:"<<modules.size()<<std::endl;
    allModules.clear();

    int id=0;
    for (NoiseModule *module : modules)
    {
        allModules.insert(std::make_pair(module, id++));
    }
}

TiXmlDocument* NoiseXMLGenerator::generateExport(const std::set<NoiseModule*> &modules, const QVector<GradientEditor::GradientPoint> &gradientPoints)
{
    doc = new TiXmlDocument();
    TiXmlElement *root = new TiXmlElement("NoiseMap");
    doc->LinkEndChild(root);

    generate(modules, gradientPoints, root, false);

    return doc;
}
TiXmlDocument* NoiseXMLGenerator::generateSave(const std::set<NoiseModule*> &modules, const QVector<GradientEditor::GradientPoint> &gradientPoints)
{
    doc = new TiXmlDocument();
    TiXmlElement *root = new TiXmlElement("NoiseTextureGeneratorProject");
    doc->LinkEndChild(root);

    generate(modules, gradientPoints, root, true);

    return doc;
}

TiXmlDocument* NoiseXMLGenerator::generate(
        const std::set<NoiseModule*> &modules,
        const QVector<GradientEditor::GradientPoint> &gradientPoints,
        TiXmlElement *root,
        bool isSave)
{
    xmlModules = new TiXmlElement("Modules");
    xmlLinks = new TiXmlElement("Links");
    gradient = new TiXmlElement("Gradient");

    root->LinkEndChild(xmlModules);
    root->LinkEndChild(xmlLinks);
    root->LinkEndChild(gradient);

    prepareModules(modules);

    writeModules(isSave);

    writeLinks();

    writeGradientPoints(gradientPoints);

}

void NoiseXMLGenerator::writeModules(bool savePosition)
{
    std::cerr<<__FUNCTION__<<std::endl;
/*    for(std::map<NoiseGeneratorModule*, int>::iterator it = generatorModules.begin(); it!=generatorModules.end(); ++it)
    {
        NoiseGeneratorModule *m = it->first;
        int id = it->second;
        TiXmlElement *generator = new TiXmlElement("Generator");
        generators->LinkEndChild(generator);
        generator->SetAttribute("id", id);
        generator->SetAttribute("type", m->getGeneratorType());
        if(savePosition)
        {
            generator->SetAttribute("PosX", m->pos().x());
            generator->SetAttribute("PosY", m->pos().y());
        }

        writeGenerator(m, generator);
    }*/
}
void NoiseXMLGenerator::writeModule(NoiseModule *m, TiXmlElement *generator)
{
    std::cerr<<__FUNCTION__<<std::endl;
}

void NoiseXMLGenerator::generateLinks(NoiseModule *m)
{
    QList<Arrow*> arrows = m->getArrows();
    if(arrows.empty())return;
    foreach(Arrow *arrow, arrows)
    {
        if(arrow->endItem()!=m)continue;
        std::map<NoiseModule*, int>::iterator it = allModules.find(arrow->startItem());
        std::map<NoiseModule*, int>::iterator itEnd = allModules.find(arrow->endItem());
        if(it==allModules.end())continue;
        if(itEnd == allModules.end())continue;

        links.insert(std::make_pair(it->second, itEnd->second));
    }
}


void NoiseXMLGenerator::writeLinks()
{
    for(std::map<int, int>::iterator it = links.begin(); it != links.end(); ++it)
    {
        TiXmlElement *xmlLink = new TiXmlElement("Link");
        xmlLink->SetAttribute("source", it->first);
        xmlLink->SetAttribute("destination", it->second);
        xmlLinks->LinkEndChild(xmlLink);
    }
}

void NoiseXMLGenerator::writeGradientPoints(const QVector<GradientEditor::GradientPoint> &gradientPoints)
{
    foreach (GradientEditor::GradientPoint point, gradientPoints)
    {
        TiXmlElement *xmlPoint = new TiXmlElement("Point");
        char buf[20];
        sprintf(buf, "%f", point.pos);
        xmlPoint->SetAttribute("pos", buf);
        xmlPoint->SetAttribute("r", point.color.red());
        xmlPoint->SetAttribute("g", point.color.green());
        xmlPoint->SetAttribute("b", point.color.blue());
        xmlPoint->SetAttribute("a", 255);

        gradient->LinkEndChild(xmlPoint);
    }
}

#pragma once

#include "tinyXml/tinyxml.h"
#include "noisemodule.h"
#include "noiseoutput.h"
#include <set>
#include <map>
#include "GradientEditor/gradienteditor.h"

class NoiseXMLGenerator
{
    public:
    TiXmlDocument* generateExport(const std::set<NoiseModule*>&);
    TiXmlDocument* generateSave(const std::set<NoiseModule*>&);

    private:
    TiXmlDocument* generate(const std::set<NoiseModule*>&, TiXmlElement *root, bool isSave);

    void prepareModules(const std::set<NoiseModule*>&);

    void writeModules(bool savePosition = false);
    void writeModule(NoiseModule *m, TiXmlElement *xmlModule);

    void generateLinks(NoiseModule *);
    void writeLink(int src, int dst, int srcSlot, int dstSlot, NoiseModuleConnector::ConnectorType type);

	TiXmlDocument *doc;
    TiXmlElement *xmlModules;
    TiXmlElement *xmlLinks;

	std::map<NoiseModule*, int> allModules;
};



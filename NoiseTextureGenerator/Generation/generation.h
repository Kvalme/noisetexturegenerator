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
    TiXmlDocument* generateExport(const std::set<NoiseModule*>&, const QVector<GradientEditor::GradientPoint> &gradientPoints);
    TiXmlDocument* generateSave(const std::set<NoiseModule*>&, const QVector<GradientEditor::GradientPoint> &gradientPoints);

    private:
    TiXmlDocument* generate(const std::set<NoiseModule*>&, const QVector<GradientEditor::GradientPoint> &gradientPoints, TiXmlElement *root, bool isSave);

    void prepareModules(const std::set<NoiseModule*>&);

    void writeModules(bool savePosition = false);
    void writeModule(NoiseModule *m, TiXmlElement *output);

    void generateLinks(NoiseModule *);
    void writeLinks();

    void writeGradientPoints(const QVector<GradientEditor::GradientPoint> &gradientPoints);

	TiXmlDocument *doc;
    TiXmlElement *xmlModules;
    TiXmlElement *xmlLinks;
    TiXmlElement *gradient;

	std::map<NoiseModule*, int> allModules;
    std::multimap<int, int> links;

};



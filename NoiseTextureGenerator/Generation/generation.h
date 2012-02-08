#pragma once

#include "tinyXml/tinyxml.h"
#include "noisemodule.h"
#include "noisegenerator.h"
#include "noiseoutput.h"
#include <set>
#include <map>

class NoiseXMLGenerator
{
    public:
	TiXmlDocument* generateExport(std::set<NoiseModule*>);
	TiXmlDocument* generateSave(std::set<NoiseModule*>);

    private:
	void writeGenerators(bool savePosition = false);
	void writeGenerator(NoiseGeneratorModule *m, TiXmlElement *generator);

	void writeOutputs(bool savePosition = false);
	void writeOutput(NoiseOutputModule *m, TiXmlElement *output);


	TiXmlDocument *doc;
	TiXmlElement *generators;
	TiXmlElement *outputs;
	std::map<NoiseGeneratorModule*, int> generatorModules;
	std::map<NoiseOutputModule*, int> outputModules;
	std::map<NoiseModule*, int> allModules;

};



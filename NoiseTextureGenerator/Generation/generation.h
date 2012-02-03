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
	TiXmlDocument* generate(std::set<NoiseModule*>);

    private:
	void writeGenerators();
	void writeGenerator(NoiseGeneratorModule *m, TiXmlElement *generator);

	void writeOutputs();
	void writeOutput(NoiseOutputModule *m, TiXmlElement *output);


	TiXmlDocument *doc;
	TiXmlElement *generators;
	TiXmlElement *outputs;
	std::map<NoiseGeneratorModule*, int> generatorModules;
	std::map<NoiseOutputModule*, int> outputModules;
	std::map<NoiseModule*, int> allModules;

};



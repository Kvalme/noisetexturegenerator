#pragma once

#include "tinyXml/tinyxml.h"
#include "noisemodule.h"
#include "noisegenerator.h"
#include "noiseoutput.h"
#include "noisemodifier.h"
#include "noisecombiner.h"
#include "noiseselector.h"
#include <set>
#include <map>

class NoiseXMLGenerator
{
    public:
	TiXmlDocument* generateExport(const std::set<NoiseModule*>&);
	TiXmlDocument* generateSave(const std::set<NoiseModule*>&);

    private:
	void prepareModules(const std::set<NoiseModule*>&);

	void writeGenerators(bool savePosition = false);
	void writeGenerator(NoiseGeneratorModule *m, TiXmlElement *generator);

	void writeOutputs(bool savePosition = false);
	void writeOutput(NoiseOutputModule *m, TiXmlElement *output);

	void writeModifiers(bool savePosition = false);
	void writeModifier(NoiseModifierModule *m, TiXmlElement *output);

	void writeCombiners(bool savePosition = false);
	void writeCombiner(NoiseCombinerModule *m, TiXmlElement *output);

	void writeSelectors(bool savePosition = false);
	void writeSelector(NoiseSelectorModule *m, TiXmlElement *output);



	TiXmlDocument *doc;
	TiXmlElement *generators;
	TiXmlElement *outputs;
	TiXmlElement *modifiers;
	TiXmlElement *combiners;
	TiXmlElement *selectors;
	std::map<NoiseGeneratorModule*, int> generatorModules;
	std::map<NoiseOutputModule*, int> outputModules;
	std::map<NoiseModifierModule*, int> modifierModules;
	std::map<NoiseCombinerModule*, int> combinerModules;
	std::map<NoiseSelectorModule*, int> selectorModules;
	std::map<NoiseModule*, int> allModules;

};



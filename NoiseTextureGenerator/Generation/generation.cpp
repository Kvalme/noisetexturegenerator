#include "generation.h"
#include <iostream>

TiXmlDocument* NoiseXMLGenerator::generateExport(std::set<NoiseModule*> modules)
{
    doc = new TiXmlDocument();
    TiXmlElement *root = new TiXmlElement("NoiseMap");
    doc->LinkEndChild(root);
    generators = new TiXmlElement("Generators");
    outputs = new TiXmlElement("Outputs");
    root->LinkEndChild(generators);
    root->LinkEndChild(outputs);

    std::cerr<<"Modules count:"<<modules.size()<<std::endl;

    generatorModules.clear();
    outputModules.clear();
    int id=0;
    for(std::set<NoiseModule*>::iterator it = modules.begin(); it!= modules.end(); ++it, ++id)
    {
	NoiseModule *module = *it;
	if(module->moduleType() == NoiseModule::Generator)
	{
	    NoiseGeneratorModule *m = dynamic_cast<NoiseGeneratorModule*>(module);
	    generatorModules.insert(std::make_pair(m, id));
	}
	else if(module->moduleType() == NoiseModule::Output)
	{
	    NoiseOutputModule *m = dynamic_cast<NoiseOutputModule*>(module);
	    outputModules.insert(std::make_pair(m, id));
	}
	allModules.insert(std::make_pair(module, id));
    }
    writeGenerators();
    writeOutputs();
    return doc;
}
TiXmlDocument* NoiseXMLGenerator::generateSave(std::set<NoiseModule*> modules)
{
    doc = new TiXmlDocument();
    TiXmlElement *root = new TiXmlElement("NoiseTextureGeneratorProject");
    doc->LinkEndChild(root);
    generators = new TiXmlElement("Generators");
    outputs = new TiXmlElement("Outputs");
    root->LinkEndChild(generators);
    root->LinkEndChild(outputs);

    std::cerr<<"Modules count:"<<modules.size()<<std::endl;

    generatorModules.clear();
    outputModules.clear();
    int id=0;
    for(std::set<NoiseModule*>::iterator it = modules.begin(); it!= modules.end(); ++it, ++id)
    {
	NoiseModule *module = *it;
	if(module->moduleType() == NoiseModule::Generator)
	{
	    NoiseGeneratorModule *m = dynamic_cast<NoiseGeneratorModule*>(module);
	    generatorModules.insert(std::make_pair(m, id));
	}
	else if(module->moduleType() == NoiseModule::Output)
	{
	    NoiseOutputModule *m = dynamic_cast<NoiseOutputModule*>(module);
	    outputModules.insert(std::make_pair(m, id));
	}
	allModules.insert(std::make_pair(module, id));
    }
    writeGenerators(true);
    writeOutputs(true);
    return doc;
}

void NoiseXMLGenerator::writeGenerators(bool savePosition)
{
    std::cerr<<__FUNCTION__<<std::endl;
    for(std::map<NoiseGeneratorModule*, int>::iterator it = generatorModules.begin(); it!=generatorModules.end(); ++it)
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
    }
}
void NoiseXMLGenerator::writeGenerator(NoiseGeneratorModule *m, TiXmlElement *generator)
{
    std::cerr<<__FUNCTION__<<std::endl;
    if(m->getGeneratorType() == NoiseGeneratorModule::Billow)
    {
	noise::module::Billow *mod = dynamic_cast<noise::module::Billow*>(m->getModule());
	generator->SetAttribute("OctaveCount", mod->GetOctaveCount());
	generator->SetDoubleAttribute("Frequency", mod->GetFrequency());
	generator->SetDoubleAttribute("Lacunarity", mod->GetLacunarity());
	generator->SetDoubleAttribute("Persistance", mod->GetPersistence());
	generator->SetAttribute("NoiseQuality", mod->GetNoiseQuality());
    }
    else if(m->getGeneratorType() == NoiseGeneratorModule::Const)
    {
	noise::module::Const *mod = dynamic_cast<noise::module::Const*>(m->getModule());
	generator->SetDoubleAttribute("ConstValue", mod->GetConstValue());
    }
    else if(m->getGeneratorType() == NoiseGeneratorModule::Cylinders)
    {
	noise::module::Cylinders *mod = dynamic_cast<noise::module::Cylinders*>(m->getModule());
	generator->SetDoubleAttribute("Frequency", mod->GetFrequency());
    }
    else if(m->getGeneratorType() == NoiseGeneratorModule::Perlin)
    {
	noise::module::Perlin *mod = dynamic_cast<noise::module::Perlin*>(m->getModule());
	generator->SetAttribute("OctaveCount", mod->GetOctaveCount());
	generator->SetDoubleAttribute("Frequency", mod->GetFrequency());
	generator->SetDoubleAttribute("Lacunarity", mod->GetLacunarity());
	generator->SetDoubleAttribute("Persistance", mod->GetPersistence());
	generator->SetAttribute("NoiseQuality", mod->GetNoiseQuality());
    }
    else if(m->getGeneratorType() == NoiseGeneratorModule::RidgedMulti)
    {
	noise::module::RidgedMulti *mod = dynamic_cast<noise::module::RidgedMulti*>(m->getModule());
	generator->SetAttribute("OctaveCount", mod->GetOctaveCount());
	generator->SetDoubleAttribute("Frequency", mod->GetFrequency());
	generator->SetDoubleAttribute("Lacunarity", mod->GetLacunarity());
	generator->SetAttribute("NoiseQuality", mod->GetNoiseQuality());
    }
    else if(m->getGeneratorType() == NoiseGeneratorModule::Spheres)
    {
	noise::module::Spheres *mod = dynamic_cast<noise::module::Spheres*>(m->getModule());
	generator->SetDoubleAttribute("Frequency", mod->GetFrequency());
    }
    else if(m->getGeneratorType() == NoiseGeneratorModule::Voronoi)
    {
	noise::module::Voronoi *mod = dynamic_cast<noise::module::Voronoi*>(m->getModule());
	generator->SetDoubleAttribute("Frequency", mod->GetFrequency());
	generator->SetDoubleAttribute("Displacement", mod->GetDisplacement());
    }
}
void NoiseXMLGenerator::writeOutputs(bool savePosition)
{
    std::cerr<<__FUNCTION__<<std::endl;
    for(std::map<NoiseOutputModule*, int>::iterator it = outputModules.begin(); it!=outputModules.end(); ++it)
    {
	NoiseOutputModule *m = it->first;
	int id = it->second;
	TiXmlElement *output = new TiXmlElement("Output");
	outputs->LinkEndChild(output);
	output->SetAttribute("id", id);
	output->SetAttribute("type", m->getOutputType());
	if(savePosition)
	{
	    output->SetAttribute("PosX", m->pos().x());
	    output->SetAttribute("PosY", m->pos().y());
	}

	writeOutput(m, output);
    }
}
void NoiseXMLGenerator::writeOutput(NoiseOutputModule *m, TiXmlElement *output)
{
    std::cerr<<__FUNCTION__<<std::endl;
    output->SetAttribute("Width", (int)(m->getModule()->GetDestWidth()));
    output->SetAttribute("Height", (int)(m->getModule()->GetDestHeight()));
    std::cerr<<"Output type:"<<m->getOutputType()<<std::endl;
    if(m->getOutputType() == NoiseOutputModule::Cylinder)
    {
	noise::utils::NoiseMapBuilderCylinder *mod = dynamic_cast<noise::utils::NoiseMapBuilderCylinder*>(m->getModule());
	output->SetDoubleAttribute("LowerAngleBound", mod->GetLowerAngleBound());
	output->SetDoubleAttribute("UpperAngleBound", mod->GetUpperAngleBound());
	output->SetDoubleAttribute("LowerHeightBound", mod->GetLowerHeightBound());
	output->SetDoubleAttribute("UpperHeightBound", mod->GetUpperHeightBound());
    }
    else if(m->getOutputType() == NoiseOutputModule::Plane)
    {
	noise::utils::NoiseMapBuilderPlane *mod = dynamic_cast<noise::utils::NoiseMapBuilderPlane*>(m->getModule());
	output->SetDoubleAttribute("LowerXBound", mod->GetLowerXBound());
	output->SetDoubleAttribute("UpperXBound", mod->GetUpperXBound());
	output->SetDoubleAttribute("LowerZBound", mod->GetLowerZBound());
	output->SetDoubleAttribute("UpperZBound", mod->GetUpperZBound());
	output->SetDoubleAttribute("Seamless", mod->IsSeamlessEnabled());
    }
    else if(m->getOutputType() == NoiseOutputModule::Sphere)
    {
	noise::utils::NoiseMapBuilderSphere *mod = dynamic_cast<noise::utils::NoiseMapBuilderSphere*>(m->getModule());
	output->SetDoubleAttribute("EastLonBound", mod->GetEastLonBound());
	output->SetDoubleAttribute("WestLonBound", mod->GetWestLonBound());
	output->SetDoubleAttribute("NorthLonBound", mod->GetNorthLatBound());
	output->SetDoubleAttribute("SouthLonBound", mod->GetSouthLatBound());
    }
    QList<Arrow*> arrows = m->getArrows();
    if(arrows.empty())return;
    Arrow* arrow;
    TiXmlElement *sources = new TiXmlElement("Sources");
    output->LinkEndChild(sources);
    foreach(arrow, arrows)
    {
	if(arrow->endItem()!=m)continue;
	std::map<NoiseModule*, int>::iterator it = allModules.find(arrow->startItem());
	if(it==allModules.end())continue;
	TiXmlElement *source = new TiXmlElement("Source");
	int id = it->second;
	source->SetAttribute("sourceId", id);
	sources->LinkEndChild(source);
    }
}

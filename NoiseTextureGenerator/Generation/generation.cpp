#include "generation.h"
#include <iostream>
void NoiseXMLGenerator::prepareModules(const std::set<NoiseModule*> &modules)
{
    std::cerr<<"Modules count:"<<modules.size()<<std::endl;
    generatorModules.clear();
    outputModules.clear();
    combinerModules.clear();
    modifierModules.clear();

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
	else if(module->moduleType() == NoiseModule::Modifier)
	{
	    NoiseModifierModule *m = dynamic_cast<NoiseModifierModule*>(module);
	    modifierModules.insert(std::make_pair(m, id));
	}
	else if(module->moduleType() == NoiseModule::Combiner)
	{
	    NoiseCombinerModule *m = dynamic_cast<NoiseCombinerModule*>(module);
	    combinerModules.insert(std::make_pair(m, id));
	}
	else if(module->moduleType() == NoiseModule::Selector)
	{
	    NoiseSelectorModule *m = dynamic_cast<NoiseSelectorModule*>(module);
	    selectorModules.insert(std::make_pair(m, id));
	}
	allModules.insert(std::make_pair(module, id));
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
    generators = new TiXmlElement("Generators");
    outputs = new TiXmlElement("Outputs");
    modifiers = new TiXmlElement("Modifiers");
    combiners = new TiXmlElement("Combiners");
    selectors = new TiXmlElement("Selectors");
    xmlLinks = new TiXmlElement("Links");
    gradient = new TiXmlElement("Gradient");

    root->LinkEndChild(generators);
    root->LinkEndChild(outputs);
    root->LinkEndChild(modifiers);
    root->LinkEndChild(combiners);
    root->LinkEndChild(selectors);
    root->LinkEndChild(xmlLinks);
    root->LinkEndChild(gradient);

    prepareModules(modules);

    writeGenerators(isSave);
    writeModifiers(isSave);
    writeCombiners(isSave);
    writeSelectors(isSave);
    writeOutputs(isSave);

    writeLinks();

    writeGradientPoints(gradientPoints);

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
        generator->SetAttribute("NoiseQuality", (int)mod->GetNoiseQuality());
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
        generator->SetAttribute("NoiseQuality", (int)mod->GetNoiseQuality());
    }
    else if(m->getGeneratorType() == NoiseGeneratorModule::RidgedMulti)
    {
        noise::module::RidgedMulti *mod = dynamic_cast<noise::module::RidgedMulti*>(m->getModule());
        generator->SetAttribute("OctaveCount", mod->GetOctaveCount());
        generator->SetDoubleAttribute("Frequency", mod->GetFrequency());
        generator->SetDoubleAttribute("Lacunarity", mod->GetLacunarity());
        generator->SetAttribute("NoiseQuality", (int)mod->GetNoiseQuality());
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

    generateLinks(m);
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

void NoiseXMLGenerator::writeModifiers(bool savePosition)
{
    std::cerr<<__FUNCTION__<<std::endl;
    for(std::map<NoiseModifierModule*, int>::iterator it = modifierModules.begin(); it!=modifierModules.end(); ++it)
    {
        NoiseModifierModule *m = it->first;
        int id = it->second;
        TiXmlElement *modifier= new TiXmlElement("Modifier");
        modifiers->LinkEndChild(modifier);
        modifier->SetAttribute("id", id);
        modifier->SetAttribute("type", m->getType());
        if(savePosition)
        {
            modifier->SetAttribute("PosX", m->pos().x());
            modifier->SetAttribute("PosY", m->pos().y());
        }
        writeModifier(m, modifier);
    }
}
void NoiseXMLGenerator::writeModifier(NoiseModifierModule *m, TiXmlElement *modifier)
{
    std::cerr<<__FUNCTION__<<std::endl;
    if(m->getType() == NoiseModifierModule::Clamp)
    {
        noise::module::Clamp *mod = dynamic_cast<noise::module::Clamp*>(m->getModule());
        modifier->SetDoubleAttribute("LowerBound", mod->GetLowerBound());
        modifier->SetDoubleAttribute("UpperBound", mod->GetUpperBound());
    }
    else if(m->getType() == NoiseModifierModule::Curve)
    {
        ///@TODO Implement curve
    }
    else if(m->getType() == NoiseModifierModule::Exponent)
    {
        noise::module::Exponent *mod = dynamic_cast<noise::module::Exponent*>(m->getModule());
        modifier->SetDoubleAttribute("Exponent", mod->GetExponent());
    }
    else if(m->getType() == NoiseModifierModule::ScaleBias)
    {
        noise::module::ScaleBias *mod = dynamic_cast<noise::module::ScaleBias*>(m->getModule());
        modifier->SetDoubleAttribute("Scale", mod->GetScale());
        modifier->SetDoubleAttribute("Bias", mod->GetBias());
    }
    else if(m->getType() == NoiseModifierModule::Terrace)
    {
        ///@TODO Implement terrace
    }

    generateLinks(m);
}

void NoiseXMLGenerator::writeCombiners(bool savePosition)
{
    std::cerr<<__FUNCTION__<<std::endl;
    for(std::map<NoiseCombinerModule*, int>::iterator it = combinerModules.begin(); it!=combinerModules.end(); ++it)
    {
        NoiseCombinerModule *m = it->first;
        int id = it->second;
        TiXmlElement *combiner= new TiXmlElement("Combiner");
        combiners->LinkEndChild(combiner);
        combiner->SetAttribute("id", id);
        combiner->SetAttribute("type", m->getType());
        if(savePosition)
        {
            combiner->SetAttribute("PosX", m->pos().x());
            combiner->SetAttribute("PosY", m->pos().y());
        }
        writeCombiner(m, combiner);
    }
}
void NoiseXMLGenerator::writeCombiner(NoiseCombinerModule *m, TiXmlElement *combiner)
{
    std::cerr<<__FUNCTION__<<std::endl;

    generateLinks(m);
}
void NoiseXMLGenerator::writeSelectors(bool savePosition)
{
    std::cerr<<__FUNCTION__<<std::endl;
    for(std::map<NoiseSelectorModule*, int>::iterator it = selectorModules.begin(); it!=selectorModules.end(); ++it)
    {
        NoiseSelectorModule *m = it->first;
        int id = it->second;
        TiXmlElement *selector= new TiXmlElement("Selector");
        selectors->LinkEndChild(selector);
        selector->SetAttribute("id", id);
        selector->SetAttribute("type", m->getType());
        if(savePosition)
        {
            selector->SetAttribute("PosX", m->pos().x());
            selector->SetAttribute("PosY", m->pos().y());
        }
        writeSelector(m, selector);
    }

}
void NoiseXMLGenerator::writeSelector(NoiseSelectorModule *m, TiXmlElement *output)
{
    std::cerr<<__FUNCTION__<<std::endl;
    if(m->getType() == NoiseSelectorModule::Select)
    {
        noise::module::Select *mod = dynamic_cast<noise::module::Select*>(m->getModule());
        output->SetDoubleAttribute("LowerBound", mod->GetLowerBound());
        output->SetDoubleAttribute("UpperBound", mod->GetUpperBound());
        output->SetDoubleAttribute("EdgeFalloff", mod->GetEdgeFalloff());
    }

    generateLinks(m);
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

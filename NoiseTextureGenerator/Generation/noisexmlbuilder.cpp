#include <iostream>
#include "noisexmlbuilder.h"

NoiseXMLBuilder::NoiseXMLBuilder()
{
}
void NoiseXMLBuilder::load(TiXmlDocument *doc)
{
    TiXmlElement *root = doc->RootElement();
    TiXmlElement *generators = root->FirstChildElement("Generators");
    TiXmlElement *outputs = root->FirstChildElement("Outputs");
    TiXmlElement *modifiers = root->FirstChildElement("Modifiers");
    TiXmlElement *combiners = root->FirstChildElement("Combiners");
    TiXmlElement *selectors = root->FirstChildElement("Selectors");
    TiXmlElement *xmlLinks = root->FirstChildElement("Links");

    readGenerators(generators);
    readCombiners(combiners);
    readModifiers(modifiers);
    readSelectors(selectors);
    readOutputs(outputs);

    readLinks(xmlLinks);
}
void NoiseXMLBuilder::readGenerators(TiXmlElement *src)
{
    for(TiXmlElement *generator = src->FirstChildElement("Generator"); generator; generator = generator->NextSiblingElement("Generator"))
    {
        noise::module::Module* module;
        GeneratorType type = (GeneratorType)atol(generator->Attribute("type"));
        int id = atol(generator->Attribute("id"));
        switch(type)
        {
            case Billow: module = readGeneratorBillow(generator); break;
            case Checkerboard: module = readGeneratorCheckerboard(generator); break;
            case Const: module = readGeneratorConst(generator); break;
            case Cylinders: module = readGeneratorCylinders(generator); break;
            case Perlin: module = readGeneratorPerlin(generator); break;
            case RidgedMulti: module = readGeneratorRidgedMulty(generator); break;
            case Spheres: module = readGeneratorSpheres(generator); break;
            case Voronoi: module = readGeneratorVoronoi(generator); break;
            default: module = 0;
        }
        if(!module)continue;
        modules.insert(std::make_pair(id, module));
    }
}
void NoiseXMLBuilder::readOutputs(TiXmlElement *src)
{
    for(TiXmlElement *output = src->FirstChildElement("Output"); output; output = output->NextSiblingElement("Output"))
    {
        noise::utils::NoiseMapBuilder* module;
        OutputType type = (OutputType)atol(output->Attribute("type"));
        int id = atol(output->Attribute("id"));
        switch(type)
        {
            case Cylinder: module = readOutputCylinder(output); break;
            case Plane: module = readOutputPlane(output); break;
            case Sphere: module = readOutputSphere(output); break;
            default: module = 0;
        }
        if(!module)continue;
        mapBuilders.insert(std::make_pair(id, module));
    }
}
void NoiseXMLBuilder::readModifiers(TiXmlElement *src)
{
    for(TiXmlElement *modifier = src->FirstChildElement("Modifier"); modifier; modifier = modifier->NextSiblingElement("Modifier"))
    {
	noise::module::Module* module;
	ModifierType type = (ModifierType)atol(modifier->Attribute("type"));
	int id = atol(modifier->Attribute("id"));
	switch(type)
	{
	    case Abs: module = readModifierAbs(modifier); break;
	    case Clamp: module = readModifierClamp(modifier); break;
	    case Curve: module = readModifierCurve(modifier); break;
	    case Exponent: module = readModifierExponent(modifier); break;
	    case Invert: module = readModifierInvert(modifier); break;
	    case ScaleBias: module = readModifierScaleBias(modifier); break;
	    case Terrace: module = readModifierTerrace(modifier); break;
	    default: module = 0;
	}
	if(!module)continue;
	modules.insert(std::make_pair(id, module));
    }
}
void NoiseXMLBuilder::readCombiners(TiXmlElement *src)
{
    for(TiXmlElement *combiner = src->FirstChildElement("Combiner"); combiner; combiner = combiner->NextSiblingElement("Combiner"))
    {
	noise::module::Module* module;
	CombinerType type = (CombinerType)atol(combiner->Attribute("type"));
	int id = atol(combiner->Attribute("id"));
	switch(type)
	{
	    case Add: module = readCombinerAdd(combiner); break;
	    case Max: module = readCombinerMax(combiner); break;
	    case Min: module = readCombinerMin(combiner); break;
	    case Multiply: module = readCombinerMultiply(combiner); break;
	    case Power: module = readCombinerPower(combiner); break;
	    default: module = 0;
	}
	if(!module)continue;
	modules.insert(std::make_pair(id, module));
    }
}
void NoiseXMLBuilder::readSelectors(TiXmlElement *src)
{
    for(TiXmlElement *selector= src->FirstChildElement("Selector"); selector; selector= selector->NextSiblingElement("Selector"))
    {
	noise::module::Module* module;
	SelectorType type = (SelectorType)atol(selector->Attribute("type"));
	int id = atol(selector->Attribute("id"));
	switch(type)
	{
	    case Blend: module = readSelectorBlend(selector); break;
	    case Select: module = readSelectorSelect(selector); break;
	    default: module = 0;
	}
	if(!module)continue;
	modules.insert(std::make_pair(id, module));
    }
}

noise::module::Module* NoiseXMLBuilder::readGeneratorBillow(TiXmlElement *src)
{
    noise::module::Billow *mod = new noise::module::Billow;
    mod->SetOctaveCount(atoi(src->Attribute("OctaveCount")));
    mod->SetNoiseQuality((noise::NoiseQuality)atoi(src->Attribute("NoiseQuality")));
    mod->SetFrequency(atof(src->Attribute("Frequency")));
    mod->SetLacunarity(atof(src->Attribute("Lacunarity")));
    mod->SetPersistence(atof(src->Attribute("Persistance")));
    return mod;
}
noise::module::Module* NoiseXMLBuilder::readGeneratorCheckerboard(TiXmlElement *src)
{
    noise::module::Checkerboard *mod = new noise::module::Checkerboard;
    return mod;
}
noise::module::Module* NoiseXMLBuilder::readGeneratorConst(TiXmlElement *src)
{
    noise::module::Const *mod = new noise::module::Const;
    mod->SetConstValue(atof(src->Attribute("ConstValue")));
    return mod;
}
noise::module::Module* NoiseXMLBuilder::readGeneratorCylinders(TiXmlElement *src)
{
    noise::module::Cylinders *mod = new noise::module::Cylinders;
    mod->SetFrequency(atof(src->Attribute("Frequency")));
    return mod;
}

noise::module::Module* NoiseXMLBuilder::readGeneratorPerlin(TiXmlElement *src)
{
    noise::module::Perlin *mod = new noise::module::Perlin;
    mod->SetOctaveCount(atoi(src->Attribute("OctaveCount")));
    mod->SetNoiseQuality((noise::NoiseQuality)atoi(src->Attribute("NoiseQuality")));
    mod->SetFrequency(atof(src->Attribute("Frequency")));
    mod->SetLacunarity(atof(src->Attribute("Lacunarity")));
    mod->SetPersistence(atof(src->Attribute("Persistance")));
    return mod;
}

noise::module::Module* NoiseXMLBuilder::readGeneratorRidgedMulty(TiXmlElement *src)
{
    noise::module::RidgedMulti *mod = new noise::module::RidgedMulti;
    mod->SetOctaveCount(atoi(src->Attribute("OctaveCount")));
    mod->SetNoiseQuality((noise::NoiseQuality)atoi(src->Attribute("NoiseQuality")));
    mod->SetFrequency(atof(src->Attribute("Frequency")));
    mod->SetLacunarity(atof(src->Attribute("Lacunarity")));
    return mod;
}

noise::module::Module* NoiseXMLBuilder::readGeneratorSpheres(TiXmlElement *src)
{
    noise::module::Spheres *mod = new noise::module::Spheres;
    mod->SetFrequency(atof(src->Attribute("Frequency")));
    return mod;
}

noise::module::Module* NoiseXMLBuilder::readGeneratorVoronoi(TiXmlElement *src)
{
    noise::module::Voronoi *mod = new noise::module::Voronoi;
    mod->SetDisplacement(atof(src->Attribute("Frequency")));
    mod->SetFrequency(atof(src->Attribute("Displacement")));
    return mod;
}


noise::utils::NoiseMapBuilder* NoiseXMLBuilder::readOutputCylinder(TiXmlElement *src)
{
    noise::utils::NoiseMapBuilderCylinder *mod = new noise::utils::NoiseMapBuilderCylinder;
    float lab, uab, lhb, uhb;
    int w, h;
    w = atoi(src->Attribute("Width"));
    h = atoi(src->Attribute("Height"));
    lab = atof(src->Attribute("LowerAngleBound"));
    uab = atof(src->Attribute("UpperAngleBound"));
    lhb = atof(src->Attribute("LowerHeightBound"));
    uhb = atof(src->Attribute("UpperHeightBound"));
    mod->SetBounds(lab, uab, lhb, uhb);
    mod->SetDestSize(w, h);

    return mod;
}

noise::utils::NoiseMapBuilder* NoiseXMLBuilder::readOutputPlane(TiXmlElement *src)
{
    noise::utils::NoiseMapBuilderPlane *mod = new noise::utils::NoiseMapBuilderPlane;
    float lxb, uxb, lzb, uzb;
    int w, h;
    w = atoi(src->Attribute("Width"));
    h = atoi(src->Attribute("Height"));
    lxb = atof(src->Attribute("LowerXBound"));
    uxb = atof(src->Attribute("UpperXBound"));
    lzb = atof(src->Attribute("LowerZBound"));
    uzb = atof(src->Attribute("UpperZBound"));
    mod->SetBounds(lxb, uxb, lzb, uzb);
    mod->SetDestSize(w, h);
    mod->EnableSeamless(atoi(src->Attribute("Seamless"))>0);

    return mod;
}

noise::utils::NoiseMapBuilder* NoiseXMLBuilder::readOutputSphere(TiXmlElement *src)
{
    noise::utils::NoiseMapBuilderSphere *mod = new noise::utils::NoiseMapBuilderSphere;
    float elb, wlb, nlb, slb;
    int w, h;
    w = atoi(src->Attribute("Width"));
    h = atoi(src->Attribute("Height"));
    elb = atof(src->Attribute("EastLonBound"));
    wlb = atof(src->Attribute("WestLonBound"));
    nlb = atof(src->Attribute("NorthLonBound"));
    slb = atof(src->Attribute("SouthLonBound"));

    mod->SetBounds(slb, nlb, wlb, elb);
    mod->SetDestSize(w, h);

    return mod;
}

void NoiseXMLBuilder::connectOutputSources(noise::utils::NoiseMapBuilder *mod, int dstId)
{
    noise::module::Module *module = modules[dstId];
    if(!module)
    {
        std::cerr<<"ERROR! No module with id="<<dstId<<std::endl;
        return;
    }
    mod->SetSourceModule(*module);
}
void NoiseXMLBuilder::connectSources(noise::module::Module *mod, int dstId)
{
    noise::module::Module *module = modules[dstId];
    if(!module)
    {
        std::cerr<<"ERROR! No module with id="<<dstId<<std::endl;
        return;
    }
    int index = 0;
    std::map<noise::module::Module*, int>::iterator indexIt = moduleIndexes.find(mod);
    if(indexIt == moduleIndexes.end())
    {
        moduleIndexes.insert(std::make_pair(mod, index));
    }
    else
    {
        index = ++indexIt->second;
    }
    mod->SetSourceModule(index, *module);
}

noise::utils::Image* NoiseXMLBuilder::getImage(std::vector<GradientPoint> *gradient)
{
    utils::NoiseMap noiseMap;
    noise::utils::NoiseMapBuilder *builder = mapBuilders.begin()->second;
    builder->SetDestNoiseMap(noiseMap);
    builder->Build();

    utils::Image *img = new utils::Image;
    utils::RendererImage renderer;
    renderer.SetSourceNoiseMap(noiseMap);
    renderer.SetDestImage(*img);
    if(gradient)
    {
        renderer.ClearGradient();
        for(std::vector<GradientPoint>::iterator it = gradient->begin(); it != gradient->end(); ++it)
        {

            noise::utils::Color color(it->r, it->g, it->b, it->a);
            renderer.AddGradientPoint(it->pos, color);
        }
    }
    renderer.Render();
    return img;
}

noise::module::Module* NoiseXMLBuilder::readModifierAbs(TiXmlElement *src)
{
    noise::module::Abs *mod = new noise::module::Abs;
    return mod;
}

noise::module::Module* NoiseXMLBuilder::readModifierClamp(TiXmlElement *src)
{
    noise::module::Clamp *mod = new noise::module::Clamp;
    float lb, ub;
    lb = atof(src->Attribute("LowerBound"));
    ub = atof(src->Attribute("UpperBound"));
    mod->SetBounds(lb, ub);
    return mod;
}

noise::module::Module* NoiseXMLBuilder::readModifierCurve(TiXmlElement *src)
{
    return 0;
}

noise::module::Module* NoiseXMLBuilder::readModifierExponent(TiXmlElement *src)
{
    noise::module::Exponent *mod = new noise::module::Exponent;
    mod->SetExponent(atof(src->Attribute("Exponent")));
    return mod;
}
noise::module::Module* NoiseXMLBuilder::readModifierInvert(TiXmlElement *src)
{
    noise::module::Invert *mod = new noise::module::Invert;
    return mod;
}

noise::module::Module* NoiseXMLBuilder::readModifierScaleBias(TiXmlElement *src)
{
    noise::module::ScaleBias *mod = new noise::module::ScaleBias;
    mod->SetScale(atof(src->Attribute("Scale")));
    mod->SetBias(atof(src->Attribute("Bias")));
    return mod;
}
noise::module::Module* NoiseXMLBuilder::readModifierTerrace(TiXmlElement *src)
{
    return 0;
}

noise::module::Module* NoiseXMLBuilder::readCombinerAdd(TiXmlElement *src)
{
    noise::module::Add *mod = new noise::module::Add;
    return mod;
}
noise::module::Module* NoiseXMLBuilder::readCombinerMax(TiXmlElement *src)
{
    noise::module::Max *mod = new noise::module::Max;
    return mod;
}
noise::module::Module* NoiseXMLBuilder::readCombinerMin(TiXmlElement *src)
{
    noise::module::Min *mod = new noise::module::Min;
    return mod;
}
noise::module::Module* NoiseXMLBuilder::readCombinerMultiply(TiXmlElement *src)
{
    noise::module::Multiply *mod = new noise::module::Multiply;
    return mod;
}
noise::module::Module* NoiseXMLBuilder::readCombinerPower(TiXmlElement *src)
{
    noise::module::Power *mod = new noise::module::Power;
    return mod;
}
noise::module::Module* NoiseXMLBuilder::readSelectorBlend(TiXmlElement *src)
{
    noise::module::Blend *mod = new noise::module::Blend;
    return mod;
}
noise::module::Module* NoiseXMLBuilder::readSelectorSelect(TiXmlElement *src)
{
    noise::module::Select *mod = new noise::module::Select;
    double lb, ub;
    lb = atof(src->Attribute("LowerBound"));
    ub = atof(src->Attribute("UpperBound"));
    mod->SetEdgeFalloff(atof(src->Attribute("EdgeFalloff")));
    mod->SetBounds(lb, ub);
    return mod;
}

void NoiseXMLBuilder::readLinks(TiXmlElement *src)
{
    for(TiXmlElement *xmlLink = src->FirstChildElement("Link"); xmlLink; xmlLink = xmlLink->NextSiblingElement("Link"))
    {
        int fromId = atoi(xmlLink->Attribute("source"));
        int toId = atoi(xmlLink->Attribute("destination"));

        std::map<int, noise::utils::NoiseMapBuilder*>::iterator mapBuilderModule = mapBuilders.find(toId);

        if(mapBuilderModule != mapBuilders.end()) //Output module
        {
            connectOutputSources(mapBuilderModule->second, fromId);
        }
        else
        {
            std::map<int, noise::module::Module*>::iterator module = modules.find(toId);
            connectSources(module->second, fromId);
        }
    }
}

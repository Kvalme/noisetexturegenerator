#include "ntgploader.h"
#include "noisegenerator.h"
#include "noiseoutput.h"
#include "noisemodifier.h"
#include "noisecombiner.h"
#include "noiseselector.h"
#include "arrow.h"

NTGPLoader::NTGPLoader()
{
}
void NTGPLoader::load(TiXmlDocument *doc, NoiseModuleScene *scene)
{
    TiXmlElement *root = doc->RootElement();
    TiXmlElement *generators = root->FirstChildElement("Generators");
    TiXmlElement *outputs = root->FirstChildElement("Outputs");
    TiXmlElement *modifiers = root->FirstChildElement("Modifiers");
    TiXmlElement *combiners = root->FirstChildElement("Combiners");
    TiXmlElement *selectors = root->FirstChildElement("Selectors");
    TiXmlElement *xmlLinks = root->FirstChildElement("Links");

    if(generators)readGenerators(generators, scene);
    if(outputs)readOutputs(outputs, scene);
    if(modifiers)readModifiers(modifiers, scene);
    if(combiners)readCombiners(combiners, scene);
    if(selectors)readSelectors(selectors, scene);

    if(xmlLinks)readLinks(xmlLinks, scene);
}

void NTGPLoader::readGenerators(TiXmlElement *src, NoiseModuleScene *scene)
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

        NoiseGeneratorModule *mod = dynamic_cast<NoiseGeneratorModule*>(scene->addModule(NoiseModule::Generator));
        float x, y;
        x = atof(generator->Attribute("PosX"));
        y = atof(generator->Attribute("PosY"));
        mod->setModule(module);
        mod->setPos(x, y);
        mod->setGeneratorType((NoiseGeneratorModule::GeneratorType)type);
        modules.insert(std::make_pair(id, mod));
    }
}
void NTGPLoader::readOutputs(TiXmlElement *src, NoiseModuleScene *scene)
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
        NoiseOutputModule *mod = dynamic_cast<NoiseOutputModule*>(scene->addModule(NoiseModule::Output));
        float x, y;
        x = atof(output->Attribute("PosX"));
        y = atof(output->Attribute("PosY"));
        mod->setModule(module);
        mod->setPos(x, y);
        mod->setOutputType((NoiseOutputModule::OutputType)type);
        modules.insert(std::make_pair(id, mod));
    }
}
void NTGPLoader::readModifiers(TiXmlElement *src, NoiseModuleScene *scene)
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
        NoiseModifierModule  *mod = dynamic_cast<NoiseModifierModule*>(scene->addModule(NoiseModule::Modifier));
        float x, y;
        x = atof(modifier->Attribute("PosX"));
        y = atof(modifier->Attribute("PosY"));
        mod->setModule(module);
        mod->setPos(x, y);
        mod->setType((NoiseModifierModule::ModifierType)type);
        modules.insert(std::make_pair(id, mod));
    }
}
void NTGPLoader::readCombiners(TiXmlElement *src, NoiseModuleScene *scene)
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
        NoiseCombinerModule  *mod = dynamic_cast<NoiseCombinerModule*>(scene->addModule(NoiseModule::Combiner));
        float x, y;
        x = atof(combiner->Attribute("PosX"));
        y = atof(combiner->Attribute("PosY"));
        mod->setModule(module);
        mod->setPos(x, y);
        mod->setType((NoiseCombinerModule::CombinerType)type);
        modules.insert(std::make_pair(id, mod));
    }
}
void NTGPLoader::readSelectors(TiXmlElement *src, NoiseModuleScene *scene)
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
        NoiseSelectorModule  *mod = dynamic_cast<NoiseSelectorModule*>(scene->addModule(NoiseModule::Selector));
        float x, y;
        x = atof(selector->Attribute("PosX"));
        y = atof(selector->Attribute("PosY"));
        mod->setModule(module);
        mod->setPos(x, y);
        mod->setType((NoiseSelectorModule::SelectorType)type);
        modules.insert(std::make_pair(id, mod));
    }
}

noise::module::Module* NTGPLoader::readGeneratorBillow(TiXmlElement *src)
{
    noise::module::Billow *mod = new noise::module::Billow;
    mod->SetOctaveCount(atoi(src->Attribute("OctaveCount")));
    mod->SetNoiseQuality((noise::NoiseQuality)atoi(src->Attribute("NoiseQuality")));
    mod->SetFrequency(atof(src->Attribute("Frequency")));
    mod->SetLacunarity(atof(src->Attribute("Lacunarity")));
    mod->SetPersistence(atof(src->Attribute("Persistance")));
    return mod;
}
noise::module::Module* NTGPLoader::readGeneratorCheckerboard(TiXmlElement *src)
{
    noise::module::Checkerboard *mod = new noise::module::Checkerboard;
    return mod;
}
noise::module::Module* NTGPLoader::readGeneratorConst(TiXmlElement *src)
{
    noise::module::Const *mod = new noise::module::Const;
    mod->SetConstValue(atof(src->Attribute("ConstValue")));
    return mod;
}
noise::module::Module* NTGPLoader::readGeneratorCylinders(TiXmlElement *src)
{
    noise::module::Cylinders *mod = new noise::module::Cylinders;
    mod->SetFrequency(atof(src->Attribute("Frequency")));
    return mod;
}

noise::module::Module* NTGPLoader::readGeneratorPerlin(TiXmlElement *src)
{
    noise::module::Perlin *mod = new noise::module::Perlin;
    mod->SetOctaveCount(atoi(src->Attribute("OctaveCount")));
    mod->SetNoiseQuality((noise::NoiseQuality)atoi(src->Attribute("NoiseQuality")));
    mod->SetFrequency(atof(src->Attribute("Frequency")));
    mod->SetLacunarity(atof(src->Attribute("Lacunarity")));
    mod->SetPersistence(atof(src->Attribute("Persistance")));
    return mod;
}

noise::module::Module* NTGPLoader::readGeneratorRidgedMulty(TiXmlElement *src)
{
    noise::module::RidgedMulti *mod = new noise::module::RidgedMulti;
    mod->SetOctaveCount(atoi(src->Attribute("OctaveCount")));
    mod->SetNoiseQuality((noise::NoiseQuality)atoi(src->Attribute("NoiseQuality")));
    mod->SetFrequency(atof(src->Attribute("Frequency")));
    mod->SetLacunarity(atof(src->Attribute("Lacunarity")));
    return mod;
}

noise::module::Module* NTGPLoader::readGeneratorSpheres(TiXmlElement *src)
{
    noise::module::Spheres *mod = new noise::module::Spheres;
    mod->SetFrequency(atof(src->Attribute("Frequency")));
    return mod;
}

noise::module::Module* NTGPLoader::readGeneratorVoronoi(TiXmlElement *src)
{
    noise::module::Voronoi *mod = new noise::module::Voronoi;
    mod->SetDisplacement(atof(src->Attribute("Frequency")));
    mod->SetFrequency(atof(src->Attribute("Displacement")));
    return mod;
}


noise::utils::NoiseMapBuilder* NTGPLoader::readOutputCylinder(TiXmlElement *src)
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

noise::utils::NoiseMapBuilder* NTGPLoader::readOutputPlane(TiXmlElement *src)
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

noise::utils::NoiseMapBuilder* NTGPLoader::readOutputSphere(TiXmlElement *src)
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

void NTGPLoader::readLinks(TiXmlElement *src, NoiseModuleScene *scene )
{
    for(TiXmlElement *xmlLink = src->FirstChildElement("Link"); xmlLink; xmlLink = xmlLink->NextSiblingElement("Link"))
    {
        int fromId = atoi(xmlLink->Attribute("source"));
        int toId = atoi(xmlLink->Attribute("destination"));

        NoiseModule *fromMod = modules[fromId];
        NoiseModule *toMod = modules[toId];
        if(!fromMod || !toMod)continue;

        Arrow *arrow = new Arrow(fromMod, toMod);
        fromMod->addArrow(arrow);
        toMod->addArrow(arrow);
        arrow->setZValue(-1000.0);
        arrow->updatePosition();
        scene->addItem(arrow);
    }
}

noise::module::Module* NTGPLoader::readModifierAbs(TiXmlElement *src)
{
    noise::module::Abs *mod = new noise::module::Abs;
    return mod;
}

noise::module::Module* NTGPLoader::readModifierClamp(TiXmlElement *src)
{
    noise::module::Clamp *mod = new noise::module::Clamp;
    float lb, ub;
    lb = atof(src->Attribute("LowerBound"));
    ub = atof(src->Attribute("UpperBound"));
    mod->SetBounds(lb, ub);
    return mod;
}

noise::module::Module* NTGPLoader::readModifierCurve(TiXmlElement *src)
{
    return 0;
}

noise::module::Module* NTGPLoader::readModifierExponent(TiXmlElement *src)
{
    noise::module::Exponent *mod = new noise::module::Exponent;
    mod->SetExponent(atof(src->Attribute("Exponent")));
    return mod;
}
noise::module::Module* NTGPLoader::readModifierInvert(TiXmlElement *src)
{
    noise::module::Invert *mod = new noise::module::Invert;
    return mod;
}

noise::module::Module* NTGPLoader::readModifierScaleBias(TiXmlElement *src)
{
    noise::module::ScaleBias *mod = new noise::module::ScaleBias;
    mod->SetScale(atof(src->Attribute("Scale")));
    mod->SetBias(atof(src->Attribute("Bias")));
    return mod;
}
noise::module::Module* NTGPLoader::readModifierTerrace(TiXmlElement *src)
{
    return 0;
}

noise::module::Module* NTGPLoader::readCombinerAdd(TiXmlElement *src)
{
    noise::module::Add *mod = new noise::module::Add;
    return mod;
}
noise::module::Module* NTGPLoader::readCombinerMax(TiXmlElement *src)
{
    noise::module::Max *mod = new noise::module::Max;
    return mod;
}
noise::module::Module* NTGPLoader::readCombinerMin(TiXmlElement *src)
{
    noise::module::Min *mod = new noise::module::Min;
    return mod;
}
noise::module::Module* NTGPLoader::readCombinerMultiply(TiXmlElement *src)
{
    noise::module::Multiply *mod = new noise::module::Multiply;
    return mod;
}
noise::module::Module* NTGPLoader::readCombinerPower(TiXmlElement *src)
{
    noise::module::Power *mod = new noise::module::Power;
    return mod;
}
noise::module::Module* NTGPLoader::readSelectorBlend(TiXmlElement *src)
{
    noise::module::Blend *mod = new noise::module::Blend;
    return mod;
}
noise::module::Module* NTGPLoader::readSelectorSelect(TiXmlElement *src)
{
    noise::module::Select *mod = new noise::module::Select;
    double lb, ub;
    lb = atof(src->Attribute("LowerBound"));
    ub = atof(src->Attribute("UpperBound"));
    mod->SetEdgeFalloff(atof(src->Attribute("EdgeFalloff")));
    mod->SetBounds(lb, ub);
    return mod;
}


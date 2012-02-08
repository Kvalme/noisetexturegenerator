#include "ntgploader.h"
#include "noisegenerator.h"
#include "noiseoutput.h"
#include "arrow.h"

NTGPLoader::NTGPLoader()
{
}
void NTGPLoader::load(TiXmlDocument *doc, NoiseModuleScene *scene)
{
    TiXmlElement *root = doc->RootElement();
    TiXmlElement *generators = root->FirstChildElement("Generators");
    TiXmlElement *outputs = root->FirstChildElement("Outputs");

    readGenerators(generators, scene);
    readOutputs(outputs, scene);
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
	connectOutputSources(mod, output, scene);
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

void NTGPLoader::connectOutputSources(NoiseOutputModule *srcMod, TiXmlElement *src, NoiseModuleScene *scene )
{
    TiXmlElement *sources = src->FirstChildElement("Sources");
    for(TiXmlElement *source = sources->FirstChildElement("Source"); source; source = source->NextSiblingElement("Source"))
    {
	int id = atoi(source->Attribute("sourceId"));
	NoiseModule *mod = modules[id];
	Arrow *arrow = new Arrow(mod, srcMod);
	mod->addArrow(arrow);
	srcMod->addArrow(arrow);
	arrow->setZValue(-1000.0);
	arrow->updatePosition();
	scene->addItem(arrow);
    }
}

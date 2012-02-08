#include "noisexmlbuilder.h"

NoiseXMLBuilder::NoiseXMLBuilder()
{
}
void NoiseXMLBuilder::load(TiXmlDocument *doc)
{
    TiXmlElement *root = doc->RootElement();
    TiXmlElement *generators = root->FirstChildElement("Generators");
    TiXmlElement *outputs = root->FirstChildElement("Outputs");

    readGenerators(generators);
    readOutputs(outputs);
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

    connectOutputSources(mod, src);
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

    connectOutputSources(mod, src);
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

    connectOutputSources(mod, src);
    return mod;
}

void NoiseXMLBuilder::connectOutputSources(noise::utils::NoiseMapBuilder *mod, TiXmlElement *src)
{
    TiXmlElement *sources = src->FirstChildElement("Sources");
    for(TiXmlElement *source = sources->FirstChildElement("Source"); source; source = source->NextSiblingElement("Source"))
    {
	int id = atoi(source->Attribute("sourceId"));
	noise::module::Module *module = modules[id];
	mod->SetSourceModule(*module);
    }
}

noise::utils::Image* NoiseXMLBuilder::getImage()
{
    utils::NoiseMap noiseMap;
    noise::utils::NoiseMapBuilder *builder = mapBuilders.begin()->second;
    builder->SetDestNoiseMap(noiseMap);
    builder->Build();

    utils::Image *img = new utils::Image;
    utils::RendererImage renderer;
    renderer.SetSourceNoiseMap(noiseMap);
    renderer.SetDestImage(*img);
    renderer.Render();
    return img;
}

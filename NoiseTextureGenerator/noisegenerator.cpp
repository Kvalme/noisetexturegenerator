#include "noisegenerator.h"

NoiseGeneratorModule::NoiseGeneratorModule(QMenu *contextMenu, QGraphicsItem *parent, QGraphicsScene *scene) : NoiseModule(Generator, contextMenu, parent, scene)
{
    genType = Billow;
    text.setAcceptTouchEvents(false);
    text.setAcceptHoverEvents(false);
    text.setPos(-50, -25);
    text.setDefaultTextColor(Qt::black);
    text.setPlainText(getGeneratorName(genType).c_str());
    text.setParentItem(this);

    int hw = 50, hh=25;

    myPolygon << QPointF(-hw, -hh) << QPointF(hw, -hh)
	  << QPointF(hw, hh) << QPointF(-hw, hh)
	  << QPointF(-hw, -hh);
    setPolygon(myPolygon);
    module = new noise::module::Billow;
}
NoiseGeneratorModule::~NoiseGeneratorModule()
{
}

void NoiseGeneratorModule::setGeneratorType(GeneratorType type)
{
    if(type == genType)return;
    genType = type;
    text.setPlainText(getGeneratorName(genType).c_str());
    delete module;
    switch(type)
    {
    case Billow: module=new noise::module::Billow;
	break;
    case Checkerboard: module = new noise::module::Checkerboard;
	break;
    case Const: module = new noise::module::Const;
	break;
    case Cylinders: module = new noise::module::Cylinders;
	break;
    case Perlin: module = new noise::module::Perlin;
	break;
    case RidgedMulti: module = new noise::module::RidgedMulti;
	break;
    case Spheres: module = new noise::module::Spheres;
	break;
    case Voronoi: module = new noise::module::Voronoi;
	break;

    }
}

std::string NoiseGeneratorModule::getGeneratorName(GeneratorType type)
{
    switch(type)
    {
    case Billow: return "Billow";
	break;
    case Checkerboard: return "Checkerboard";
	break;
    case Const: return "Const";
	break;
    case Cylinders: return "Cylinders";
	break;
    case Perlin: return "Perlin";
	break;
    case RidgedMulti: return "RidgedMulti";
	break;
    case Spheres: return "Spheres";
	break;
    case Voronoi: return "Voronoi";
	break;

    }
    return "";
}

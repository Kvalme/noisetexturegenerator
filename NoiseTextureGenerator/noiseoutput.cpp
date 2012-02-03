#include "noiseoutput.h".h"

NoiseOutputModule::NoiseOutputModule(QMenu *contextMenu, QGraphicsItem *parent, QGraphicsScene *scene) : NoiseModule(Output, contextMenu, parent, scene)
{
    oType = Plane;
    text.setAcceptTouchEvents(false);
    text.setAcceptHoverEvents(false);
    text.setPos(-50, -25);
    text.setDefaultTextColor(Qt::black);
    text.setPlainText(getOutputName(oType).c_str());
    text.setParentItem(this);

    int hw = 50, hh=25;

    myPolygon << QPointF(-hw, -hh) << QPointF(hw, -hh) << QPointF(hw+hw/2, 0)
	  << QPointF(hw, hh) << QPointF(-hw, hh)
	  << QPointF(-hw, -hh);
    setPolygon(myPolygon);
    builder = new noise::utils::NoiseMapBuilderPlane;
}
NoiseOutputModule::~NoiseOutputModule()
{
}

void NoiseOutputModule::setOutputType(OutputType type)
{
    if(type == oType)return;
    oType = type;
    text.setPlainText(getOutputName(oType).c_str());
    delete builder;
    switch(type)
    {
    case Cylinder: builder = new noise::utils::NoiseMapBuilderCylinder;
	break;
    case Plane: builder = new noise::utils::NoiseMapBuilderPlane;
	break;
    case Sphere: builder = new noise::utils::NoiseMapBuilderSphere;
	break;

    }
}

std::string NoiseOutputModule::getOutputName(OutputType type)
{
    switch(type)
    {
    case Cylinder: return "Cylinder";
	break;
    case Plane: return "Plane";
	break;
    case Sphere: return "Sphere";
	break;

    }
    return "";
}

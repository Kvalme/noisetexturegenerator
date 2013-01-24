#include "noiseoutput.h"

#include "clnoiseoutput.h"

NoiseOutputModule::NoiseOutputModule(QMenu *contextMenu, QGraphicsItem *parent, QGraphicsScene *scene) : NoiseModule(contextMenu, parent, scene)
{
    myModuleType = OutputModule;
    text.setAcceptTouchEvents(false);
    text.setAcceptHoverEvents(false);
    text.setPos(-50, -25);
    text.setDefaultTextColor(Qt::black);
    text.setPlainText("Output");
    text.setParentItem(this);

    int hw = 50, hh=25;

    myPolygon << QPointF(-hw, -hh) << QPointF(hw, -hh) << QPointF(hw+hw/2, 0)
	  << QPointF(hw, hh) << QPointF(-hw, hh)
	  << QPointF(-hw, -hh);
    setPolygon(myPolygon);
//    builder = new noise::utils::NoiseMapBuilderPlane;

    moduleSourceCount = 1;
    checkSourceCount();
}
NoiseOutputModule::~NoiseOutputModule()
{
}

/*std::string NoiseOutputModule::getOutputName(OutputType type)
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
*/

#include "noisecombiner.h"

NoiseCombinerModule::NoiseCombinerModule(QMenu *contextMenu, QGraphicsItem *parent, QGraphicsScene *scene) : NoiseModule(Combiner, contextMenu, parent, scene)
{
    comType = Add;
    module = new noise::module::Add;
    text.setAcceptTouchEvents(false);
    text.setAcceptHoverEvents(false);
    text.setPos(-25, -25);
    text.setDefaultTextColor(Qt::black);
    text.setPlainText(getName(comType).c_str());
    text.setParentItem(this);

    int hw = 50, hh=25;

    myPolygon << QPointF(-hw, -hh) << QPointF(hw/2, -hh) << QPointF(hw, 0) << QPointF(hw/2, hh)
	      << QPointF(-hw, hh) << QPointF(-hw/2, 0) <<QPointF(-hw, -hh);
    setPolygon(myPolygon);

    moduleSourceCount = module->GetSourceModuleCount();
    checkSourceCount();
}
NoiseCombinerModule::~NoiseCombinerModule()
{
}

void NoiseCombinerModule::setType(CombinerType type)
{
    if(type == comType)return;
    comType = type;
    text.setPlainText(getName(comType).c_str());
    delete module;
    switch(type)
    {
    case Add: module=new noise::module::Add;
	break;
    case Max: module = new noise::module::Max;
	break;
    case Min: module = new noise::module::Min;
	break;
    case Multiply: module = new noise::module::Multiply;
	break;
    case Power: module = new noise::module::Power;
	break;

    }
}

std::string NoiseCombinerModule::getName(CombinerType type)
{
    std::string name;
    switch(type)
    {
    case Add: name = "Add";
	break;
    case Max: name = "Max";
	break;
    case Min: name = "Min";
	break;
    case Multiply: name = "Multiply";
	break;
    case Power: name = "Power";
	break;
    }

    return name;
}

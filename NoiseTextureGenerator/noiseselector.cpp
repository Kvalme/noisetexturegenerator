#include "noiseselector.h"

NoiseSelectorModule::NoiseSelectorModule(QMenu *contextMenu, QGraphicsItem *parent, QGraphicsScene *scene) : NoiseModule(Selector, contextMenu, parent, scene)
{
    modType = Blend;
    module = new noise::module::Blend;
    text.setAcceptTouchEvents(false);
    text.setAcceptHoverEvents(false);
    text.setPos(-25, -25);
    text.setDefaultTextColor(Qt::black);
    text.setPlainText(getName(modType).c_str());
    text.setParentItem(this);

    int hw = 50, hh=25;

    myPolygon << QPointF(-hw, -hh) << QPointF(hw/2, -hh) << QPointF(hw, 0) << QPointF(hw/2, hh)
	      << QPointF(-hw, hh) << QPointF(-hw/2, 0) <<QPointF(-hw, -hh);
    setPolygon(myPolygon);
}
NoiseSelectorModule::~NoiseSelectorModule()
{
}

void NoiseSelectorModule::setType(SelectorType type)
{
    if(type == modType)return;
    modType = type;
    text.setPlainText(getName(modType).c_str());
    delete module;
    switch(type)
    {
    case Blend: module=new noise::module::Blend;
	break;
    case Select: module = new noise::module::Select;
	break;
    }
}

std::string NoiseSelectorModule::getName(SelectorType type)
{
    std::string name;
    switch(type)
    {
    case Blend: name = "Blend";
	break;
    case Select: name = "Select";
	break;
    }

    return name;
}

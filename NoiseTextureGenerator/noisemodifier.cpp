#include "noisemodifier.h"

NoiseModifierModule::NoiseModifierModule(QMenu *contextMenu, QGraphicsItem *parent, QGraphicsScene *scene) : NoiseModule(Modifier, contextMenu, parent, scene)
{
    modType = Abs;
    module = new noise::module::Abs;
    text.setAcceptTouchEvents(false);
    text.setAcceptHoverEvents(false);
    text.setPos(-25, -25);
    text.setDefaultTextColor(Qt::black);
    text.setPlainText(getName(modType).c_str());
    text.setParentItem(this);

    int hw = 50, hh=25;

    myPolygon << QPointF(-hw, -hh) << QPointF(hw/2, -hh)
	  << QPointF(hw, hh) << QPointF(-hw/2, hh)
	  << QPointF(-hw, -hh);
    setPolygon(myPolygon);
}
NoiseModifierModule::~NoiseModifierModule()
{
}

void NoiseModifierModule::setType(ModifierType type)
{
    if(type == modType)return;
    modType = type;
    text.setPlainText(getName(modType).c_str());
    delete module;
    switch(type)
    {
    case Abs: module=new noise::module::Abs;
	break;
    case Clamp: module = new noise::module::Clamp;
	break;
    case Curve: module = new noise::module::Curve;
	break;
    case Exponent: module = new noise::module::Exponent;
	break;
    case Invert: module = new noise::module::Invert;
	break;
    case ScaleBias: module = new noise::module::ScaleBias;
	break;
    case Terrace: module = new noise::module::Terrace;
	break;

    }
}

std::string NoiseModifierModule::getName(ModifierType type)
{
    std::string name;
    switch(type)
    {
    case Abs: name = "Abs";
	break;
    case Clamp: name = "Clamp";
	break;
    case Curve: name = "Curve";
	break;
    case Exponent: name = "Exponent";
	break;
    case Invert: name = "Invert";
	break;
    case ScaleBias: name = "ScaleBias";
	break;
    case Terrace: name = "Terrace";
	break;
    }

    return name;
}

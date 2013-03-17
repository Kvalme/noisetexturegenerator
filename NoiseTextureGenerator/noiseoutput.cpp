#include <QMessageBox>
#include "noiseoutput.h"
#include "noisemodulescene.h"
#include "clnoise/output.h"

NoiseOutputModule::NoiseOutputModule(QMenu *contextMenu, CLNoise::Noise *noise, QString typeStr, CLNoise::BaseModule *mod, QGraphicsItem *parent, QGraphicsScene *scene) :
    NoiseModule(contextMenu, noise, typeStr, mod, parent, scene)
{
    int hw = 50, hh=25;

    myPolygon.clear();
    myPolygon << QPointF(-hw, -hh) << QPointF(hw, -hh) << QPointF(hw+hw/2, 0)
             << QPointF(hw, hh) << QPointF(-hw, hh)
             << QPointF(-hw, -hh);
    setPolygon(myPolygon);

    if(!mod)
    {
        module = dynamic_cast<CLNoise::Output*>(noiseLibrary->createModule(typeStr.toUtf8().data(), CLNoise::BaseModule::OUTPUT));
    }
    else
    {
        module = mod;
    }
    text.setPlainText(module->getName().c_str());
    myModuleType = OutputModule;

    checkSourceCount();
}
NoiseOutputModule::~NoiseOutputModule()
{
}

int NoiseOutputModule::type() const
{
    return NoiseModuleScene::OutputModule;
}

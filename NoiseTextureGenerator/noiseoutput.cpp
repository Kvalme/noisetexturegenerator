#include <QMessageBox>
#include "noiseoutput.h"
#include "noisemodulescene.h"
#include "clnoiseoutput.h"

NoiseOutputModule::NoiseOutputModule(QMenu *contextMenu, CLNoise::Noise *noise, QGraphicsItem *parent, QGraphicsScene *scene) : NoiseModule(contextMenu, noise, parent, scene)
{
    int hw = 50, hh=25;

    myPolygon.clear();
    myPolygon << QPointF(-hw, -hh) << QPointF(hw, -hh) << QPointF(hw+hw/2, 0)
             << QPointF(hw, hh) << QPointF(-hw, hh)
             << QPointF(-hw, -hh);
    setPolygon(myPolygon);


    std::vector<std::string> mods = noiseLibrary->getModulesOfType(CLNoise::Module::OUTPUT);

    if(mods.empty())
    {
        QMessageBox::critical(0, "Error in libclnoise", "Empty module set returned");
        return;
    }

    std::string firstModuleName = *mods.begin();
    module = noiseLibrary->createOutput(firstModuleName);
    text.setPlainText(firstModuleName.c_str());

    moduleSourceCount = 1;
    checkSourceCount();
}
NoiseOutputModule::~NoiseOutputModule()
{
}

int NoiseOutputModule::type() const
{
    return NoiseModuleScene::OutputModule;
}

#include "noisemodifier.h"
#include "noisemodulescene.h"


NoiseModifier::NoiseModifier(QMenu *contextMenu, CLNoise::Noise *noise, QString typeStr, CLNoise::BaseModule *mod, QGraphicsItem *parent, QGraphicsScene *scene) :
    NoiseModule(contextMenu, noise, typeStr, mod, parent, scene)
{
    if(!mod)
    {
        module = dynamic_cast<CLNoise::Filter*>(noiseLibrary->createModule(typeStr.toUtf8().data(), CLNoise::BaseModule::FILTER));
    }
    else
    {
        module = mod;
    }
    text.setPlainText(module->getName().c_str());
    myModuleType = ModifierModule;

    checkSourceCount();
}

NoiseModifier::~NoiseModifier()
{
}

int NoiseModifier::type() const
{
    return NoiseModuleScene::ModifierModule;
}

#include "noisemodifier.h"
#include "noisemodulescene.h"


NoiseModifier::NoiseModifier(QMenu *contextMenu, CLNoise::Noise *noise, QString typeStr, CLNoise::Module *mod, QGraphicsItem *parent, QGraphicsScene *scene) :
    NoiseModule(contextMenu, noise, typeStr, mod, parent, scene)
{
    if(!mod)
    {
        module = dynamic_cast<CLNoise::Modifier*>(noiseLibrary->createModule(typeStr.toUtf8().data(), CLNoise::BaseModule::MODIFIER));
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

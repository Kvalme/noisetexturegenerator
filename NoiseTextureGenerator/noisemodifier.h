#pragma once

#include "noisemodule.h"
#include "noise.h"

class NoiseModifierModule : public NoiseModule
{
public:
    enum ModifierType { Abs, Clamp, Curve, Exponent, Invert, ScaleBias, Terrace};

    NoiseModifierModule(QMenu *contextMenu, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

    virtual ~NoiseModifierModule();

    void setType(ModifierType type);
    ModifierType getType() const { return modType;}
    std::string getName(ModifierType type);
    noise::module::Module* getModule() { return module;}
    void setModule(noise::module::Module *mod) { module = mod;}

protected:
    ModifierType modType;
    QGraphicsTextItem text;
    noise::module::Module *module;
};

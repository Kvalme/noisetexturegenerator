#pragma once

#include "noisemodule.h"
#include "noise.h"

class NoiseSelectorModule : public NoiseModule
{
public:
    enum SelectorType { Blend, Select};

    NoiseSelectorModule(QMenu *contextMenu, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

    virtual ~NoiseSelectorModule();

    void setType(SelectorType type);
    SelectorType getType() const { return modType;}
    std::string getName(SelectorType type);
    noise::module::Module* getModule() { return module;}
    void setModule(noise::module::Module *mod) { module = mod;}

protected:
    SelectorType modType;
    QGraphicsTextItem text;
    noise::module::Module *module;
};

#pragma once

#include "noisemodule.h"
#include "noise.h"

class NoiseCombinerModule : public NoiseModule
{
public:
    enum CombinerType { Add, Max, Min, Multiply, Power};

    NoiseCombinerModule(QMenu *contextMenu, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

    virtual ~NoiseCombinerModule();

    void setType(CombinerType type);
    CombinerType getType() const { return comType;}
    std::string getName(CombinerType type);
    noise::module::Module* getModule() { return module;}
    void setModule(noise::module::Module *mod) { module = mod;}

protected:
    CombinerType comType;
    QGraphicsTextItem text;
    noise::module::Module *module;
};

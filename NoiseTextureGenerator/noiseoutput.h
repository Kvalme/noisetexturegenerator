#pragma once

#include <QGraphicsPolygonItem>
#include "noisemodule.h"

namespace CLNoise
{
    class Output;
}

class NoiseOutputModule : public NoiseModule
{
public:
    NoiseOutputModule(QMenu *contextMenu, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

    virtual ~NoiseOutputModule();

//    void setOutputType(OutputType type);
//    OutputType getOutputType() const { return oType;}
//    std::string getOutputName(OutputType type);
    CLNoise::Output* getModule() { return module;}
    void setModule(CLNoise::Output *mod) { module = mod;}
protected:
    QGraphicsTextItem text;
    CLNoise::Output *module;
};

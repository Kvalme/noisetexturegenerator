#pragma once

#include <QGraphicsPolygonItem>
#include "noisemodule.h"
#include "clnoiseoutput.h"

class NoiseOutputModule : public NoiseModule
{
public:

    int type() const;
    NoiseOutputModule(QMenu *contextMenu, CLNoise::Noise *noise, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
    virtual ~NoiseOutputModule();

//    void setOutputType(OutputType type);
//    OutputType getOutputType() const { return oType;}
//    std::string getOutputName(OutputType type);
    CLNoise::Output* getModule() { return dynamic_cast<CLNoise::Output*>(module);}
    void setModule(CLNoise::Output *mod) { module = mod;}
protected:

};

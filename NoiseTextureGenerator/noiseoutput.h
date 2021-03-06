#pragma once

#include <QGraphicsPolygonItem>
#include "noisemodule.h"
#include "clnoise/output.h"

class NoiseOutputModule : public NoiseModule
{
public:

    virtual int type() const;
    NoiseOutputModule(QMenu *contextMenu, CLNoise::Noise *noise, QString typeStr, CLNoise::BaseModule *mod = 0, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
    virtual ~NoiseOutputModule();

    CLNoise::Output* getModule() { return dynamic_cast<CLNoise::Output*>(module);}
    void setModule(CLNoise::Output *mod) { module = mod;}

protected:

};

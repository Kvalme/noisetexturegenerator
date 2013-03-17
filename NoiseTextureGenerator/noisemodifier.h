#pragma once

#include <QGraphicsPolygonItem>
#include "noisemodule.h"
#include "clnoise/filter.h"

class NoiseModifier : public NoiseModule
{
public:
    virtual int type() const;
    NoiseModifier(QMenu *contextMenu, CLNoise::Noise *noise, QString typeStr, CLNoise::BaseModule *mod = 0, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
    virtual ~NoiseModifier();

    CLNoise::Filter* getModule() { return dynamic_cast<CLNoise::Filter*>(module);}
    void setModule(CLNoise::Filter *mod) { module = mod;}
};


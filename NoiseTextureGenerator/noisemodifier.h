#pragma once

#include <QGraphicsPolygonItem>
#include "noisemodule.h"
#include "clnoisemodifier.h"

class NoiseModifier : public NoiseModule
{
public:
    virtual int type() const;
    NoiseModifier(QMenu *contextMenu, CLNoise::Noise *noise, QString typeStr, CLNoise::Module *mod = 0, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
    virtual ~NoiseModifier();

    CLNoise::Modifier* getModule() { return dynamic_cast<CLNoise::Modifier*>(module);}
    void setModule(CLNoise::Modifier *mod) { module = mod;}
};


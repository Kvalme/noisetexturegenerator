#pragma once

#include <QGraphicsPolygonItem>
#include "noisemodule.h"
#include "noiseutils.h"

class NoiseOutputModule : public NoiseModule
{
public:
    enum OutputType { Cylinder, Plane, Sphere};

    NoiseOutputModule(QMenu *contextMenu, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

    virtual ~NoiseOutputModule();

    void setOutputType(OutputType type);
    OutputType getOutputType() const { return oType;}
    std::string getOutputName(OutputType type);
    noise::utils::NoiseMapBuilder* getModule() { return builder;}
    void setModule(noise::utils::NoiseMapBuilder *mod) { builder = mod;}
protected:
    OutputType oType;
    QGraphicsTextItem text;
    noise::utils::NoiseMapBuilder *builder;
};

#pragma once

#include <QGraphicsPolygonItem>
#include "noisemodule.h"
#include "noise.h"

class NoiseGeneratorModule : public NoiseModule
{
public:
    enum GeneratorType { Billow, Checkerboard, Const, Cylinders, Perlin, RidgedMulti, Spheres, Voronoi};

    NoiseGeneratorModule(QMenu *contextMenu, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

    virtual ~NoiseGeneratorModule();

    void setGeneratorType(GeneratorType type);
    GeneratorType getGeneratorType() const { return genType;}
    std::string getGeneratorName(GeneratorType type);
    noise::module::Module* getModule() { return module;}
protected:
    GeneratorType genType;
    QGraphicsTextItem text;
    noise::module::Module *module;
};

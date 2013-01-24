#pragma once

#include <QGraphicsPolygonItem>
#include "noisemodule.h"
#include "libnoisecl/src/noiseoutput.h"

class NoiseOutputModule : public NoiseModule
{
public:
    NoiseOutputModule(QMenu *contextMenu, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

    virtual ~NoiseOutputModule();

//    void setOutputType(OutputType type);
//    OutputType getOutputType() const { return oType;}
//    std::string getOutputName(OutputType type);
    NOISECL::NoiseOutput* getModule() { return module;}
    void setModule(NOISECL::NoiseOutput *mod) { module = mod;}
protected:
    QGraphicsTextItem text;
    NOISECL::NoiseOutput *module;
};

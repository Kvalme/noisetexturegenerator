#ifndef NOISEMODULE_H
#define NOISEMODULE_H

#include <QGraphicsPolygonItem>
#include "arrow.h"
#include "clnoise/basemodule.h"
#include "clnoise/noise.h"
#include "noisemoduleconnector.h"

class NoiseModule : public QGraphicsPolygonItem
{
public:
    NoiseModule();
    enum ModuleType { GeneratorModule, OutputModule, ModifierModule};

    NoiseModule(QMenu *contextMenu, CLNoise::Noise *noise, QString typeStr, CLNoise::BaseModule *mod = 0, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

    ModuleType moduleType() const { return myModuleType; }
    QPolygonF polygon() const { return myPolygon; }
    virtual int type() const;
    void setConnectors();
    CLNoise::BaseModule* getNoiseModule() { return module;}

    void setInput(int id, NoiseModule *input);

    NoiseModuleConnector* getConnector(int slotId, NoiseModuleConnector::ConnectorType type);

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    void keyReleaseEvent ( QKeyEvent *event );

    void checkSourceCount();


    ModuleType myModuleType;
    QPolygonF myPolygon;
    QMenu *myContextMenu;

    QGraphicsTextItem text;

    CLNoise::Noise *noiseLibrary;
    CLNoise::BaseModule *module;
};

#endif // NOISEMODULE_H

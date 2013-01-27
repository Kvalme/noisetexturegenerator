#ifndef NOISEMODULE_H
#define NOISEMODULE_H

#include <QGraphicsPolygonItem>
#include "arrow.h"
#include "clnoisemodule.h"
#include "clnoise.h"
#include "noisemoduleconnector.h"

class NoiseModule : public QGraphicsPolygonItem
{
public:
    NoiseModule();
    enum ModuleType { BaseModule, OutputModule};

    NoiseModule(QMenu *contextMenu, CLNoise::Noise *noise, CLNoise::Module *mod = 0, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

    ModuleType moduleType() const { return myModuleType; }
    QPolygonF polygon() const { return myPolygon; }
    virtual int type() const override;
    void setConnectors();
    CLNoise::Module* getNoiseModule() { return module;}

    void setInput(int id, NoiseModule *input);
    void setControl(int id, NoiseModule *control);

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
    CLNoise::Module *module;
};

#endif // NOISEMODULE_H

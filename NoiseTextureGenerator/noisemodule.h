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

    NoiseModule(QMenu *contextMenu, CLNoise::Noise *noise, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

    void removeArrow(Arrow *arrow);
    void removeArrows();

    ModuleType moduleType() const { return myModuleType; }
    QPolygonF polygon() const { return myPolygon; }
    void addArrow(Arrow *arrow);
    int type() const;
    QList<Arrow*> getArrows() const { return arrows;}
    void setConnectors();

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void keyReleaseEvent ( QKeyEvent *event );
    void checkSourceCount();


    ModuleType myModuleType;
    QPolygonF myPolygon;
    QMenu *myContextMenu;
    QList<Arrow *> arrows;
    int moduleSourceCount;

    QGraphicsTextItem text;
    QVector<NoiseModuleConnector*> inputs;
    QVector<NoiseModuleConnector*> outputs;
    QVector<NoiseModuleConnector*> controls;

    CLNoise::Noise *noiseLibrary;
    CLNoise::Module *module;
};

#endif // NOISEMODULE_H

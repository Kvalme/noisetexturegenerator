#ifndef NOISEMODULE_H
#define NOISEMODULE_H

#include <QGraphicsPolygonItem>
#include "arrow.h"

class NoiseModule : public QGraphicsPolygonItem
{
public:
    NoiseModule();
    enum { Type = UserType + 15 };
    enum ModuleType { Generator, Modifier, Combiner, Selector, Transformer, Output};

    NoiseModule(ModuleType moduleType, QMenu *contextMenu, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

    void removeArrow(Arrow *arrow);
    void removeArrows();
    ModuleType moduleType() const { return myModuleType; }
    QPolygonF polygon() const { return myPolygon; }
    void addArrow(Arrow *arrow);
    QPixmap image() const;
    int type() const { return Type;}
    QList<Arrow*> getArrows() const { return arrows;}

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    ModuleType myModuleType;
    QPolygonF myPolygon;
    QMenu *myContextMenu;
    QList<Arrow *> arrows;
};

#endif // NOISEMODULE_H

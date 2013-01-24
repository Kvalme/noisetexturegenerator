#include "noisemoduleconnector.h"
#include <QBrush>
#include <QPen>
#include <QGraphicsSceneMouseEvent>
#include "noisemodulescene.h"

NoiseModuleConnector::NoiseModuleConnector(ConnectorType cType, QGraphicsItem *parent) :
    QGraphicsPolygonItem(parent),
    connectorType(cType)
{
    setFlag(QGraphicsItem::ItemIsMovable, false);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    setFlag(QGraphicsItem::ItemIsFocusable, false);

    int hw = 6, hh=3;

    connectorPoly << QPointF(-hw, -hh) << QPointF(hw, -hh)
      << QPointF(hw, hh) << QPointF(-hw, hh)
      << QPointF(-hw, -hh);

    setPolygon(connectorPoly);
    setPen(QPen(QBrush(Qt::red), 1));
    setBrush(QBrush(Qt::red));

    setAcceptDrops(true);

}

void NoiseModuleConnector::mousePressEvent ( QGraphicsSceneMouseEvent * event )
{
    if(event->button() == Qt::LeftButton)
    {
        NoiseModuleScene *scn = dynamic_cast<NoiseModuleScene*>(scene());
        scn->setMode(NoiseModuleScene::InsertLine, this);
    }
}

int NoiseModuleConnector::type() const
{
    return NoiseModuleScene::ConnectorModule;
}

void NoiseModuleConnector::addArrow(Arrow *arrow)
{
    if(parentItem()->type() < UserType)return;
    dynamic_cast<NoiseModule*>(parentItem())->addArrow(arrow);
}

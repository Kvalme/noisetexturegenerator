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

QVariant NoiseModuleConnector::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
    foreach (Arrow *arrow, arrows) {
        arrow->updatePosition();
    }
    }

    return value;
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

NoiseModule* NoiseModuleConnector::getModule()
{
    if(!parentItem() || parentItem()->type() < UserType)return 0;
    return dynamic_cast<NoiseModule*>(parentItem());
}

void NoiseModuleConnector::addArrow(Arrow *arrow)
{
    NoiseModule *parent = getModule();
    if(!parent)return;

    if(!arrow->startItem())return;
    NoiseModule *source = arrow->startItem()->getModule();
    if(!source)return;

    if (connectorType == InputConnector)
    {
        parent->setInput(connectorId, source);
    }
    else if(connectorType == InputConnector)
    {
        parent->setControl(connectorId, source);
    }

    arrows.push_back(arrow);
    setPen(QPen(QBrush(Qt::green), 1));
    setBrush(QBrush(Qt::green));
}

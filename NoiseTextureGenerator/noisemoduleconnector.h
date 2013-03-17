#pragma once

#include <QGraphicsPolygonItem>

class Arrow;
class NoiseModule;
class NoiseModuleConnector : public QGraphicsPolygonItem
{
public:

    int type() const;

    enum ConnectorType { InputConnector, OutputConnector};
    explicit NoiseModuleConnector(ConnectorType cType, QGraphicsItem *parent = 0);
    QPolygonF polygon() const { return connectorPoly; }

    void addArrow(Arrow *arrow);
    void setConnectorId(int id) { connectorId = id;}
    int getConnectorId() const { return connectorId;}
    QList<Arrow*> getArrows() { return arrows;}

    NoiseModule* getModule();

    ConnectorType getConnectorType() const { return connectorType;}
    
signals:
    
public slots:

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    virtual void mousePressEvent ( QGraphicsSceneMouseEvent * event );

    QPolygonF connectorPoly;
    ConnectorType connectorType;
    int connectorId;
    QList<Arrow *> arrows;
    
};

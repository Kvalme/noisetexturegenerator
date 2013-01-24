#ifndef NOISEMODULECONNECTOR_H
#define NOISEMODULECONNECTOR_H

#include <QGraphicsPolygonItem>

class Arrow;
class NoiseModuleConnector : public QGraphicsPolygonItem
{
public:

    int type() const;

    enum ConnectorType { InputConnector, OutputConnector, ControlConnector};
    explicit NoiseModuleConnector(ConnectorType cType, QGraphicsItem *parent = 0);
    QPolygonF polygon() const { return connectorPoly; }
    void addArrow(Arrow *arrow);

    ConnectorType getConnectorType() const { return connectorType;}
    
signals:
    
public slots:

protected:

    virtual void mousePressEvent ( QGraphicsSceneMouseEvent * event );
    QPolygonF connectorPoly;
    ConnectorType connectorType;
    
};

#endif // NOISEMODULECONNECTOR_H

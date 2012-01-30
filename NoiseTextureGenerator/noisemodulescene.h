#ifndef NOISEMODULESCENE_H
#define NOISEMODULESCENE_H

#include <QGraphicsScene>
#include "noisemodule.h"

class NoiseModuleScene : public QGraphicsScene
{
    Q_OBJECT
public:
    enum Mode { InsertItem, InsertLine, InsertText, MoveItem };
    explicit NoiseModuleScene(QObject *parent = 0);
    void setLineColor(const QColor &color);
    void setItemColor(const QColor &color);

public slots:
    void setMode(Mode mode);
    void setItemType(NoiseModule::ModuleType type);

signals:
    void itemInserted(NoiseModule *item);
    void itemSelected(QGraphicsItem *item);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

private:
    bool isItemChange(int type);

    NoiseModule::ModuleType myItemType;
    QMenu *myItemMenu;
    Mode myMode;
    bool leftButtonDown;
    QPointF startPoint;
    QGraphicsLineItem *line;
    QFont myFont;
    QColor myTextColor;
    QColor myItemColor;
    QColor myLineColor;

};

#endif // NOISEMODULESCENE_H

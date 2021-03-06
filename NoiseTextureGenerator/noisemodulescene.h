#ifndef NOISEMODULESCENE_H
#define NOISEMODULESCENE_H

#include <QGraphicsScene>
#include <QAction>
#include "clnoise/noise.h"
#include "noisemodule.h"
#include "noisemoduleconnector.h"

class NoiseModuleScene : public QGraphicsScene
{
    Q_OBJECT
public:
    enum Mode { InsertLine, MoveItem };
    enum ModuleTypes { BaseModule = QGraphicsItem::UserType + 1, OutputModule, ConnectorModule, ArrowModule, ModifierModule };

    explicit NoiseModuleScene(QObject *parent = 0);
    void addModule(NoiseModule::ModuleType type, CLNoise::Noise *noise, QString text);
    NoiseModule *addModule(CLNoise::Noise *noise, CLNoise::BaseModule *mod, QString text);

public slots:
    void setMode(Mode mode, NoiseModuleConnector *item);
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
    NoiseModule* createModule(NoiseModule::ModuleType type, CLNoise::Noise *noise, CLNoise::BaseModule *mod = 0, QString text = "");

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
    QAction *deleteAction;

    NoiseModuleConnector *startConnector;
    NoiseModuleConnector *endConnector;

};

#endif // NOISEMODULESCENE_H

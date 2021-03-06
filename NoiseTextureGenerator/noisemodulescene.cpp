#include "noisemodulescene.h"
#include "arrow.h"
#include <QGraphicsSceneMouseEvent>
#include "noiseoutput.h"
#include <QMenu>
#include "noisemoduleconnector.h"
#include "noisemodifier.h"

NoiseModuleScene::NoiseModuleScene(QObject *parent) :
    QGraphicsScene(parent)
{
    myMode = MoveItem;
    myItemType = NoiseModule::GeneratorModule;
    line = 0;
    myItemColor = Qt::white;
    myTextColor = Qt::black;
    myLineColor = Qt::red;

    myItemMenu = new QMenu;
    deleteAction = myItemMenu->addAction(QIcon(), "Delete");
    startConnector = endConnector = 0;
}

NoiseModule* NoiseModuleScene::addModule(CLNoise::Noise *noise, CLNoise::BaseModule *mod, QString text)
{
    NoiseModule::ModuleType type;
    switch(mod->getType())
    {
        case CLNoise::BaseModule::GENERATOR:
            type = NoiseModule::GeneratorModule;
            break;
        case CLNoise::BaseModule::OUTPUT:
            type = NoiseModule::OutputModule;
            break;
        case CLNoise::BaseModule::FILTER:
            type = NoiseModule::ModifierModule;
            break;
        default:
            return 0;
    }

    NoiseModule *item = createModule(type, noise, mod, text);
    if (!item) return 0;
    item->setBrush(myItemColor);
    addItem(item);
    item->setConnectors();
    item->setPos(0, 0);
    return item;
}


NoiseModule* NoiseModuleScene::createModule(NoiseModule::ModuleType type, CLNoise::Noise *noise, CLNoise::BaseModule *mod, QString text)
{
    switch(type)
    {
        case NoiseModule::GeneratorModule:
            return new NoiseModule(myItemMenu, noise, text, mod);
        case NoiseModule::OutputModule:
            return new NoiseOutputModule(myItemMenu, noise, text, mod);
        case NoiseModule::ModifierModule:
            return new NoiseModifier(myItemMenu, noise, text, mod);
        default:
            return 0;
    }
    return 0;
}
void NoiseModuleScene::addModule(NoiseModule::ModuleType type, CLNoise::Noise *noise, QString text)
{
    NoiseModule *item = createModule(type, noise, 0, text);
    if (!item) return;
    item->setBrush(myItemColor);
    addItem(item);
    item->setConnectors();
    item->setPos(0, 0);
    emit itemInserted(item);
}

void NoiseModuleScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void NoiseModuleScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (myMode == InsertLine && line != 0)
    {
        QRectF box(mouseEvent->scenePos(), QSizeF(10.0, 10.0));
        box.setLeft(box.left() - 3);
        box.setTop(box.top() - 3);

        QList<QGraphicsItem *> objects = items(box);

        QPointF finalPoint = mouseEvent->scenePos();
        line->setPen(QPen(myLineColor, 1));

        endConnector = 0;

        for(QGraphicsItem *object : objects)
        {
            if (object->type() == ConnectorModule)
            {
                NoiseModuleConnector *con = dynamic_cast<NoiseModuleConnector*>(object);
                if(con->getConnectorType() != NoiseModuleConnector::OutputConnector)
                {
                    finalPoint = con->scenePos();
                    line->setPen(QPen(Qt::green, 1));
                    endConnector = con;
                    break;
                }
            }
        }
        QLineF newLine(line->line().p1(), finalPoint);
        line->setLine(newLine);
    }
    else if (myMode == MoveItem)
    {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
}
void NoiseModuleScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (line != 0 && myMode == InsertLine && endConnector != 0 && startConnector != 0)
    {
        removeItem(line);
        delete line;

        Arrow *arrow = new Arrow(startConnector, endConnector);
        startConnector->addArrow(arrow);
        endConnector->addArrow(arrow);
        arrow->setZValue(-1000.0);
        addItem(arrow);
        arrow->updatePosition();
    }
    else
    {
        removeItem(line);
        delete line;
    }

    myMode = MoveItem;
    line = 0;
    startConnector = endConnector = 0;
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

bool NoiseModuleScene::isItemChange(int type)
{
    foreach (QGraphicsItem *item, selectedItems()) {
	if (item->type() == type)
	    return true;
    }
    return false;
}

void NoiseModuleScene::setMode(Mode mode, NoiseModuleConnector *item)
{
    if (item->getConnectorType() != NoiseModuleConnector::OutputConnector)return;

    myMode = mode;
    line = new QGraphicsLineItem(QLineF(item->scenePos(), item->scenePos()));
    line->setPen(QPen(myLineColor, 1));
    addItem(line);
    startConnector = item;
}

void NoiseModuleScene::setItemType(NoiseModule::ModuleType type)
{
    myItemType = type;
}

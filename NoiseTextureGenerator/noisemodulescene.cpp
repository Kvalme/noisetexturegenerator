#include "noisemodulescene.h"
#include "arrow.h"
#include <QGraphicsSceneMouseEvent>
#include "noisegenerator.h"
#include "noiseoutput.h"
#include "noisemodifier.h"
#include "noisecombiner.h"
#include "noiseselector.h"
#include <QMenu>

NoiseModuleScene::NoiseModuleScene(QObject *parent) :
    QGraphicsScene(parent)
{
    myMode = MoveItem;
    myItemType = NoiseModule::Generator;
    line = 0;
    myItemColor = Qt::white;
    myTextColor = Qt::black;
    myLineColor = Qt::black;

    myItemMenu = new QMenu;
    deleteAction = myItemMenu->addAction(QIcon(), "Delete");
}

NoiseModule* NoiseModuleScene::createModule(NoiseModule::ModuleType type)
{
    switch(type)
    {
        case NoiseModule::Generator:
            return new NoiseGeneratorModule(myItemMenu);
        case NoiseModule::Output:
            return new NoiseOutputModule(myItemMenu);
        case NoiseModule::Modifier:
            return new NoiseModifierModule(myItemMenu);
        case NoiseModule::Combiner:
            return new NoiseCombinerModule(myItemMenu);
        case NoiseModule::Selector:
            return new NoiseSelectorModule(myItemMenu);
        default:
            return 0;
    }
    return 0;
}
NoiseModule* NoiseModuleScene::addModule(NoiseModule::ModuleType type)
{
    NoiseModule *item= createModule(type);
    if(!item)return 0;
    item->setBrush(myItemColor);
    addItem(item);
    item->setPos(0, 0);
    emit itemInserted(item);
    return item;
}

void NoiseModuleScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton) return;

    switch (myMode)
    {
	case InsertLine:
	    line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(), mouseEvent->scenePos()));
	    line->setPen(QPen(myLineColor, 2));
	    addItem(line);
	    break;
	default:
	    ;
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
}
void NoiseModuleScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (myMode == InsertLine && line != 0)
    {
        QLineF newLine(line->line().p1(), mouseEvent->scenePos());
        line->setLine(newLine);
    }
    else if (myMode == MoveItem)
    {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
}
void NoiseModuleScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
     if (line != 0 && myMode == InsertLine)
     {
	 QList<QGraphicsItem *> startItems = items(line->line().p1());
	 if (startItems.count() && startItems.first() == line) startItems.removeFirst();

	 QList<QGraphicsItem *> endItems = items(line->line().p2());
	 if (endItems.count() && endItems.first() == line) endItems.removeFirst();

	 removeItem(line);
	 delete line;
	 if (startItems.count() > 0 && endItems.count() > 0 &&
		   startItems.first()->type() == NoiseModule::Type &&
		   endItems.first()->type() == NoiseModule::Type &&
		   startItems.first() != endItems.first())
	 {
		   NoiseModule *startItem = qgraphicsitem_cast<NoiseModule*>(startItems.first());
		   NoiseModule *endItem = qgraphicsitem_cast<NoiseModule*>(endItems.first());
		   Arrow *arrow = new Arrow(startItem, endItem);
		   arrow->setColor(myLineColor);
		   startItem->addArrow(arrow);
		   endItem->addArrow(arrow);
		   arrow->setZValue(-1000.0);
		   addItem(arrow);
		   arrow->updatePosition();
	}
    }
    line = 0;
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
void NoiseModuleScene::setMode(Mode mode)
{
    myMode = mode;
}

void NoiseModuleScene::setItemType(NoiseModule::ModuleType type)
{
    myItemType = type;
}

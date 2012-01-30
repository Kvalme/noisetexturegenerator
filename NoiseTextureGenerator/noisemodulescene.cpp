#include "noisemodulescene.h"
#include "arrow.h"


NoiseModuleScene::NoiseModuleScene(QObject *parent) :
    QGraphicsScene(parent)
{
    myMode = MoveItem;
    myItemType = NoiseModule::NoiseGenerator;
    line = 0;
    myItemColor = Qt::white;
    myTextColor = Qt::black;
    myLineColor = Qt::black;

}

void NoiseModuleScene::setLineColor(const QColor &color)
{
    myLineColor = color;
    if (isItemChange(Arrow::Type)) {
	Arrow *item = qgraphicsitem_cast<Arrow *>(selectedItems().first());
	item->setColor(myLineColor);
	update();
    }
}
void NoiseModuleScene::setItemColor(const QColor &color)
{
    myItemColor = color;
    if (isItemChange(DiagramItem::Type)) {
	NoiseModule *item = qgraphicsitem_cast<NoiseModule*>(selectedItems().first());
	item->setBrush(myItemColor);
    }
}
void NoiseModuleScene::editorLostFocus(NoiseModule *item)
{
    QTextCursor cursor = item->textCursor();
    cursor.clearSelection();
    item->setTextCursor(cursor);

    if (item->toPlainText().isEmpty()) {
	removeItem(item);
	item->deleteLater();
    }
}

void NoiseModuleScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton) return;

    NoiseModule *item;
    switch (myMode)
    {
	case InsertItem:
	    item = new DiagramItem(myItemType, myItemMenu);
	    item->setBrush(myItemColor);
	    addItem(item);
	    item->setPos(mouseEvent->scenePos());
	    emit itemInserted(item);
	    break;
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
    } else if (myMode == MoveItem)
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
		   startItems.first()->type() == DiagramItem::Type &&
		   endItems.first()->type() == DiagramItem::Type &&
		   startItems.first() != endItems.first())
	 {
		   NoiseModule *startItem = qgraphicsitem_cast<DiagramItem *>(startItems.first());
		   NoiseModule *endItem = qgraphicsitem_cast<DiagramItem *>(endItems.first());
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


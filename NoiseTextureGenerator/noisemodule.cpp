/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui>

#include "noisemodule.h"
#include "arrow.h"
#include "noisemodulescene.h"


NoiseModule::NoiseModule(QMenu *contextMenu, CLNoise::Noise *noise, QString typeStr, CLNoise::Module *mod,
         QGraphicsItem *parent, QGraphicsScene *scene)
    : QGraphicsPolygonItem(parent, scene)
{
    myModuleType = BaseModule;
    myContextMenu = contextMenu;
    noiseLibrary = noise;

    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    setFlag(QGraphicsItem::ItemIsFocusable, true);
    setFiltersChildEvents(false);

    text.setAcceptTouchEvents(false);
    text.setAcceptHoverEvents(false);
    text.setPos(-50, -25);
    text.setDefaultTextColor(Qt::black);
    text.setParentItem(this);

    int hw = 50, hh=25;

    myPolygon << QPointF(-hw, -hh) << QPointF(hw, -hh)
      << QPointF(hw, hh) << QPointF(-hw, hh)
      << QPointF(-hw, -hh);
    setPolygon(myPolygon);

    if(!mod)
    {
        module = dynamic_cast<CLNoise::Module*>(noiseLibrary->createModule(typeStr.toUtf8().data(), CLNoise::BaseModule::BASE));
    }
    else
    {
        module = mod;
    }
    if(module)
    {
        text.setPlainText(module->getName().c_str());
    }
}

void NoiseModule::setConnectors()
{
    for(unsigned int id = 0; id < module->getOutputCount(); ++id)
    {
        NoiseModuleConnector *conn = new NoiseModuleConnector(NoiseModuleConnector::OutputConnector, this);
        conn->setConnectorId(id);

        float h = (float)myPolygon.boundingRect().height();
        float ys = (float)myPolygon.boundingRect().top();
        float y = ys + (h - (id + 1) * h / ((float)module->getOutputCount() + 1));
        float x = myPolygon.boundingRect().right() + conn->polygon().boundingRect().width()/2.;

        conn->setPos(x, y);
    }

    for(unsigned int id = 0; id < module->getInputCount(); ++id)
    {
        NoiseModuleConnector *conn = new NoiseModuleConnector(NoiseModuleConnector::InputConnector, this);
        conn->setConnectorId(id);

        float h = (float)myPolygon.boundingRect().height();
        float ys = (float)myPolygon.boundingRect().top();
        float y = ys + (h - (id + 1) * h / ((float)module->getInputCount() + 1));
        float x = myPolygon.boundingRect().left() - conn->polygon().boundingRect().width()/2.;

        conn->setPos(x, y);
    }

    for(unsigned int id = 0; id < module->getControlCount(); ++id)
    {
        NoiseModuleConnector *conn = new NoiseModuleConnector(NoiseModuleConnector::ControlConnector, this);
        conn->setConnectorId(id);

        float w = (float)myPolygon.boundingRect().width();
        float xs = (float)myPolygon.boundingRect().left();
        float x = xs + (w - (id + 1) * w / ((float)module->getControlCount() + 1));
        float y = myPolygon.boundingRect().bottom() + conn->polygon().boundingRect().height()/2.;

        conn->setPos(x, y);
    }
}

void NoiseModule::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    if (myContextMenu)
    {
        QAction *act = myContextMenu->exec(event->screenPos());
        if(act->text() == "Delete")
        {
            scene()->removeItem(this);
            delete this;
        }
    }
}

void NoiseModule::keyReleaseEvent ( QKeyEvent *event )
{
    if(event->matches(QKeySequence::Delete))
    {
        scene()->removeItem(this);
        delete this;
    }
}

NoiseModuleConnector* NoiseModule::getConnector(int slotId, NoiseModuleConnector::ConnectorType type)
{
    foreach(QGraphicsItem *item,  childItems())
    {
        if(item->type() != NoiseModuleScene::ConnectorModule)continue;
        NoiseModuleConnector *conn = dynamic_cast<NoiseModuleConnector*>(item);
        if(!conn)continue;
        if(conn->getConnectorType() != type)continue;
        if(conn->getConnectorId() == slotId)return conn;
    }
    return 0;
}

void NoiseModule::checkSourceCount()
{
/*    int sourceCount = 0;
    foreach (Arrow *arrow, arrows)
    {
        if(arrow->endItem() == this)sourceCount++;
    }
    if(sourceCount!=moduleSourceCount)
    {
        setPen(QPen(QBrush(Qt::red), 1));
    }
    else
    {
        setPen(QPen(QBrush(Qt::green), 1));
    }*/
}

int NoiseModule::type() const
{
    return NoiseModuleScene::BaseModule;
}

void NoiseModule::setInput(int id, NoiseModule *input)
{
    if(!module || !input || !input->getNoiseModule())return;
    module->setInput(id, input->getNoiseModule());
}

void NoiseModule::setControl(int id, NoiseModule *control)
{
    if(!module || !control || !control->getNoiseModule())return;
    module->setControl(id, control->getNoiseModule());
}

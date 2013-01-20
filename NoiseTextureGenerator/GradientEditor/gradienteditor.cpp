#include "gradienteditor.h"
#include "QPainter"
#include <iostream>
#include "QColorDialog"
#include <QMouseEvent>

GradientEditor::GradientEditor(QWidget *parent) :
    QLabel(parent)
{
    gradient = 0;

    gradientPoints.push_back(GradientPoint(-1.0, QColor(0, 0, 0)));
    gradientPoints.push_back(GradientPoint(1.0, QColor(255, 255, 255)));

    selectedGradientPoint = -1;
    menuPoint = -1;

    pointContextMenu = new QMenu("Point", this);
    pointContextMenu->addAction(QIcon::fromTheme("edit-delete"), tr("Remove"), this, SLOT(removePoint()));
    pointContextMenu->addAction(tr("Change color"), this, SLOT(changePointColor()));

    mainContextMenu = new QMenu("Gradient", this);
    mainContextMenu->addAction(QIcon::fromTheme("edit-delete"), tr("Clear"), this, SLOT(clearGradient()));
    QMenu *mainSubMenu = mainContextMenu->addMenu(QIcon::fromTheme("folder-open"), tr("Load preset"));
    mainSubMenu->addAction(tr("Terrain (libnoise)"), this, SLOT(loadTerrainLibNoiseGradient()));

}

GradientEditor::~GradientEditor()
{
}

void GradientEditor::paintEvent ( QPaintEvent *event )
{
    rebuildGradient();
    QLabel::paintEvent(event);
}

void GradientEditor::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() != Qt::LeftButton)
    {
        QLabel::mouseDoubleClickEvent(event);
        return;
    }

    QPoint pos = event->pos();
    float xPos = ((float)pos.x() / (float)width()) * 2.0 - 1.0;
    gradientPoints.push_back(GradientPoint(xPos, QColor(255, 255, 255)));
}

int GradientEditor::findGradientPoint(float pos)
{
    float workZone = (float)arrowSize / (float)width();

    for(int a = 0; a<gradientPoints.size(); ++a)
    {
        GradientPoint &point = gradientPoints[a];
        if (pos > point.pos - workZone && pos < point.pos + workZone) return a;
    }
    return -1;
}

void GradientEditor::mousePressEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
    float xPos = ((float)pos.x() / (float)width()) * 2.0 - 1.0;

    int point = findGradientPoint(xPos);

    if(event->button() == Qt::LeftButton && point != -1)
    {
        GradientPoint &gp = gradientPoints[point];
        if (gp.pos == -1.0 || gp.pos == 1.0) return;
        selectedGradientPoint = point;
    }
    else
    {
        QLabel::mousePressEvent(event);
    }
}

void GradientEditor::contextMenuEvent(QContextMenuEvent *event)
{
    QPoint pos = event->pos();
    float xPos = ((float)pos.x() / (float)width()) * 2.0 - 1.0;

    int point = findGradientPoint(xPos);

    if(point != -1)
    {
        menuPoint = point;
        pointContextMenu->exec(event->globalPos());
        menuPoint = -1;
    }
    else
    {
        QAction *action = mainContextMenu->exec(event->globalPos());
    }

}

void GradientEditor::mouseReleaseEvent(QMouseEvent *event)
{
    selectedGradientPoint = -1;
}

void GradientEditor::mouseMoveEvent(QMouseEvent *ev)
{
    if (selectedGradientPoint != -1)
    {
        QPoint pos = ev->pos();
        float xPos = ((float)pos.x() / (float)width()) * 2.0 - 1.0;
        gradientPoints[selectedGradientPoint].pos = xPos;
    }
    else
    {
        QLabel::mouseMoveEvent(ev);
    }
}

void GradientEditor::rebuildGradient()
{
    if(gradient)delete gradient;
    gradient = new QLinearGradient(QPointF(0, 0), QPointF(width(), 0));

    QPixmap pix(width(), height());
    pix.fill(Qt::transparent);
    QPainter painter(&pix);

    int xs = 0;
    int ys = 0;
    int xe = width();
    int ye = height();
    arrowSize = height()/3;

    foreach (GradientPoint p, gradientPoints)
    {

        float pos = (p.pos + 1.0)/2.0;
        int r = p.color.red();
        int g = p.color.green();
        int b = p.color.blue();

        gradient->setColorAt(pos, QColor(r, g, b));

        int xc = (xe - xs) * pos;

        painter.setPen(QColor(r, g, b));
        painter.setBrush(QBrush(QColor(r, g, b), Qt::SolidPattern));

        QPoint points[3];
        points[0] = QPoint(xc, ys + arrowSize);
        points[1] = QPoint(xc + arrowSize/2, ys);
        points[2] = QPoint(xc - arrowSize/2, ys);

        painter.drawPolygon(points, 3);

        points[0] = QPoint(xc, ye - arrowSize);
        points[1] = QPoint(xc + arrowSize/2, ye);
        points[2] = QPoint(xc - arrowSize/2, ye);

        painter.drawPolygon(points, 3);
    }

    QBrush brush(*gradient);
    painter.fillRect(0, height()/3, width(), height()/3, brush);

    setPixmap(pix);

}

void GradientEditor::removePoint()
{
    if (menuPoint == -1) return;
    GradientPoint &point = gradientPoints[menuPoint];
    if(point.pos == -1.0 || point.pos == 1.0)return;

    gradientPoints.remove(menuPoint);
}

void GradientEditor::changePointColor()
{
    if (menuPoint == -1) return;
    GradientPoint &point = gradientPoints[menuPoint];

    point.color = QColorDialog::getColor(point.color);
}

void GradientEditor::clearGradient()
{
    gradientPoints.clear();
    gradientPoints.push_back(GradientPoint(-1.0, QColor(0, 0, 0)));
    gradientPoints.push_back(GradientPoint(1.0, QColor(255, 255, 255)));
}


void GradientEditor::loadTerrainLibNoiseGradient()
{
    gradientPoints.clear();

#define AddGradientPoint(pos, r, g, b) \
    { \
        gradientPoints.push_back(GradientPoint(pos, QColor(r, g, b))); \
    }


    AddGradientPoint (-1.00, 0,   0, 128 );
    AddGradientPoint (-0.20, 32,  64, 128 );
    AddGradientPoint (-0.04, 64,  96, 192 );
    AddGradientPoint (-0.02, 192, 192, 128 );
    AddGradientPoint ( 0.00, 0, 192,   0 );
    AddGradientPoint ( 0.25, 192, 192,   0 );
    AddGradientPoint ( 0.50, 160,  96,  64 );
    AddGradientPoint ( 0.75, 128, 255, 255 );
    AddGradientPoint ( 1.00, 255, 255, 255 );

    rebuildGradient();
}

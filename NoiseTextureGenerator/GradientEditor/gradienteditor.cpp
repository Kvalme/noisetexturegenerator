#include "gradienteditor.h"
#include "ui_gradienteditor.h"
#include "QPainter"
#include <iostream>
#include "QColorDialog"

GradientEditor::GradientEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GradientEditor)
{
    ui->setupUi(this);
    gradient = new QLinearGradient(QPointF(0, 0), QPointF(ui->gradientPreview->width(), 0/*ui->gradientPreview->height()*/));
    gradient->setColorAt(0, QColor(0, 0, 0));
    gradient->setColorAt(1, QColor(255, 255, 255));
    gradientPoints.insert(0, QColor(0, 0, 0));
    gradientPoints.insert(1, QColor(255, 255, 255));

    QList<QVariant> l;
    l.push_back(-1.0);
    l.push_back(0);
    l.push_back(0);
    l.push_back(0);

    ui->gradientPoints->addItem(QString("%1").arg(-1.0), QVariant(l));

    l.clear();
    l.push_back(1.0);
    l.push_back(255);
    l.push_back(255);
    l.push_back(255);
    ui->gradientPoints->addItem(QString("%1").arg(1.0), QVariant(l));
    rebuildGradient();
}

GradientEditor::~GradientEditor()
{
    delete ui;
}

void GradientEditor::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
void GradientEditor::showEvent ( QShowEvent * event )
{
    QWidget::showEvent(event);
    ui->gradientPreview->setMinimumWidth(ui->addGradientPoint->width());
    ui->gradientPreview->setFixedWidth(ui->addGradientPoint->width());

    gradient->setFinalStop(ui->gradientPreview->width(), 0);
    QPixmap pix(ui->gradientPreview->width(), ui->gradientPreview->height());
    pix.fill(Qt::black);
    QPainter painter(&pix);
    QBrush brush(*gradient);
    painter.fillRect(0, 0, ui->gradientPreview->width(), ui->gradientPreview->height(), brush);
    ui->gradientPreview->setPixmap(pix);
}

void GradientEditor::on_gradientPoints_currentIndexChanged(int index)
{
    if(index<0)return;
    QVariant data = ui->gradientPoints->itemData(index);
    float pos = data.toList().at(0).toFloat();
    int r = data.toList().at(1).toInt();
    int g = data.toList().at(2).toInt();
    int b = data.toList().at(3).toInt();

    ui->gradientPointPosition->setValue(pos);
    rebuildGradient();
}

void GradientEditor::on_deleteGradientPoint_released()
{
    int index = ui->gradientPoints->currentIndex();

    ui->gradientPoints->removeItem(index);
    rebuildGradient();
}

void GradientEditor::on_gradientColor_released()
{
    QVariant data = ui->gradientPoints->itemData(ui->gradientPoints->currentIndex());
    QList<QVariant> l = data.toList();
    QList<QVariant> newList;

    QColor newColor = QColorDialog::getColor(QColor(l.at(1).toInt(), l.at(2).toInt(), l.at(3).toInt()));

    newList.push_back(l.at(0).toFloat());
    newList.push_back(newColor.red());
    newList.push_back(newColor.green());
    newList.push_back(newColor.blue());
    ui->gradientPoints->setItemData(ui->gradientPoints->currentIndex(), newList);
    rebuildGradient();
}

void GradientEditor::on_addGradientPoint_released()
{
    QList<QVariant> newList;
    newList.push_back(0.0);
    newList.push_back(255);
    newList.push_back(255);
    newList.push_back(255);
    ui->gradientPoints->insertItem(ui->gradientPoints->count(),"0.0", newList);
    ui->gradientPoints->setCurrentIndex(ui->gradientPoints->count()-1);
    rebuildGradient();
}

void GradientEditor::on_gradientPointPosition_valueChanged(double arg1)
{
    QVariant data = ui->gradientPoints->itemData(ui->gradientPoints->currentIndex());
    QList<QVariant> l = data.toList();
    QList<QVariant> newList;

    newList.push_back(arg1);
    newList.push_back(l.at(1));
    newList.push_back(l.at(2));
    newList.push_back(l.at(3));
    ui->gradientPoints->setItemData(ui->gradientPoints->currentIndex(), newList);
    ui->gradientPoints->setItemText(ui->gradientPoints->currentIndex(), QString("%1").arg(arg1));

    rebuildGradient();
}

void GradientEditor::rebuildGradient()
{
    delete gradient;
    gradient = new QLinearGradient(QPointF(0, 0), QPointF(ui->gradientPreview->width(), 0));
    gradientPoints.clear();
    for(int a=0; a<ui->gradientPoints->count(); ++a)
    {
        QVariant data = ui->gradientPoints->itemData(a);
        float pos = data.toList().at(0).toFloat();
        int r = data.toList().at(1).toFloat();
        int g = data.toList().at(2).toFloat();
        int b = data.toList().at(3).toFloat();

        gradientPoints.insert(pos, QColor(r, g, b));

        gradient->setColorAt((pos+1.0)/2.0, QColor(r, g, b));
    }
    QPixmap pix(ui->gradientPreview->width(), ui->gradientPreview->height());
    pix.fill(Qt::black);
    QPainter painter(&pix);
    QBrush brush(*gradient);
    painter.fillRect(0, 0, ui->gradientPreview->width(), ui->gradientPreview->height(), brush);
    ui->gradientPreview->setPixmap(pix);}

void GradientEditor::on_pushButton_released()
{
    ui->gradientPoints->clear();

#define AddGradientPoint(pos, r, g, b) \
    { \
        QList<QVariant> newList; \
        newList.push_back(pos); \
        newList.push_back(r); \
        newList.push_back(g); \
        newList.push_back(b); \
        ui->gradientPoints->insertItem(ui->gradientPoints->count(),QString("%1").arg(pos), newList); \
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

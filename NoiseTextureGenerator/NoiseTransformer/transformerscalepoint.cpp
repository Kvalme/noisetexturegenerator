#include "transformerscalepoint.h"
#include "ui_transformerscalepoint.h"

TransformerScalePoint::TransformerScalePoint(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransformerScalePoint)
{
    ui->setupUi(this);
}

TransformerScalePoint::~TransformerScalePoint()
{
    delete ui;
}

void TransformerScalePoint::changeEvent(QEvent *e)
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

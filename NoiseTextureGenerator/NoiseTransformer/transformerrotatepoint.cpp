#include "transformerrotatepoint.h"
#include "ui_transformerrotatepoint.h"

TransformerRotatePoint::TransformerRotatePoint(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransformerRotatePoint)
{
    ui->setupUi(this);
}

TransformerRotatePoint::~TransformerRotatePoint()
{
    delete ui;
}

void TransformerRotatePoint::changeEvent(QEvent *e)
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

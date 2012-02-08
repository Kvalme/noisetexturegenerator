#include "transformertranslatepoint.h"
#include "ui_transformertranslatepoint.h"

TransformerTranslatePoint::TransformerTranslatePoint(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransformerTranslatePoint)
{
    ui->setupUi(this);
}

TransformerTranslatePoint::~TransformerTranslatePoint()
{
    delete ui;
}

void TransformerTranslatePoint::changeEvent(QEvent *e)
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

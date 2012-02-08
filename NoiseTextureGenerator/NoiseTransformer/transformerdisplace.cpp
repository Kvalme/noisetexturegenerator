#include "transformerdisplace.h"
#include "ui_transformerdisplace.h"

TransformerDisplace::TransformerDisplace(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransformerDisplace)
{
    ui->setupUi(this);
}

TransformerDisplace::~TransformerDisplace()
{
    delete ui;
}

void TransformerDisplace::changeEvent(QEvent *e)
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

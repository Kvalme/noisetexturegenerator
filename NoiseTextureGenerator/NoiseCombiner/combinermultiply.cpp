#include "combinermultiply.h"
#include "ui_combinermultiply.h"

CombinerMultiply::CombinerMultiply(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CombinerMultiply)
{
    ui->setupUi(this);
}

CombinerMultiply::~CombinerMultiply()
{
    delete ui;
}

void CombinerMultiply::changeEvent(QEvent *e)
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

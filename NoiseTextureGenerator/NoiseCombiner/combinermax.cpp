#include "combinermax.h"
#include "ui_combinermax.h"

CombinerMax::CombinerMax(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CombinerMax)
{
    ui->setupUi(this);
}

CombinerMax::~CombinerMax()
{
    delete ui;
}

void CombinerMax::changeEvent(QEvent *e)
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

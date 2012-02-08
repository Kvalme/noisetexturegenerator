#include "combinerpower.h"
#include "ui_combinerpower.h"

CombinerPower::CombinerPower(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CombinerPower)
{
    ui->setupUi(this);
}

CombinerPower::~CombinerPower()
{
    delete ui;
}

void CombinerPower::changeEvent(QEvent *e)
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

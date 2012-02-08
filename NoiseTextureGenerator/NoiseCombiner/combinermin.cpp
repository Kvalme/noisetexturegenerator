#include "combinermin.h"
#include "ui_combinermin.h"

CombinerMin::CombinerMin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CombinerMin)
{
    ui->setupUi(this);
}

CombinerMin::~CombinerMin()
{
    delete ui;
}

void CombinerMin::changeEvent(QEvent *e)
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

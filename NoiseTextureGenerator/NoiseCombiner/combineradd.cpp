#include "combineradd.h"
#include "ui_combineradd.h"

CombinerAdd::CombinerAdd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CombinerAdd)
{
    ui->setupUi(this);
}

CombinerAdd::~CombinerAdd()
{
    delete ui;
}

void CombinerAdd::changeEvent(QEvent *e)
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

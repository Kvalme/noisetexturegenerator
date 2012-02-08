#include "selectorblend.h"
#include "ui_selectorblend.h"

SelectorBlend::SelectorBlend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectorBlend)
{
    ui->setupUi(this);
}

SelectorBlend::~SelectorBlend()
{
    delete ui;
}

void SelectorBlend::changeEvent(QEvent *e)
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

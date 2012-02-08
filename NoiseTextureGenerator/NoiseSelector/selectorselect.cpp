#include "selectorselect.h"
#include "ui_selectorselect.h"

SelectorSelect::SelectorSelect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectorSelect)
{
    ui->setupUi(this);
}

SelectorSelect::~SelectorSelect()
{
    delete ui;
}

void SelectorSelect::changeEvent(QEvent *e)
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

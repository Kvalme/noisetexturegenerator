#include "modifierexponent.h"
#include "ui_modifierexponent.h"

ModifierExponent::ModifierExponent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModifierExponent)
{
    ui->setupUi(this);
}

ModifierExponent::~ModifierExponent()
{
    delete ui;
}

void ModifierExponent::changeEvent(QEvent *e)
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

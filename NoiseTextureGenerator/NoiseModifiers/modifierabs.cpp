#include "modifierabs.h"
#include "ui_modifierabs.h"

ModifierAbs::ModifierAbs(NoiseModifierModule *mod, QWidget *parent) :
    QWidget(parent),
    module(mod),
    ui(new Ui::ModifierAbs)
{
    ui->setupUi(this);
}

ModifierAbs::~ModifierAbs()
{
    delete ui;
}

void ModifierAbs::changeEvent(QEvent *e)
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

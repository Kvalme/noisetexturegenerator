#include "modifierclamp.h"
#include "ui_modifierclamp.h"

ModifierClamp::ModifierClamp(NoiseModifierModule *m, QWidget *parent) :
    QWidget(parent),
    module(m),
    ui(new Ui::ModifierClamp)
{
    ui->setupUi(this);
    noise::module::Clamp *mod = dynamic_cast<noise::module::Clamp*>(module->getModule());
    ui->upperBound->setValue(mod->GetUpperBound());
    ui->lowerBound->setValue(mod->GetLowerBound());
}

ModifierClamp::~ModifierClamp()
{
    delete ui;
}

void ModifierClamp::changeEvent(QEvent *e)
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

void ModifierClamp::on_lowerBound_valueChanged(double arg1)
{
    noise::module::Clamp *mod = dynamic_cast<noise::module::Clamp*>(module->getModule());
    mod->SetBounds(arg1, ui->upperBound->value());
}

void ModifierClamp::on_upperBound_valueChanged(double arg1)
{
    noise::module::Clamp *mod = dynamic_cast<noise::module::Clamp*>(module->getModule());
    mod->SetBounds(ui->lowerBound->value(), arg1);
}

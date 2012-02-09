#include "modifierexponent.h"
#include "ui_modifierexponent.h"

ModifierExponent::ModifierExponent(NoiseModifierModule *m, QWidget *parent) :
    QWidget(parent),
    module(m),
    ui(new Ui::ModifierExponent)
{
    ui->setupUi(this);
    noise::module::Exponent *mod = dynamic_cast<noise::module::Exponent*>(module->getModule());
    ui->exponent->setValue(mod->GetExponent());

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

void ModifierExponent::on_exponent_valueChanged(double arg1)
{
    noise::module::Exponent *mod = dynamic_cast<noise::module::Exponent*>(module->getModule());
    mod->SetExponent(arg1);
}

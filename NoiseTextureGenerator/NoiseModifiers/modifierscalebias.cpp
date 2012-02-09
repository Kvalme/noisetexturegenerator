#include "modifierscalebias.h"
#include "ui_modifierscalebias.h"

ModifierScaleBias::ModifierScaleBias(NoiseModifierModule *m, QWidget *parent) :
    QWidget(parent),
    module(m),
    ui(new Ui::ModifierScaleBias)
{
    ui->setupUi(this);
    noise::module::ScaleBias *mod = dynamic_cast<noise::module::ScaleBias*>(module->getModule());
    ui->scale->setValue(mod->GetScale());
    ui->bias->setValue(mod->GetBias());
}

ModifierScaleBias::~ModifierScaleBias()
{
    delete ui;
}

void ModifierScaleBias::changeEvent(QEvent *e)
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

void ModifierScaleBias::on_scale_valueChanged(double arg1)
{
    noise::module::ScaleBias *mod = dynamic_cast<noise::module::ScaleBias*>(module->getModule());
    mod->SetScale(arg1);
}

void ModifierScaleBias::on_bias_valueChanged(double arg1)
{
    noise::module::ScaleBias *mod = dynamic_cast<noise::module::ScaleBias*>(module->getModule());
    mod->SetBias(arg1);
}

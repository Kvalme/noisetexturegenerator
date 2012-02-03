#include "spheresoptions.h"
#include "ui_spheresoptions.h"

SpheresOptions::SpheresOptions(NoiseGeneratorModule *gen, QWidget *parent) :
    QWidget(parent),
    generator(gen),
    ui(new Ui::SpheresOptions)
{
    ui->setupUi(this);
    noise::module::Spheres *mod = dynamic_cast<noise::module::Spheres*>(generator->getModule());
    ui->frequency->setValue(mod->GetFrequency());

}

SpheresOptions::~SpheresOptions()
{
    delete ui;
}

void SpheresOptions::changeEvent(QEvent *e)
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

void SpheresOptions::on_frequency_valueChanged(double arg1)
{
    noise::module::Spheres *mod = dynamic_cast<noise::module::Spheres*>(generator->getModule());
    mod->SetFrequency(arg1);
}

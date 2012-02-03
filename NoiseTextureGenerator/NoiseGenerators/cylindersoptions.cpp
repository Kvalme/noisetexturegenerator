#include "cylindersoptions.h"
#include "ui_cylindersoptions.h"

CylindersOptions::CylindersOptions(NoiseGeneratorModule *gen, QWidget *parent) :
    QWidget(parent),
    generator(gen),
    ui(new Ui::CylindersOptions)
{
    ui->setupUi(this);
    noise::module::Cylinders *mod = dynamic_cast<noise::module::Cylinders*>(generator->getModule());
    ui->frequency->setValue(mod->GetFrequency());

}

CylindersOptions::~CylindersOptions()
{
    delete ui;
}

void CylindersOptions::changeEvent(QEvent *e)
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

void CylindersOptions::on_frequency_valueChanged(double arg1)
{
    noise::module::Cylinders *mod = dynamic_cast<noise::module::Cylinders*>(generator->getModule());
    mod->SetFrequency(arg1);
}

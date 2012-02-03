#include "ridgedmultioptions.h"
#include "ui_ridgedmultioptions.h"

RidgedMultiOptions::RidgedMultiOptions(NoiseGeneratorModule *gen, QWidget *parent) :
    QWidget(parent),
    generator(gen),
    ui(new Ui::RidgedMultiOptions)
{
    ui->setupUi(this);
    noise::module::RidgedMulti *mod = dynamic_cast<noise::module::RidgedMulti*>(generator->getModule());
    ui->octaveCount->setValue(mod->GetOctaveCount());
    ui->frequency->setValue(mod->GetFrequency());
    ui->lancunarity->setValue(mod->GetLacunarity());
    ui->quality->setCurrentIndex(mod->GetNoiseQuality());
}

RidgedMultiOptions::~RidgedMultiOptions()
{
    delete ui;
}

void RidgedMultiOptions::changeEvent(QEvent *e)
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

void RidgedMultiOptions::on_quality_currentIndexChanged(int index)
{
    noise::module::RidgedMulti *mod = dynamic_cast<noise::module::RidgedMulti*>(generator->getModule());
    mod->SetNoiseQuality((noise::NoiseQuality)index);
}

void RidgedMultiOptions::on_octaveCount_valueChanged(int arg1)
{
    noise::module::RidgedMulti *mod = dynamic_cast<noise::module::RidgedMulti*>(generator->getModule());
    mod->SetOctaveCount(arg1);
}

void RidgedMultiOptions::on_frequency_valueChanged(double arg1)
{
    noise::module::RidgedMulti *mod = dynamic_cast<noise::module::RidgedMulti*>(generator->getModule());
    mod->SetFrequency(arg1);
}

void RidgedMultiOptions::on_lancunarity_valueChanged(double arg1)
{
    noise::module::RidgedMulti *mod = dynamic_cast<noise::module::RidgedMulti*>(generator->getModule());
    mod->SetLacunarity(arg1);
}

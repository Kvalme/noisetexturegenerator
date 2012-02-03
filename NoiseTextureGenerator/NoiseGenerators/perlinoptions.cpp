#include "perlinoptions.h"
#include "ui_perlinoptions.h"

PerlinOptions::PerlinOptions(NoiseGeneratorModule *gen, QWidget *parent) :
    QWidget(parent),
    generator(gen),
    ui(new Ui::PerlinOptions)
{
    ui->setupUi(this);
    noise::module::Perlin *mod = dynamic_cast<noise::module::Perlin*>(generator->getModule());
    ui->octaveCount->setValue(mod->GetOctaveCount());
    ui->frequency->setValue(mod->GetFrequency());
    ui->lancunarity->setValue(mod->GetLacunarity());
    ui->persistance->setValue(mod->GetPersistence());
    ui->quality->setCurrentIndex(mod->GetNoiseQuality());
}

PerlinOptions::~PerlinOptions()
{
    delete ui;
}

void PerlinOptions::changeEvent(QEvent *e)
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

void PerlinOptions::on_lancunarity_valueChanged(double arg1)
{
    noise::module::Perlin *mod = dynamic_cast<noise::module::Perlin*>(generator->getModule());
    mod->SetLacunarity(arg1);
}

void PerlinOptions::on_persistance_valueChanged(double arg1)
{
    noise::module::Perlin *mod = dynamic_cast<noise::module::Perlin*>(generator->getModule());
    mod->SetPersistence(arg1);
}

void PerlinOptions::on_frequency_valueChanged(double arg1)
{
    noise::module::Perlin *mod = dynamic_cast<noise::module::Perlin*>(generator->getModule());
    mod->SetFrequency(arg1);
}

void PerlinOptions::on_octaveCount_valueChanged(int arg1)
{
    noise::module::Perlin *mod = dynamic_cast<noise::module::Perlin*>(generator->getModule());
    mod->SetOctaveCount(arg1);
}

void PerlinOptions::on_quality_currentIndexChanged(int index)
{
    noise::module::Perlin *mod = dynamic_cast<noise::module::Perlin*>(generator->getModule());
    mod->SetNoiseQuality((noise::NoiseQuality)index);
}

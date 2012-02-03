#include "billowoptions.h"
#include "ui_billowoptions.h"

BillowOptions::BillowOptions(NoiseGeneratorModule *gen, QWidget *parent):
    QWidget(parent),
    generator(gen),
    ui(new Ui::BillowOptions)
{
    ui->setupUi(this);
    noise::module::Billow *mod = dynamic_cast<noise::module::Billow*>(generator->getModule());
    ui->octaveCount->setValue(mod->GetOctaveCount());
    ui->frequency->setValue(mod->GetFrequency());
    ui->lancunarity->setValue(mod->GetLacunarity());
    ui->persistance->setValue(mod->GetPersistence());
    ui->quality->setCurrentIndex(mod->GetNoiseQuality());
}

BillowOptions::~BillowOptions()
{
    delete ui;
}

void BillowOptions::changeEvent(QEvent *e)
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

void BillowOptions::on_octaveCount_valueChanged(int arg1)
{
    noise::module::Billow *mod = dynamic_cast<noise::module::Billow*>(generator->getModule());
    mod->SetOctaveCount(arg1);
}

void BillowOptions::on_frequency_valueChanged(double arg1)
{
    noise::module::Billow *mod = dynamic_cast<noise::module::Billow*>(generator->getModule());
    mod->SetFrequency(arg1);
}

void BillowOptions::on_lancunarity_valueChanged(double arg1)
{
    noise::module::Billow *mod = dynamic_cast<noise::module::Billow*>(generator->getModule());
    mod->SetLacunarity(arg1);
}

void BillowOptions::on_persistance_valueChanged(double arg1)
{
    noise::module::Billow *mod = dynamic_cast<noise::module::Billow*>(generator->getModule());
    mod->SetPersistence(arg1);
}

void BillowOptions::on_quality_currentIndexChanged(int index)
{
    noise::module::Billow *mod = dynamic_cast<noise::module::Billow*>(generator->getModule());
    mod->SetNoiseQuality((noise::NoiseQuality)index);
}

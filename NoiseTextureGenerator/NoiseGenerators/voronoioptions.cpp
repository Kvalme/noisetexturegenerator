#include "voronoioptions.h"
#include "ui_voronoioptions.h"

VoronoiOptions::VoronoiOptions(NoiseGeneratorModule *gen, QWidget *parent) :
    QWidget(parent),
    generator(gen),
    ui(new Ui::VoronoiOptions)
{
    ui->setupUi(this);
    noise::module::Voronoi *mod = dynamic_cast<noise::module::Voronoi*>(generator->getModule());
    ui->frequency->setValue(mod->GetFrequency());
    ui->displacement->setValue(mod->GetDisplacement());
}

VoronoiOptions::~VoronoiOptions()
{
    delete ui;
}

void VoronoiOptions::changeEvent(QEvent *e)
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

void VoronoiOptions::on_frequency_valueChanged(double arg1)
{
    noise::module::Voronoi *mod = dynamic_cast<noise::module::Voronoi*>(generator->getModule());
    mod->SetFrequency(arg1);
}

void VoronoiOptions::on_displacement_valueChanged(double arg1)
{
    noise::module::Voronoi *mod = dynamic_cast<noise::module::Voronoi*>(generator->getModule());
    mod->SetDisplacement(arg1);
}

#include "sphereoptions.h"
#include "ui_sphereoptions.h"

SphereOptions::SphereOptions(NoiseOutputModule *m, QWidget *parent):
    QWidget(parent),
    module(m),
    ui(new Ui::SphereOptions)
{
    ui->setupUi(this);
    noise::utils::NoiseMapBuilderSphere *mod = dynamic_cast<noise::utils::NoiseMapBuilderSphere*>(module->getModule());
    mod->SetDestSize(512, 256);
    mod->SetBounds(-90, 90, -180, 180);
    ui->imageHeight->setValue(mod->GetDestHeight());
    ui->imageWidth->setValue(mod->GetDestWidth());
    ui->eastLonBound->setValue(mod->GetEastLonBound());
    ui->westLonBound->setValue(mod->GetWestLonBound());
    ui->NorthLatBound->setValue(mod->GetNorthLatBound());
    ui->southLatBound->setValue(mod->GetSouthLatBound());
}

SphereOptions::~SphereOptions()
{
    delete ui;
}

void SphereOptions::changeEvent(QEvent *e)
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

void SphereOptions::on_imageWidth_valueChanged(int)
{
    noise::utils::NoiseMapBuilderSphere *mod = dynamic_cast<noise::utils::NoiseMapBuilderSphere*>(module->getModule());
    mod->SetDestSize(ui->imageWidth->value(), mod->GetDestHeight());
}

void SphereOptions::on_imageHeight_valueChanged(int )
{
    noise::utils::NoiseMapBuilderSphere *mod = dynamic_cast<noise::utils::NoiseMapBuilderSphere*>(module->getModule());
    mod->SetDestSize(mod->GetDestWidth(), ui->imageHeight->value());
}

void SphereOptions::on_southLatBound_valueChanged(double arg)
{
    noise::utils::NoiseMapBuilderSphere *mod = dynamic_cast<noise::utils::NoiseMapBuilderSphere*>(module->getModule());
    double slb = arg;
    double nlb = mod->GetNorthLatBound();
    double wlb = mod->GetWestLonBound();
    double elb = mod->GetEastLonBound();
    mod->SetBounds(slb, nlb, wlb, elb);
}

void SphereOptions::on_NorthLatBound_valueChanged(double arg)
{
    noise::utils::NoiseMapBuilderSphere *mod = dynamic_cast<noise::utils::NoiseMapBuilderSphere*>(module->getModule());
    double slb = mod->GetSouthLatBound();
    double nlb = arg;
    double wlb = mod->GetWestLonBound();
    double elb = mod->GetEastLonBound();
    mod->SetBounds(slb, nlb, wlb, elb);
}

void SphereOptions::on_westLonBound_valueChanged(double arg)
{
    noise::utils::NoiseMapBuilderSphere *mod = dynamic_cast<noise::utils::NoiseMapBuilderSphere*>(module->getModule());
    double slb = mod->GetSouthLatBound();
    double nlb = mod->GetNorthLatBound();
    double wlb = arg;
    double elb = mod->GetEastLonBound();
    mod->SetBounds(slb, nlb, wlb, elb);
}

void SphereOptions::on_eastLonBound_valueChanged(double arg)
{
    noise::utils::NoiseMapBuilderSphere *mod = dynamic_cast<noise::utils::NoiseMapBuilderSphere*>(module->getModule());
    double slb = mod->GetSouthLatBound();
    double nlb = mod->GetNorthLatBound();
    double wlb = mod->GetWestLonBound();
    double elb = arg;
    mod->SetBounds(slb, nlb, wlb, elb);
}

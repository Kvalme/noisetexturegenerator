#include "planeoptions.h"
#include "ui_planeoptions.h"
#include "tinyXml/tinyxml.h"

PlaneOptions::PlaneOptions(NoiseOutputModule *m, QWidget *parent):
    QWidget(parent),
    module(m),
    ui(new Ui::PlaneOptions)
{
    ui->setupUi(this);
    noise::utils::NoiseMapBuilderPlane *mod = dynamic_cast<noise::utils::NoiseMapBuilderPlane*>(module->getModule());
    mod->SetDestSize(512, 512);
    mod->SetBounds(-1, 1, -1, 1);

    ui->imageHeight->setValue(mod->GetDestHeight());
    ui->imageWidth->setValue(mod->GetDestWidth());
    ui->lowerXBound->setValue(mod->GetLowerXBound());
    ui->lowerZBound->setValue(mod->GetLowerZBound());
    ui->upperXBound->setValue(mod->GetUpperXBound());
    ui->upperZBound->setValue(mod->GetUpperZBound());
    ui->seamless->setChecked(mod->IsSeamlessEnabled());
}

PlaneOptions::~PlaneOptions()
{
    delete ui;
}

void PlaneOptions::changeEvent(QEvent *e)
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

void PlaneOptions::on_imageWidth_valueChanged(int )
{
    noise::utils::NoiseMapBuilderPlane *mod = dynamic_cast<noise::utils::NoiseMapBuilderPlane*>(module->getModule());
    mod->SetDestSize(ui->imageWidth->value(), mod->GetDestHeight());
}

void PlaneOptions::on_imageHeight_valueChanged(int )
{
    noise::utils::NoiseMapBuilderPlane *mod = dynamic_cast<noise::utils::NoiseMapBuilderPlane*>(module->getModule());
    mod->SetDestSize(mod->GetDestWidth(), ui->imageHeight->value());
}

void PlaneOptions::on_lowerXBound_valueChanged(double arg1)
{
    noise::utils::NoiseMapBuilderPlane *mod = dynamic_cast<noise::utils::NoiseMapBuilderPlane*>(module->getModule());
    double lx = arg1;
    double lz = mod->GetLowerZBound();
    double ux = mod->GetUpperXBound();
    double uz = mod->GetUpperZBound();
    mod->SetBounds(lx, ux, lz, uz);
}

void PlaneOptions::on_upperXBound_valueChanged(double arg1)
{
    noise::utils::NoiseMapBuilderPlane *mod = dynamic_cast<noise::utils::NoiseMapBuilderPlane*>(module->getModule());
    double lx = mod->GetLowerXBound();
    double lz = mod->GetLowerZBound();
    double ux = arg1;
    double uz = mod->GetUpperZBound();
    mod->SetBounds(lx, ux, lz, uz);
}

void PlaneOptions::on_lowerZBound_valueChanged(double arg1)
{
    noise::utils::NoiseMapBuilderPlane *mod = dynamic_cast<noise::utils::NoiseMapBuilderPlane*>(module->getModule());
    double lx = mod->GetLowerXBound();
    double lz = arg1;
    double ux = mod->GetUpperXBound();
    double uz = mod->GetUpperZBound();
    mod->SetBounds(lx, ux, lz, uz);
}

void PlaneOptions::on_upperZBound_valueChanged(double arg1)
{
    noise::utils::NoiseMapBuilderPlane *mod = dynamic_cast<noise::utils::NoiseMapBuilderPlane*>(module->getModule());
    double lx = mod->GetLowerXBound();
    double lz = mod->GetLowerZBound();
    double ux = mod->GetUpperXBound();
    double uz = arg1;
    mod->SetBounds(lx, ux, lz, uz);
}

void PlaneOptions::on_seamless_toggled(bool checked)
{
    noise::utils::NoiseMapBuilderPlane *mod = dynamic_cast<noise::utils::NoiseMapBuilderPlane*>(module->getModule());
    mod->EnableSeamless(checked);
}


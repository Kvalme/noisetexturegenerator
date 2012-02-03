#include "cylinderoutput.h"
#include "ui_cylinderoutput.h"

CylinderOutput::CylinderOutput(NoiseOutputModule *m, QWidget *parent):
    QWidget(parent),
    module(m),
    ui(new Ui::CylinderOutput)
{
    ui->setupUi(this);
    noise::utils::NoiseMapBuilderCylinder *mod = dynamic_cast<noise::utils::NoiseMapBuilderCylinder*>(module->getModule());
    mod->SetDestSize(512, 512);
    mod->SetBounds(-180, 180, -1, 1);

    ui->loverAngleBound->setValue(mod->GetLowerAngleBound());
    ui->lowerHeightBound->setValue(mod->GetLowerHeightBound());
    ui->upperAngleBound->setValue(mod->GetUpperAngleBound());
    ui->upperHeightBound->setValue(mod->GetUpperHeightBound());
    ui->imageHeight->setValue(mod->GetDestHeight());
    ui->imageWidth->setValue(mod->GetDestWidth());
}

CylinderOutput::~CylinderOutput()
{
    delete ui;
}

void CylinderOutput::changeEvent(QEvent *e)
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

void CylinderOutput::on_loverAngleBound_valueChanged(double arg)
{
    noise::utils::NoiseMapBuilderCylinder *mod = dynamic_cast<noise::utils::NoiseMapBuilderCylinder*>(module->getModule());
    double lab = arg;
    double uab = mod->GetUpperAngleBound();
    double lhb = mod->GetLowerHeightBound();
    double uhb = mod->GetUpperHeightBound();
    mod->SetBounds(lab, uab, lhb, uhb);
}

void CylinderOutput::on_upperAngleBound_valueChanged(double arg)
{
    noise::utils::NoiseMapBuilderCylinder *mod = dynamic_cast<noise::utils::NoiseMapBuilderCylinder*>(module->getModule());
    double lab = mod->GetLowerAngleBound();
    double uab = arg;
    double lhb = mod->GetLowerHeightBound();
    double uhb = mod->GetUpperHeightBound();
    mod->SetBounds(lab, uab, lhb, uhb);
}

void CylinderOutput::on_lowerHeightBound_valueChanged(double arg)
{
    noise::utils::NoiseMapBuilderCylinder *mod = dynamic_cast<noise::utils::NoiseMapBuilderCylinder*>(module->getModule());
    double lab = mod->GetLowerAngleBound();
    double uab = mod->GetUpperAngleBound();
    double lhb = arg;
    double uhb = mod->GetUpperHeightBound();
    mod->SetBounds(lab, uab, lhb, uhb);
}

void CylinderOutput::on_upperHeightBound_valueChanged(double arg)
{
    noise::utils::NoiseMapBuilderCylinder *mod = dynamic_cast<noise::utils::NoiseMapBuilderCylinder*>(module->getModule());
    double lab = mod->GetLowerAngleBound();
    double uab = mod->GetUpperAngleBound();
    double lhb = mod->GetLowerHeightBound();
    double uhb = arg;
    mod->SetBounds(lab, uab, lhb, uhb);
}

void CylinderOutput::on_imageWidth_valueChanged(int)
{
    noise::utils::NoiseMapBuilderCylinder *mod = dynamic_cast<noise::utils::NoiseMapBuilderCylinder*>(module->getModule());
    mod->SetDestSize(ui->imageWidth->value(), mod->GetDestHeight());
}

void CylinderOutput::on_imageHeight_valueChanged(int)
{
    noise::utils::NoiseMapBuilderCylinder *mod = dynamic_cast<noise::utils::NoiseMapBuilderCylinder*>(module->getModule());
    mod->SetDestSize(mod->GetDestWidth(), ui->imageHeight->value());
}

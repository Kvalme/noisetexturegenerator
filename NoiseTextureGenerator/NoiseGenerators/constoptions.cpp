#include "constoptions.h"
#include "ui_constoptions.h"

ConstOptions::ConstOptions(NoiseGeneratorModule *gen, QWidget *parent) :
    QWidget(parent),
    generator(gen),
    ui(new Ui::ConstOptions)
{
    ui->setupUi(this);
    noise::module::Const *mod = dynamic_cast<noise::module::Const*>(generator->getModule());

    ui->doubleSpinBox->setValue(mod->GetConstValue());
}

ConstOptions::~ConstOptions()
{
    delete ui;
}

void ConstOptions::changeEvent(QEvent *e)
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

void ConstOptions::on_doubleSpinBox_valueChanged(double arg1)
{
    noise::module::Const *mod = dynamic_cast<noise::module::Const*>(generator->getModule());
    mod->SetConstValue(arg1);
}

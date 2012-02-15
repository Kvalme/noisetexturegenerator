#include "selectorselect.h"
#include "ui_selectorselect.h"

SelectorSelect::SelectorSelect(NoiseSelectorModule *mod, QWidget *parent) :
    QWidget(parent),
    module(mod),
    ui(new Ui::SelectorSelect)
{
    ui->setupUi(this);
    noise::module::Select *m = dynamic_cast<noise::module::Select*>(module->getModule());
    ui->upperBound->setValue(m->GetUpperBound());
    ui->lowerBound->setValue(m->GetLowerBound());
    ui->edgeFallof->setValue(m->GetEdgeFalloff());

}

SelectorSelect::~SelectorSelect()
{
    delete ui;
}

void SelectorSelect::changeEvent(QEvent *e)
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

void SelectorSelect::on_lowerBound_valueChanged(double arg1)
{
    noise::module::Select *mod = dynamic_cast<noise::module::Select*>(module->getModule());
    mod->SetBounds(arg1, ui->upperBound->value());
}

void SelectorSelect::on_upperBound_valueChanged(double arg1)
{
    noise::module::Select *mod = dynamic_cast<noise::module::Select*>(module->getModule());
    mod->SetBounds(ui->lowerBound->value(), arg1);
}

void SelectorSelect::on_edgeFallof_valueChanged(double arg1)
{
    noise::module::Select *mod = dynamic_cast<noise::module::Select*>(module->getModule());
    mod->SetEdgeFalloff(arg1);
}

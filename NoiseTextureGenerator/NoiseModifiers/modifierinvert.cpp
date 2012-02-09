#include "modifierinvert.h"
#include "ui_modifierinvert.h"

ModifierInvert::ModifierInvert(NoiseModifierModule *mod, QWidget *parent) :
    QWidget(parent),
    module(mod),
    ui(new Ui::ModifierInvert)
{
    ui->setupUi(this);
}

ModifierInvert::~ModifierInvert()
{
    delete ui;
}

void ModifierInvert::changeEvent(QEvent *e)
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

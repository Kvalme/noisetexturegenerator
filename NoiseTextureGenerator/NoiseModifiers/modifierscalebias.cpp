#include "modifierscalebias.h"
#include "ui_modifierscalebias.h"

ModifierScaleBias::ModifierScaleBias(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModifierScaleBias)
{
    ui->setupUi(this);
}

ModifierScaleBias::~ModifierScaleBias()
{
    delete ui;
}

void ModifierScaleBias::changeEvent(QEvent *e)
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

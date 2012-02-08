#include "modifierterrace.h"
#include "ui_modifierterrace.h"

ModifierTerrace::ModifierTerrace(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModifierTerrace)
{
    ui->setupUi(this);
}

ModifierTerrace::~ModifierTerrace()
{
    delete ui;
}

void ModifierTerrace::changeEvent(QEvent *e)
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

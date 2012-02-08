#include "modifierinvert.h"
#include "ui_modifierinvert.h"

ModifierInvert::ModifierInvert(QWidget *parent) :
    QWidget(parent),
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

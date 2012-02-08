#include "modifierclamp.h"
#include "ui_modifierclamp.h"

ModifierClamp::ModifierClamp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModifierClamp)
{
    ui->setupUi(this);
}

ModifierClamp::~ModifierClamp()
{
    delete ui;
}

void ModifierClamp::changeEvent(QEvent *e)
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

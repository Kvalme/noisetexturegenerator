#include "modifiercurve.h"
#include "ui_modifiercurve.h"

ModifierCurve::ModifierCurve(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModifierCurve)
{
    ui->setupUi(this);
}

ModifierCurve::~ModifierCurve()
{
    delete ui;
}

void ModifierCurve::changeEvent(QEvent *e)
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

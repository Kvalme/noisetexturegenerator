#include "transformerturbulence.h"
#include "ui_transformerturbulence.h"

TransformerTurbulence::TransformerTurbulence(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransformerTurbulence)
{
    ui->setupUi(this);
}

TransformerTurbulence::~TransformerTurbulence()
{
    delete ui;
}

void TransformerTurbulence::changeEvent(QEvent *e)
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

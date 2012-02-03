#include "checkerboardoptions.h"
#include "ui_checkerboardoptions.h"

CheckerboardOptions::CheckerboardOptions(NoiseGeneratorModule *gen, QWidget *parent) :
    QWidget(parent),
    generator(gen),
    ui(new Ui::CheckerboardOptions)
{
    ui->setupUi(this);
}

CheckerboardOptions::~CheckerboardOptions()
{
    delete ui;
}

void CheckerboardOptions::changeEvent(QEvent *e)
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

#ifndef SPHERESOPTIONS_H
#define SPHERESOPTIONS_H

#include <QWidget>
#include "noisegenerator.h"

namespace Ui {
    class SpheresOptions;
}

class SpheresOptions : public QWidget
{
    Q_OBJECT

public:
    explicit SpheresOptions(NoiseGeneratorModule *gen, QWidget *parent = 0);
    ~SpheresOptions();

protected:
    void changeEvent(QEvent *e);
    NoiseGeneratorModule *generator;

private slots:
    void on_frequency_valueChanged(double arg1);

private:
    Ui::SpheresOptions *ui;
};

#endif // SPHERESOPTIONS_H

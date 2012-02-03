#ifndef RIDGEDMULTIOPTIONS_H
#define RIDGEDMULTIOPTIONS_H

#include <QWidget>
#include "noisegenerator.h"

namespace Ui {
    class RidgedMultiOptions;
}

class RidgedMultiOptions : public QWidget
{
    Q_OBJECT

public:
    explicit RidgedMultiOptions(NoiseGeneratorModule *gen, QWidget *parent = 0);
    ~RidgedMultiOptions();

protected:
    void changeEvent(QEvent *e);
    NoiseGeneratorModule *generator;

private slots:
    void on_quality_currentIndexChanged(int index);

    void on_octaveCount_valueChanged(int arg1);

    void on_frequency_valueChanged(double arg1);

    void on_lancunarity_valueChanged(double arg1);

private:
    Ui::RidgedMultiOptions *ui;
};

#endif // RIDGEDMULTIOPTIONS_H

#ifndef BILLOWOPTIONS_H
#define BILLOWOPTIONS_H

#include <QWidget>
#include "noisegenerator.h"

namespace Ui {
    class BillowOptions;
}

class BillowOptions : public QWidget
{
    Q_OBJECT

public:
    explicit BillowOptions(NoiseGeneratorModule *gen, QWidget *parent = 0);
    ~BillowOptions();

protected:
    void changeEvent(QEvent *e);
    NoiseGeneratorModule *generator;

private slots:
    void on_octaveCount_valueChanged(int arg1);

    void on_frequency_valueChanged(double arg1);

    void on_lancunarity_valueChanged(double arg1);

    void on_persistance_valueChanged(double arg1);

    void on_quality_currentIndexChanged(int index);

private:
    Ui::BillowOptions *ui;
};

#endif // BILLOWOPTIONS_H

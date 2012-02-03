#ifndef PERLINOPTIONS_H
#define PERLINOPTIONS_H

#include <QWidget>
#include "noisegenerator.h"
namespace Ui {
    class PerlinOptions;
}

class PerlinOptions : public QWidget
{
    Q_OBJECT

public:
    explicit PerlinOptions(NoiseGeneratorModule *gen, QWidget *parent = 0);
    ~PerlinOptions();

protected:
    void changeEvent(QEvent *e);
    NoiseGeneratorModule *generator;

private slots:
    void on_lancunarity_valueChanged(double arg1);

    void on_persistance_valueChanged(double arg1);

    void on_frequency_valueChanged(double arg1);

    void on_octaveCount_valueChanged(int arg1);

    void on_quality_currentIndexChanged(int index);

private:
    Ui::PerlinOptions *ui;
};

#endif // PERLINOPTIONS_H

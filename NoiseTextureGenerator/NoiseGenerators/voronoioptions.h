#ifndef VORONOIOPTIONS_H
#define VORONOIOPTIONS_H

#include <QWidget>
#include "noisegenerator.h"
namespace Ui {
    class VoronoiOptions;
}

class VoronoiOptions : public QWidget
{
    Q_OBJECT

public:
    explicit VoronoiOptions(NoiseGeneratorModule *gen, QWidget *parent = 0);
    ~VoronoiOptions();

protected:
    void changeEvent(QEvent *e);
    NoiseGeneratorModule *generator;

private slots:
    void on_frequency_valueChanged(double arg1);

    void on_displacement_valueChanged(double arg1);

private:
    Ui::VoronoiOptions *ui;
};

#endif // VORONOIOPTIONS_H

#ifndef PLANEOPTIONS_H
#define PLANEOPTIONS_H

#include <QWidget>
#include "noiseoutput.h"

namespace Ui {
    class PlaneOptions;
}

class PlaneOptions : public QWidget
{
    Q_OBJECT

public:
    explicit PlaneOptions(NoiseOutputModule *m, QWidget *parent = 0);
    ~PlaneOptions();

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_imageWidth_valueChanged(int arg1);

    void on_imageHeight_valueChanged(int arg1);

    void on_lowerXBound_valueChanged(double arg1);

    void on_upperXBound_valueChanged(double arg1);

    void on_lowerZBound_valueChanged(double arg1);

    void on_upperZBound_valueChanged(double arg1);

    void on_seamless_toggled(bool checked);

    void on_generate_released();

private:
    Ui::PlaneOptions *ui;
    NoiseOutputModule *module;
};

#endif // PLANEOPTIONS_H

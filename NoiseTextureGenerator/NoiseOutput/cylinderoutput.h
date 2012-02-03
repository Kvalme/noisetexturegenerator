#ifndef CYLINDEROUTPUT_H
#define CYLINDEROUTPUT_H

#include <QWidget>
#include "noiseoutput.h"

namespace Ui {
    class CylinderOutput;
}

class CylinderOutput : public QWidget
{
    Q_OBJECT

public:
    explicit CylinderOutput(NoiseOutputModule *m, QWidget *parent = 0);
    ~CylinderOutput();

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_loverAngleBound_valueChanged(double arg1);

    void on_upperAngleBound_valueChanged(double arg1);

    void on_lowerHeightBound_valueChanged(double arg1);

    void on_upperHeightBound_valueChanged(double arg1);

    void on_imageWidth_valueChanged(int arg1);

    void on_imageHeight_valueChanged(int arg1);

private:
    Ui::CylinderOutput *ui;
    NoiseOutputModule *module;
};

#endif // CYLINDEROUTPUT_H

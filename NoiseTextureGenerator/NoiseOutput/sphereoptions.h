#ifndef SPHEREOPTIONS_H
#define SPHEREOPTIONS_H

#include <QWidget>
#include "noiseoutput.h"

namespace Ui {
    class SphereOptions;
}

class SphereOptions : public QWidget
{
    Q_OBJECT

public:
    explicit SphereOptions(NoiseOutputModule *m, QWidget *parent = 0);
    ~SphereOptions();

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_imageWidth_valueChanged(int arg1);

    void on_imageHeight_valueChanged(int arg1);

    void on_southLatBound_valueChanged(double arg1);

    void on_NorthLatBound_valueChanged(double arg1);

    void on_westLonBound_valueChanged(double arg1);

    void on_eastLonBound_valueChanged(double arg1);

private:
    Ui::SphereOptions *ui;
    NoiseOutputModule *module;
};

#endif // SPHEREOPTIONS_H

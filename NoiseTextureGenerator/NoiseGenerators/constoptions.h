#ifndef CONSTOPTIONS_H
#define CONSTOPTIONS_H

#include <QWidget>
#include "noisegenerator.h"

namespace Ui {
    class ConstOptions;
}

class ConstOptions : public QWidget
{
    Q_OBJECT

public:
    explicit ConstOptions(NoiseGeneratorModule *gen, QWidget *parent = 0);
    ~ConstOptions();

protected:
    void changeEvent(QEvent *e);
    NoiseGeneratorModule *generator;

private slots:
    void on_doubleSpinBox_valueChanged(double arg1);

private:
    Ui::ConstOptions *ui;
};

#endif // CONSTOPTIONS_H

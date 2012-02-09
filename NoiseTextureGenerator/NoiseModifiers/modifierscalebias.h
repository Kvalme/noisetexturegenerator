#ifndef MODIFIERSCALEBIAS_H
#define MODIFIERSCALEBIAS_H

#include <QWidget>
#include "noisemodifier.h"

namespace Ui {
    class ModifierScaleBias;
}

class ModifierScaleBias : public QWidget
{
    Q_OBJECT

public:
    explicit ModifierScaleBias(NoiseModifierModule *mod, QWidget *parent = 0);
    ~ModifierScaleBias();

protected:
    void changeEvent(QEvent *e);
    NoiseModifierModule *module;

private slots:
    void on_scale_valueChanged(double arg1);

    void on_bias_valueChanged(double arg1);

private:
    Ui::ModifierScaleBias *ui;
};

#endif // MODIFIERSCALEBIAS_H

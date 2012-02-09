#ifndef MODIFIERCLAMP_H
#define MODIFIERCLAMP_H

#include <QWidget>
#include "noisemodifier.h"

namespace Ui {
    class ModifierClamp;
}

class ModifierClamp : public QWidget
{
    Q_OBJECT

public:
    explicit ModifierClamp(NoiseModifierModule *mod, QWidget *parent = 0);
    ~ModifierClamp();

protected:
    void changeEvent(QEvent *e);
    NoiseModifierModule *module;

private slots:
    void on_lowerBound_valueChanged(double arg1);

    void on_upperBound_valueChanged(double arg1);

private:
    Ui::ModifierClamp *ui;
};

#endif // MODIFIERCLAMP_H

#ifndef MODIFIEREXPONENT_H
#define MODIFIEREXPONENT_H

#include <QWidget>
#include "noisemodifier.h"
namespace Ui {
    class ModifierExponent;
}

class ModifierExponent : public QWidget
{
    Q_OBJECT

public:
    explicit ModifierExponent(NoiseModifierModule *mod, QWidget *parent = 0);
    ~ModifierExponent();

protected:
    void changeEvent(QEvent *e);
    NoiseModifierModule *module;
private slots:
    void on_exponent_valueChanged(double arg1);

private:
    Ui::ModifierExponent *ui;
};

#endif // MODIFIEREXPONENT_H

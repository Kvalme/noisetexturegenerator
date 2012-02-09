#ifndef MODIFIERTERRACE_H
#define MODIFIERTERRACE_H

#include <QWidget>
#include "noisemodifier.h"

namespace Ui {
    class ModifierTerrace;
}

class ModifierTerrace : public QWidget
{
    Q_OBJECT

public:
    explicit ModifierTerrace(NoiseModifierModule *mod, QWidget *parent = 0);
    ~ModifierTerrace();

protected:
    void changeEvent(QEvent *e);
    NoiseModifierModule *module;

private:
    Ui::ModifierTerrace *ui;
};

#endif // MODIFIERTERRACE_H

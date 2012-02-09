#ifndef MODIFIERCURVE_H
#define MODIFIERCURVE_H

#include <QWidget>
#include "noisemodifier.h"
namespace Ui {
    class ModifierCurve;
}

class ModifierCurve : public QWidget
{
    Q_OBJECT

public:
    explicit ModifierCurve(NoiseModifierModule *mod, QWidget *parent = 0);
    ~ModifierCurve();

protected:
    void changeEvent(QEvent *e);
    NoiseModifierModule *module;
private:
    Ui::ModifierCurve *ui;
};

#endif // MODIFIERCURVE_H

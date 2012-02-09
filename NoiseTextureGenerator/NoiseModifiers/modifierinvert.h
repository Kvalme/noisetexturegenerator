#ifndef MODIFIERINVERT_H
#define MODIFIERINVERT_H

#include <QWidget>
#include "noisemodifier.h"

namespace Ui {
    class ModifierInvert;
}

class ModifierInvert : public QWidget
{
    Q_OBJECT

public:
    explicit ModifierInvert(NoiseModifierModule *mod, QWidget *parent = 0);
    ~ModifierInvert();

protected:
    void changeEvent(QEvent *e);
    NoiseModifierModule *module;

private:
    Ui::ModifierInvert *ui;
};

#endif // MODIFIERINVERT_H

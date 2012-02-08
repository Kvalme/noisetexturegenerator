#ifndef MODIFIEREXPONENT_H
#define MODIFIEREXPONENT_H

#include <QWidget>

namespace Ui {
    class ModifierExponent;
}

class ModifierExponent : public QWidget
{
    Q_OBJECT

public:
    explicit ModifierExponent(QWidget *parent = 0);
    ~ModifierExponent();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ModifierExponent *ui;
};

#endif // MODIFIEREXPONENT_H

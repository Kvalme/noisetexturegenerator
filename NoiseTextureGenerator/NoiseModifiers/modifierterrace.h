#ifndef MODIFIERTERRACE_H
#define MODIFIERTERRACE_H

#include <QWidget>

namespace Ui {
    class ModifierTerrace;
}

class ModifierTerrace : public QWidget
{
    Q_OBJECT

public:
    explicit ModifierTerrace(QWidget *parent = 0);
    ~ModifierTerrace();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ModifierTerrace *ui;
};

#endif // MODIFIERTERRACE_H

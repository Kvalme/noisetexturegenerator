#ifndef MODIFIERABS_H
#define MODIFIERABS_H

#include <QWidget>

namespace Ui {
    class ModifierAbs;
}

class ModifierAbs : public QWidget
{
    Q_OBJECT

public:
    explicit ModifierAbs(QWidget *parent = 0);
    ~ModifierAbs();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ModifierAbs *ui;
};

#endif // MODIFIERABS_H

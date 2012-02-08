#ifndef MODIFIERCLAMP_H
#define MODIFIERCLAMP_H

#include <QWidget>

namespace Ui {
    class ModifierClamp;
}

class ModifierClamp : public QWidget
{
    Q_OBJECT

public:
    explicit ModifierClamp(QWidget *parent = 0);
    ~ModifierClamp();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ModifierClamp *ui;
};

#endif // MODIFIERCLAMP_H

#ifndef MODIFIERCURVE_H
#define MODIFIERCURVE_H

#include <QWidget>

namespace Ui {
    class ModifierCurve;
}

class ModifierCurve : public QWidget
{
    Q_OBJECT

public:
    explicit ModifierCurve(QWidget *parent = 0);
    ~ModifierCurve();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ModifierCurve *ui;
};

#endif // MODIFIERCURVE_H

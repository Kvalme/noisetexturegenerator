#ifndef MODIFIERINVERT_H
#define MODIFIERINVERT_H

#include <QWidget>

namespace Ui {
    class ModifierInvert;
}

class ModifierInvert : public QWidget
{
    Q_OBJECT

public:
    explicit ModifierInvert(QWidget *parent = 0);
    ~ModifierInvert();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ModifierInvert *ui;
};

#endif // MODIFIERINVERT_H

#ifndef MODIFIERSCALEBIAS_H
#define MODIFIERSCALEBIAS_H

#include <QWidget>

namespace Ui {
    class ModifierScaleBias;
}

class ModifierScaleBias : public QWidget
{
    Q_OBJECT

public:
    explicit ModifierScaleBias(QWidget *parent = 0);
    ~ModifierScaleBias();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ModifierScaleBias *ui;
};

#endif // MODIFIERSCALEBIAS_H

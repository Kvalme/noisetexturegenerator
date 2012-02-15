#ifndef SELECTORSELECT_H
#define SELECTORSELECT_H

#include <QWidget>
#include "noiseselector.h"

namespace Ui {
    class SelectorSelect;
}

class SelectorSelect : public QWidget
{
    Q_OBJECT

public:
    explicit SelectorSelect(NoiseSelectorModule *mod, QWidget *parent = 0);
    ~SelectorSelect();

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_lowerBound_valueChanged(double arg1);

    void on_upperBound_valueChanged(double arg1);

    void on_edgeFallof_valueChanged(double arg1);

private:
    Ui::SelectorSelect *ui;
    NoiseSelectorModule *module;
};

#endif // SELECTORSELECT_H

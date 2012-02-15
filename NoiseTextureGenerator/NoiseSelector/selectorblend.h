#ifndef SELECTORBLEND_H
#define SELECTORBLEND_H

#include <QWidget>
#include "noiseselector.h"

namespace Ui {
    class SelectorBlend;
}

class SelectorBlend : public QWidget
{
    Q_OBJECT

public:
    explicit SelectorBlend(NoiseSelectorModule *mod, QWidget *parent = 0);
    ~SelectorBlend();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::SelectorBlend *ui;
    NoiseSelectorModule *module;
};

#endif // SELECTORBLEND_H

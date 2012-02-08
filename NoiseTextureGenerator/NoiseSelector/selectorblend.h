#ifndef SELECTORBLEND_H
#define SELECTORBLEND_H

#include <QWidget>

namespace Ui {
    class SelectorBlend;
}

class SelectorBlend : public QWidget
{
    Q_OBJECT

public:
    explicit SelectorBlend(QWidget *parent = 0);
    ~SelectorBlend();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::SelectorBlend *ui;
};

#endif // SELECTORBLEND_H

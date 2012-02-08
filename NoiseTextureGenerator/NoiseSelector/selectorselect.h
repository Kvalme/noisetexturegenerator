#ifndef SELECTORSELECT_H
#define SELECTORSELECT_H

#include <QWidget>

namespace Ui {
    class SelectorSelect;
}

class SelectorSelect : public QWidget
{
    Q_OBJECT

public:
    explicit SelectorSelect(QWidget *parent = 0);
    ~SelectorSelect();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::SelectorSelect *ui;
};

#endif // SELECTORSELECT_H

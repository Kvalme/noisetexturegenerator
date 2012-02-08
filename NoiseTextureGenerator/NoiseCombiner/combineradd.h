#ifndef COMBINERADD_H
#define COMBINERADD_H

#include <QWidget>

namespace Ui {
    class CombinerAdd;
}

class CombinerAdd : public QWidget
{
    Q_OBJECT

public:
    explicit CombinerAdd(QWidget *parent = 0);
    ~CombinerAdd();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::CombinerAdd *ui;
};

#endif // COMBINERADD_H

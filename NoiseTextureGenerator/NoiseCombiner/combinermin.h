#ifndef COMBINERMIN_H
#define COMBINERMIN_H

#include <QWidget>

namespace Ui {
    class CombinerMin;
}

class CombinerMin : public QWidget
{
    Q_OBJECT

public:
    explicit CombinerMin(QWidget *parent = 0);
    ~CombinerMin();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::CombinerMin *ui;
};

#endif // COMBINERMIN_H

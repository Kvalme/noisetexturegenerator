#ifndef COMBINERMAX_H
#define COMBINERMAX_H

#include <QWidget>

namespace Ui {
    class CombinerMax;
}

class CombinerMax : public QWidget
{
    Q_OBJECT

public:
    explicit CombinerMax(QWidget *parent = 0);
    ~CombinerMax();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::CombinerMax *ui;
};

#endif // COMBINERMAX_H

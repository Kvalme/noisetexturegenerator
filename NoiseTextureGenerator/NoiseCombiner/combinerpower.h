#ifndef COMBINERPOWER_H
#define COMBINERPOWER_H

#include <QWidget>

namespace Ui {
    class CombinerPower;
}

class CombinerPower : public QWidget
{
    Q_OBJECT

public:
    explicit CombinerPower(QWidget *parent = 0);
    ~CombinerPower();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::CombinerPower *ui;
};

#endif // COMBINERPOWER_H

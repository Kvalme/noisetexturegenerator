#ifndef COMBINERMULTIPLY_H
#define COMBINERMULTIPLY_H

#include <QWidget>

namespace Ui {
    class CombinerMultiply;
}

class CombinerMultiply : public QWidget
{
    Q_OBJECT

public:
    explicit CombinerMultiply(QWidget *parent = 0);
    ~CombinerMultiply();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::CombinerMultiply *ui;
};

#endif // COMBINERMULTIPLY_H

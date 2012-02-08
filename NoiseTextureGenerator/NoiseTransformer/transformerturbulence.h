#ifndef TRANSFORMERTURBULENCE_H
#define TRANSFORMERTURBULENCE_H

#include <QWidget>

namespace Ui {
    class TransformerTurbulence;
}

class TransformerTurbulence : public QWidget
{
    Q_OBJECT

public:
    explicit TransformerTurbulence(QWidget *parent = 0);
    ~TransformerTurbulence();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::TransformerTurbulence *ui;
};

#endif // TRANSFORMERTURBULENCE_H

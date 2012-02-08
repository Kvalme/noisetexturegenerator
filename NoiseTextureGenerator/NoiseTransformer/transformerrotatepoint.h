#ifndef TRANSFORMERROTATEPOINT_H
#define TRANSFORMERROTATEPOINT_H

#include <QWidget>

namespace Ui {
    class TransformerRotatePoint;
}

class TransformerRotatePoint : public QWidget
{
    Q_OBJECT

public:
    explicit TransformerRotatePoint(QWidget *parent = 0);
    ~TransformerRotatePoint();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::TransformerRotatePoint *ui;
};

#endif // TRANSFORMERROTATEPOINT_H

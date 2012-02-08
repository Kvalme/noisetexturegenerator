#ifndef TRANSFORMERSCALEPOINT_H
#define TRANSFORMERSCALEPOINT_H

#include <QWidget>

namespace Ui {
    class TransformerScalePoint;
}

class TransformerScalePoint : public QWidget
{
    Q_OBJECT

public:
    explicit TransformerScalePoint(QWidget *parent = 0);
    ~TransformerScalePoint();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::TransformerScalePoint *ui;
};

#endif // TRANSFORMERSCALEPOINT_H

#ifndef TRANSFORMERDISPLACE_H
#define TRANSFORMERDISPLACE_H

#include <QWidget>

namespace Ui {
    class TransformerDisplace;
}

class TransformerDisplace : public QWidget
{
    Q_OBJECT

public:
    explicit TransformerDisplace(QWidget *parent = 0);
    ~TransformerDisplace();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::TransformerDisplace *ui;
};

#endif // TRANSFORMERDISPLACE_H

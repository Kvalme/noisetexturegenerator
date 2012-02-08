#ifndef TRANSFORMERTRANSLATEPOINT_H
#define TRANSFORMERTRANSLATEPOINT_H

#include <QWidget>

namespace Ui {
    class TransformerTranslatePoint;
}

class TransformerTranslatePoint : public QWidget
{
    Q_OBJECT

public:
    explicit TransformerTranslatePoint(QWidget *parent = 0);
    ~TransformerTranslatePoint();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::TransformerTranslatePoint *ui;
};

#endif // TRANSFORMERTRANSLATEPOINT_H

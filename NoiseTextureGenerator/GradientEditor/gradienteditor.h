#ifndef GRADIENTEDITOR_H
#define GRADIENTEDITOR_H

#include <QWidget>
#include <QMap>
#include <QColor>
#include "QLinearGradient"

namespace Ui {
    class GradientEditor;
}
class GradientEditor : public QWidget
{
    Q_OBJECT

public:
    explicit GradientEditor(QWidget *parent = 0);
    ~GradientEditor();
    QLinearGradient* getGradient() { return gradient;}



    const QMap<float, QColor>& getGradientPoints() const { return gradientPoints;}


protected:
    void changeEvent(QEvent *e);
    void showEvent ( QShowEvent * event );

private slots:
    void on_gradientPoints_currentIndexChanged(int index);
    void on_deleteGradientPoint_released();
    void on_gradientColor_released();
    void on_addGradientPoint_released();
    void on_gradientPointPosition_valueChanged(double arg1);

    void on_pushButton_released();

private:
    void rebuildGradient();
    Ui::GradientEditor *ui;
    QLinearGradient *gradient;
    QMap<float, QColor> gradientPoints;
};

#endif // GRADIENTEDITOR_H

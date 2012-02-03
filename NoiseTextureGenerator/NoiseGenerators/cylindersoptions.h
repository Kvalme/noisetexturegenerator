#ifndef CYLINDERSOPTIONS_H
#define CYLINDERSOPTIONS_H

#include <QWidget>
#include "noisegenerator.h"

namespace Ui {
    class CylindersOptions;
}

class CylindersOptions : public QWidget
{
    Q_OBJECT

public:
    explicit CylindersOptions(NoiseGeneratorModule *gen, QWidget *parent = 0);
    ~CylindersOptions();

protected:
    void changeEvent(QEvent *e);
    NoiseGeneratorModule *generator;

private slots:
    void on_frequency_valueChanged(double arg1);

private:
    Ui::CylindersOptions *ui;
};

#endif // CYLINDERSOPTIONS_H

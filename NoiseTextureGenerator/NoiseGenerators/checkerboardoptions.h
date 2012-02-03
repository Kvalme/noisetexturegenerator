#ifndef CHECKERBOARDOPTIONS_H
#define CHECKERBOARDOPTIONS_H

#include <QWidget>
#include "noisegenerator.h"


namespace Ui {
    class CheckerboardOptions;
}

class CheckerboardOptions : public QWidget
{
    Q_OBJECT

public:
    explicit CheckerboardOptions(NoiseGeneratorModule *gen, QWidget *parent = 0);
    ~CheckerboardOptions();

protected:
    void changeEvent(QEvent *e);
    NoiseGeneratorModule *generator;

private:
    Ui::CheckerboardOptions *ui;

};

#endif // CHECKERBOARDOPTIONS_H

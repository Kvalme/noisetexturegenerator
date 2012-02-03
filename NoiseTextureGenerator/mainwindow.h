#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsItem>

class NoiseModuleScene;
class NoiseModule;
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);
    void fillModuleType(NoiseModule *module);

    void fillGeneratorModuleType(NoiseModule *module);
    void generatorSelected(NoiseModule *module, int index);

    void fillOutputModuleType(NoiseModule *module);
    void outputSelected(NoiseModule *module, int index);



public slots:
    void itemInserted(NoiseModule *);
    void itemSelected();

private slots:
    void on_actionNoise_generator_triggered(bool checked);
    void on_moduleType_currentIndexChanged(int index);

    void on_actionOutput_triggered(bool checked);

    void on_actionConnect_triggered(bool checked);

    void on_generateImage_released();

private:
    Ui::MainWindow *ui;
    NoiseModuleScene *nmScene;
    bool blockCurrentIndexChange;
    QWidget *opt;

};

#endif // MAINWINDOW_H

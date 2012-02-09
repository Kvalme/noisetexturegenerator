#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsItem>
#include "PreviewRenderer/previewrenderer.h"

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

    void fillModifierModuleType(NoiseModule *module);
    void modifierSelected(NoiseModule *module, int index);

    void fillCombinerModuleType(NoiseModule *module);
    void combinerSelected(NoiseModule *module, int index);

    void exportSceneData(const char *fname);



public slots:
    void itemInserted(NoiseModule *);
    void itemSelected();

private slots:
    void on_actionNoise_generator_triggered(bool checked);
    void on_moduleType_currentIndexChanged(int index);

    void on_actionOutput_triggered(bool checked);

    void on_actionConnect_triggered(bool checked);

    void on_generateImage_released();

    void on_action_Save_project_triggered();

    void on_action_Load_project_triggered();

    void on_action_Export_noise_description_triggered();

    void on_actionModifier_triggered();

    void on_actionCombiner_triggered();

private:
    Ui::MainWindow *ui;
    NoiseModuleScene *nmScene;
    bool blockCurrentIndexChange;
    QWidget *opt;
    PreviewRenderer *previewRenderer;

};

#endif // MAINWINDOW_H

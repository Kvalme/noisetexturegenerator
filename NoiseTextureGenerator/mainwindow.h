#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsItem>
#include <QString>
#include "PreviewRenderer/previewrenderer.h"
#include "clnoise.h"


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

    void exportSceneData(const char *fname);



public slots:
    void itemInserted(NoiseModule *);
    void itemSelected();

private slots:
    void on_actionNoise_module_triggered();
    void on_moduleType_currentIndexChanged(int index);
    void on_actionOutput_triggered(bool);
    void on_generateImage_released();
    void on_action_Save_project_triggered();
    void on_action_Load_project_triggered();
    void on_action_Export_noise_description_triggered();
    void on_action_New_project_triggered();

private:
    void moduleSelected(NoiseModule *module, int index);

    Ui::MainWindow *ui;
    NoiseModuleScene *nmScene;
    bool blockCurrentIndexChange;
    QWidget *opt;
    PreviewRenderer *previewRenderer;
    QString lastFileName;
    CLNoise::Noise *noise;

};

#endif // MAINWINDOW_H

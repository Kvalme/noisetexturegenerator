#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsItem>
#include <QString>
#include <QTreeWidgetItem>
#include "PreviewRenderer/previewrenderer.h"
#include "clnoise/noise.h"


class NoiseModuleScene;
class NoiseModule;
class QListWidgetItem;
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
    void exportSceneData(const char *fname, bool isExport = false);
    void closeEvent(QCloseEvent *);


public slots:
    void itemSelected();

private slots:
    void on_generateImage_released();
    void on_action_Save_project_triggered();
    void on_action_Load_project_triggered();
    void on_action_Export_noise_description_triggered();
    void on_action_New_project_triggered();
    void onAttributeValueChanged(int value);
    void on_attribute_gradient_changed();

    void on_clPlatform_currentIndexChanged(int index);
    void on_clDevice_currentIndexChanged(int index);

    void on_modulesTree_itemDoubleClicked(QTreeWidgetItem *item, int);

private:
    void populateOpenCLPlatforms();
    void populateOpenCLDevices(cl_platform_id platform);

    void buildModuleOptions(NoiseModule*);
    Ui::MainWindow *ui;
    NoiseModuleScene *nmScene;
    bool blockCurrentIndexChange;
    QWidget *opt;
    PreviewRenderer *previewRenderer;
    QString lastFileName;
    CLNoise::Noise *noise;
    NoiseModule *currentModule;

    cl_context clContext;

};

#endif // MAINWINDOW_H

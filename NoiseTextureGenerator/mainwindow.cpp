#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "noisemodulescene.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    nmScene = new NoiseModuleScene;
    ui->graphicsView->setScene(nmScene);

    connect(nmScene, SIGNAL(itemInserted(NoiseModule*)), this, SLOT(itemInserted(NoiseModule*)));
    connect(nmScene, SIGNAL(itemSelected(QGraphicsItem*)), this, SLOT(itemSelected(QGraphicsItem*)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::on_pushButton_released()
{
    nmScene->setMode(NoiseModuleScene::InsertItem);
    nmScene->setItemType(NoiseModule::NoiseGenerator);
}
void MainWindow::itemInserted(NoiseModule *)
{
    nmScene->setMode(NoiseModuleScene::MoveItem);
}

void MainWindow::itemSelected(NoiseModule *)
{

}

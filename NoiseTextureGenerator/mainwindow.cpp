#include <QLayout>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "noisemodulescene.h"
#include "noisemodule.h"
#include "noisegenerator.h"
#include "noiseoutput.h"

#include "NoiseGenerators/billowoptions.h"
#include "NoiseGenerators/checkerboardoptions.h"
#include "NoiseGenerators/constoptions.h"
#include "NoiseGenerators/cylindersoptions.h"
#include "NoiseGenerators/perlinoptions.h"
#include "NoiseGenerators/ridgedmultioptions.h"
#include "NoiseGenerators/spheresoptions.h"
#include "NoiseGenerators/voronoioptions.h"

#include "NoiseOutput/cylinderoutput.h"
#include "NoiseOutput/planeoptions.h"
#include "NoiseOutput/sphereoptions.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    nmScene = new NoiseModuleScene;
    ui->graphicsView->setScene(nmScene);

    connect(nmScene, SIGNAL(itemInserted(NoiseModule*)), this, SLOT(itemInserted(NoiseModule*)));
    connect(nmScene, SIGNAL(selectionChanged()), this, SLOT(itemSelected()));
    blockCurrentIndexChange = false;
    opt = 0;

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

void MainWindow::itemInserted(NoiseModule *)
{
//    nmScene->setMode(NoiseModuleScene::MoveItem);
}

void MainWindow::itemSelected()
{
    std::cerr<<__FUNCTION__<<std::endl;
    if(nmScene->selectedItems().empty())return;
    QGraphicsItem *item = nmScene->selectedItems().first();
    if(item->type()!=NoiseModule::Type)return;
    NoiseModule *module = dynamic_cast<NoiseModule*>(item);
    fillModuleType(module);
}

void MainWindow::on_actionNoise_generator_triggered(bool)
{
    nmScene->addModule(NoiseModule::Generator);
}
void MainWindow::on_actionOutput_triggered(bool checked)
{
    nmScene->addModule(NoiseModule::Output);
}

void MainWindow::on_moduleType_currentIndexChanged(int index)
{
    std::cerr<<"Block:"<<blockCurrentIndexChange<<" index:"<<index<<std::endl;
    if(blockCurrentIndexChange)return;
    if(index<0)return;
    NoiseModule *module = dynamic_cast<NoiseModule*>(nmScene->selectedItems().first());
    switch(module->moduleType())
    {
	case NoiseModule::Generator: generatorSelected(module, index);
	    break;
	case NoiseModule::Output: outputSelected(module, index);
	    break;
    }
}

void MainWindow::fillModuleType(NoiseModule *module)
{
    switch(module->moduleType())
    {
	case NoiseModule::Generator: fillGeneratorModuleType(module);
	    break;
	case NoiseModule::Output: fillOutputModuleType(module);
	    break;
    }
}
void MainWindow::fillGeneratorModuleType(NoiseModule *module)
{
    std::cerr<<__FUNCTION__<<std::endl;
    NoiseGeneratorModule *m = dynamic_cast<NoiseGeneratorModule*>(module);
    blockCurrentIndexChange = true;
    std::cerr<<__FUNCTION__<<" Start blocking"<<std::endl;
    ui->moduleType->clear();
    int curIndex = 0;
    for(int a=NoiseGeneratorModule::Billow; a<=NoiseGeneratorModule::Voronoi; ++a)
    {
	ui->moduleType->addItem(m->getGeneratorName((NoiseGeneratorModule::GeneratorType)a).c_str());
	if((NoiseGeneratorModule::GeneratorType)a == m->getGeneratorType())curIndex = a;

    }
    blockCurrentIndexChange = false;
    std::cerr<<__FUNCTION__<<" End blocking"<<std::endl;
    ui->moduleType->setCurrentIndex(curIndex>2?curIndex-1:curIndex+1);
    ui->moduleType->setCurrentIndex(curIndex);
}
void MainWindow::generatorSelected(NoiseModule *module, int index)
{
    std::cerr<<__FUNCTION__<<std::endl;
    NoiseGeneratorModule *m = dynamic_cast<NoiseGeneratorModule*>(module);
    m->setGeneratorType((NoiseGeneratorModule::GeneratorType)index);
    if(opt)
    {
	delete opt;
	QLayout *layout = ui->moduleOptionsFrame->layout();
	delete layout;
    }

    switch((NoiseGeneratorModule::GeneratorType)index)
    {
	case NoiseGeneratorModule::Billow:
	    opt = new BillowOptions(m);
	    break;
	case NoiseGeneratorModule::Checkerboard:
	    opt = new CheckerboardOptions(m);
	    break;
	case NoiseGeneratorModule::Const:
	    opt = new ConstOptions(m);
	    break;
	case NoiseGeneratorModule::Cylinders:
	    opt = new CylindersOptions(m);
	    break;
	case NoiseGeneratorModule::Perlin:
	    opt = new PerlinOptions(m);
	    break;
	case NoiseGeneratorModule::RidgedMulti:
	    opt = new RidgedMultiOptions(m);
	    break;
	case NoiseGeneratorModule::Spheres:
	    opt = new SpheresOptions(m);
	    break;
	case NoiseGeneratorModule::Voronoi:
	    opt = new VoronoiOptions(m);
	    break;
    }
    ui->moduleOptionsFrame->setLayout(new QVBoxLayout());
    ui->moduleOptionsFrame->layout()->addWidget(opt);

}

void MainWindow::fillOutputModuleType(NoiseModule *module)
{
    std::cerr<<__FUNCTION__<<std::endl;
    NoiseOutputModule *m = dynamic_cast<NoiseOutputModule*>(module);
    blockCurrentIndexChange = true;
    std::cerr<<__FUNCTION__<<" Start blocking"<<std::endl;
    ui->moduleType->clear();
    int curIndex = 0;
    for(int a=NoiseOutputModule::Cylinder; a<=NoiseOutputModule::Sphere; ++a)
    {
	ui->moduleType->addItem(m->getOutputName((NoiseOutputModule::OutputType)a).c_str());
	if((NoiseOutputModule::OutputType)a == m->getOutputType())curIndex = a;

    }
    blockCurrentIndexChange = false;
    std::cerr<<__FUNCTION__<<"End blocking"<<std::endl;
    ui->moduleType->setCurrentIndex(curIndex>1?curIndex-1:curIndex+1);
    ui->moduleType->setCurrentIndex(curIndex);

}
void MainWindow::outputSelected(NoiseModule *module, int index)
{
    std::cerr<<__FUNCTION__<<std::endl;
    NoiseOutputModule *m = dynamic_cast<NoiseOutputModule*>(module);
    m->setOutputType((NoiseOutputModule::OutputType)index);
    if(opt)
    {
	delete opt;
	QLayout *layout = ui->moduleOptionsFrame->layout();
	delete layout;
    }

    switch((NoiseOutputModule::OutputType)index)
    {
	case NoiseOutputModule::Cylinder:
	    opt = new CylinderOutput(m);
	    break;
	case NoiseOutputModule::Plane:
	    opt = new PlaneOptions(m);
	    break;
	case NoiseGeneratorModule::Const:
	    opt = new SphereOptions(m);
	    break;
    }
    ui->moduleOptionsFrame->setLayout(new QVBoxLayout());
    ui->moduleOptionsFrame->layout()->addWidget(opt);
}

void MainWindow::on_actionConnect_triggered(bool checked)
{
    if(checked)nmScene->setMode(NoiseModuleScene::InsertLine);
    else nmScene->setMode(NoiseModuleScene::MoveItem);
}

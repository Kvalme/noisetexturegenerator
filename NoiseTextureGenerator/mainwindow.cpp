#include <iostream>
#include <set>
#include <QLayout>
#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "noisemodulescene.h"
#include "noisemodule.h"
#include "noisegenerator.h"
#include "noiseoutput.h"
#include "noisecombiner.h"
#include "noisemodifier.h"
#include "noiseselector.h"

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

#include "NoiseModifiers/modifierabs.h"
#include "NoiseModifiers/modifierclamp.h"
#include "NoiseModifiers/modifiercurve.h"
#include "NoiseModifiers/modifierexponent.h"
#include "NoiseModifiers/modifierinvert.h"
#include "NoiseModifiers/modifierscalebias.h"
#include "NoiseModifiers/modifierterrace.h"

#include "NoiseSelector/selectorblend.h"
#include "NoiseSelector/selectorselect.h"

#include "Generation/generation.h"
#include "Generation/ntgploader.h"

#include "PreviewRenderer/previewrenderer.h"


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
    previewRenderer = new PreviewRenderer(this);

    foreach (QAction *action, ui->menu_File->actions())
    {
        QString name = action->text();
        if(action->text() == "&Save project")action->setIcon(QIcon::fromTheme("document-save"));
        if(action->text() == "&Open project")action->setIcon(QIcon::fromTheme("document-open"));
        if(action->text() == "&Export noise description")action->setIcon(QIcon::fromTheme("text-x-script"));
    }
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
void MainWindow::on_actionModifier_triggered()
{
    nmScene->addModule(NoiseModule::Modifier);
}
void MainWindow::on_actionCombiner_triggered()
{
    nmScene->addModule(NoiseModule::Combiner);
}
void MainWindow::on_actionSelector_triggered()
{
    nmScene->addModule(NoiseModule::Selector);
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
	case NoiseModule::Modifier: modifierSelected(module, index);
	    break;
	case NoiseModule::Combiner: combinerSelected(module, index);
	    break;
	case NoiseModule::Selector: selectorSelected(module, index);
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
	case NoiseModule::Modifier: fillModifierModuleType(module);
	    break;
	case NoiseModule::Combiner: fillCombinerModuleType(module);
	    break;
	case NoiseModule::Selector: fillSelectorModuleType(module);
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

void MainWindow::on_generateImage_released()
{
    NoiseXMLGenerator generator;

    QList<QGraphicsItem*> items = nmScene->items();
    QGraphicsItem* item;
    std::set<NoiseModule*> modules;
    foreach(item, items)
    {
        if(item->type()!=NoiseModule::Type)continue;
        NoiseModule *mod = dynamic_cast<NoiseModule*>(item);
        modules.insert(mod);
    }

    TiXmlDocument *doc = generator.generateExport(modules, ui->gradientEditor->getGradientPoints());

    previewRenderer->show();
    previewRenderer->showTexture(doc);
}

void MainWindow::on_action_Save_project_triggered()
{
    QFileDialog dialog;
    dialog.setDefaultSuffix("ntgp");
    dialog.setNameFilter(tr("NoiseTextureGenerator project (*.ntgp)"));
    dialog.setLabelText(QFileDialog::Accept, tr("Save"));
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setViewMode(QFileDialog::Detail);
    QString saveFileName;
    if(dialog.exec())
    {
	QStringList saveFileNames = dialog.selectedFiles();
	saveFileName = saveFileNames.at(0);

	exportSceneData(saveFileName.toUtf8().data());
    }

}

void MainWindow::on_action_Load_project_triggered()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    QString fileName = dialog.getOpenFileName(this, tr("Open project"), "", tr("NoiseTextureGenerator project (*.ntgp)"));
    if(fileName.isEmpty())return;

    NTGPLoader loader;
    TiXmlDocument doc;
    doc.LoadFile(fileName.toUtf8().data());
    QVector<GradientEditor::GradientPoint> gradient;
    loader.load(&doc, nmScene, &gradient);
    ui->gradientEditor->setGradient(gradient);
}

void MainWindow::on_action_Export_noise_description_triggered()
{
    QFileDialog dialog;
    dialog.setDefaultSuffix("xml");
    dialog.setNameFilter(tr("noise description (*.xml)"));
    dialog.setLabelText(QFileDialog::Accept, tr("Save"));
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setViewMode(QFileDialog::Detail);
    QString saveFileName;
    if(dialog.exec())
    {
        QStringList saveFileNames = dialog.selectedFiles();
        saveFileName = saveFileNames.at(0);

        NoiseXMLGenerator generator;

        QList<QGraphicsItem*> items = nmScene->items();
        QGraphicsItem* item;
        std::set<NoiseModule*> modules;
        foreach(item, items)
        {
            if(item->type()!=NoiseModule::Type)continue;
            NoiseModule *mod = dynamic_cast<NoiseModule*>(item);
            modules.insert(mod);
        }
        TiXmlDocument *doc = generator.generateExport(modules, ui->gradientEditor->getGradientPoints());
        doc->SaveFile(saveFileName.toUtf8().data());
    }
}
void MainWindow::exportSceneData(const char *fname)
{
    NoiseXMLGenerator generator;

    QList<QGraphicsItem*> items = nmScene->items();
    QGraphicsItem* item;
    std::set<NoiseModule*> modules;
    foreach(item, items)
    {
	if(item->type()!=NoiseModule::Type)continue;
	NoiseModule *mod = dynamic_cast<NoiseModule*>(item);
	modules.insert(mod);
    }
    TiXmlDocument *doc = generator.generateSave(modules, ui->gradientEditor->getGradientPoints());
    doc->SaveFile(fname);
}


void MainWindow::fillModifierModuleType(NoiseModule *module)
{
    std::cerr<<__FUNCTION__<<std::endl;
    NoiseModifierModule *m = dynamic_cast<NoiseModifierModule*>(module);
    blockCurrentIndexChange = true;
    std::cerr<<__FUNCTION__<<" Start blocking"<<std::endl;
    ui->moduleType->clear();
    int curIndex = 0;
    for(int a=NoiseModifierModule::Abs; a<=NoiseModifierModule::Terrace; ++a)
    {
	ui->moduleType->addItem(m->getName((NoiseModifierModule::ModifierType)a).c_str());
	if((NoiseModifierModule::ModifierType)a == m->getType())curIndex = a;

    }
    blockCurrentIndexChange = false;
    std::cerr<<__FUNCTION__<<" End blocking"<<std::endl;
    ui->moduleType->setCurrentIndex(curIndex>2?curIndex-1:curIndex+1);
    ui->moduleType->setCurrentIndex(curIndex);
}
void MainWindow::modifierSelected(NoiseModule *module, int index)
{
    std::cerr<<__FUNCTION__<<std::endl;
    NoiseModifierModule *m = dynamic_cast<NoiseModifierModule*>(module);
    m->setType((NoiseModifierModule::ModifierType)index);
    if(opt)
    {
	delete opt;
	QLayout *layout = ui->moduleOptionsFrame->layout();
	delete layout;
    }

    switch((NoiseModifierModule::ModifierType)index)
    {
	case NoiseModifierModule::Abs:
	    opt = new ModifierAbs(m);
	    break;
	case NoiseModifierModule::Clamp:
	    opt = new ModifierClamp(m);
	    break;
	case NoiseModifierModule::Curve:
	    opt = new ModifierCurve(m);
	    break;
	case NoiseModifierModule::Exponent:
	    opt = new ModifierExponent(m);
	    break;
	case NoiseModifierModule::Invert:
	    opt = new ModifierInvert(m);
	    break;
	case NoiseModifierModule::ScaleBias:
	    opt = new ModifierScaleBias(m);
	    break;
	case NoiseModifierModule::Terrace:
	    opt = new ModifierTerrace(m);
	    break;
    }
    ui->moduleOptionsFrame->setLayout(new QVBoxLayout());
    ui->moduleOptionsFrame->layout()->addWidget(opt);

}

void MainWindow::fillCombinerModuleType(NoiseModule *module)
{
    std::cerr<<__FUNCTION__<<std::endl;
    NoiseCombinerModule *m = dynamic_cast<NoiseCombinerModule*>(module);
    blockCurrentIndexChange = true;
    ui->moduleType->clear();
    int curIndex = 0;
    for(int a=NoiseCombinerModule::Add; a<=NoiseCombinerModule::Power; ++a)
    {
	ui->moduleType->addItem(m->getName((NoiseCombinerModule::CombinerType)a).c_str());
	if((NoiseCombinerModule::CombinerType)a == m->getType())curIndex = a;

    }
    blockCurrentIndexChange = false;
    ui->moduleType->setCurrentIndex(curIndex>2?curIndex-1:curIndex+1);
    ui->moduleType->setCurrentIndex(curIndex);
}
void MainWindow::combinerSelected(NoiseModule *module, int index)
{
    std::cerr<<__FUNCTION__<<std::endl;
    NoiseCombinerModule *m = dynamic_cast<NoiseCombinerModule*>(module);
    m->setType((NoiseCombinerModule::CombinerType)index);
}

void MainWindow::fillSelectorModuleType(NoiseModule *module)
{
    std::cerr<<__FUNCTION__<<std::endl;
    NoiseSelectorModule *m = dynamic_cast<NoiseSelectorModule*>(module);
    blockCurrentIndexChange = true;
    ui->moduleType->clear();
    int curIndex = 0;
    for(int a=NoiseSelectorModule::Blend; a<=NoiseSelectorModule::Select; ++a)
    {
	ui->moduleType->addItem(m->getName((NoiseSelectorModule::SelectorType)a).c_str());
	if((NoiseSelectorModule::ModuleType)a == m->getType())curIndex = a;

    }
    blockCurrentIndexChange = false;
    ui->moduleType->setCurrentIndex(curIndex>2?curIndex-1:curIndex+1);
    ui->moduleType->setCurrentIndex(curIndex);
}

void MainWindow::selectorSelected(NoiseModule *module, int index)
{
    std::cerr<<__FUNCTION__<<std::endl;
    NoiseSelectorModule *m = dynamic_cast<NoiseSelectorModule*>(module);
    m->setType((NoiseSelectorModule::SelectorType)index);
    if(opt)
    {
	delete opt;
	QLayout *layout = ui->moduleOptionsFrame->layout();
	delete layout;
    }

    switch((NoiseSelectorModule::SelectorType)index)
    {
	case NoiseSelectorModule::Blend:
	    opt = new SelectorBlend(m);
	    break;
	case NoiseSelectorModule::Select:
	    opt = new SelectorSelect(m);
	    break;
    }
    ui->moduleOptionsFrame->setLayout(new QVBoxLayout());
    ui->moduleOptionsFrame->layout()->addWidget(opt);
}

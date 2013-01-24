#include <iostream>
#include <set>
#include <QLayout>
#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "noisemodulescene.h"
#include "noisemodule.h"
#include "noiseoutput.h"

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
        else if(action->text() == "&Open project")action->setIcon(QIcon::fromTheme("document-open"));
        else if(action->text() == "&Export noise description")action->setIcon(QIcon::fromTheme("text-x-script"));
        else if(action->text() == "&New project")action->setIcon(QIcon::fromTheme("document-new"));

    }
    lastFileName = "";
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

void MainWindow::on_actionNoise_module_triggered(bool)
{
    nmScene->addModule(NoiseModule::Base);
}

void MainWindow::on_actionOutput_triggered(bool)
{
    nmScene->addModule(NoiseModule::Output);
}

void MainWindow::on_moduleType_currentIndexChanged(int index)
{
    if(blockCurrentIndexChange)return;
    if(index<0)return;
    NoiseModule *module = dynamic_cast<NoiseModule*>(nmScene->selectedItems().first());
    moduleSelected(module, index);
}

void MainWindow::fillModuleType(NoiseModule *module)
{
/*    switch(module->moduleType())
    {
    case NoiseModule::Base: fillGeneratorModuleType(module);
	    break;
	case NoiseModule::Output: fillOutputModuleType(module);
	    break;
    }*/
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
    if(lastFileName == "")
    {
        if(dialog.exec())
        {
            QStringList saveFileNames = dialog.selectedFiles();
            saveFileName = saveFileNames.at(0);
        }
    }
    else saveFileName = lastFileName;

    if (saveFileName != "") exportSceneData(saveFileName.toUtf8().data());
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

    nmScene->clear();
    QVector<GradientEditor::GradientPoint> gradient;
    loader.load(&doc, nmScene, &gradient);

    ui->gradientEditor->setGradient(gradient);
    lastFileName = fileName;
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



void MainWindow::on_action_New_project_triggered()
{
    nmScene->clear();
}


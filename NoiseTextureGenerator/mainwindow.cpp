#include <iostream>
#include <set>
#include <QLayout>
#include <QFileDialog>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "noisemodulescene.h"
#include "noisemodule.h"
#include "noiseoutput.h"

#include "Generation/generation.h"
#include "Generation/ntgploader.h"

#include "PreviewRenderer/previewrenderer.h"

class AttributeData : public QObjectUserData
{
public:
    AttributeData(const std::string &name, CLNoise::ModuleAttribute::ATTRIBUTE_TYPE t) : attName(name), type(t){}
    std::string getAddName() const { return attName;}
    CLNoise::ModuleAttribute::ATTRIBUTE_TYPE getType() const { return type;}
private:
    std::string attName;
    CLNoise::ModuleAttribute::ATTRIBUTE_TYPE type;
};

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
    try
    {
        noise = new CLNoise::Noise;
        noise->initCLContext();
    }
    catch(CLNoise::Error &error)
    {
        QMessageBox::critical(this, "Error in libclnoise", error.what());
        return;
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
    if(nmScene->selectedItems().empty())return;

    QGraphicsItem *item;
    foreach(item, nmScene->selectedItems())
    {
        int type = item->type();
        if(type != NoiseModuleScene::BaseModule && type!= NoiseModuleScene::OutputModule)return;
        else break;
    }

    buildModuleOptions(dynamic_cast<NoiseModule*>(item));

}

void MainWindow::on_actionNoise_module_triggered()
{
    try
    {
        nmScene->addModule(NoiseModule::BaseModule, noise);
    }
    catch(CLNoise::Error &error)
    {
        QMessageBox::critical(this, "Error in libclnoise", error.what());
        return;
    }

}

void MainWindow::on_actionOutput_triggered(bool)
{
    try
    {
        nmScene->addModule(NoiseModule::OutputModule, noise);
    }
    catch(CLNoise::Error &error)
    {
        QMessageBox::critical(this, "Error in libclnoise", error.what());
        return;
    }
}

void MainWindow::on_moduleType_currentIndexChanged(int index)
{
    if(blockCurrentIndexChange)return;
    if(index<0)return;
//    NoiseModule *module = dynamic_cast<NoiseModule*>(nmScene->selectedItems().first());
}

void MainWindow::buildModuleOptions(NoiseModule *module)
{
    CLNoise::Module *noiseModule = module->getNoiseModule();
    if(!noiseModule)return;
    auto attributes = noiseModule->getAttributes();

    if(ui->moduleOptionsFrame->layout())
    {
        QLayout *l = ui->moduleOptionsFrame->layout();
        QLayoutItem* item;
        while ( ( item = l->takeAt( 0 ) ) != NULL )
        {
            delete item->widget();
            delete item;
        }
        delete l;
    }

    QGridLayout *layout = new QGridLayout();
    ui->moduleOptionsFrame->setLayout(layout);

    int row = 1;
    for(const CLNoise::ModuleAttribute &att : attributes)
    {
        QString val;
        QSlider *control = new QSlider(Qt::Horizontal);
        AttributeData *data = new AttributeData(att.getName(), att.getType());
        if(att.getType() == CLNoise::ModuleAttribute::FLOAT)
        {
            val = QString("%1").arg(att.getFloat());
            control->setMinimum(0);
            control->setMaximum(100);
            control->setMaximumWidth(100);
            control->setEnabled(true);
            control->setValue(att.getFloat() * 100.);
            control->activateWindow();
            control->setUserData(Qt::UserRole + 1, data);
        }
        else if(att.getType() == CLNoise::ModuleAttribute::INT)
        {
            val = QString("%1").arg(att.getInt());
            control->setMinimum(0);
            control->setMaximum(100);
            control->setMaximumWidth(100);
            control->setEnabled(true);
            control->setValue(att.getInt());
            control->activateWindow();
            control->setUserData(Qt::UserRole + 1, data);
        }
        connect(control, SIGNAL(valueChanged(int)), this, SLOT(onAttributeValueChanged(int)));
        QLabel *value = new QLabel(val);
        value->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        value->setObjectName(QString(att.getName().c_str()) + "Value");
        value->setAlignment(Qt::AlignLeft);

        QLabel *valueName = new QLabel(QString(att.getName().c_str())+":");
        valueName->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        valueName->setAlignment(Qt::AlignRight);

        control->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

        layout->addWidget(valueName, row, 0);
        layout->addWidget(value, row, 1);
        layout->addWidget(control, row, 2);
        row++;
    }
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

void MainWindow::onAttributeValueChanged(int value)
{
    QObject *s = sender();
    if(!s)return;
    QWidget *w = dynamic_cast<QWidget*>(s);
    AttributeData *a= dynamic_cast<AttributeData*>(w->userData(Qt::UserRole + 1));
    if(!a)return;

    std::string name = a->getAddName();
    QLabel *valLabel = ui->moduleOptionsFrame->findChild<QLabel*>(QString(name.c_str())+"Value");
    if(!valLabel)return;

    if(a->getType() == CLNoise::ModuleAttribute::FLOAT)
    {
        char buf[10];
        snprintf(buf, 10, "%.2f", (float)value/100.);
        valLabel->setText(buf);
    }
    else if(a->getType() == CLNoise::ModuleAttribute::INT)
    {
        valLabel->setText(QString("%1").arg(value));
    }

}

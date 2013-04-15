#include <iostream>
#include <set>
#include <QLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QSettings>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "noisemodulescene.h"
#include "noisemodule.h"
#include "noiseoutput.h"

#include "Generation/generation.h"
#include "Generation/ntgploader.h"

#include "PreviewRenderer/previewrenderer.h"

#include "oclutils.h"
#include "clnoise/error.h"
#include "clnoise/gradientattribute.h"

class AttributeData : public QObjectUserData
{
public:
    AttributeData(const std::string &name, CLNoise::Attribute::ATTRIBUTE_TYPE t) : attName(name), type(t){}
    std::string getAddName() const { return attName;}
    CLNoise::Attribute::ATTRIBUTE_TYPE getType() const { return type;}
private:
    std::string attName;
    CLNoise::Attribute::ATTRIBUTE_TYPE type;
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSettings settings;
    restoreGeometry(settings.value("mainWindowGeometry").toByteArray());


    nmScene = new NoiseModuleScene;
    ui->graphicsView->setScene(nmScene);
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
        ui->modulesTree->clear();

        QTreeWidgetItem *parent = new QTreeWidgetItem(QStringList(tr("Generators")));
        ui->modulesTree->addTopLevelItem(parent);
        for(std::string &str : noise->getModulesOfType(CLNoise::BaseModule::GENERATOR))
        {
            QTreeWidgetItem *item = new QTreeWidgetItem();
            item->setText(0, str.c_str());
            item->setData(0, Qt::UserRole, NoiseModule::GeneratorModule);
            parent->addChild(item);
        }

        parent = new QTreeWidgetItem(QStringList(tr("Filters")));
        ui->modulesTree->addTopLevelItem(parent);
        for(std::string &str : noise->getModulesOfType(CLNoise::BaseModule::FILTER))
        {
            QTreeWidgetItem *item = new QTreeWidgetItem();
            item->setText(0, str.c_str());
            item->setData(0, Qt::UserRole, NoiseModule::ModifierModule);
            parent->addChild(item);
        }

        parent = new QTreeWidgetItem(QStringList(tr("Outputs")));
        ui->modulesTree->addTopLevelItem(parent);
        for(std::string &str : noise->getModulesOfType(CLNoise::BaseModule::OUTPUT))
        {
            QTreeWidgetItem *item = new QTreeWidgetItem();
            item->setText(0, str.c_str());
            item->setData(0, Qt::UserRole, NoiseModule::OutputModule);
            parent->addChild(item);
        }

        ui->modulesTree->expandAll();
        ui->modulesTree->resizeColumnToContents(0);

    }
    catch(CLNoise::Error &error)
    {
        QMessageBox::critical(this, "Error in libclnoise", error.what());
        return;
    }

    clContext = 0;
    populateOpenCLPlatforms();

    lastFileName = "";

    restoreState(settings.value("mainWindowState").toByteArray());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent*)
{
    QSettings settings;
    settings.setValue("mainWindowGeometry", saveGeometry());
    settings.setValue("mainWindowState", saveState());
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

void MainWindow::itemSelected()
{
    if(nmScene->selectedItems().empty())return;

    QGraphicsItem *item = 0;
    foreach(item, nmScene->selectedItems())
    {
        int type = item->type();
        if(type != NoiseModuleScene::BaseModule && type!= NoiseModuleScene::OutputModule)continue;
        else break;
    }
    buildModuleOptions(dynamic_cast<NoiseModule*>(item));
}

void MainWindow::buildModuleOptions(NoiseModule *module)
{
    if(!module)return;
    currentModule = module;

    CLNoise::BaseModule *noiseModule = module->getNoiseModule();
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
    for(const CLNoise::Attribute *att : attributes)
    {
        QString val;
        AttributeData *data = new AttributeData(att->getName(), att->getType());
        if(att->getType() == CLNoise::Attribute::FLOAT)
        {
            QSlider *control = new QSlider(Qt::Horizontal);
            val = QString("%1").arg(att->getFloat());
            control->setMinimum(att->getFloatMin() * 100.);
            control->setMaximum(att->getFloatMax() * 100.);
            control->setSingleStep(1);
            control->setTickInterval(100);
            control->setEnabled(true);
            control->setValue(att->getFloat() * 100.);
            control->activateWindow();
            control->setUserData(Qt::UserRole + 1, data);
            control->setTickPosition(QSlider::TicksBothSides);
            control->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
            connect(control, SIGNAL(valueChanged(int)), this, SLOT(onAttributeValueChanged(int)));
            layout->addWidget(control, row, 2);
        }
        else if(att->getType() == CLNoise::Attribute::INT)
        {
            QSlider *control = new QSlider(Qt::Horizontal);
            val = QString("%1").arg(att->getInt());
            control->setMinimum(att->getIntMin());
            control->setMaximum(att->getIntMax());
            int range = att->getIntMax() - att->getIntMin();
            control->setTickInterval( range > 100?range/100:1 );
            control->setSingleStep(1);
            control->setEnabled(true);
            control->setValue(att->getInt());
            control->activateWindow();
            control->setUserData(Qt::UserRole + 1, data);
            control->setTickPosition(QSlider::TicksBothSides);
            control->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
            connect(control, SIGNAL(valueChanged(int)), this, SLOT(onAttributeValueChanged(int)));
            layout->addWidget(control, row, 2);
        }
        else if(att->getType() == CLNoise::Attribute::GRADIENT)
        {
            GradientEditor *gradEditor = new GradientEditor();
            gradEditor->setMinimumHeight(60);
            gradEditor->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
            gradEditor->setUserData(Qt::UserRole + 1, data);

            QVector<GradientEditor::GradientPoint> gradPoints;
            const CLNoise::GradientAttribute *grad = static_cast<const CLNoise::GradientAttribute*>(att);
            for (int a = 0; a < grad->getPointCount(); ++a)
            {
                float pos;
                CLNoise::GradientAttribute::GradientPoint point(0, 0, 0, 0);
                grad->getPoint(a, &pos, &point);

                gradPoints.push_back(GradientEditor::GradientPoint(pos, QColor(point.r * 255., point.g*255., point.b*255., point.a*255.)));
            }
            gradEditor->setGradient(gradPoints);

            layout->addWidget(gradEditor, row, 2);
            connect(gradEditor, SIGNAL(valueChanged()), this, SLOT(on_attribute_gradient_changed()));
        }

        QLabel *value = new QLabel(val);
        value->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        value->setObjectName(QString(att->getName().c_str()) + "Value");
        value->setAlignment(Qt::AlignLeft | Qt::AlignCenter);

        QLabel *valueName = new QLabel(QString(att->getName().c_str())+":");
        valueName->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        valueName->setAlignment(Qt::AlignRight | Qt::AlignCenter);

        layout->addWidget(valueName, row, 0);
        layout->addWidget(value, row, 1);

        row++;
    }
    layout->addItem(new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding), row, 0 );

    //Add Output special configuration
    if (noiseModule->getType() == CLNoise::BaseModule::OUTPUT)
    {
        QPushButton *button = new QPushButton("Generate");
        button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        connect(button, SIGNAL(released()), this, SLOT(on_generateImage_released()));
        layout->addWidget(button, row, 0);
    }
}

void MainWindow::on_generateImage_released()
{
    if(currentModule->type() != NoiseModuleScene::OutputModule)return;
    if(!currentModule->getNoiseModule())return;

    previewRenderer->setNoise(noise);
    previewRenderer->show();
    previewRenderer->generateTexture(dynamic_cast<CLNoise::Output*>(currentModule->getNoiseModule()));
}

void MainWindow::on_action_Save_project_triggered()
{
    QFileDialog dialog;
    dialog.setDefaultSuffix("ntgp");
    dialog.setNameFilter(tr("NoiseTextureGenerator project (*.ntgp)"));
    dialog.setLabelText(QFileDialog::Accept, tr("Save"));
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setDirectory(qApp->applicationDirPath());
    QString saveFileName;
    if(lastFileName == "")
    {
        if(dialog.exec())
        {
            QStringList saveFileNames = dialog.selectedFiles();
            saveFileName = saveFileNames.at(0);
            lastFileName = saveFileName;
        }
    }
    else saveFileName = lastFileName;

    try
    {
        if (saveFileName != "") exportSceneData(saveFileName.toUtf8().data());
    }
    catch(CLNoise::Error &error)
    {
        QMessageBox::critical(this, "Error in libclnoise", error.what());
        return;
    }

}

void MainWindow::on_action_Load_project_triggered()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);

    QString fileName = dialog.getOpenFileName(this, tr("Open project"), qApp->applicationDirPath(), tr("NoiseTextureGenerator project (*.ntgp)"));
    if(fileName.isEmpty())return;

    NTGPLoader loader;
    TiXmlDocument doc;
    doc.LoadFile(fileName.toUtf8().data());

    nmScene->clear();
    loader.load(&doc, nmScene, noise);

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

        try
        {
            if (saveFileName != "") exportSceneData(saveFileName.toUtf8().data(), true);
        }
        catch(CLNoise::Error &error)
        {
            QMessageBox::critical(this, "Error in libclnoise", error.what());
            return;
        }
    }
}
void MainWindow::exportSceneData(const char *fname, bool isExport)
{
    NoiseXMLGenerator generator;

    QList<QGraphicsItem*> items = nmScene->items();
    QGraphicsItem* item;
    std::set<NoiseModule*> modules;
    foreach(item, items)
    {
        NoiseModule *mod = dynamic_cast<NoiseModule*>(item);
        if(mod) modules.insert(mod);
    }
    TiXmlDocument *doc;
    if(isExport) doc = generator.generateExport(modules);
    else doc = generator.generateSave(modules);
    doc->SaveFile(fname);
}



void MainWindow::on_action_New_project_triggered()
{
    nmScene->clear();
}

void MainWindow::on_attribute_gradient_changed()
{
    if(!currentModule)return;
    CLNoise::BaseModule *noiseModule = currentModule->getNoiseModule();
    if(!noiseModule)return;

    QObject *s = sender();
    if(!s)return;
    QWidget *w = dynamic_cast<QWidget*>(s);
    AttributeData *a= dynamic_cast<AttributeData*>(w->userData(Qt::UserRole + 1));
    if(!a)return;

    std::string name = a->getAddName();

    if(a->getType() == CLNoise::Attribute::GRADIENT)
    {
        GradientEditor *editor = static_cast<GradientEditor*>(s);
        const QVector<GradientEditor::GradientPoint> &points = editor->getGradientPoints();
        CLNoise::GradientAttribute att(name);

        for(auto it = points.begin(); it != points.end(); ++it)
        {
            GradientEditor::GradientPoint point = *it;
            att.addPoint(point.pos, CLNoise::GradientAttribute::GradientPoint(point.color.redF(), point.color.greenF(), point.color.blueF(), point.color.alphaF()));
        }
        noiseModule->setAttribute(att);
    }

}

void MainWindow::onAttributeValueChanged(int value)
{
    if(!currentModule)return;
    CLNoise::BaseModule *noiseModule = currentModule->getNoiseModule();
    if(!noiseModule)return;

    QObject *s = sender();
    if(!s)return;
    QWidget *w = dynamic_cast<QWidget*>(s);
    AttributeData *a= dynamic_cast<AttributeData*>(w->userData(Qt::UserRole + 1));
    if(!a)return;

    std::string name = a->getAddName();
    QLabel *valLabel = ui->moduleOptionsFrame->findChild<QLabel*>(QString(name.c_str())+"Value");
    if(!valLabel)return;

    if(a->getType() == CLNoise::Attribute::FLOAT)
    {
        char buf[10];
        snprintf(buf, 10, "%.2f", (float)value/100.);
        valLabel->setText(buf);
        CLNoise::Attribute att(name, (float)value/100.f, 0.f, 0.f);
        noiseModule->setAttribute(att);
    }
    else if(a->getType() == CLNoise::Attribute::INT)
    {
        valLabel->setText(QString("%1").arg(value));
        CLNoise::Attribute att(name, value, 0, 0);
        noiseModule->setAttribute(att);
    }
}

void MainWindow::populateOpenCLPlatforms()
{
    ui->clPlatform->clear();

    auto platforms = oclGetPlatforms();
    for( auto it = platforms.begin(); it != platforms.end(); ++it)
    {
        cl_platform_id p = it.key();
        qlonglong lp = (qlonglong)p;
        ui->clPlatform->addItem(it.value(), QVariant(lp));
    }
}

void MainWindow::populateOpenCLDevices(cl_platform_id platform)
{
    ui->clDevice->clear();

    auto devices = oclGetDevicesForPlatform(platform);
    for( auto it = devices.begin(); it != devices.end(); ++it)
    {
        cl_device_id p = it.key();
        qlonglong lp = (qlonglong)p;
        ui->clDevice->addItem(it.value(), QVariant(lp));
    }
}


void MainWindow::on_clPlatform_currentIndexChanged(int index)
{
    cl_platform_id platform = (cl_platform_id)(ui->clPlatform->itemData(index).toLongLong());
    populateOpenCLDevices(platform);
}

void MainWindow::on_clDevice_currentIndexChanged(int index)
{
    if (index < 0)return;
    cl_device_id device = (cl_device_id)(ui->clDevice->itemData(index).toLongLong());
    if (!device) return;

    // Create a compute context
    cl_int err;
    clContext = clCreateContext(0, 1, &device, NULL, NULL, &err);
    if (!clContext) QMessageBox::critical(this, "OpenCL error", (std::string("Failed to create compute context: ") + CLNoise::getCLError(err)).c_str());

    try
    {
        noise->setCLDevice(device, clContext);
    }
    catch (CLNoise::Error &error)
    {
        QMessageBox::critical(this, "Error in libclnoise", error.what());
        return;
    }
}

void MainWindow::on_modulesTree_itemDoubleClicked(QTreeWidgetItem *item, int)
{
    bool isOk = true;
    int type = item->data(0, Qt::UserRole).toInt(&isOk);
    if (!isOk)return;

    try
    {
        nmScene->addModule((NoiseModule::ModuleType)type, noise, item->text(0));
    }
    catch(CLNoise::Error &error)
    {
        QMessageBox::critical(this, "Error in libclnoise", error.what());
        return;
    }
}

#include <QThread>
#include <QPainter>
#include <QMessageBox>
#include <QFileDialog>
#include <QTime>
#include "previewrenderer.h"
#include "ui_previewrenderer.h"
#include "clnoisemap.h"


PreviewRenderer::PreviewRenderer(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::PreviewRenderer)
{
    ui->setupUi(this);
    QPixmap pix(0, 0);
    pix.fill(Qt::black);
    ui->previewPixmap->setPixmap(pix);
    isAutoupdateOn = false;
    timer.connect(&timer, SIGNAL(timeout()), this, SLOT(generateTexture()));
    timer.setSingleShot(true);
}

void PreviewRenderer::generateTexture(CLNoise::Output *output)
{
    if(!output) return;
    currentOutput = output;

    generateTexture();
}

void PreviewRenderer::generateTexture()
{
    try
    {
        textureWidth = ui->width->currentText().toInt();
        textureHeight = ui->height->currentText().toInt();

        if (textureWidth == 0) textureWidth = 256;
        if (textureHeight == 0) textureWidth = 256;

        unsigned char *buf = new unsigned char[textureWidth * textureHeight * 4];
        currentOutput->setImageDimension(textureWidth, textureHeight);
        QTime tm;

        CLNoise::NoiseMap noiseMap(*noise);

        tm.start();
        noiseMap.build(currentOutput);
        noiseMap.allocateResources();
        noiseMap.buildKernel();
        ui->buildTime->setNum(tm.elapsed());

        tm.restart();
        noiseMap.runKernel();
        ui->runTime->setNum(tm.elapsed());

        tm.restart();
        noiseMap.transferData();
        ui->getTime->setNum(tm.elapsed());

        tm.restart();
        drawImage(currentOutput->getData());
        ui->drawTime->setNum(tm.elapsed());
        delete[] buf;

        if(isAutoupdateOn)
        {
            timer.start(ui->autoupdateTime->value() * 1000.);
        }

    }
    catch(CLNoise::Error &error)
    {
        QMessageBox::critical(this, "Error in libclnoise", error.what());
        return;
    }
}

void PreviewRenderer::drawImage(const unsigned char *image)
{
    QImage img(image, textureWidth, textureHeight, QImage::Format_ARGB32);
    QPixmap pix = QPixmap::fromImage(img);
    ui->previewPixmap->setPixmap(pix);
}

PreviewRenderer::~PreviewRenderer()
{
    delete ui;
}

void PreviewRenderer::changeEvent(QEvent *e)
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

void PreviewRenderer::on_action_Save_triggered()
{
    QFileDialog dialog;
    dialog.setDefaultSuffix("png");
    dialog.setNameFilter(tr("PNG image (*.png)"));
    dialog.setLabelText(QFileDialog::Accept, tr("Save"));
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setViewMode(QFileDialog::Detail);
    QString saveFileName;
    if(dialog.exec())
    {
        QStringList saveFileNames = dialog.selectedFiles();
        saveFileName = saveFileNames.at(0);
        QImage img = ui->previewPixmap->pixmap()->toImage();
        img.save(saveFileName, "png", 100);
    }
}

void PreviewRenderer::on_pushButton_released()
{
    generateTexture();
}

void PreviewRenderer::on_enableAutoupdate_toggled(bool checked)
{
    if(checked)
    {
        if(isAutoupdateOn) return;
        isAutoupdateOn = true;
        ui->pushButton->setEnabled(false);
        timer.start(ui->autoupdateTime->value() * 1000.);
    }
    else
    {
        ui->pushButton->setEnabled(true);
        if(isAutoupdateOn)
        {
            isAutoupdateOn = false;
            timer.stop();
        }
    }
}

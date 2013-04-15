#include <QThread>
#include <QPainter>
#include <QMessageBox>
#include <QFileDialog>
#include <QTime>
#include "previewrenderer.h"
#include "ui_previewrenderer.h"
#include "clnoise/noisemap.h"
#include "clnoise/error.h"
#include <fstream>

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

#ifdef DEBUG
        std::ofstream err("kernel.cl");
        err<<noiseMap.getKernelCode();
#endif
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
    QImage img(textureWidth, textureHeight, QImage::Format_ARGB32);
    int point = 0;
    for (int y = 0; y < textureHeight; ++y)
    {
        for (int x =0; x<textureWidth; ++x)
        {
            img.setPixel(x, y, qRgb(image[point*4], image[point*4+1], image[point*4+2]));
            point++;
        }
    }
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

    QStringList filters;
    filters<<tr("PNG image (*.png)")<<tr("JPG image (*.jpg)");
    dialog.setNameFilters(filters);

    dialog.setLabelText(QFileDialog::Accept, tr("Save"));
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setFileMode(QFileDialog::AnyFile);

    QString saveFileName;
    if(dialog.exec())
    {
        QStringList saveFileNames = dialog.selectedFiles();
        saveFileName = saveFileNames.at(0);
        QImage img = ui->previewPixmap->pixmap()->toImage();
        img.save(saveFileName, 0, 100);
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

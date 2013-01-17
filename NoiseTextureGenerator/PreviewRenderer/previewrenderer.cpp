#include "previewrenderer.h"
#include "ui_previewrenderer.h"
#include <QPainter>
#include <QFileDialog>
#include <QThread>


PreviewRenderer::PreviewRenderer(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::PreviewRenderer)
{
    ui->setupUi(this);
    xmlBuilder = 0;
    source = 0;
    QPixmap pix(0, 0);
    pix.fill(Qt::black);
    ui->previewPixmap->setPixmap(pix);
    isWorkerStarted = false;

    ui->statusbar->addPermanentWidget(&progressBar, 1);
}

void PreviewRenderer::showTexture(TiXmlDocument *doc)
{
    source = doc;
    if(xmlBuilder)delete xmlBuilder;
    xmlBuilder = new NoiseXMLBuilder;
    xmlBuilder->load(source);

    progressBar.setMaximum((xmlBuilder->getLineCount()-1) * 2);
    progressBar.setValue(0);

    if(isWorkerStarted)return;

    isWorkerStarted = true;
    ImageRenderer *worker = new ImageRenderer(xmlBuilder);
    QThread *workerThread = new QThread(this);

    connect(workerThread, SIGNAL(started()), worker, SLOT(renderImage()));
    connect(workerThread, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(worker, SIGNAL(finished()), workerThread, SLOT(quit()));

    connect(worker, SIGNAL(imageRendered(noise::utils::Image*)), this, SLOT(imageRendered(noise::utils::Image*)));
    connect(worker, SIGNAL(lineReady(int)), this, SLOT(lineReady(int)));
    worker->moveToThread(workerThread);

    workerThread->start();
}

void PreviewRenderer::imageRendered(noise::utils::Image *img)
{
    utils::Color *c = img->GetSlabPtr();
    int w = img->GetWidth();
    int h = img->GetHeight();

    QPixmap pix(w, h);
    pix.fill(Qt::black);
    QPainter painter(&pix);

    for(int y = 0; y < h; ++y)
    {
        for(int x = 0; x < w; ++x)
        {
            painter.setPen(QPen(QBrush(QColor(c->red, c->green, c->blue)), 1, Qt::SolidLine));
            painter.drawPoint(x, y);
            c++;
        }
        lineReady(h+y);
    }
    ui->previewPixmap->setPixmap(pix);
    isWorkerStarted = false;
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

void PreviewRenderer::lineReady(int value)
{
    progressBar.setValue(value);
}

ImageRenderer *ImageRenderer::current = 0;
void ImageRenderer::onLineReady(int row)
{
    ImageRenderer::current->lineReadySignalSender(row);
}
void ImageRenderer::lineReadySignalSender(int row)
{
    emit lineReady(row);
}

void ImageRenderer::renderImage()
{
    current = this;

    builder->setLineReadyCallback(onLineReady);

    noise::utils::Image *img = builder->getImage();

    builder->setLineReadyCallback(0);

    emit imageRendered(img);
    emit finished();
}


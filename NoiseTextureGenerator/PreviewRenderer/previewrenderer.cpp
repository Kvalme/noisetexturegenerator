#include <QThread>
#include <QPainter>
#include <QMessageBox>
#include <QFileDialog>
#include "previewrenderer.h"
#include "ui_previewrenderer.h"


PreviewRenderer::PreviewRenderer(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::PreviewRenderer)
{
    ui->setupUi(this);
    QPixmap pix(0, 0);
    pix.fill(Qt::black);
    ui->previewPixmap->setPixmap(pix);
}

void PreviewRenderer::generateTexture(CLNoise::Output *output)
{
    if(!output) return;

    try
    {
        textureWidth = 256;
        textureHeight = 256;
        unsigned char *buf = new unsigned char[textureWidth * textureHeight * 4];
        output->setImageDimension(textureWidth, textureHeight);
        output->build();
        output->run();
        output->getImage(buf);

        drawImage(buf);
        delete[] buf;
    }
    catch(CLNoise::Error &error)
    {
        QMessageBox::critical(this, "Error in libclnoise", error.what());
        return;
    }
}

void PreviewRenderer::drawImage(const unsigned char *image)
{
    QPixmap pix(textureWidth, textureHeight);
    pix.fill(Qt::black);
    QPainter painter(&pix);

#pragma pack(push, 1)
    struct Color
    {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    };
#pragma pack(pop)

    Color *c = (Color*)(image);

    for(int y = 0; y < textureWidth; ++y)
    {
        for(int x = 0; x < textureHeight; ++x)
        {
            painter.setPen(QPen(QBrush(QColor(c->r, c->g, c->b, c->a)), 1, Qt::SolidLine));
            painter.drawPoint(x, y);
            c++;
        }
    }
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

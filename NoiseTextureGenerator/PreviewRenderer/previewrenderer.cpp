#include "previewrenderer.h"
#include "ui_previewrenderer.h"
#include <QPainter>
#include <QFileDialog>
#include "GradientEditor/gradienteditor.h"


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
    ui->gradient->setLayout(new QVBoxLayout());
    gradientEditor = new GradientEditor(this);
    ui->gradient->layout()->addWidget(gradientEditor);
}
void PreviewRenderer::showTexture(TiXmlDocument *doc)
{
    source = doc;
    if(xmlBuilder)delete xmlBuilder;
    xmlBuilder = new NoiseXMLBuilder;
    xmlBuilder->load(source);

    drawImage();
}
#include <iostream>
void PreviewRenderer::drawImage()
{
    const QMap<float, QColor > &gradientPoints = gradientEditor->getGradientPoints();

    std::vector<NoiseXMLBuilder::GradientPoint> gradient;

    for(QMap<float, QColor>::const_iterator it = gradientPoints.constBegin(); it != gradientPoints.end(); ++it)
    {
        NoiseXMLBuilder::GradientPoint gPoint;
        gPoint.pos = it.key();
        gPoint.r = it.value().red();
        gPoint.g = it.value().green();
        gPoint.b = it.value().blue();
        gPoint.a = 255;
        gradient.push_back(gPoint);

        std::cerr<<"Adding point ["<<gPoint.pos<<"] = ["<<(int)gPoint.r<<":"<<(int)gPoint.g<<":"<<(int)gPoint.b<<":"<<(int)gPoint.a<<"]"<<std::endl;
    }


    noise::utils::Image *img = xmlBuilder->getImage(gradient.empty()?0:&gradient);

    utils::Color *c = img->GetSlabPtr();
    int w = img->GetWidth();
    int h = img->GetHeight();
    textureWidth = w;
    textureHeight = h;

    QPixmap pix(textureWidth, textureHeight);
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

void PreviewRenderer::on_refreshImage_released()
{
    drawImage();
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

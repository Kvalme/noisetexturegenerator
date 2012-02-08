#include "previewrenderer.h"
#include "ui_previewrenderer.h"
#include <QPainter>


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
}
void PreviewRenderer::showTexture(TiXmlDocument *doc)
{
    source = doc;
    if(xmlBuilder)delete xmlBuilder;
    xmlBuilder = new NoiseXMLBuilder;
    xmlBuilder->load(source);

    noise::utils::Image *img = xmlBuilder->getImage();

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

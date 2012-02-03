#include "previewrenderer.h"
#include "ui_previewrenderer.h"


PreviewRenderer::PreviewRenderer(TiXmlDocument *doc, QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::PreviewRenderer)
{
    ui->setupUi(this);
    source = doc;

    xmlBuilder = new NoiseXMLBuilder;
    xmlBuilder->load(source);

    QPixmap pix(textureWidth, textureHeight);
    pix.fill(Qt::black);
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

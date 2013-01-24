#ifndef PREVIEWRENDERER_H
#define PREVIEWRENDERER_H

#include <QMainWindow>
#include "tinyXml/tinyxml.h"
#include "Generation/noisexmlbuilder.h"
#include "QLinearGradient"
#include "QProgressBar"

namespace Ui {
    class PreviewRenderer;
}

class ImageRenderer : public QObject
{
    Q_OBJECT
public:
    ImageRenderer(NoiseXMLBuilder *xmlBuilder) : QObject(0), builder(xmlBuilder){};
    static void onLineReady(int row);
    void lineReadySignalSender(int row);

public slots:
    void renderImage();

signals:
//    void imageRendered(noise::utils::Image*);
    void lineReady(int);
    void finished();

private:
    static ImageRenderer *current;
    NoiseXMLBuilder *builder;
};

class PreviewRenderer : public QMainWindow
{
    Q_OBJECT

public:
    explicit PreviewRenderer(QWidget *parent = 0);
    void showTexture(TiXmlDocument *doc);
    ~PreviewRenderer();

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_action_Save_triggered();
//    void imageRendered(noise::utils::Image *image);
    void lineReady(int);

private:
    void drawImage();
    Ui::PreviewRenderer *ui;
    TiXmlDocument *source;
    int textureWidth;
    int textureHeight;
    NoiseXMLBuilder *xmlBuilder;

    bool isWorkerStarted;
    QProgressBar progressBar;
};

#endif // PREVIEWRENDERER_H

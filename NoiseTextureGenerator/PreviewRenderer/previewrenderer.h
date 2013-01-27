#ifndef PREVIEWRENDERER_H
#define PREVIEWRENDERER_H

#include <QMainWindow>
#include <QTimer>
#include "QLinearGradient"
#include "QProgressBar"
#include "clnoise.h"
#include "clnoiseoutput.h"

namespace Ui {
    class PreviewRenderer;
}

/*class ImageRenderer : public QObject
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
*/
class PreviewRenderer : public QMainWindow
{
    Q_OBJECT

public:
    explicit PreviewRenderer(QWidget *parent = 0);
    void generateTexture(CLNoise::Output *output);
    ~PreviewRenderer();

protected:
    void changeEvent(QEvent *e);

private slots:
    void generateTexture();
    void on_action_Save_triggered();
    void on_pushButton_released();

    void on_enableAutoupdate_toggled(bool checked);

private:
    void drawImage(const unsigned char *image);

    Ui::PreviewRenderer *ui;
    int textureWidth;
    int textureHeight;
    CLNoise::Output *currentOutput;
    bool isAutoupdateOn;
    QTimer timer;
};

#endif // PREVIEWRENDERER_H

#ifndef PREVIEWRENDERER_H
#define PREVIEWRENDERER_H

#include <QMainWindow>
#include "tinyXml/tinyxml.h"
#include "Generation/noisexmlbuilder.h"
#include "QLinearGradient"
#include "GradientEditor/gradienteditor.h"

namespace Ui {
    class PreviewRenderer;
}

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
    void on_refreshImage_released();

    void on_action_Save_triggered();

private:
    void drawImage();
    Ui::PreviewRenderer *ui;
    TiXmlDocument *source;
    int textureWidth;
    int textureHeight;
    NoiseXMLBuilder *xmlBuilder;
    GradientEditor *gradientEditor;

};

#endif // PREVIEWRENDERER_H

#ifndef PREVIEWRENDERER_H
#define PREVIEWRENDERER_H

#include <QMainWindow>
#include "tinyXml/tinyxml.h"
#include "Generation/noisexmlbuilder.h"

namespace Ui {
    class PreviewRenderer;
}

class PreviewRenderer : public QMainWindow
{
    Q_OBJECT

public:
    explicit PreviewRenderer(TiXmlDocument *doc, QWidget *parent = 0);
    ~PreviewRenderer();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::PreviewRenderer *ui;
    TiXmlDocument *source;
    int textureWidth;
    int textureHeight;
    NoiseXMLBuilder *xmlBuilder;
};

#endif // PREVIEWRENDERER_H

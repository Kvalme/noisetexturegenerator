#ifndef PREVIEWRENDERER_H
#define PREVIEWRENDERER_H

#include <QMainWindow>
#include "tinyXml/tinyxml.h"

namespace Ui {
    class PreviewRenderer;
}

class PreviewRenderer : public QMainWindow
{
    Q_OBJECT

public:
    explicit PreviewRenderer(int w, int h, TiXmlDocument *doc, QWidget *parent = 0);
    ~PreviewRenderer();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::PreviewRenderer *ui;
    TiXmlDocument *source;
    int textureWidth;
    int textureHeight;
};

#endif // PREVIEWRENDERER_H

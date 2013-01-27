#ifndef GRADIENTEDITOR_H
#define GRADIENTEDITOR_H

#include <QLabel>
#include <QMap>
#include <QColor>
#include "QLinearGradient"
#include <QMenu>

class GradientEditor : public QLabel
{
    Q_OBJECT

public:
    explicit GradientEditor(QWidget *parent = 0);
    ~GradientEditor();

    struct GradientPoint
    {
        float pos;
        QColor color;

        GradientPoint(float p, QColor c) : pos(p), color(c){};
        GradientPoint() : pos(0.0) {};
    };

    const QVector<GradientPoint>& getGradientPoints() const { return gradientPoints; }
    void setGradient(const QVector<GradientPoint> &gradient) { gradientPoints = gradient;}

protected:
    virtual void paintEvent ( QPaintEvent * );
    virtual void mouseDoubleClickEvent ( QMouseEvent * event );
    virtual void mousePressEvent ( QMouseEvent * event );
    virtual void mouseReleaseEvent (QMouseEvent* );
    virtual void mouseMoveEvent (QMouseEvent *event );
    virtual void contextMenuEvent ( QContextMenuEvent * event );

public slots:
    void removePoint();
    void changePointColor();
    void loadTerrainLibNoiseGradient();
    void clearGradient();

private:
    int findGradientPoint(float pos);
    void rebuildGradient();
    QLinearGradient *gradient;
    QVector<GradientPoint> gradientPoints;
    int arrowSize;

    int selectedGradientPoint;
    int menuPoint;

    QMenu *pointContextMenu;
    QMenu *mainContextMenu;
};

#endif // GRADIENTEDITOR_H

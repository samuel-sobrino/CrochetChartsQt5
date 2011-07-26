/*************************************************\
| Copyright (c) 2011 Stitch Works Software        |
| Brian C. Milco <brian@stitchworkssoftware.com>  |
\*************************************************/
#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QGraphicsView>

/**
 * The default view on the ChartScene.
 */
class ChartView : public QGraphicsView
{
    Q_OBJECT
public:
    ChartView(QWidget *parent = 0);
    ~ChartView();

    void zoomIn() { zoom(120); }
    void zoomOut() { zoom(-120); }
    //zoom takes the mouseDelta which is usually +/- 120;
    void zoom(int mouseDelta);

signals:
    void scrollBarChanged(int dx, int dy);
    
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    
private:
};
#endif //CHARTVIEW_H
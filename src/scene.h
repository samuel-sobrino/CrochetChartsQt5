/*************************************************\
| Copyright (c) 2010 Stitch Works Software        |
| Brian C. Milco <brian@stitchworkssoftware.com>  |
\*************************************************/
#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

#include "crochetcell.h"

#include <QUndoStack>
#include <QRubberBand>

#include "indicator.h"

class QKeyEvent;

class Scene : public QGraphicsScene
{
    Q_OBJECT
    friend class SaveFile;
    friend class SaveThread;
    friend class SetCellStitch;
    friend class SetCellColor;
    friend class SetCellRotation;
    friend class AddCell;
    friend class RemoveCell;
public:

    enum EditMode {
        StitchMode = 10, //place stitches on the chart.
        ColorMode = 11,       //place colors behind stitches.
        AngleMode = 14,       //adjust the angle of the
        StretchMode = 15,       //stretch the stitches.
        IndicatorMode = 16
    };

    enum ChartStyle {
        Rows = 100, // flat chart rows calc'ed based on grid.
        Rounds,     // round chart rows clac'ed with trig.
        Blank       // start w/no sts and allow anything.
    };
    
    Scene(QObject *parent = 0);
    ~Scene();

    virtual void createRow(int row, int columns, QString stitch) = 0;

    virtual void appendCell(int row, CrochetCell *c, bool fromSave = false) = 0;

    /**
     * p(x = column, y = row)
     */
    virtual void addCell(QPoint p, CrochetCell *c) = 0;
    
    int rowCount();
    int columnCount(int row);

    //if you have the position in x, y use the overload function
    CrochetCell* cell(int row, int column);
    //convert x,y to rows, columns.
    CrochetCell* cell(QPoint position);

    virtual void removeCell(CrochetCell *c) = 0;

    virtual void createChart(int rows, int cols, QString stitch, QSizeF rowSize) = 0;

    void setEditMode(EditMode mode) { mMode = mode; }
    EditMode editMode() { return mMode; }

    void setEditStitch(QString stitch) { mEditStitch = stitch; }

    void setEditFgColor(QColor color) { mEditFgColor = color; }
    void setEditBgColor(QColor color) { mEditBgColor = color; }

    QUndoStack* undoStack() { return &mUndoStack; }

    void addIndicator(Indicator *i);
    void removeIndicator(Indicator *i);

    QList<QList<CrochetCell *> > grid() { return mGrid; }
    
    QStringList modes();
    
public slots:
    
    void updateRubberBand(int dx, int dy);

private slots:
    void stitchUpdated(QString oldSt, QString newSt);
    
signals:
    void stitchChanged(QString oldSt, QString newSt);
    void colorChanged(QString oldColor, QString newColor);
    
protected:
/*
    virtual void    contextMenuEvent ( QGraphicsSceneContextMenuEvent * contextMenuEvent )
    virtual void    helpEvent ( QGraphicsSceneHelpEvent * helpEvent )
    virtual void    keyPressEvent ( QKeyEvent * keyEvent )
    virtual void    wheelEvent ( QGraphicsSceneWheelEvent * wheelEvent )
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *e);
*/
    void keyReleaseEvent(QKeyEvent *keyEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *e);
    void mousePressEvent(QGraphicsSceneMouseEvent *e);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *e);
/*
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
*/
    //find the x,y positions on the grid for a given cell;
    QPoint findGridPosition(CrochetCell *c);

    QList<Indicator*> indicators() { return mIndicators; }
    
    /**
     * WARING: This funciton should be called after the cell has been added
     * to the grid so that it calcs based on the new count of stitches.
     */
    virtual void setCellPosition(int row, int column, CrochetCell *c, int columns = 1, bool updateAnchor = false) = 0;
    
    void initDemoBackground();

protected:
    void colorModeMouseMove(QGraphicsSceneMouseEvent *e);
    void colorModeMouseRelease(QGraphicsSceneMouseEvent *e);
    
    void indicatorModeMouseMove(QGraphicsSceneMouseEvent *e);
    void indicatorModeMouseRelease(QGraphicsSceneMouseEvent *e);

    /**
     * Used in the mouse*Event()s to keep the mouse movements on the same cell.
     */
    CrochetCell *mCurCell;
    QPointF mCellStartPos;
    QPointF mLeftButtonDownPos;
    
    Indicator *mCurIndicator;
    
    /**
     * The difference between where the user clicked on the object and the (x,y) of the object.
     */
    QSizeF mDiff;
    qreal mCurCellRotation;

    QRubberBand *mRubberBand;
    QPointF mRubberBandStart;

    QMap<QGraphicsItem *, QPointF> mOldPositions;
    
    //Is the user moving an object.
    bool mMoving;

    int mRowSpacing;
    
    EditMode mMode;
    
    QString mEditStitch;
    QColor mEditFgColor;
    QColor mEditBgColor;
    
    QUndoStack mUndoStack;

    QSizeF mDefaultSize;
    
    //The grid just keeps track of the sts in each row so they can be converted to instructions.
    QList<QList<CrochetCell *> > mGrid;

    QList<Indicator*> mIndicators;
};

#endif //SCENE_H

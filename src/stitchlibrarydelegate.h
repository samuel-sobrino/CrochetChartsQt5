/*************************************************\
| Copyright (c) 2011 Stitch Works Software        |
| Brian C. Milco <brian@stitchworkssoftware.com>  |
\*************************************************/
#ifndef STITCHLIBRARYDELEGATE_H
#define STITCHLIBRARYDELEGATE_H

#include <QStyledItemDelegate>
#include <QSignalMapper>

class StitchLibraryDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    StitchLibraryDelegate(QWidget *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    
//public slots:
signals:
    void addStitchToMasterSet(int row);

private:
    QSignalMapper *mSignalMapper;
};

#endif //STITCHLIBRARYDELEGATE_H

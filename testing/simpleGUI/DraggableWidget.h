#ifndef DRAGGABLEWIDGET_H
#define DRAGGABLEWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QLabel>
#include <QPixmap>

class DraggableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DraggableWidget(const QString &imagePath, QWidget *parent = nullptr);
    void setGridPos(int x, int y);
    void setGridPos(QPoint pos);
    void setGridSize(int w, int h);
    void enableGrid(bool f = true);
    void setGridSectionSize(int dx, int dy);
    void makeGrid(int x, int y, int dx, int dy, int cx, int cy);
    auto getGrid();


protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    struct{
        int x,y,w,h,dx,dy;
        bool f;
    } grid;

    bool dragging;
    QPoint dragStartPosition;
    QPoint previousPosition;
    QLabel *imageLabel;
};

#endif // DRAGGABLEWIDGET_H

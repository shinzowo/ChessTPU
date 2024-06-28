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

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    bool dragging;
    QPoint dragStartPosition;
    QLabel *imageLabel;
};

#endif // DRAGGABLEWIDGET_H

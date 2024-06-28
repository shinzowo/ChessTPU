#include "DraggableWidget.h"
#include <QVBoxLayout>

DraggableWidget::DraggableWidget(const QString &imagePath, QWidget *parent) : QWidget(parent), dragging(false), grid({0,0,0,0,0,0,false})
{
    setMouseTracking(true);

    imageLabel = new QLabel(this);
    QPixmap pixmap(imagePath);
    imageLabel->setPixmap(pixmap);
    imageLabel->setAlignment(Qt::AlignCenter);

    setFixedSize(pixmap.size());

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(imageLabel);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);
}

void DraggableWidget::setGridPos(int x, int y)
{
    grid.x = x;
    grid.y = y;
}

void DraggableWidget::setGridPos(QPoint pos)
{
    setGridPos(pos.x(), pos.y());
}

void DraggableWidget::setGridSize(int w, int h)
{
    grid.h = h;
    grid.w = w;
}

void DraggableWidget::enableGrid(bool f)
{
    grid.f = f;
}

void DraggableWidget::setGridSectionSize(int dx, int dy)
{
    grid.dx = dx;
    grid.dy = dy;
}


void DraggableWidget::makeGrid(int x, int y, int dx, int dy, int cx, int cy)
{
    grid.x = x;
    grid.y = y;
    grid.dx = dx;
    grid.dy = dy;
    grid.w = dx * cx;
    grid.h = dy * cy;
    grid.f = true;
}

auto DraggableWidget::getGrid()
{
    return grid;
}


void DraggableWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragging = true;
        dragStartPosition = event->pos();
        previousPosition = pos();
    }
}

void DraggableWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (dragging) {
        int dx = event->pos().x() - dragStartPosition.x();
        int dy = event->pos().y() - dragStartPosition.y();
        move(pos() + QPoint(dx, dy));
    }
}

void DraggableWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragging = false;
        //if(pos().x() < grid.x || pos().x() > grid.x + grid.w || pos().y() < grid.y || pos().y() > grid.y + grid.h) return;
        int x = (pos().x() + grid.x - grid.dx/2) / grid.dx * grid.dx + grid.x;
        int y = (pos().y() + grid.y - grid.dy/2) / grid.dy * grid.dy + grid.y;
        if(x <= grid.x || y <= grid.y || x >= grid.x + grid.w || y >= grid.y + grid.h){
            move(previousPosition);
        }else{
            move(x, y);
        }
    }
}

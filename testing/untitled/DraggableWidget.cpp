#include "DraggableWidget.h"
#include <QVBoxLayout>

DraggableWidget::DraggableWidget(const QString &imagePath, QWidget *parent) : QWidget(parent), dragging(false)
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

void DraggableWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragging = true;
        dragStartPosition = event->pos();
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
    }
}

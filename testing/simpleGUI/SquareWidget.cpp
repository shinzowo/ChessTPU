#include "SquareWidget.h"


SquareWidget::SquareWidget(QWidget *parent)
    : QWidget(parent)
{

}

void SquareWidget::resizeEvent(QResizeEvent *event)
{
    QSize s = event->size();
    auto len = std::min(s.height(), s.width());
    this->resize(len, len);
    //qobject_cast<QWidget*>(this->children().back())->resize(len, len);
}

// QSize SquareWidget::sizeHint() const
// {
//     return this->size();

// }

// void SquareWidget::paintEvent(QPaintEvent *event)
// {
//     QWidget::paintEvent(event);
// }

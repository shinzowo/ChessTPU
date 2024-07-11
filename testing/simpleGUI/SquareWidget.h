#ifndef SQUAREWIDGET_H
#define SQUAREWIDGET_H

#include <QWidget>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QPainter>

class SquareWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SquareWidget(QWidget *parent = nullptr);


protected:
    void resizeEvent(QResizeEvent *event) override;
};

#endif // SQUAREWIDGET_H

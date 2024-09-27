#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class chessBoard : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit chessBoard(QObject *parent = nullptr);

private:
    void setupBoard();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
signals:
    void clicked(const QPointF &pos);
};

#endif // CHESSBOARD_H

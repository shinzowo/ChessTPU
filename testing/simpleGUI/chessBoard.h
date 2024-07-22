#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsPixmapItem>

class chessBoard : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit chessBoard(QObject *parent = nullptr);

private:
    void setupBoard();


};

#endif // CHESSBOARD_H

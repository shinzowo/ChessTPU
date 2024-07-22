#include "chessBoard.h"


chessBoard::chessBoard(QObject *parent)
    : QGraphicsScene(parent)
{
    setupBoard();
}

void chessBoard::setupBoard()
{

    QPixmap boardPixmap=QPixmap(":/img/board.png");

    if (boardPixmap.isNull()) {
        qWarning() << "Failed to load board image";
        return; // Handle the error appropriately
    }

    QGraphicsPixmapItem *board_pixmapItem = new QGraphicsPixmapItem(boardPixmap);

    //
    addItem(board_pixmapItem);





}



#include "game.h"
#include "gridpixmapitem.h"

game::game(QGraphicsView *view, QObject *parent)
    : QObject(parent), graphicsView(view)
{
    board = new chessBoard(this);
    graphicsView->setScene(board);

    //отключение полосы прокрутки

    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    graphicsView->setRenderHint(QPainter::Antialiasing);
    graphicsView->setRenderHint(QPainter::SmoothPixmapTransform);
    graphicsView->setAlignment(Qt::AlignCenter | Qt::AlignCenter);

    graphicsView->viewport()->resize(600, 600);
    graphicsView->resize(600, 600);


    graphicsView->fitInView(board->sceneRect(), Qt::KeepAspectRatio);


    QPixmap pawnPixmap=QPixmap(":/img/pieces600/wk.png");
    if (pawnPixmap.isNull()) {
        qWarning() << "Failed to load pawn image";
        return;
    }

    pawnPixmap=pawnPixmap.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    GridPixmapItem *pawn=new GridPixmapItem(pawnPixmap, 200);
    pawn->moveBy(200, 200);
    pawn->setFlag(QGraphicsItem::ItemIsMovable);
    board->addItem(pawn);

    qDebug()<<"Size of viewport:"<<graphicsView->viewport()->size();
    qDebug()<<"Size of graphicsView:"<<graphicsView->size();
    qDebug()<<"Size of scene:"<<board->sceneRect();
}






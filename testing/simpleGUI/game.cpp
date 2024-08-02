#include "game.h"
#include <QVector>
#include <QDebug>

game::game(QGraphicsView *view, QObject *parent)
    : QObject(parent), graphicsView(view)
{
    board = new chessBoard(this);
    graphicsView->setScene(board);
    setGame();


    qDebug()<<"Size of viewport:"<<graphicsView->viewport()->size();
    qDebug()<<"Size of graphicsView:"<<graphicsView->size();
    qDebug()<<"Size of scene:"<<board->sceneRect();
}

void game::setGame(){
    //отключение полосы прокрутки

    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    graphicsView->setRenderHint(QPainter::Antialiasing);
    graphicsView->setRenderHint(QPainter::SmoothPixmapTransform);
    graphicsView->setAlignment(Qt::AlignCenter | Qt::AlignCenter);

    graphicsView->viewport()->resize(600, 600);
    graphicsView->resize(600, 600);


    graphicsView->fitInView(board->sceneRect(), Qt::KeepAspectRatio);
}

void game::startGame(){
    QVector<QString>whitePieceNames={"wp", "wr", "wn", "wb", "wq", "wk"};
    QVector<QString>blackPieceNames={"bp", "br", "bn", "bb", "bq", "bk"};
    for(int i=0;i<8;i++){
        GridPixmapItem *piecePixmapItem=new GridPixmapItem(whitePieceNames[0], 200);

        piecePixmapItem->setBoardState(&boardState);
        boardState[piecePixmapItem->toChessNotaion(200*i, 1200)]=piecePixmapItem;

        piecePixmapItem->moveBy(200*i, 1200);
        piecePixmapItem->setFlag(QGraphicsItem::ItemIsMovable);
        board->addItem(piecePixmapItem);
    }

    for(int i=0;i<8;i++){

        GridPixmapItem *piecePixmapItem=new GridPixmapItem(whitePieceNames[(i+1)*(i+1<=5)+(8-i)*(i+1>5)], 200);


        piecePixmapItem->setBoardState(&boardState);
        boardState[piecePixmapItem->toChessNotaion(200*i, 1400)]=piecePixmapItem;

        piecePixmapItem->moveBy(200*i, 1400);
        piecePixmapItem->setFlag(QGraphicsItem::ItemIsMovable);
        board->addItem(piecePixmapItem);
    }


    for(int i=0;i<8;i++){
        GridPixmapItem *piecePixmapItem=new GridPixmapItem(blackPieceNames[0], 200);

        piecePixmapItem->setBoardState(&boardState);
        boardState[piecePixmapItem->toChessNotaion(200*i, 200)]=piecePixmapItem;

        piecePixmapItem->moveBy(200*i, 200);
        piecePixmapItem->setFlag(QGraphicsItem::ItemIsMovable);
        board->addItem(piecePixmapItem);
    }
    for(int i=0;i<8;i++){

        GridPixmapItem *piecePixmapItem=new GridPixmapItem(blackPieceNames[(i+1)*(i+1<=5)+(8-i)*(i+1>5)], 200);

        piecePixmapItem->setBoardState(&boardState);
        boardState[piecePixmapItem->toChessNotaion(200*i, 0)]=piecePixmapItem;

        piecePixmapItem->moveBy(200*i, 0);
        piecePixmapItem->setFlag(QGraphicsItem::ItemIsMovable);
        board->addItem(piecePixmapItem);
    }
    //qDebug()<<boardState.keys();
}





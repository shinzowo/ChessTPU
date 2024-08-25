#include "game.h"
#include <QVector>
#include <QDebug>


game::game(QGraphicsView *view, QObject *parent)
    : QObject(parent), graphicsView(view)
{
    board = new chessBoard(this);
    graphicsView->setScene(board);
    setGame();
    connect(board, &chessBoard::clicked, this, &game::onBoardClicked);// для связи с обработчиком событий mousepressevent

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

    //стандартная инициализация
    allow_edit=false;
}

void game::makeMove(QString move){
    boardState[move.left(2)]->moveToSquare(move);
}
void game::startGame(){
    QVector<QString>whitePieceNames={"wp", "wr", "wn", "wb", "wq", "wk"};
    QVector<QString>blackPieceNames={"bp", "br", "bn", "bb", "bq", "bk"};
    for(int i=0;i<8;i++){
        GridPixmapItem *piecePixmapItem=new GridPixmapItem(whitePieceNames[0], 200);

        piecePixmapItem->setLastMove(&lastMove);//связь с lastmove
        connect(piecePixmapItem, &GridPixmapItem::moveIsMade, this, &game::makeNextMove);

        piecePixmapItem->setBoardState(&boardState);
        boardState[piecePixmapItem->toChessNotaion(200*i, 1200)]=piecePixmapItem;

        piecePixmapItem->moveBy(200*i, 1200);
        piecePixmapItem->setFlag(QGraphicsItem::ItemIsMovable);
        board->addItem(piecePixmapItem);
    }

    for(int i=0;i<8;i++){

        GridPixmapItem *piecePixmapItem=new GridPixmapItem(whitePieceNames[(i+1)*(i+1<=5)+(8-i)*(i+1>5)], 200);

        piecePixmapItem->setLastMove(&lastMove);//связь с lastmove

        piecePixmapItem->setBoardState(&boardState);
        boardState[piecePixmapItem->toChessNotaion(200*i, 1400)]=piecePixmapItem;

        piecePixmapItem->moveBy(200*i, 1400);
        piecePixmapItem->setFlag(QGraphicsItem::ItemIsMovable);
        board->addItem(piecePixmapItem);
    }


    for(int i=0;i<8;i++){
        GridPixmapItem *piecePixmapItem=new GridPixmapItem(blackPieceNames[0], 200);

        piecePixmapItem->setLastMove(&lastMove);//связь с lastmove

        piecePixmapItem->setBoardState(&boardState);
        boardState[piecePixmapItem->toChessNotaion(200*i, 200)]=piecePixmapItem;

        piecePixmapItem->moveBy(200*i, 200);
        piecePixmapItem->setFlag(QGraphicsItem::ItemIsMovable);
        board->addItem(piecePixmapItem);
    }
    for(int i=0;i<8;i++){

        GridPixmapItem *piecePixmapItem=new GridPixmapItem(blackPieceNames[(i+1)*(i+1<=5)+(8-i)*(i+1>5)], 200);

        piecePixmapItem->setLastMove(&lastMove);//связь с lastmove

        piecePixmapItem->setBoardState(&boardState);
        boardState[piecePixmapItem->toChessNotaion(200*i, 0)]=piecePixmapItem;

        piecePixmapItem->moveBy(200*i, 0);
        piecePixmapItem->setFlag(QGraphicsItem::ItemIsMovable);
        board->addItem(piecePixmapItem);
    }
    //qDebug()<<boardState.keys();
}

void game::resetGame(){

    for (auto it = boardState.begin(); it != boardState.end(); ++it) {
        GridPixmapItem* piece = it.value();
        if (piece != nullptr) {
            delete piece; // Удаление объекта
        }
    }
    boardState.clear();
    return;
}

void game::setAllowEdit(bool edit){
    allow_edit=edit;
}

void game::updateToolButtonName(QString buttonName){

    tool_ButtonName=buttonName;

}

void game::onBoardClicked(const QPointF &pos){
    if(!allow_edit){
        return;
    }
    int m_gridSize=200;

    QPointF newPos=pos;
    newPos.setX(qFloor(pos.x() / m_gridSize) * m_gridSize);
    newPos.setY(qFloor(pos.y() / m_gridSize) * m_gridSize);
    bool out_of_border=newPos.x()<0 || newPos.x()>1400 || newPos.y()<0 || newPos.y()>1400;
    qDebug()<<newPos;
    QString nameSquare=GridPixmapItem::toChessNotaion(newPos.x(),newPos.y());
    if(tool_ButtonName!="moveButton" && tool_ButtonName!="deleteButton"){
        if(!boardState.contains(nameSquare) && !out_of_border){
            tool_ButtonName=tool_ButtonName.left(2);
            GridPixmapItem *piecePixmapItem=new GridPixmapItem(tool_ButtonName, m_gridSize);

            // Временно отключаем обработку событий мыши
            piecePixmapItem->setAcceptedMouseButtons(Qt::NoButton);

            piecePixmapItem->setBoardState(&boardState);
            boardState[GridPixmapItem::toChessNotaion(newPos.x(), newPos.y())]=piecePixmapItem;

            piecePixmapItem->setPos(newPos.x(), newPos.y());
            piecePixmapItem->setFlag(QGraphicsItem::ItemIsMovable);
            board->addItem(piecePixmapItem);
        }

    }
    else if(tool_ButtonName=="moveButton"){
        if(boardState.contains(nameSquare)){
            boardState[nameSquare]->setAcceptedMouseButtons(Qt::AllButtons);
        }
    }
    else if(tool_ButtonName=="deleteButton"){
        if(boardState.contains(nameSquare)){
            delete boardState.take(nameSquare);
        }
    }
}

void game::makeNextMove(){
    qDebug()<<"method makeNextMove is called";
}


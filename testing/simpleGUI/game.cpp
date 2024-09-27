#include "game.h"
#include <QVector>
#include <QRandomGenerator>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>

enum{white, black, random};
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


    allow_edit=false;
    isBotConnected=false;

}

void game::setupFEN(){
    if(game_mode=="classic" || game_mode=="three_check"){
        if(isBotWith){
            if(player_side==white){
                FEN="rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
            }
            else if (player_side==black){
                FEN="RNBKQBNR/PPPPPPPP/8/8/8/8/pppppppp/rnbkqbnr w KQkq - 0 1";
            }
        }
        else{
            FEN="rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
        }
    }
    else if(game_mode=="fischer"){
        //вызвать функцию для генерации расстанавки фишера
    }

}

void game::setupChessBoard(){
    if(game_mode.size()==0){
        qDebug()<<"game_mode is not initialised";
        return;
    }

    setupFEN();
    moves_all="";

    int board_X=0,board_Y=0;
    for(int i=0;i<FEN.size();i++){
        if(FEN[i].isDigit()){
            board_X+=FEN[i].digitValue();
        }
        else if(FEN[i]!='/' && FEN[i]!=' '){
            QString piece_name=FEN[i].toLower();
            if(FEN[i].isUpper()){
                piece_name="w"+piece_name;
            }
            else{
                piece_name="b"+piece_name;
            }
            GridPixmapItem *piecePixmapItem=new GridPixmapItem(piece_name, 200);
            piecePixmapItem->setLastMove(&lastMove);//связь с lastmove

            connect(piecePixmapItem, &GridPixmapItem::moveIsMade, this, &game::moveIsMade); //connect для вызова события при сделанном ходе

            piecePixmapItem->setBoardState(&boardState, player_side);
            boardState[piecePixmapItem->toChessNotation(200*board_X, 200*board_Y, player_side)]=piecePixmapItem;

            piecePixmapItem->moveBy(200*board_X, 200*board_Y);
            if(isBotWith && (player_side!=(piece_name[0]=='b'))){
                piecePixmapItem->setAcceptedMouseButtons(Qt::NoButton);
            }
            else{
                piecePixmapItem->setFlag(QGraphicsItem::ItemIsMovable);
            }
            board->addItem(piecePixmapItem);

            board_X++;
        }
        else if(FEN[i]=='/'){
            board_X=0;
            board_Y++;
        }
        else if(FEN[i]==' '){
            break;
        }
    }

}
void game::makeMove(QString move){
    if(move.size()!=4){
        qDebug()<<"move is incorrect in makeMove";
    }
    boardState[move.left(2)]->moveToSquare(move);
    moves_all=moves_all+" "+lastMove; // добавляем этот ход в историю
}
void game::startTwoPlayersGame(QString game_mode){
    this->game_mode=game_mode;
    this->player_side=white;
    isBotWith=false;
    setupChessBoard();
}

void game::startBotGames(QString game_mode, int player_side, int game_difficulty, QString path){
    if(player_side==random){
        player_side=QRandomGenerator::system()->bounded(2);
    }
    this->game_mode=game_mode;
    this->player_side=player_side;
    this->game_difficulty=game_difficulty;
    isBotWith=true;
    setupChessBoard();



    if(path.isEmpty()){
        QMessageBox::warning(nullptr, "Ошибка", "Путь до шахматного бота пустой");
    }
    if(!isBotConnected){
        chessBot=new ChessBot(this);
        connect(chessBot, &ChessBot::outputReceived, this, &game::onEngineOutputReceived);
        chessBot->startEngine(path);
        chessBot->sendCommand("uci");
        isBotConnected=true;
    }
    chessBot->sendCommand("setoption name Skill Level value "+QString::number(game_difficulty*2));
    if(game_mode=="three_check"){
        chessBot->sendCommand("setoption name UCI_Variant value threecheck");
    }
    chessBot->sendCommand("ucinewgame");
    if(player_side==black){
        chessBot->sendCommand("position startpos");                                         //изменить на fen когда доделаем
        chessBot->sendCommand("go movetime 100");
    }
}

void game::resetGame(){
    for (auto it = boardState.begin(); it != boardState.end(); ++it) {
        GridPixmapItem* piece = it.value();
        //qDebug()<<"piece:"<<it.key();
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

void game::setAcceptedButtons(){
    for (auto it = boardState.begin(); it != boardState.end(); ++it) {
        GridPixmapItem* piece = it.value();
        qDebug()<<"piece:"<<it.key();
        piece->setAcceptedMouseButtons(Qt::AllButtons);
    }
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
    QString nameSquare=GridPixmapItem::toChessNotation(newPos.x(),newPos.y());
    if(tool_ButtonName!="moveButton" && tool_ButtonName!="deleteButton"){
        if(!out_of_border){
            tool_ButtonName=tool_ButtonName.left(2);
            GridPixmapItem *piecePixmapItem=new GridPixmapItem(tool_ButtonName, m_gridSize);
            piecePixmapItem->setLastMove(&lastMove);//связь с lastmove

            connect(piecePixmapItem, &GridPixmapItem::moveIsMade, this, &game::moveIsMade); //connect для вызова события при сделанном ходе

            // Временно отключаем обработку событий мыши
            piecePixmapItem->setAcceptedMouseButtons(Qt::NoButton);

            piecePixmapItem->setBoardState(&boardState, white);

            if(boardState.contains(nameSquare)){
                delete boardState.take(nameSquare);
            }
            boardState[nameSquare]=piecePixmapItem;

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

void game::moveIsMade(){
    //qDebug()<<boardState.keys();
    //qDebug()<<"method makeNextMove is called";

    moves_all=moves_all+" "+lastMove; //добавляем ход, который сделал игрок в историю
    if(!isBotWith){
        return;
    }
    chessBot->sendCommand("position startpos moves "+moves_all);                        //изменить на fen когда доделаем
    chessBot->sendCommand("go movetime 100");

}
void game::onEngineOutputReceived(const QString &output)
{
    qDebug() << "Engine output:" << output;
    if(output.contains("bestmove")){
        bestmove=output.mid(output.indexOf("bestmove")+9, 4);
        qDebug()<<"bestmove: "<<bestmove;
        makeMove(bestmove);
    }
    // Обработка вывода движка
}




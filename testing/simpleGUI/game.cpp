#include "game.h"

#include <QRandomGenerator>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <algorithm>
#include <sstream>

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
QString game::generateFisherChessFEN() {
    QVector<QChar> pieces = {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'};
        bool valid = false;

        while (!valid) {
            // Перемешиваем фигуры случайным образом
            std::shuffle(pieces.begin(), pieces.end(), *QRandomGenerator::global());

            // Проверяем условия:
            // 1. Король должен находиться между двумя ладьями для корректной рокировки
            int kingIndex = pieces.indexOf('K');
            int rook1Index = pieces.indexOf('R');
            int rook2Index = pieces.lastIndexOf('R');
            bool kingBetweenRooks = (rook1Index < kingIndex && kingIndex < rook2Index);

            // 2. Слоны должны находиться на полях разного цвета
            int bishop1Index = pieces.indexOf('B');
            int bishop2Index = pieces.lastIndexOf('B');
            bool bishopsOnDifferentColors = (bishop1Index % 2 != bishop2Index % 2);

            // Если оба условия выполнены, позиция считается валидной
            valid = kingBetweenRooks && bishopsOnDifferentColors;
        }

        // Формируем строку FEN для стартовой позиции
        QString fen;

        // Добавляем черные фигуры сверху
        for (const QChar &piece : pieces) {
            fen.append(piece.toLower());  // Черные фигуры в FEN записываются маленькими буквами
        }
        fen.append("/pppppppp/8/8/8/8/PPPPPPPP/");

        // Добавляем белые фигуры снизу
        for (const QChar &piece : pieces) {
            fen.append(piece);  // Белые фигуры в FEN записываются большими буквами
        }

        fen.append(" w KQkq - 0 1");  // Остальные части FEN (белый ходит первым, право рокировки, нет взятия на проходе)

        return fen;
}

void game::setupFEN(){
    if(game_mode=="classic" || game_mode=="three_check"){
        if(isBotWith){
            if(player_side==white){
                FEN="rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
            }
            else if (player_side==black){
                FEN="rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
            }
        }
        else{
            FEN="rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
        }
    }
    else if(game_mode=="fischer"){
        FEN=generateFisherChessFEN();
        qDebug()<<FEN;
    }

}

void game::setupChessBoard(){
    if(game_mode.size()==0){
        qDebug()<<"game_mode is not initialised";
        return;
    }

    setupFEN();

    GameLogic=new Chess::Game(FEN.toStdString());

    moves_all="";
    int board_X=0,board_Y=7;
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

            QString square = QString(QChar('a' + board_X));
            square=square+QString::number(board_Y+1);


            GridPixmapItem *piecePixmapItem=new GridPixmapItem(piece_name, 200);
            piecePixmapItem->setLastMove(&lastMove);//связь с lastmove

            connect(piecePixmapItem, &GridPixmapItem::moveIsMade, this, &game::moveIsMade); //connect для вызова события при сделанном ходе

            piecePixmapItem->setBoardState(&boardState, player_side);
            boardState[square]=piecePixmapItem;

            QPointF position = piecePixmapItem->toIntNotation(square, player_side);
            piecePixmapItem->moveBy(position.x(), position.y());
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
            board_Y--;
        }
        else if(FEN[i]==' '){
            break;
        }
    }
    //qDebug()<<boardState.keys();
}
void game::makeMove(QString move){
    if(move.size()!=4){
        qDebug()<<"move is incorrect in makeMove";
    }
    boardState[move.left(2)]->moveToSquare(move);
    moves_all=moves_all+" "+lastMove; // добавляем этот ход в историю
    FEN=updateFEN(FEN, lastMove);
    qDebug()<<FEN;
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
        chessBot->sendCommand("position fen "+FEN);                                         //изменить на fen когда доделаем
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
    FEN=updateFEN(FEN, lastMove);
    qDebug()<<FEN;
    if(!isBotWith){
        return;
    }
    chessBot->sendCommand("position fen " + FEN + " moves " + moves_all);                        //изменить на fen когда доделаем
    chessBot->sendCommand("go movetime 100");

}
void game::onEngineOutputReceived(const QString &output)
{
    //qDebug() << "Engine output:" << output;
    if(output.contains("bestmove")){
        bestmove=output.mid(output.indexOf("bestmove")+9, 4);
        qDebug()<<"bestmove: "<<bestmove;
        makeMove(bestmove);
    }
    // Обработка вывода движка
}

QStringList game::split(const QString &str, const QChar &delimiter) {
    return str.split(delimiter);
}
QString game::updateFEN(QString &fen, const QString &move) {
    // 1. Разделяем FEN строку на части
    QStringList fenParts = split(fen, ' ');
    QString piecePlacement = fenParts[0]; // расположение фигур
    QString activeColor = fenParts[1]; // активный цвет (w/b)
    QString castlingAvailability = fenParts[2]; // возможность рокировки
    QString enPassantTarget = fenParts[3]; // возможность взятия на проходе
    int halfmoveClock = fenParts[4].toInt(); // количество полуходов
    int fullmoveNumber = fenParts[5].toInt(); // номер полного хода

    // 2. Применение хода к расположению фигур
    // Пример хода: "e2e4" (перемещение с e2 на e4)
    int fromFile = move[0].toLatin1() - 'a'; // столбец начальной клетки
    int fromRank = 8 - (move[1].toLatin1() - '0'); // строка начальной клетки
    int toFile = move[2].toLatin1() - 'a'; // столбец конечной клетки
    int toRank = 8 - (move[3].toLatin1() - '0'); // строка конечной клетки

    // Разделяем строку расположения фигур по '/'. Каждая строка описывает ряд доски.
    QStringList rows = split(piecePlacement, '/');

    // Преобразуем FEN строку в реальную шахматную доску.
    QStringList board(8);
    for (int i = 0; i < 8; ++i) {
        QString row = rows[i];
        QString expandedRow;
        for (QChar c : row) {
            if (c.isDigit()) {
                expandedRow += QString(c.toLatin1() - '0', '1'); // '1' обозначает пустую клетку
            } else {
                expandedRow += c;
            }
        }
        board[i] = expandedRow;
    }

    // 3. Изменение доски: перемещение фигуры
    QChar piece = board[fromRank][fromFile];
    board[fromRank][fromFile] = '1'; // исходная клетка становится пустой
    board[toRank][toFile] = piece; // фигура перемещается на конечную клетку

    // 4. Преобразование доски обратно в FEN формат
    for (int i = 0; i < 8; ++i) {
        QString compressedRow;
        int emptyCount = 0;
        for (QChar c : board[i]) {
            if (c == '1') {
                emptyCount++;
            } else {
                if (emptyCount > 0) {
                    compressedRow += QString::number(emptyCount);
                    emptyCount = 0;
                }
                compressedRow += c;
            }
        }
        if (emptyCount > 0) {
            compressedRow += QString::number(emptyCount);
        }
        rows[i] = compressedRow;
    }

    // Собираем новую строку расположения фигур
    QString newPiecePlacement = rows.join('/');

    // 5. Обновляем активную сторону
    activeColor = (activeColor == "w") ? "b" : "w";

    // 6. Устанавливаем возможность рокировки (упрощенно, если это важно, можно доработать)
    // (Если была сделана рокировка или король/ладья двигались, обновляем флаг)

    // 7. Обновляем возможность взятия на проходе (при ходе пешкой на 2 клетки)
    if (piece == 'P' || piece == 'p') {
        if (fromRank == 6 && toRank == 4) {
            enPassantTarget = move.mid(0, 2);
        } else if (fromRank == 1 && toRank == 3) {
            enPassantTarget = move.mid(0, 2);
        } else {
            enPassantTarget = "-";
        }
    } else {
        enPassantTarget = "-";
    }

    // 8. Обновляем количество полуходов (если был ход пешкой или взятие фигуры, сбрасываем счетчик)
    if (piece == 'P' || piece == 'p' || board[toRank][toFile] != '1') {
        halfmoveClock = 0;
    } else {
        halfmoveClock++;
    }

    // 9. Увеличиваем номер полного хода, если ход черных
    if (activeColor == "w") {
        fullmoveNumber++;
    }

    // Собираем новую FEN строку
    QString newFEN = newPiecePlacement + " " + activeColor + " " + castlingAvailability + " " + enPassantTarget + " " + QString::number(halfmoveClock) + " " + QString::number(fullmoveNumber);

    return newFEN;
}

QString game::getFEN(){
    return FEN;
}





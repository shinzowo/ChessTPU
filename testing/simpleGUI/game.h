#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QGraphicsView>
#include <QMap>
#include <QString>
#include "chessBoard.h"
#include "gridpixmapitem.h"
#include "chessbot.h"

class game : public QObject
{
    Q_OBJECT
public:
    explicit game(QGraphicsView *view, QObject *parent);
    void startTwoPlayersGame(QString game_mode);
    void startBotGames(QString game_mode, int player_side, int game_difficulty, QString path);
    void resetGame();
    void saveGame();
    void setAllowEdit(bool edit);
    void updateToolButtonName(QString buttonName);
    void setAcceptedButtons();
private slots:
    void onBoardClicked(const QPointF &pos);
    void moveIsMade();
    void onEngineOutputReceived(const QString &output);
private:
    ChessBot *chessBot;
    int player_side;
    int game_difficulty;
    QString game_mode;
    QString FEN;
    QString moves_all;

    bool isBotWith;
    bool isBotConnected;
    QString bestmove;

    bool allow_edit;
    QString lastMove;
    QString tool_ButtonName;

    chessBoard* board;
    QMap<QString, GridPixmapItem*>boardState;
    QGraphicsView* graphicsView;

    void setGame();
    void setupFEN();
    void setupChessBoard();
    void makeMove(QString move);

signals:

};

#endif // GAME_H

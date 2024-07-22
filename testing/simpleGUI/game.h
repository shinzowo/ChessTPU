#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QGraphicsView>
#include "chessBoard.h"
#include <QDebug>  // For qWarning()

class game : public QObject
{
    Q_OBJECT
public:
    explicit game(QGraphicsView *view, QObject *parent);
    void startGame();
    void resetGame();
    void saveGame();
private slots:

private:
    int game_difficulty;
    int game_mode;
    chessBoard* board;
    QGraphicsView* graphicsView;

signals:

};

#endif // GAME_H

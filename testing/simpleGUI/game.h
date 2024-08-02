#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QGraphicsView>
#include "chessBoard.h"
#include "gridpixmapitem.h"
#include <QMap>

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
    QMap<QString, GridPixmapItem*>boardState;
    QGraphicsView* graphicsView;

    void setGame();


signals:

};

#endif // GAME_H

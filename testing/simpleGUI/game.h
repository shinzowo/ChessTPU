#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QGraphicsView>
#include "chessBoard.h"
#include "gridpixmapitem.h"
#include <QMap>
#include <QString>

class game : public QObject
{
    Q_OBJECT
public:
    explicit game(QGraphicsView *view, QObject *parent);
    void startGame();
    void resetGame();
    void saveGame();
    void setAllowEdit(bool edit);
    void updateToolButtonName(QString buttonName);
private slots:
    void onBoardClicked(const QPointF &pos);
    void makeNextMove();
private:
    int game_difficulty;
    int game_mode;
    bool allow_edit;
    QString lastMove;
    QString tool_ButtonName;

    chessBoard* board;
    QMap<QString, GridPixmapItem*>boardState;
    QGraphicsView* graphicsView;

    void setGame();
    void makeMove(QString move);


signals:

};

#endif // GAME_H

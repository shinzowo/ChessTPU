#ifndef GRIDPIXMAPITEM_H
#define GRIDPIXMAPITEM_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainterPath>
#include <QVariant>
#include <QString>
#include "ChessLogic.h"




class GridPixmapItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    int getGridSize();
    GridPixmapItem(const QString pieceName, int gridSize, QGraphicsItem *parent = nullptr);
    void setBoardState(QMap<QString, GridPixmapItem*>* state, int player_side);
    static QString toChessNotation(int x_sqr, int y_sqr, int player_side=0);
    static QPointF toIntNotation(QString square, int player_side=0);
    void setLastMove(QString *lastmove);
    void moveToSquare(QString toSquare);
protected:

    QPainterPath shape() const override;



    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
private:
    Chess::Piece *piece;

    QPixmap piecePixmap;

    int m_gridSize;
    int side;
    int player_side;

    QPointF previousPosition;

    QString previousSquare;
    QString newSquare;
    QString *move;


    QMap<QString, GridPixmapItem *>*boardState;

    qreal originalZvalue;

    void updateBoardState();
signals:
    void moveIsMade();

};

#endif // GRIDPIXMAPITEM_H

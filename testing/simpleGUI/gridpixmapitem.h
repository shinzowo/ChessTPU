#ifndef GRIDPIXMAPITEM_H
#define GRIDPIXMAPITEM_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainterPath>
#include <QVariant>
#include <QString>



enum{white, black};
class GridPixmapItem : public QGraphicsPixmapItem
{
public:
    GridPixmapItem(const QString pieceName, int gridSize, QGraphicsItem *parent = nullptr);
    void setBoardState(QMap<QString, GridPixmapItem*>* state);
    QString toChessNotaion(int x_sqr, int y_sqr);
    QPointF toIntNotaion(QString square);
protected:

    QPainterPath shape() const override;



    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
private:


    QPixmap piecePixmap;

    int m_gridSize;
    int side;

    QPointF previousPosition;

    QString previousSquare;
    QString newSquare;

    QMap<QString, GridPixmapItem *>*boardState;

    qreal originalZvalue;

    void updateBoardState();

};

#endif // GRIDPIXMAPITEM_H

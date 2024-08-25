#ifndef GRIDPIXMAPITEM_H
#define GRIDPIXMAPITEM_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainterPath>
#include <QVariant>
#include <QString>



enum{white, black};
class GridPixmapItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    int getGridSize();
    GridPixmapItem(const QString pieceName, int gridSize, QGraphicsItem *parent = nullptr);
    void setBoardState(QMap<QString, GridPixmapItem*>* state);
    static QString toChessNotaion(int x_sqr, int y_sqr);
    static QPointF toIntNotaion(QString square);
    void setLastMove(QString *lastmove);
    void moveToSquare(QString toSquare);
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
    QString *move;


    QMap<QString, GridPixmapItem *>*boardState;

    qreal originalZvalue;

    void updateBoardState();
signals:
    void moveIsMade();

};

#endif // GRIDPIXMAPITEM_H

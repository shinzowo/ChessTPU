#ifndef GRIDPIXMAPITEM_H
#define GRIDPIXMAPITEM_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QVariant>

class GridPixmapItem : public QGraphicsPixmapItem
{
public:
    GridPixmapItem(const QPixmap &pixmap, int gridSize, QGraphicsItem *parent = nullptr)
        : QGraphicsPixmapItem(pixmap, parent), m_gridSize(gridSize) {}
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
private:
    int m_gridSize;
};

#endif // GRIDPIXMAPITEM_H

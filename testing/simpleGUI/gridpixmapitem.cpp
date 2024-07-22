#include "gridpixmapitem.h"


QVariant GridPixmapItem::itemChange(GraphicsItemChange change, const QVariant &value){
       if (change == ItemPositionChange && scene()) {
           QPointF newPos = value.toPointF();
           newPos.setX(qRound(newPos.x() / m_gridSize)* m_gridSize);
           newPos.setY(qRound(newPos.y() / m_gridSize) * m_gridSize);

           return newPos;
    }

    return QGraphicsPixmapItem::itemChange(change, value);
}
void GridPixmapItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if (event->button() == Qt::LeftButton) {
                QPointF newPos = pos();
                newPos.setX(qRound(newPos.x() / m_gridSize) * m_gridSize);
                newPos.setY(qRound(newPos.y() / m_gridSize) * m_gridSize);
                setPos(newPos);
            }
            QGraphicsPixmapItem::mouseReleaseEvent(event);
    }

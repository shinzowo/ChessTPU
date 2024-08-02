#include "gridpixmapitem.h"
#include <cmath>
#include<QDebug>


GridPixmapItem::GridPixmapItem(const QString pieceName, int gridSize, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent), m_gridSize(gridSize), originalZvalue(0) {
    QPixmap piecePixmap=QPixmap(":/img/pieces600/"+pieceName+".png");
    if (piecePixmap.isNull()) {
        qWarning() << "Failed to load pawn image";
        return;
    }
    if(pieceName[0]=='w'){
        side=white;
    }
    else{
        side=black;
    }
    piecePixmap=piecePixmap.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    setPixmap(piecePixmap);
    setTransformationMode(Qt::SmoothTransformation);
    previousPosition=pos();


}

QPainterPath GridPixmapItem::shape() const{
    QPainterPath path;
    path.addRect(boundingRect().adjusted(-m_gridSize, -m_gridSize, m_gridSize, m_gridSize)); // Расширяем область захвата
    return path;
}

void GridPixmapItem::setBoardState(QMap<QString, GridPixmapItem *> *state){
    boardState=state;
}
void GridPixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        setZValue(100);//слои наложение иерархия
        previousPosition=pos();
        previousSquare=toChessNotaion(pos().x(), pos().y());

        QPointF cursorPos=event->scenePos();
        cursorPos.setX(cursorPos.x()-m_gridSize/2);
        cursorPos.setY(cursorPos.y()-m_gridSize/2);
        setPos(cursorPos);



        QGraphicsPixmapItem::mousePressEvent(event);
    }
}

void GridPixmapItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if (event->button() == Qt::LeftButton) {
                setZValue(originalZvalue);//слои наложение иерархия
                QPointF newPos = pos();
                QPointF newRoundPos;
                QString square;

                newRoundPos.setX(qRound(newPos.x() / m_gridSize) * m_gridSize);
                newRoundPos.setY(qRound(newPos.y() / m_gridSize) * m_gridSize);

                square=toChessNotaion(newRoundPos.x(), newRoundPos.y());

                bool IsOutBorders=newPos.x()<-100 || newPos.x()>1500 || newPos.y()<-100 || newPos.y()>1500;
                if( IsOutBorders || boardState->contains(square) && (*boardState)[square]->side==this->side){

                    setPos(previousPosition);


                }
                else{
                    if(boardState->contains(square) && (*boardState)[square]->side!=this->side){
                        delete (*boardState)[square];
                    }
                    newPos.setX(newRoundPos.x());
                    newPos.setY(newRoundPos.y());
                    newSquare=square;
                    setPos(newPos);

                    updateBoardState();

                }


            }
            QGraphicsPixmapItem::mouseReleaseEvent(event);
    }
QString GridPixmapItem::toChessNotaion(int x_sqr, int y_sqr){
    QString square="";
    switch(x_sqr/200){
        case 0: square+="a"; break;
        case 1: square+="b"; break;
        case 2: square+="c";break;
        case 3: square+="d";break;
        case 4: square+="e";break;
        case 5: square+="f";break;
        case 6: square+="g";break;
        case 7: square+="h";break;
    }
    square+=QString::number(abs((y_sqr/200)-8));
    return square;
}
QPointF GridPixmapItem::toIntNotaion(QString square){
    QPointF pos_piece;
    switch(square[0].toLatin1()){
        case 'a': pos_piece.setX(0); break;
        case 'b': pos_piece.setX(1*200); break;
        case 'c': pos_piece.setX(2*200);break;
        case 'd': pos_piece.setX(3*200);break;
        case 'e': pos_piece.setX(4*200);break;
        case 'f': pos_piece.setX(5*200);break;
        case 'g': pos_piece.setX(6*200);break;
        case 'h': pos_piece.setX(7*200);break;
    }
    pos_piece.setY((square[1].digitValue()*(-1)+8)*200);
    return pos_piece;
}

void GridPixmapItem::updateBoardState(){
    boardState->remove(previousSquare);
    (*boardState)[newSquare]=this;

}

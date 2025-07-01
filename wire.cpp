#include "wire.h"

#define Radius 4

QPen Wire::WirePen(Qt::red, 2);
QBrush Wire::WireBrush(Qt::red);

Wire::Wire(QPointF start):StartPos(Utils::GetNearestGridPoint(start)) {
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable |QGraphicsItem::ItemHasNoContents);
    //Create Items Associated with each wire
    HLine = new QGraphicsLineItem(this);
    VLine = new QGraphicsLineItem(this);
    HLine->setPen(WirePen);
    VLine->setPen(WirePen);
    StartNode = new QGraphicsEllipseItem(-Radius / 2, -Radius / 2, Radius, Radius, this);
    EndNode = new QGraphicsEllipseItem(-Radius / 2, -Radius / 2, Radius, Radius, this);
    StartNode->setBrush(WireBrush);
    StartNode->setPos(StartPos);
    EndNode->setBrush(WireBrush);
    EndNode->setPos(StartPos);
}
void Wire::AdjustEndPoint(QPointF end){
    EndPos = Utils::GetNearestGridPoint(end);
    double Hdist = EndPos.x() - StartPos.x();
    double Vdist = EndPos.y() - StartPos.y();
    qDebug() << "ah";
    HLine->setLine(0, 0, Hdist, 0);
    VLine->setLine(0, 0, 0, Vdist);
    if(Hdist >= Vdist) {
        HLine->setPos(StartPos);
        VLine->setPos(StartPos.x() + Hdist, StartPos.y());
    }else{
        VLine->setPos(StartPos);
        HLine->setPos(StartPos.x(), StartPos.y() + Vdist);
    }
    EndNode->setPos(EndPos);
}

void Wire::GetWireConnection(QPointF& s, QPointF& e){
    s = StartPos;
    e = EndPos;
}

QRectF Wire::boundingRect() const
{
    return childrenBoundingRect();
}

void Wire::paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*)
{

}

void Wire::mousePressEvent(QGraphicsSceneMouseEvent* event){
    if(event->button() == Qt::RightButton){
        QMenu menu;
        menu.addAction(QIcon(QDir::currentPath() + "\\remove.png"), "Delete", [this](){this->scene()->removeItem(this); delete this;});
        menu.exec(event->screenPos());
    }
}

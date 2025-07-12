#include "wire.h"
#include "graphicsview.h"
#define Radius 4

QPen Wire::WirePen(Qt::red, 2);
QBrush Wire::WireBrush(Qt::red);

Wire::Wire(GraphicsView* View, QPointF start):StartPos(Utils::GetNearestGridPoint(start)){
    view = View;
    Component = new IVSItem;
    Component->SetValue(0, true);
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable |QGraphicsItem::ItemHasNoContents);
    //Create Items Associated with each wire
    Line = new QGraphicsPathItem(this);
    Line->setPen(WirePen);
    StartNode = new QGraphicsEllipseItem(-Radius / 2, -Radius / 2, Radius, Radius, this);
    EndNode = new QGraphicsEllipseItem(-Radius / 2, -Radius / 2, Radius, Radius, this);
    StartNode->setBrush(WireBrush);
    StartNode->setPos(StartPos);
    EndNode->setBrush(WireBrush);
    EndNode->setPos(StartPos);
}

bool Wire::isValidPath(QList<QPointF>& Points){
    for(int i = 0; i < Points.size() - 1; i++){
        QGraphicsLineItem TestLine(QLineF(Points[i], Points[i+1]), this);
        TestLine.setPen(Qt::NoPen);
        TestLine.setZValue(-1);
        TestLine.setVisible(false);
        QList<QGraphicsItem*> Collisions= TestLine.scene()->collidingItems(&TestLine);
        for(int i = 0; i < Collisions.size(); i++)
            if(dynamic_cast<GraphicsItem*>(Collisions[i])) return false;
    }
    return true;
}

void Wire::AdjustEndPoint(QVector<QVector<Vertex>> & Grid, QPointF End){
    EndPos = Utils::GetNearestGridPoint(End);
    EndNode->setPos(EndPos);
    QList<QPointF> Points = Utils::ShortestPath(Grid, Utils::GetGridID(StartPos), Utils::GetGridID(EndPos));
    QPainterPath Path;
    if(!Points.empty()){
        Path.moveTo(Points[0]);
        for(int i = 1; i < Points.size(); i++) Path.lineTo(Points[i]);
        Line->setPath(Path);
    }
}

IComponent* Wire::GetComponent(){ return Component; }

void Wire::FixWireNodes(QVector<QVector<Vertex>> & Grid){
    int SGID = Utils::GetGridID(StartPos), EGID = Utils::GetGridID(EndPos);
    Component->SetNodes(&Grid[SGID/31][SGID%31], &Grid[EGID/31][EGID%31]);
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
        menu.addAction(QIcon(QDir::currentPath() + "\\remove.png"), "Delete", [this](){view->RemoveItemFromNetlist(Component);this->scene()->removeItem(this); delete this;});
        menu.exec(event->screenPos());
    }
}

#include "wire.h"

#define Radius 4

QPen Wire::WirePen(Qt::red);
QBrush Wire::WireBrush(Qt::red);

Wire::Wire(QGraphicsScene* scene, QPointF start):StartPos(Utils::GetNearestGridPoint(start)) {
    WirePen.setWidth(2);
    //Create Items Associated with each wire
    HLine = new QGraphicsLineItem();
    VLine = new QGraphicsLineItem();
    HLine->setPen(WirePen);
    VLine->setPen(WirePen);
    StartNode = new QGraphicsEllipseItem(-Radius / 2, -Radius / 2, Radius, Radius);
    EndNode = new QGraphicsEllipseItem(-Radius / 2, -Radius / 2, Radius, Radius);
    StartNode->setBrush(WireBrush);
    StartNode->setPos(StartPos);
    EndNode->setBrush(WireBrush);

    scene->addItem(HLine);
    scene->addItem(VLine);
    scene->addItem(StartNode);
    scene->addItem(EndNode);

}
void Wire::AdjustEndPoint(QPointF end){
    EndPos = Utils::GetNearestGridPoint(end);
    double Hdist = EndPos.x() - StartPos.x();
    double Vdist = EndPos.y() - StartPos.y();
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

Wire::~Wire(){
    HLine->scene()->removeItem(HLine);
    VLine->scene()->removeItem(VLine);
    StartNode->scene()->removeItem(StartNode);
    EndNode->scene()->removeItem(EndNode);

    delete HLine;
    delete VLine;
    delete StartNode;
    delete EndNode;
}

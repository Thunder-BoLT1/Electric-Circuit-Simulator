#include "graphicsview.h"

//Vertex::Vertex(int node){ NodeId = node; } Ignored for now

GraphicsView::GraphicsView(QWidget * widget): QGraphicsView(widget) {
    MovingItem = nullptr;
    this->setMouseTracking(true);
}

void GraphicsView::mousePressEvent(QMouseEvent* event){
    if(MovingItem){
        NetList.push_back(MovingItem);
        MovingItem->setOpacity(1);
        MovingItem = nullptr;
    }
    QGraphicsView::mousePressEvent(event);
}

void GraphicsView::mouseMoveEvent(QMouseEvent* event){
    if(MovingItem){
        QPointF NewPos((int(event->pos().x()) / 30) * 30, (int(event->pos().y()) / 30)* 30);
        if(int(event->pos().x() - NewPos.x()) > 15) NewPos.setX(NewPos.x() + 30);
        if(int(event->pos().y() - NewPos.y()) > 15) NewPos.setY(NewPos.y() + 30);
        // If Invalid Position (Out of the Grid) Return to The initial Press Position
        if(NewPos.x() > 0 && NewPos.x() < 900 && NewPos.y() > 0 && NewPos.y() < 600) MovingItem->setPos(NewPos);
    }
    QGraphicsView::mouseMoveEvent(event);
}

void GraphicsView::SetMovingItem(GraphicsItem* Item){
    if(MovingItem) {
        this->scene()->removeItem(MovingItem);
        delete MovingItem;
    }
    MovingItem = (Item)? Item : nullptr;
}

GraphicsItem* GraphicsView::GetMovingItem(){ return MovingItem; }

void GraphicsView::HandleDuplicate(GraphicsItem* Item){
    AddToGV(new GraphicsItem(*Item));
}

void GraphicsView::AddToGV(GraphicsItem* Item){
    if(Item){
        connect(Item, &GraphicsItem::duplicateRequest, this, &GraphicsView::HandleDuplicate);
        Item->setOpacity(0.5); //For Ghost effect will be changed later to 1
        Item->setPos(150, 210);
        this->scene()->addItem(Item);
        SetMovingItem(Item);
    }
}

void GraphicsView::BuildGraph(){
    for(int i = 0; i < NetList.size(); i++){
        int GridId = NetList[i]->pos().x() / 30 + (NetList[i]->pos().y() / 30) * 31 ;
        int SnodeGId = -1 , EnodeGId = -1;
        switch(abs(int(NetList[i]->rotation()))){
        case 0:
            SnodeGId = GridId - 1;
            EnodeGId = GridId + 1;
            break;
        case 180:
            SnodeGId = GridId + 1;
            EnodeGId = GridId - 1;
            break;
        case 90:
            SnodeGId = GridId + 31;
            EnodeGId = GridId - 31;
            break;
        case 270:
            SnodeGId = GridId - 31;
            EnodeGId = GridId + 31;
            break;
        }
        Graph[SnodeGId].append({EnodeGId, NetList[i]});
        qDebug() << SnodeGId << EnodeGId;
    }
}

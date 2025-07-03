#include "graphicsview.h"

//Vertex::Vertex(int node){ NodeId = node; } Ignored for now

GraphicsView::GraphicsView(QWidget * widget): QGraphicsView(widget) {
    MovingItem = nullptr;
    CurrWire = nullptr;
    Grid = QVector<QVector<Vertex>>(21);
    for(int i = 0; i < 21; i++) {
        Grid[i].reserve(31);
        for(int j = 0; j < 31; j++) Grid[i].append(Vertex());
    }
    this->setMouseTracking(true);
}

void GraphicsView::mousePressEvent(QMouseEvent* event){
    if(MovingItem){
        if(event->button() == Qt::LeftButton){
            NetList.push_back(MovingItem);
            AddItemToGrid(MovingItem);
            MovingItem->setOpacity(1);
        }else{
            MovingItem->scene()->removeItem(MovingItem);
            delete MovingItem;
        }
        MovingItem = nullptr;
    }else if(CurrWire){
        if(event->button() == Qt::LeftButton){
            Wires.append(CurrWire);
        }else{
            CurrWire->scene()->removeItem(CurrWire);
            delete CurrWire;
        }
        CurrWire = nullptr;
    }
    QGraphicsView::mousePressEvent(event);
}

void GraphicsView::mouseMoveEvent(QMouseEvent* event){
    if(MovingItem){
        QPointF NewPos = Utils::GetNearestGridPoint(event->pos());
        // If Invalid Position (Out of the Grid) Return to The initial Press Position
        if(NewPos.x() > 0 && NewPos.x() < 900 && NewPos.y() > 0 && NewPos.y() < 600) MovingItem->setPos(NewPos);
    }else if(CurrWire){
        ResetGrid();
        CurrWire->AdjustEndPoint(Grid, event->pos());
    }
    QGraphicsView::mouseMoveEvent(event);
}

void GraphicsView::mouseDoubleClickEvent(QMouseEvent *event){
    //Check if there is a previous item
    QGraphicsItem* ItemClicked = this->scene()->itemAt(mapToScene((event->pos())), transform());
    if(!dynamic_cast<GraphicsItem*>(ItemClicked)){
        CurrWire = new Wire(event->pos());
        this->scene()->addItem(CurrWire);
    }
    QGraphicsView::mouseDoubleClickEvent(event);
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
        //Remove any Wire was being added
        if(CurrWire){
            delete CurrWire;
            CurrWire = nullptr;
        }
        connect(Item, &GraphicsItem::duplicateRequest, this, &GraphicsView::HandleDuplicate);
        Item->setOpacity(0.5); //For Ghost effect will be changed later to 1
        Item->setPos(150, 210);
        this->scene()->addItem(Item);
        SetMovingItem(Item);
    }
}

void GraphicsView::BuildGraph(){
    for(int i = 0; i < NetList.size(); i++){
        int GridId = Utils::GetGridID(NetList[i]->pos()) ;
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
        Graph[SnodeGId].append({EnodeGId, NetList[i]->GetComponent()});
    }
    for(int i = 0; i < Wires.size(); i++){
        int SnodeGId = -1 ,  EnodeGId = -1;
        Wires[i]->GetWireConnection(SnodeGId, EnodeGId);
        IVSItem *NewWire = new IVSItem;
        NewWire->SetValue(0, true);
        Graph[SnodeGId].append({EnodeGId, NewWire});
    }
}

void GraphicsView::RemoveItemFromGrid(GraphicsItem *Item){
    Grid[int(Item->pos().y())/30][int(Item->pos().x())/30].hasItem = false;;
}

void GraphicsView::AddItemToGrid(GraphicsItem *Item){
    Grid[int(Item->pos().y())/30][int(Item->pos().x())/30].hasItem = true;
}

void GraphicsView::ResetGrid(){
    for(int i = 0; i < Grid.size(); i++)
        for(int j = 0; j < Grid[i].size(); j++) {
            Grid[i][j].G_cost = INT_MAX;
            Grid[i][j].H_cost = INT_MAX;
            Grid[i][j].isVisited = 0;
            Grid[i][j].Parent = nullptr;
        }
}

void GraphicsView::ResetGV(){
    this->scene()->clear();
    NetList.clear();
    Wires.clear();
    Graph.clear();
    ResetGrid();
    for(int i = 0; i < Grid.size(); i++) for(int j = 0; j < Grid[i].size(); j++) Grid[i][j].hasItem = false;
}

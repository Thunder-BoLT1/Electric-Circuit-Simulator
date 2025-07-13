#include "graphicsview.h"

//Vertex::Vertex(int node){ NodeId = node; } Ignored for now

GraphicsView::GraphicsView(QWidget * widget): QGraphicsView(widget) {
    MovingItem = nullptr;
    CurrWire = nullptr;
    currMode = Design;
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
            NetList.push_back(MovingItem->GetComponent());
            AddItemToGrid(MovingItem);
            MovingItem->setOpacity(1);
        }else{
            MovingItem->scene()->removeItem(MovingItem);
            delete MovingItem;
        }
        MovingItem = nullptr;
    }else if(CurrWire){
        if(event->button() == Qt::LeftButton){
            NetList.push_back(CurrWire->GetComponent());
            CurrWire->FixWireNodes(Grid);
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
        CurrWire = new Wire(this, event->pos());
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

void GraphicsView::SetElementNodes(GraphicsItem* item){
    int GridId = Utils::GetGridID(item->pos()) ;
    int SnodeGId = -1 , EnodeGId = -1, SCnodeGId = -1, ECnodeGId = -1;
    Vertex* StartNode = nullptr, *EndNode = nullptr, *SCNode = nullptr, *ECNode = nullptr;
    switch(abs(int(item->rotation()))){
    case 0:
        SnodeGId = GridId - 1;
        EnodeGId = GridId + 1;
        SCnodeGId = SnodeGId + 62;
        ECnodeGId = EnodeGId + 62;
        break;
    case 180:
        SnodeGId = GridId + 1;
        EnodeGId = GridId - 1;
        SCnodeGId = SnodeGId - 62;
        ECnodeGId = EnodeGId - 62;
        break;
    case 90:
        SnodeGId = GridId - 31;
        EnodeGId = GridId + 31;
        SCnodeGId = SnodeGId - 2;
        ECnodeGId = EnodeGId - 2;
        break;
    case 270:
        SnodeGId = GridId + 31;
        EnodeGId = GridId - 31;
        SCnodeGId = SnodeGId + 2;
        ECnodeGId = EnodeGId + 2;
        break;
    }
    StartNode = &Grid[SnodeGId/31][SnodeGId%31];
    EndNode = &Grid[EnodeGId/31][EnodeGId%31];
    SCNode = &Grid[SCnodeGId/31][SCnodeGId%31];
    ECNode = &Grid[ECnodeGId/31][ECnodeGId%31];
    DComponent* Component = dynamic_cast<DComponent*>(item->GetComponent());
    if(Component){
        Component->SetNodes(SCNode, ECNode);
        Component->SetCtrNodes(StartNode, EndNode);
    }else
        item->GetComponent()->SetNodes(StartNode, EndNode);
}

int GraphicsView::NumberNodes(){
    int UniqueNodes = 0, n = NetList.size(), m = Wires.size();
    ResetGrid();
    for(int i = 0; i < n; i++){
        Vertex* sVertex = nullptr, *eVertex = nullptr;
        NetList[i]->GetNodes(sVertex, eVertex);
        if(sVertex->NodeID == -1) sVertex->NodeID = UniqueNodes++;
        if(eVertex->NodeID == -1) eVertex->NodeID = UniqueNodes++;
    }
    for(int i = 0; i < m; i++){
        Vertex* sVertex = nullptr, *eVertex = nullptr;
        Wires[i]->GetComponent()->GetNodes(sVertex, eVertex);
        if(sVertex->NodeID == -1) sVertex->NodeID = UniqueNodes++;
        if(eVertex->NodeID == -1) eVertex->NodeID = UniqueNodes++;
    }
    //FOR DEBUGGING PUPOSES ONLY WILL BE REMOVED AFTER
    qDebug() << "Unique nodes : " << n;
    for(int i = 0; i < n; i++){
        Vertex* sVertex = nullptr, *eVertex = nullptr;
        NetList[i]->GetNodes(sVertex, eVertex);
        qDebug() << sVertex->NodeID << "  " << eVertex->NodeID;
    }
    return UniqueNodes;
}

void GraphicsView::RunSimulation(){
    int n = NumberNodes();
    if(n <= 0) return;
    Eigen::MatrixXd GMatrix = Eigen::MatrixXd::Zero(n-1, n-1);
    Eigen::MatrixXd CMatrix = Eigen::MatrixXd::Zero(n-1, 1);

    BuildMatrix(GMatrix, CMatrix);

    qDebug() << " G/Matrix :";
    for(int i = 0; i < GMatrix.rows(); i++){
        for(int j = 0; j < GMatrix.rows(); j++) qDebug() << GMatrix(i, j);
        qDebug() << CMatrix(i,0) << "\n";
    }

    Eigen::MatrixXd Result = GMatrix.colPivHouseholderQr().solve(CMatrix);
    UpdateComponents(Result, n-1);
    for(int i = 0; i < Result.rows(); i++) qDebug() << Result(i,0);

}

void GraphicsView::BuildMatrix(Eigen::MatrixXd &GMatrix, Eigen::MatrixXd &CMatrix){
    int n = NetList.size(), m = Wires.size();
    for(int i = 0; i < n; i++)
        NetList[i]->WriteToMatrix(GMatrix, CMatrix);

    for(int i = 0; i < m; i++)
        Wires[i]->GetComponent()->WriteToMatrix(GMatrix, CMatrix);
}

void GraphicsView::UpdateComponents(Eigen::MatrixXd &Result, int newRowIndex){
    int n = NetList.size(), m = Wires.size();
    for(int i = 0; i < n; i++)
        NetList[i]->ReadFromMatrix(Result, newRowIndex);

    for(int i = 0; i < m; i++)
        Wires[i]->GetComponent()->ReadFromMatrix(Result, newRowIndex);

}


void GraphicsView::RemoveItemFromNetlist(IComponent *Item){
    for(int i = 0; i < NetList.size(); i++)
        if(NetList[i] == Item){
            NetList.remove(i);
            return;
        }
}

void GraphicsView::RemoveItemFromGrid(GraphicsItem *Item){
    int row = Item->pos().y()/30, col = Item->pos().x()/30;
    Grid[row][col].hasItem = false;
    DComponent *Component = dynamic_cast<DComponent*>(Item->GetComponent());
    if(Component){
        switch(abs(int(Item->rotation()))){
        case 0:
            Grid[row+1][col].hasItem = false;
            Grid[row+2][col].hasItem = false;
            break;
        case 180:
            Grid[row-1][col].hasItem = false;
            Grid[row-2][col].hasItem = false;
            break;
        case 90:
            Grid[row][col-1].hasItem = false;
            Grid[row][col-2].hasItem = false;
            break;
        case 270:
            Grid[row][col+1].hasItem = false;
            Grid[row][col+2].hasItem = false;
            break;
        }
    }
}

void GraphicsView::AddItemToGrid(GraphicsItem *Item){
    int row = Item->pos().y()/30, col = Item->pos().x()/30;
    Grid[row][col].hasItem = true;
    DComponent *Component = dynamic_cast<DComponent*>(Item->GetComponent());
    if(Component){
        switch(abs(int(Item->rotation()))){
        case 0:
            Grid[row+1][col].hasItem = true;
            Grid[row+2][col].hasItem = true;
            break;
        case 180:
            Grid[row-1][col].hasItem = true;
            Grid[row-2][col].hasItem = true;
            break;
        case 90:
            Grid[row][col-1].hasItem = true;
            Grid[row][col-2].hasItem = true;
            break;
        case 270:
            Grid[row][col+1].hasItem = true;
            Grid[row][col+2].hasItem = true;
            break;
        }
    }
    SetElementNodes(Item);
}

void GraphicsView::ResetGrid(){
    for(int i = 0; i < Grid.size(); i++)
        for(int j = 0; j < Grid[i].size(); j++) {
            Grid[i][j].G_cost = INT_MAX;
            Grid[i][j].H_cost = INT_MAX;
            Grid[i][j].isVisited = 0;
            Grid[i][j].Parent = nullptr;
            Grid[i][j].NodeID = -1;
        }
}

Mode GraphicsView::GetMode() { return currMode; }
void GraphicsView::ToggleMode(){currMode = (currMode == Design)? Run: Design;}

void GraphicsView::ResetGV(){
    this->scene()->clear();
    NetList.clear();
    Graph.clear();
    ResetGrid();
    for(int i = 0; i < Grid.size(); i++) for(int j = 0; j < Grid[i].size(); j++) Grid[i][j].hasItem = false;
}

#include "GraphicsItem.h"
#include "graphicsview.h"

QPointF GraphicsItem::PressPos, GraphicsItem::Offset;

GraphicsItem::GraphicsItem(QPixmap Image, Components Type, GraphicsView* view):QGraphicsPixmapItem(Image){
    //Set Important Attributes
    this->setFlag(ItemIsMovable);
    this->setOffset(-30, -30);  //To Rotate the Item Aroud it's Center Not Around the TopLeft Corner
    this->setRotation(0);
    this->setZValue(1);
    this->setPos(30, 30);
    switch(Type){
    case IVS:
        Component = new IVSItem;
        break;
    case ICS:
        Component = new ICSItem;
        break;
    case RES:
        Component = new RESItem;
        break;
    case VCVS:
        Component = new VCVSItem;
        break;
    case VCCS:
        Component = new VCCSItem;
        break;
    case CCVS:
        Component = new CCVSItem;
        break;
    case CCCS:
        Component = new CCCSItem;
        break;
    }
    View = view;
}

GraphicsItem::GraphicsItem(GraphicsItem& other){
    Component = other.Component->CreateCopy();
    this->View = other.View;
    this->setPixmap(other.pixmap());
    this->setOffset(other.offset());
    this->setFlag(ItemIsMovable);
    this->setRotation(other.rotation());
    this->setZValue(other.zValue());
    this->setPos(other.pos());
}

void GraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent* event){
    if(event->buttons() & Qt::LeftButton){
        PressPos = this->scenePos();    // Save Position of the Item For Later
        Offset = event->scenePos();     // Get Postion of the Click
        View->RemoveItemFromGrid(this);
    }
    else if(event->button() == Qt::RightButton){
        QMenu menu;
        menu.addAction(QIcon(QDir::currentPath() + "\\rotateRight.png"),"Rotate ClockWise", [this](){View->RemoveItemFromGrid(this); this->setRotation(int(this->rotation() + 90) % 360); View->AddItemToGrid(this);});
        menu.addAction(QIcon(QDir::currentPath() + "\\rotateLeft.png"), "Rotate Anti-ClockWise", [this](){View->RemoveItemFromGrid(this); this->setRotation(int(this->rotation() + 270) % 360); View->AddItemToGrid(this);});
        menu.addAction(QIcon(QDir::currentPath() + "\\duplicate.png"), "Duplicate", [this]() {emit duplicateRequest(this);});
        menu.addAction(QIcon(QDir::currentPath() + "\\remove.png"), "Delete", [this](){ View->RemoveItemFromNetlist(this->GetComponent()); View->RemoveItemFromGrid(this); this->scene()->removeItem(this); delete this;});
        menu.exec(event->screenPos());
    }
    QGraphicsPixmapItem::mousePressEvent(event);
}
void GraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event){
    if(event->buttons() & Qt::LeftButton){
        this->setPos(PressPos + Offset - event->scenePos()); // offset - event->scenePos = Displacment Vector --> DisplacmentVector + PressPos = New Position
    }
    QGraphicsPixmapItem::mouseMoveEvent(event);
}
void GraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event){
    if(event->button() == Qt::LeftButton){
        QPointF NewPos = Utils::GetNearestGridPoint(event->scenePos());
        if(!Utils::isCorrectPos(NewPos)) NewPos = PressPos; // If Invalid Position (Out of the Grid) Return to The initial Press Position
        this->setPos(NewPos);
        View->AddItemToGrid(this);
    }
    QGraphicsPixmapItem::mouseReleaseEvent(event);
}

void GraphicsItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    //Open DIALOGUE FOR USER INPUTS
    if(View->GetMode() == Design){
        IndependentInputDialog Input(Component->GetName(), Component->GetValue());
        if(Input.exec() == QDialog::Accepted){
            GetComponent()->SetName(Input.Get_Name());
            bool Operation =  GetComponent()->SetValue(Input.Get_Value());
            if(!Operation){
                QMessageBox msg;
                msg.setWindowTitle("Error");
                msg.setText("Invalid Component Value");
                msg.setIcon(QMessageBox::Warning);
                msg.exec();
            }
        }
    }else{
        ResultsDialog Result(Component);
        Result.exec();
    }
    QGraphicsItem::mouseDoubleClickEvent(event);
}

IComponent * GraphicsItem::GetComponent() { return Component; }

GraphicsItem::~GraphicsItem(){
    delete Component;
}

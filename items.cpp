#include "items.h"

int IVSItem::Count = 0;
IVSItem::IVSItem(){
    Count++;
    SetName("IVS" + QString::number(Count));
    SetValue(10);
}
//Override Pure Virtual Function For IVS
void IVSItem::WriteToMatrix(Eigen::MatrixXd &GMatrix, Eigen::MatrixXd &CMatrix){
    //Add new Row and Column of zeros to the end it's also the New Row/Column Index :D
    int oldSize = GMatrix.rows();
    GMatrix.conservativeResize(oldSize + 1, oldSize + 1);
    CMatrix.conservativeResize(oldSize + 1, Eigen::NoChange);
    GMatrix.row(oldSize).setZero();
    GMatrix.col(oldSize).setZero();
    CMatrix.row(oldSize).setZero();

    Vertex* StartVertex = nullptr, *EndVertex = nullptr;
    GetNodes(StartVertex, EndVertex);
    int StartNode = StartVertex->NodeID , EndNode = EndVertex->NodeID;
    double Value = GetValue();

    if (EndNode) {
        GMatrix(oldSize, EndNode - 1) = 1;
        GMatrix(EndNode - 1, oldSize) = 1;
    }
    if (StartNode) {
        GMatrix(oldSize, StartNode - 1) = -1;
        GMatrix(StartNode - 1, oldSize) = -1;
    }
    CMatrix(oldSize, 0) = Value;

}
void IVSItem::ReadFromMatrix(Eigen::MatrixXd &Result, int& newRowIndex){
    Vertex* StartVertex = nullptr, *EndVertex = nullptr;
    GetNodes(StartVertex, EndVertex);
    int StartNode = StartVertex->NodeID , EndNode = EndVertex->NodeID;

    double VD = 0, I = Result(newRowIndex++, 0);
    if (StartNode && EndNode) VD = Result(EndNode - 1, 0) - Result(StartNode - 1, 0);
    else if (StartNode) VD = -Result(StartNode - 1, 0);
    else VD = Result(EndNode - 1, 0);
    if(abs(VD) < 1e-5) VD = 0;
    if(abs(I) < 1e-5) I = 0;

    SetCurrent(I);
    SetVoltage(VD);

}

IComponent* IVSItem::CreateCopy(){
    Count++;
    IComponent* newComponent =  new IVSItem(*this);
    newComponent->SetName("IVS" + QString::number(Count));
    return newComponent;
}

int ICSItem::Count = 0;
ICSItem::ICSItem(){
    Count++;
    SetName("ICS" + QString::number(Count));
    SetValue(10);
}
//Override Pure Virtual Function For ICS
void ICSItem::WriteToMatrix(Eigen::MatrixXd &GMatrix, Eigen::MatrixXd &CMatrix){
    (void)GMatrix;  // This to Igonre Compilers Warning of unused parameters
    Vertex* StartVertex = nullptr, *EndVertex = nullptr;
    GetNodes(StartVertex, EndVertex);
    int StartNode = StartVertex->NodeID , EndNode = EndVertex->NodeID;
    double Value = GetValue();
    if (EndNode) CMatrix(EndNode - 1, 0) += Value;
    if (StartNode) CMatrix(StartNode - 1, 0) -= Value;
}
void ICSItem::ReadFromMatrix(Eigen::MatrixXd &Result, int& newRowIndex){
    (void) newRowIndex;
    Vertex* StartVertex = nullptr, *EndVertex = nullptr;
    GetNodes(StartVertex, EndVertex);
    int StartNode = StartVertex->NodeID , EndNode = EndVertex->NodeID;

    double VD = 0, I = GetValue();
    if (StartNode && EndNode) VD = Result(EndNode - 1, 0) - Result(StartNode - 1, 0);
    else if (StartNode) VD = -Result(StartNode - 1, 0);
    else VD = Result(EndNode - 1, 0);
    if(abs(VD) < 1e-5) VD = 0;
    if(abs(I) < 1e-5) I = 0;

    SetCurrent(I);
    SetVoltage(VD);
}

IComponent* ICSItem::CreateCopy(){
    Count++;
    IComponent* newComponent =  new ICSItem(*this);
    newComponent->SetName("ICS" + QString::number(Count));
    return newComponent;
}


int RESItem::Count = 0;
RESItem::RESItem(){
    Count++;
    SetName("RES" + QString::number(Count));
    SetValue(10);
}
//Override Pure Virtual Function For RES
void RESItem::WriteToMatrix(Eigen::MatrixXd &GMatrix, Eigen::MatrixXd &CMatrix){
    (void)CMatrix; // This to Igonre Compilers Warning of unused parameters
    Vertex* StartVertex = nullptr, *EndVertex = nullptr;
    GetNodes(StartVertex, EndVertex);
    int StartNode = StartVertex->NodeID , EndNode = EndVertex->NodeID;
    double Value = GetValue();
    if (StartNode) GMatrix(StartNode - 1, StartNode - 1) += 1 / Value;
    if (EndNode) GMatrix(EndNode - 1, EndNode - 1) += 1 / Value;
    if (StartNode && EndNode) {
        GMatrix(StartNode - 1, EndNode - 1) -= 1 / Value;
        GMatrix(EndNode - 1, StartNode - 1) -= 1 / Value;
    }
}

void RESItem::ReadFromMatrix(Eigen::MatrixXd &Result, int& newRowIndex){
    (void)newRowIndex;
    Vertex* StartVertex = nullptr, *EndVertex = nullptr;
    GetNodes(StartVertex, EndVertex);
    int StartNode = StartVertex->NodeID , EndNode = EndVertex->NodeID;

    double VD = 0;
    if (StartNode && EndNode) VD = Result(StartNode - 1, 0) - Result(EndNode - 1, 0) ;
    else if (EndNode) VD = -Result(EndNode - 1, 0);
    else VD = Result(StartNode - 1, 0);
    if(abs(VD) < 1e-5) VD = 0;
    double I = VD/GetValue();
    if(abs(I) < 1e-5) I = 0;

    SetCurrent(I);
    SetVoltage(VD);

}

IComponent* RESItem::CreateCopy(){
    Count++;
    IComponent* newComponent =  new RESItem(*this);
    newComponent->SetName("RES" + QString::number(Count));
    return newComponent;
}

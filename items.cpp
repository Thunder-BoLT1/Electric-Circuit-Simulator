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

int VCVSItem::Count = 0;
VCVSItem::VCVSItem(){
    Count++;
    SetName("VCVS" + QString::number(Count));
    SetValue(10);
}
//Override Pure Virtual Function For RES
void VCVSItem::WriteToMatrix(Eigen::MatrixXd &GMatrix, Eigen::MatrixXd &CMatrix){
    //Add new Row and Column of zeros to the end it's also the New Row/Column Index :D
    int oldSize = GMatrix.rows();
    GMatrix.conservativeResize(oldSize + 1, oldSize + 1);
    CMatrix.conservativeResize(oldSize + 1, Eigen::NoChange);
    GMatrix.row(oldSize).setZero();
    GMatrix.col(oldSize).setZero();
    CMatrix.row(oldSize).setZero();

    Vertex* StartVertex = nullptr, *EndVertex = nullptr, *StartCtrVertex = nullptr, *EndCtrVertex = nullptr;
    GetNodes(StartVertex, EndVertex);
    GetCtrNodes(StartCtrVertex, EndCtrVertex);
    int StartNode = StartVertex->NodeID , EndNode = EndVertex->NodeID, StartCtrNode = StartCtrVertex->NodeID, EndCtrNode = EndCtrVertex->NodeID;
    double Value = GetValue();

    if (StartNode) {
        GMatrix(StartNode - 1, oldSize) += -1;
        GMatrix(oldSize, StartNode - 1) += -1;
    }
    if (EndNode) {
        GMatrix(EndNode - 1, oldSize) += 1;
        GMatrix(oldSize, EndNode - 1) += 1;
    }
    if (StartCtrNode) GMatrix(oldSize, StartCtrNode - 1) += Value;
    if (EndCtrNode) GMatrix(oldSize, EndCtrNode - 1) += -Value;

}

void VCVSItem::ReadFromMatrix(Eigen::MatrixXd &Result, int& newRowIndex){
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

IComponent* VCVSItem::CreateCopy(){
    Count++;
    IComponent* newComponent =  new VCVSItem(*this);
    newComponent->SetName("VCVS" + QString::number(Count));
    return newComponent;
}

int VCCSItem::Count = 0;
VCCSItem::VCCSItem(){
    Count++;
    SetName("VCCS" + QString::number(Count));
    SetValue(10);
}
//Override Pure Virtual Function For VCCS
void VCCSItem::WriteToMatrix(Eigen::MatrixXd &GMatrix, Eigen::MatrixXd &CMatrix){
    (void)CMatrix; // This to Igonre Compilers Warning of unused parameters
    Vertex* StartVertex = nullptr, *EndVertex = nullptr, *StartCtrVertex = nullptr, *EndCtrVertex = nullptr;
    GetNodes(StartVertex, EndVertex);
    GetCtrNodes(StartCtrVertex, EndCtrVertex);
    int StartNode = StartVertex->NodeID , EndNode = EndVertex->NodeID, StartCtrNode = StartCtrVertex->NodeID, EndCtrNode = EndCtrVertex->NodeID;
    double Value = GetValue();
    qDebug() <<"VCCS" << StartNode << EndNode << StartCtrNode << EndCtrNode;
    if (StartCtrNode) {
        if (StartNode) GMatrix(StartNode - 1, StartCtrNode - 1) += Value;
        if (EndNode) GMatrix(EndNode - 1, StartCtrNode - 1) -= Value;
    }if (EndCtrNode) {
        if (StartNode) GMatrix(StartNode - 1,  EndCtrNode - 1) -= Value;
        if (EndNode)  GMatrix(EndNode - 1,  EndCtrNode - 1) += Value;
    }
}

void VCCSItem::ReadFromMatrix(Eigen::MatrixXd &Result, int& newRowIndex){
    (void)newRowIndex;
    Vertex* StartVertex = nullptr, *EndVertex = nullptr, *StartCtrVertex = nullptr, *EndCtrVertex = nullptr;
    GetNodes(StartVertex, EndVertex);
    GetCtrNodes(StartCtrVertex, EndCtrVertex);
    int StartNode = StartVertex->NodeID , EndNode = EndVertex->NodeID, StartCtrNode = StartCtrVertex->NodeID, EndCtrNode = EndCtrVertex->NodeID;

    double VD = 0;
    if (StartNode && EndNode) VD = Result(StartNode - 1, 0) - Result(EndNode - 1, 0) ;
    else if (EndNode) VD = -Result(EndNode - 1, 0);
    else VD = Result(StartNode - 1, 0);
    if(abs(VD) < 1e-5) VD = 0;

    double I = GetValue() * (Result(EndCtrNode-1, 0) - Result(StartCtrNode-1, 0));
    if(abs(I) < 1e-5) I = 0;

    SetVoltage(VD);
    SetCurrent(I);
}

IComponent* VCCSItem::CreateCopy(){
    Count++;
    IComponent* newComponent =  new VCCSItem(*this);
    newComponent->SetName("VCCS" + QString::number(Count));
    return newComponent;
}

int CCVSItem::Count = 0;
CCVSItem::CCVSItem(){
    Count++;
    SetName("CCVS" + QString::number(Count));
    SetValue(10);
}
//Override Pure Virtual Function For RES
void CCVSItem::WriteToMatrix(Eigen::MatrixXd &GMatrix, Eigen::MatrixXd &CMatrix){
    //Add 2 new Rows and Columns of zeros to the end it's also the First New Row/Column Index :D
    int oldSize = GMatrix.rows();
    GMatrix.conservativeResize(oldSize + 2, oldSize + 2);
    CMatrix.conservativeResize(oldSize + 2, Eigen::NoChange);
    GMatrix.row(oldSize).setZero();
    GMatrix.row(oldSize+1).setZero();
    GMatrix.col(oldSize).setZero();
    GMatrix.col(oldSize+1).setZero();
    CMatrix.row(oldSize).setZero();
    CMatrix.row(oldSize+1).setZero();

    Vertex* StartVertex = nullptr, *EndVertex = nullptr, *StartCtrVertex = nullptr, *EndCtrVertex = nullptr;
    GetNodes(StartVertex, EndVertex);
    GetCtrNodes(StartCtrVertex, EndCtrVertex);
    int StartNode = StartVertex->NodeID , EndNode = EndVertex->NodeID, StartCtrNode = StartCtrVertex->NodeID, EndCtrNode = EndCtrVertex->NodeID;
    double Value = GetValue();

    if(StartNode){
        GMatrix(StartNode - 1, oldSize + 1) = -1;
        GMatrix(oldSize + 1, StartNode - 1) = -1;
    }
    if(EndNode){
        GMatrix(EndNode - 1, oldSize + 1) = 1;
        GMatrix(oldSize + 1, EndNode - 1) = 1;
    }
    if(EndCtrNode) {
        GMatrix(EndCtrNode - 1, oldSize) = -1;
        GMatrix(oldSize, EndCtrNode - 1) = -1;
    }
    if(StartCtrNode){
        GMatrix(StartCtrNode - 1, oldSize) = 1;
        GMatrix(oldSize, StartCtrNode - 1) = 1;
    }
    GMatrix(oldSize + 1, oldSize) = -Value;
}

void CCVSItem::ReadFromMatrix(Eigen::MatrixXd &Result, int& newRowIndex){
    Vertex* StartVertex = nullptr, *EndVertex = nullptr, *StartCtrVertex = nullptr, *EndCtrVertex = nullptr;
    GetNodes(StartVertex, EndVertex);
    GetCtrNodes(StartCtrVertex, EndCtrVertex);
    int StartNode = StartVertex->NodeID , EndNode = EndVertex->NodeID, StartCtrNode = StartCtrVertex->NodeID, EndCtrNode = EndCtrVertex->NodeID;

    double VD = 0;
    if (StartNode && EndNode) VD = Result(StartNode - 1, 0) - Result(EndNode - 1, 0) ;
    else if (EndNode) VD = -Result(EndNode - 1, 0);
    else VD = Result(StartNode - 1, 0);
    if(abs(VD) < 1e-5) VD = 0;

    double I = GetValue() * Result(newRowIndex + 1, 0);
    newRowIndex += 2;
    if(abs(I) < 1e-5) I = 0;

    SetVoltage(VD);
    SetCurrent(I);
}

IComponent* CCVSItem::CreateCopy(){
    Count++;
    IComponent* newComponent =  new CCVSItem(*this);
    newComponent->SetName("CCVS" + QString::number(Count));
    return newComponent;
}


int CCCSItem::Count = 0;
CCCSItem::CCCSItem(){
    Count++;
    SetName("CCCS" + QString::number(Count));
    SetValue(10);
}
//Override Pure Virtual Function For RES
void CCCSItem::WriteToMatrix(Eigen::MatrixXd &GMatrix, Eigen::MatrixXd &CMatrix){
    (void)CMatrix; // This to Igonre Compilers Warning of unused parameters

    //Add new Row and Column of zeros to the end it's also the New Row/Column Index :D
    int oldSize = GMatrix.rows();
    GMatrix.conservativeResize(oldSize + 1, oldSize + 1);
    CMatrix.conservativeResize(oldSize + 1, Eigen::NoChange);
    GMatrix.row(oldSize).setZero();
    GMatrix.col(oldSize).setZero();
    CMatrix.row(oldSize).setZero();

    Vertex* StartVertex = nullptr, *EndVertex = nullptr, *StartCtrVertex = nullptr, *EndCtrVertex = nullptr;
    GetNodes(StartVertex, EndVertex);
    GetCtrNodes(StartCtrVertex, EndCtrVertex);
    int StartNode = StartVertex->NodeID , EndNode = EndVertex->NodeID, StartCtrNode = StartCtrVertex->NodeID, EndCtrNode = EndCtrVertex->NodeID;
    double Value = GetValue();

    if(StartNode) GMatrix(StartNode - 1, oldSize) = Value;
    if(EndNode)   GMatrix(EndNode - 1, oldSize) = -Value;
    if(EndCtrNode){
        GMatrix(EndCtrNode - 1, oldSize) = -1;
        GMatrix(oldSize, EndCtrNode - 1) = -1;
    }
    if(StartCtrNode){
        GMatrix(StartCtrNode - 1, oldSize) = 1;
        GMatrix(oldSize, StartCtrNode - 1) = 1;
    }
}

void CCCSItem::ReadFromMatrix(Eigen::MatrixXd &Result, int& newRowIndex){
    Vertex* StartVertex = nullptr, *EndVertex = nullptr, *StartCtrVertex = nullptr, *EndCtrVertex = nullptr;
    GetNodes(StartVertex, EndVertex);
    GetCtrNodes(StartCtrVertex, EndCtrVertex);
    int StartNode = StartVertex->NodeID , EndNode = EndVertex->NodeID, StartCtrNode = StartCtrVertex->NodeID, EndCtrNode = EndCtrVertex->NodeID;

    double VD = 0;
    if (StartNode && EndNode) VD = Result(StartNode - 1, 0) - Result(EndNode - 1, 0) ;
    else if (EndNode) VD = -Result(EndNode - 1, 0);
    else VD = Result(StartNode - 1, 0);
    if(abs(VD) < 1e-5) VD = 0;

    double I = GetValue() * Result(newRowIndex++, 0);
    if(abs(I) < 1e-5) I = 0;

    SetVoltage(VD);
    SetCurrent(I);
}

IComponent* CCCSItem::CreateCopy(){
    Count++;
    IComponent* newComponent =  new CCCSItem(*this);
    newComponent->SetName("CCCS" + QString::number(Count));
    return newComponent;
}

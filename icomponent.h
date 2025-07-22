#ifndef ICOMPONENT_H
#define ICOMPONENT_H
#include <QString>
#include "vertex.h"
#include <Eigen/Dense>

class IComponent
{
    QString _Name;
    Vertex *_StartNode,* _EndNode;
    double _Value, _Current, _Voltage;
    bool _Added;
public:
    IComponent();
    virtual ~IComponent();
    // setter functions
    bool SetName(QString);
    bool SetNodes(Vertex*, Vertex*);
    bool SetValue(double, bool Wire = false);
    void SetCurrent(double);
    void SetVoltage(double);
    //getter functions
    QString GetName();
    void GetNodes(Vertex*&, Vertex*&);
    double GetValue();
    double GetCurrent();
    double GetVoltage();
    //VirtualFunctions
    virtual void WriteToMatrix(Eigen::MatrixXd &, Eigen::MatrixXd &) = 0;
    virtual void ReadFromMatrix(Eigen::MatrixXd &, int&) = 0;
    virtual IComponent* CreateCopy() = 0;
};

#endif // ICOMPONENT_H

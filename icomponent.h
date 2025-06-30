#ifndef ICOMPONENT_H
#define ICOMPONENT_H
#include <QString>

class IComponent
{
    QString _Name;
    int _StartNode, _EndNode;
    double _Value, _Current, _Voltage;
public:
    IComponent();
    virtual ~IComponent();
    // setter functions
    bool SetName(QString);
    bool SetNodes(int, int);
    bool SetValue(double);
    void SetCurrent(double);
    void SetVoltage(double);
    //getter functions
    QString GetName();
    void GetNodes(int&, int&);
    double GetValue();
    double GetCurrent();
    double GetVoltage();
    //VirtualFunctions
    virtual void WriteToMatrix() = 0;
    virtual void ReadFromMatrix() = 0;
    virtual IComponent* CreateCopy() = 0;
};

#endif // ICOMPONENT_H

#include "icomponent.h"

IComponent::IComponent() {}

bool IComponent::SetName(QString name){
    if(name.isEmpty() || !name[0].isLetter()) return false;
    _Name = name;
    return true;
}
bool IComponent::SetNodes(int S, int E){
    if( S < 0 || E < 0 || S <= E) return false;
    _StartNode = S;
    _EndNode = E;
    return true;
}
bool IComponent::SetValue(double val, bool Wire){
    if(Wire) {
        _Value = 0;
        return true;
    }
    if(val <= 0) return false;
    _Value = val;
    return true;
}
void IComponent::SetCurrent(double curr){
    _Current = curr;
}
void IComponent::SetVoltage(double vol){
    _Voltage = vol;
}
//getter functions
QString IComponent::GetName(){ return _Name; }
void IComponent::GetNodes(int& S, int& E){ S = _StartNode; E = _EndNode; }
double IComponent::GetValue() { return _Value; }
double IComponent::GetCurrent() { return _Current; }
double IComponent::GetVoltage() { return _Voltage; }

IComponent::~IComponent(){

}

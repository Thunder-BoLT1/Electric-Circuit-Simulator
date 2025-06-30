#ifndef DCOMPONENT_H
#define DCOMPONENT_H
#include "IComponent.h"

class DComponent: public IComponent
{
    int _StartCtrNode, _EndCtrNode;
public:
    DComponent();
    //Setters
    bool SetCtrNodes(int &S, int &E){
        if(S < 0 || E < 0 || S == E) return false;
        _StartCtrNode = S;
        _EndCtrNode = E;
        return true;
    }
    //Getters
    void GetCtrNodes(int &S, int &E) { S = _StartCtrNode; E = _EndCtrNode; }
};

#endif // DCOMPONENT_H

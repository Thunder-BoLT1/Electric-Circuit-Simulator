#ifndef DCOMPONENT_H
#define DCOMPONENT_H
#include "IComponent.h"

class DComponent: public IComponent
{
    Vertex* _StartCtrNode, *_EndCtrNode;
public:
    DComponent();
    //Setters
    void SetCtrNodes(Vertex *S, Vertex* E);
    //Getters
    void GetCtrNodes(Vertex *&S, Vertex*&E);
};

#endif // DCOMPONENT_H

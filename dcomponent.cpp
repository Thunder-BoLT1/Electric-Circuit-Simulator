#include "dcomponent.h"

DComponent::DComponent() {}

void DComponent::SetCtrNodes(Vertex* S, Vertex* E){
    _StartCtrNode = S;
    _EndCtrNode = E;
}

void DComponent::GetCtrNodes(Vertex *&S, Vertex*&E) { S = _StartCtrNode; E = _EndCtrNode; }

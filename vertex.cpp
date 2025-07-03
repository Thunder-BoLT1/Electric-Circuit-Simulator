#include "vertex.h"

int Vertex::Count = 0;

Vertex::Vertex() {
    Parent = nullptr;
    hasItem = false;
    isVisited = 0;
    G_cost = 9999999;
    H_cost = 9999999;
    T_cost = 0;
    NodeID = -1;
    GridID = Count++;
}

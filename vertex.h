#ifndef VERTEX_H
#define VERTEX_H

struct Vertex
{
    static int Count;
    int GridID, NodeID ,G_cost, H_cost, T_cost;
    bool hasItem;
    int isVisited;
    Vertex* Parent;
    Vertex();
};

#endif // VERTEX_H

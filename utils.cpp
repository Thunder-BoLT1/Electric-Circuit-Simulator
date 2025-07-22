#include "utils.h"
#include <queue>
#include <qDebug>

struct CompareVertex {
    bool operator()(const Vertex* a, const Vertex* b) const {
        if((a->G_cost + a->H_cost + a->T_cost) != (b->G_cost + b->H_cost + b->T_cost)) return (a->G_cost + a->H_cost + a->T_cost) > (b->G_cost + b->H_cost + b->T_cost);
        return a->H_cost > b->H_cost;
    }
};

namespace Utils{
    QPointF GetNearestGridPoint(QPointF point){
        QPointF NewPoint((int(point.x()) / 30) * 30, (int(point.y()) / 30)* 30);
        if(int(point.x() - NewPoint.x()) > 15) NewPoint.setX(NewPoint.x() + 30);
        if(int(point.y() - NewPoint.y()) > 15) NewPoint.setY(NewPoint.y() + 30);
        return NewPoint;
    }
    int GetGridID(QPointF pos){ return pos.x() / 30 + (pos.y() / 30) * 31 ;}
    bool isCorrectPos(QPointF NewPos){ return !(NewPos.x() <= 30 || NewPos.x() >= 870 || NewPos.y() <= 30 || NewPos.y() >= 570); }
    bool AStar(QVector<QVector<Vertex>> & Grid, int Start, int End){
        std::priority_queue<Vertex*, std::vector<Vertex*>, CompareVertex> open;
        Vertex* curr = &Grid[Start/31][Start%31];
        curr->G_cost = 0;
        curr->H_cost = (abs(End-Start)/31 + abs(End-Start) % 31) * 10;
        open.push(curr);
        while(!open.empty()){
            curr = open.top();
            open.pop();
            curr->isVisited = 2;
            if(curr->GridID == End) return true;
            int row = curr->GridID / 31, col = curr->GridID % 31;
            int arr[4][2] = {{row, col - 1}, {row, col + 1}, {row - 1, col}, {row + 1, col}};
            for(int i = 0; i < 4; i++){
                int newRow = arr[i][0], newCol = arr[i][1];
                if(newRow >= 0 && newRow <= 20 && newCol >= 0 && newCol <= 30 && !Grid[newRow][newCol].hasItem && Grid[newRow][newCol].isVisited < 2){
                    if(curr->G_cost + 10 < Grid[newRow][newCol].G_cost){
                        Grid[newRow][newCol].G_cost = curr->G_cost + 10;
                        Grid[newRow][newCol].H_cost = (abs(End/31 - newRow) + abs(End%31 - newCol)) * 10;
                        Grid[newRow][newCol].T_cost = curr->T_cost;
                        if(curr->Parent) {
                            if(abs(curr->Parent->GridID - curr->GridID) != abs((newRow*31 + newCol) - curr->GridID))
                            Grid[newRow][newCol].T_cost += 4;
                        }
                        Grid[newRow][newCol].Parent = curr;
                        Grid[newRow][newCol].isVisited = 1;
                        open.push(&Grid[newRow][newCol]);
                    }
                }
            }
        }
        return false;
    }
    QList<QPointF> ShortestPath(QVector<QVector<Vertex>> & Grid, int Start, int End){
        QList<QPointF> path;
        if(AStar(Grid, Start, End)){
            int row = End/31, col = End%31;
            Vertex* curr = &Grid[row][col];
            while(curr){
                row = curr->GridID/31, col = curr->GridID%31;
                path.push_back(QPointF(col*30,row*30));
                curr = curr->Parent;
            }
        }
        return path;
    }
}

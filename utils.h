#ifndef UTILS_H
#define UTILS_H
#include <QPointF>
#include <QList>
#include "vertex.h"

namespace Utils{
    QPointF GetNearestGridPoint(QPointF);
    int GetGridID(QPointF);
    bool AStar(QVector<QVector<Vertex>> & Grid, int Start, int End);
    QList<QPointF> ShortestPath(QVector<QVector<Vertex>> & Grid, int Start, int End);
}
#endif // UTILS_H

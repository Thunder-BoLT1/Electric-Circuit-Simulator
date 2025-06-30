#ifndef WIRE_H
#define WIRE_H

#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include "utils.h"

class Wire
{
    static QPen WirePen;
    static QBrush WireBrush;
    QGraphicsLineItem *HLine, *VLine;
    QGraphicsEllipseItem *StartNode, *EndNode;
    QPointF StartPos, EndPos;
public:
    Wire(QGraphicsScene*, QPointF);
    ~Wire();
    void AdjustEndPoint(QPointF);
    void GetWireConnection(QPointF&, QPointF&);
};

#endif // WIRE_H

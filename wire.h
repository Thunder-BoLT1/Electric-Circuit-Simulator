#ifndef WIRE_H
#define WIRE_H

#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QDir>
#include "utils.h"

class Wire: public QGraphicsItem
{
    static QPen WirePen;
    static QBrush WireBrush;
    QGraphicsLineItem *HLine, *VLine;
    QGraphicsEllipseItem *StartNode, *EndNode;
    QPointF StartPos, EndPos;
public:
    Wire(QPointF);
    void AdjustEndPoint(QPointF);
    void GetWireConnection(QPointF&, QPointF&);
    QRectF boundingRect() const override;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) override;
protected:
   void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // WIRE_H

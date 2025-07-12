#ifndef WIRE_H
#define WIRE_H

#include <QGraphicsLineItem>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QDir>
#include "GraphicsItem.h"
#include "items.h"
#include "utils.h"

class GraphicsView;

class Wire: public QGraphicsItem
{
    static QPen WirePen;
    static QBrush WireBrush;
    IComponent* Component;
    QGraphicsPathItem *Line;
    QGraphicsEllipseItem *StartNode, *EndNode;
    QPointF StartPos, EndPos;
    GraphicsView* view;
    //Utility Functions
    bool isValidPath(QList<QPointF>&);
public:
    Wire(GraphicsView*, QPointF);
    void AdjustEndPoint(QVector<QVector<Vertex>> &, QPointF);
    IComponent* GetComponent();
    void FixWireNodes(QVector<QVector<Vertex>> & Grid);
    QRectF boundingRect() const override;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) override;
protected:
   void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // WIRE_H

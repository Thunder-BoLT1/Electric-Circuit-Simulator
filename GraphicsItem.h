#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QCoreApplication>
#include <QMenu>
#include <QDir>
#include "items.h"
#include <QRectF>
#include <independentinputdialog.h>
#include <QMessageBox>

class GraphicsItem :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    static QPointF PressPos, Offset;
    IComponent* Component;
public:
    GraphicsItem(QPixmap Image, Components type);
    GraphicsItem(GraphicsItem& other);
    ~GraphicsItem();
    IComponent * GetComponent();

signals:
    void duplicateRequest(GraphicsItem* item);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

    //QRectF boundingRect() const override;

};

#endif // GRAPHICSITEM_H

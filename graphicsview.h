#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <unordered_map>
#include <utility>
#include <QWidget>
#include "GraphicsItem.h"
#include "wire.h"

/*
 * This Might Be Used Later will ignore it for now
namespace std {
template<>
struct hash<Vertex> {
    size_t operator()(const Vertex& v) const noexcept {
        return hash<int>()(v.GridId);
    }
};
}
*/
enum Mode{
    Design,
    Run
};
class GraphicsView: public QGraphicsView
{
    GraphicsItem* MovingItem;
    QVector<IComponent*> NetList;
    QVector<Wire*> Wires;
    QVector<QVector<Vertex>> Grid; //0 For Free 1 For Blcoked (ie. Circuit Elemnt Exists)
    /*I will use an unorderedmap to store the graph each vertix will be a constant number depending on the position in the grid then for each node (ie. vertix)
     *  I will use a QVector with pairs each pair holds the other node and the connecting electric component pointer
    */
    std::pmr::unordered_map<int, QVector<std::pair<int, IComponent*>>> Graph;
    //For wiring feature
    Wire* CurrWire;
    Mode currMode;
public:
    GraphicsView(QWidget * widget = nullptr);
    void SetMovingItem(GraphicsItem* Item = nullptr);
    void AddToGV(GraphicsItem* Item);
    GraphicsItem* GetMovingItem();
    void ResetGV();
    void RemoveItemFromNetlist(IComponent*);
    void RemoveItemFromGrid(GraphicsItem*);
    void AddItemToGrid(GraphicsItem*);
    void SetElementNodes(GraphicsItem*);
    void RunSimulation();
    int NumberNodes();
    void BuildMatrix(Eigen::MatrixXd &, Eigen::MatrixXd &);
    void UpdateComponents(Eigen::MatrixXd &, int);
    void ResetGrid();
    Mode GetMode();
    void ToggleMode();
protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
private slots:
    void HandleDuplicate(GraphicsItem* Item);
};

#endif // GRAPHICSVIEW_H

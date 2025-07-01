#ifndef WIDGET_H
#define WIDGET_H
#define ComponentsCount 3

#include <QWidget>
#include <QGraphicsScene>
#include <qDebug>
#include "GraphicsItem.h"
#include "items.h"
#include <QMenuBar>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QAction>
#include "ComponentsMenu.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
    QString DirPath = QDir::currentPath();
    QPixmap ComponentsImages[ComponentsCount] = {QPixmap(DirPath + "\\IVS.png"), QPixmap(DirPath + "\\ICS.png"),QPixmap(DirPath + "\\RES2.png")};;

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QGraphicsScene * scene;

    //Initialization Functions
    void SetupGrid();
    void GVInit();
    void MenuInit();

private slots:
    void OpenComponenetsMenu();
    void RunSimulation();
    void ClearGV();
};
#endif // WIDGET_H

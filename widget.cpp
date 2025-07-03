#include "widget.h"
#include "ui_widget.h"

#define GridWidth 900
#define GridHight 600
#define GridSize 30

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    scene = new QGraphicsScene;
    MenuInit();
    GVInit();
}

//Initalization Functions
void Widget::SetupGrid(){
    for(int i = 0; i < GridWidth; i += GridSize) scene->addLine(i, 0, i , GridHight, QPen(Qt::gray));
    for(int i = 0; i < GridHight; i += GridSize) scene->addLine(0, i, GridWidth , i, QPen(Qt::gray));
}
void Widget::GVInit(){
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    SetupGrid();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}

void Widget::MenuInit(){
    QMenuBar* MenuBar = new QMenuBar(this);
    QAction* Components = new QAction(QIcon(DirPath + "\\resistor.png"), "Components", this);
    QAction* Run = new QAction(QIcon(DirPath + "\\playButton.png"), "Run", this);
    QAction* Clear = new QAction(QIcon(DirPath + "\\delete.png"), "Clear", this);
    MenuBar->addAction(Components);
    MenuBar->addAction(Run);
    MenuBar->addAction(Clear);
    MenuBar->resize(1200, 21);
    connect(Components, &QAction::triggered, this, &Widget::OpenComponenetsMenu);
    connect(Run, &QAction::triggered, this, &Widget::RunSimulation);
    connect(Clear, &QAction::triggered, this, &Widget::ClearGV);
}

void Widget::OpenComponenetsMenu(){
    ComponentsMenu menu;
    if(menu.exec() == QDialog::Accepted){
        GraphicsItem* NewItem = nullptr;
        if(menu.Get_Type() == "Voltage Source") NewItem = new GraphicsItem(ComponentsImages[IVS], IVS, ui->graphicsView);
        else if(menu.Get_Type() == "Current Source") NewItem = new GraphicsItem(ComponentsImages[ICS], ICS, ui->graphicsView);
        else if(menu.Get_Type() == "Resistor") NewItem = new GraphicsItem(ComponentsImages[RES], RES, ui->graphicsView);
        ui->graphicsView->AddToGV(NewItem);
    }
}

void Widget::RunSimulation(){
    ui->graphicsView->BuildGraph();
}

void Widget::ClearGV(){
    ui->graphicsView->ResetGV();
    SetupGrid();
}

Widget::~Widget()
{
    delete ui;
}

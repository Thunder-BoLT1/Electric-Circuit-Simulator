#ifndef ITEMS_H
#define ITEMS_H
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QCoreApplication>
#include <QMenu>
#include <QDir>
#include "IComponent.h"
#include "utils.h"

enum Components{
    IVS, ICS, RES,VCVS, VCCS, CCVS, CCCS
};

class IVSItem: public IComponent
{
    static int Count;
public:
    IVSItem();
    //Override Pure Virtual Function For IVS
    virtual void  WriteToMatrix(Eigen::MatrixXd &GMatrix, Eigen::MatrixXd &CMatrix);
    virtual void ReadFromMatrix(Eigen::MatrixXd &, int&);
    virtual IComponent*  CreateCopy();
};

class ICSItem: public IComponent
{
    static int Count;
public:
    ICSItem();
    //Override Pure Virtual Function For ICS
    virtual void  WriteToMatrix(Eigen::MatrixXd &GMatrix, Eigen::MatrixXd &CMatrix);
    virtual void ReadFromMatrix(Eigen::MatrixXd &, int&);
    virtual IComponent*  CreateCopy();
};

class RESItem: public IComponent
{
    static int Count;
public:
    RESItem();
    //Override Pure Virtual Function For RES
    virtual void  WriteToMatrix(Eigen::MatrixXd &GMatrix, Eigen::MatrixXd &CMatrix);
    virtual void ReadFromMatrix(Eigen::MatrixXd &, int&);
    virtual IComponent*  CreateCopy();
};


#endif // ITEMS_H

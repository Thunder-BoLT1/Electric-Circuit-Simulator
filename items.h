#ifndef ITEMS_H
#define ITEMS_H
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QCoreApplication>
#include <QMenu>
#include <QDir>
#include "IComponent.h"

enum Components{
    IVS, ICS, RES,VCVS, VCCS, CCVS, CCCS
};

class IVSItem: public IComponent
{
public:
    //Override Pure Virtual Function For IVS
    virtual void  WriteToMatrix();
    virtual void ReadFromMatrix();
    virtual IComponent*  CreateCopy();
};

class ICSItem: public IComponent
{
public:
    //Override Pure Virtual Function For ICS
    virtual void  WriteToMatrix();
    virtual void ReadFromMatrix();
    virtual IComponent*  CreateCopy();
};

class RESItem: public IComponent
{
public:
    //Override Pure Virtual Function For RES
    virtual void  WriteToMatrix();
    virtual void ReadFromMatrix();
    virtual IComponent*  CreateCopy();
};


#endif // ITEMS_H

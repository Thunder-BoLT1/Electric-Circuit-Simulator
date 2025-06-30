#include "utils.h"

namespace Utils{
    QPointF GetNearestGridPoint(QPointF point){
        QPointF NewPoint((int(point.x()) / 30) * 30, (int(point.y()) / 30)* 30);
        if(int(point.x() - NewPoint.x()) > 15) NewPoint.setX(NewPoint.x() + 30);
        if(int(point.y() - NewPoint.y()) > 15) NewPoint.setY(NewPoint.y() + 30);
        return NewPoint;
    }
}


#include "editor_ObjectModel.h"

ObjectModel::ObjectModel(const double &x, const double &y, const int &angle) :
        x(x),y(y),angle(angle) {}

void ObjectModel::updatePosition(double x, double y) {
    this->x=x;
    this->y=y;
}

int ObjectModel::turn() {
    return angle = (angle +10)%180;
}

void ObjectModel::getPosition(double &x, double &y) {
    x=this->x;
    y=this->y;
}

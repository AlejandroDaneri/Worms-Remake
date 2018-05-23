
#include "MapObject.h"

MapObject::MapObject(const double &x, const double &y, const int &angle) :
        x(x), y(y), angle(angle) {}

void MapObject::updatePosition(double x, double y) {
    this->x = x;
    this->y = y;
}

int MapObject::turn() {
    return angle = (angle + 10) % 180;
}

void MapObject::getPosition(double &x, double &y) const{
    x = this->x;
    y = this->y;
}

int MapObject::getAngle() const {
    return angle;
}



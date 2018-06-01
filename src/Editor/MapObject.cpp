
#include <cstdlib>
#include "MapObject.h"

MapObject::MapObject(const double &x, const double &y, const int &angle) :
        x(x), y(y), angle(angle) {}

void MapObject::updatePosition(const double &x, const double &y) {
    this->x = x;
    this->y = y;
}

int MapObject::turnCCW() {
    return angle = (angle + 10) % 180;
}

int MapObject::turnCW() {
    if (angle == 0)
        angle = 180;
    return angle = abs((angle - 10) % 180);
}

void MapObject::getPosition(double &x, double &y) const {
    x = this->x;
    y = this->y;
}

const int MapObject::getAngle() const {
    return angle;
}



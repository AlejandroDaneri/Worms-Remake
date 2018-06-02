
#include <cstdlib>
#include "MapObject.h"

MapObject::MapObject(const float &x, const float &y, const int &angle) :
        position(x,y), angle(angle) {}

void MapObject::updatePosition(const float &x, const float &y) {
    position= Position(x,y);
}

int MapObject::turn(const int &rotation){
    if (angle == 0)
        angle = 180;
    return angle = abs((angle+rotation)%180);
}

void MapObject::getPosition(float &x, float &y) const {
    y=position.getY();
    x=position.getX();
}

const int MapObject::getAngle() const {
    return angle;
}



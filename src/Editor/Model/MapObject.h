
#ifndef WORMS_OBJECTMODEL_H
#define WORMS_OBJECTMODEL_H

#include <Position.h>

class MapObject {
    Position position;
    int angle;
public:
    MapObject(const float &x, const float &y, const int &angle = 0);

    void updatePosition(const float &x, const float &y);

    int turnCCW();

    void getPosition(float &x, float &y) const;

    const int getAngle() const;

    int turnCW();
};


#endif //WORMS_OBJECTMODEL_H

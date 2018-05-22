
#ifndef WORMS_OBJECTMODEL_H
#define WORMS_OBJECTMODEL_H


#include "editor_Pos.h"

class ObjectModel {
    Pos position;
public:
    explicit ObjectModel(const Pos &position);

    void updatePos(double x, double y);

    int turn();
};


#endif //WORMS_OBJECTMODEL_H

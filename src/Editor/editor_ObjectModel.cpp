
#include "editor_ObjectModel.h"

ObjectModel::ObjectModel(const Pos &position) :
        position(position) {}

void ObjectModel::updatePos(double x, double y) {
    position.updatePos(x,y);
}

int ObjectModel::turn() {
    return position.turn();
}

void ObjectModel::getPos(double &x, double &y) {
    x=position.getX();
    y=position.getY();

}

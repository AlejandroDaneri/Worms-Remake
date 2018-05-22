
#include "editor_MapModel.h"

//TODO: cambiar posicion por centro
void MapModel::undo() {
    if(!objects.empty())
        this->objects.pop_back();
}

void MapModel::clean() {
    this->objects.clear();
}

void MapModel::add(unsigned int &id, double &x, double &y) {
    ObjectModel new_object(x,y);
    objects.emplace_back(std::make_pair(id,new_object));
}

void MapModel::moveLast(double &x, double &y) {
    ObjectModel &object = objects.back().second;
    object.updatePosition(x, y);
}

int MapModel::turnLast() {
    ObjectModel &object = objects.back().second;
    return object.turn();
}

void MapModel::getLastPosition(double &x, double &y) {
    ObjectModel &last_pos = objects.back().second;
    last_pos.getPosition(x, y);
}

bool MapModel::lastIsGirder() {
    return objects.back().first==2;
}

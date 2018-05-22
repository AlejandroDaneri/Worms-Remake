
#include "editor_MapModel.h"
#include "editor_Pos.h"

//TODO: cambiar posicion por centro
void MapModel::undo() {
    this->objects.pop_back();
}

void MapModel::clean() {
    this->objects.clear();
}

void MapModel::add(unsigned int id, double x, double y) {
    Pos new_pos(x,y);
    ObjectModel new_object(new_pos);
    objects.emplace_back(std::make_pair(id,new_object));
}

void MapModel::moveLast(double x, double y) {
    ObjectModel &object = objects.back().second;
    object.updatePos(x,y);
}

int MapModel::turnLast() {
    ObjectModel &object = objects.back().second;
    return object.turn();
}

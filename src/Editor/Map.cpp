
#include "Map.h"

//TODO: cambiar posicion por centro
void Map::undo() {
    if (!objects.empty())
        this->objects.pop_back();
}

void Map::clean() {
    this->objects.clear();
}

void Map::add(unsigned int &id, double &x, double &y) {
    ObjectModel new_object(x, y);
    objects.emplace_back(std::make_pair(id, new_object));
}

void Map::moveLast(double &x, double &y) {
    ObjectModel &object = objects.back().second;
    object.updatePosition(x, y);
}

int Map::turnLast() {
    ObjectModel &object = objects.back().second;
    return object.turn();
}

bool Map::lastIsGirder() {
    return objects.back().first == 2;
}

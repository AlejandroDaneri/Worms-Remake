
#include <yaml.h>
#include "Map.h"

void Map::undo(int index) {
    if (!objects.empty())
        this->objects.erase(objects.begin() + index);
}

void Map::clean() {
    this->objects.clear();
}

void
Map::add(unsigned int id, const double &x, const double &y, const int &angle) {
    MapObject new_object(x, y, angle);
    objects.emplace_back(std::make_pair(id, new_object));
}

void Map::move(int index, double &x, double &y) {
    MapObject &object = objects[index].second;
    object.updatePosition(x, y);
}

int Map::turnCCWLast(unsigned int index, unsigned int &id) {
    MapObject &object = objects[index].second;
    id = objects[index].first;
    return object.turnCCW();
}

int Map::turnCWLast(unsigned int index, unsigned int &id) {
    MapObject &object = objects[index].second;
    id = objects[index].first;
    return object.turnCW();
}

bool Map::isGirder(int &index) {
    return (objects[index].first > 1);
}

void Map::getObjects(std::vector<std::vector<double>> &worms,
                     std::vector<std::vector<double>> &girders) const {
    for (auto &object : objects) {
        double x, y;
        object.second.getPosition(x, y);
        if (object.first == 1) {//worm
            std::vector<double> position;
            position.push_back(x); //pos x
            position.push_back(y); //pos_y
            worms.push_back(position);
        } else { //viga
            std::vector<double> data;
            data.push_back(object.first); //len
            data.push_back(x); //pos_x
            data.push_back(y); //pos_y
            data.push_back(object.second.getAngle()); //rotation
            girders.push_back(data);
        }
    }
}




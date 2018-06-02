
#include <yaml.h>
#include "Map.h"

void Map::erase(int index) {
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

void Map::move(const int &index, const double &x,const double &y) {
    MapObject &object = objects[index].second;
    object.updatePosition(x, y);
}

const int Map::turn(const unsigned int &index, unsigned int &id, const int &rotation) {
    MapObject &object = objects[index].second;
    id = objects[index].first;
    return object.turn(rotation);
}

const bool Map::isGirder(int &index) const {
    return (objects[index].first > 1);
}

void Map::getObjects(std::vector<std::vector<double>> &worms,
                     std::vector<std::vector<double>> &girders) const {
    for (auto &object : objects) {
        float x, y;
        object.second.getPosition(x, y);
        if (object.first == 1) {
            std::vector<double> position;
            position.push_back(x);
            position.push_back(y);
            worms.push_back(position);
        } else {
            std::vector<double> data;
            data.push_back(object.first);
            data.push_back(x);
            data.push_back(y);
            data.push_back(object.second.getAngle());
            girders.push_back(data);
        }
    }
}

const int Map::getItemID(const int &index) const{
    return objects[index].first ;
}




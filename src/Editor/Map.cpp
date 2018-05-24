
#include <yaml.h>
#include "Map.h"

//TODO: cambiar posicion por centro
void Map::undo() {
    if (!objects.empty())
        this->objects.pop_back();
}

void Map::clean() {
    this->objects.clear();
}

void Map::add(unsigned int id, const double & x, const double & y, const int &angle) {
    MapObject new_object(x, y,angle);
    objects.emplace_back(std::make_pair(id, new_object));
}

void Map::moveLast(double &x, double &y) {
    MapObject &object = objects.back().second;
    object.updatePosition(x, y);
}

int Map::turnCCWLast() {
    MapObject &object = objects.back().second;
    return object.turnCCW();
}

int Map::turnCWLast() {
    MapObject &object = objects.back().second;
    return object.turnCW();
}

bool Map::lastIsGirder() {
    return (objects.back().first == 2 || objects.back().first == 3);
}

void Map::getObjects(std::vector<std::vector<double>> &worms,
                     std::vector<std::vector<double>> &girders) const {
    //gusanos
    for (auto &object : objects) {
        double x, y;
        object.second.getPosition(x, y);
        if (object.first == 1) {//worm
            std::vector<double> position;
            position.push_back(x); //pos x
            position.push_back(y); //pos_y
            worms.push_back(position);
        } else if (object.first == 2) { //viga corta
            std::vector<double> data;
            data.push_back(3); //len
            data.push_back(x); //pos_x
            data.push_back(y); //pos_y
            data.push_back(object.second.getAngle()); //rotation
            girders.push_back(data);
        }
    }

}

void Map::load_signal() {

}




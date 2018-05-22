
#ifndef WORMS_MAPMODEL_H
#define WORMS_MAPMODEL_H


#include <utility>
#include <vector>
#include "editor_ObjectModel.h"

class MapModel {
    std::vector<std::pair<int,ObjectModel>> objects;

public:
    void undo();

    void clean();

    void add(unsigned int id, double &x, double &y);

    void moveLast(double &x, double &y);

    int turnLast();

    void getLastPosition(double &x, double &y);
};


#endif //WORMS_MAPMODEL_H

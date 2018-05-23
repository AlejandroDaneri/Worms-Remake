
#ifndef WORMS_MAPMODEL_H
#define WORMS_MAPMODEL_H


#include <utility>
#include <vector>
#include "ObjectModel.h"

class Map {
    std::vector<std::pair<int, ObjectModel>> objects;

public:
    void undo();

    void clean();

    void add(unsigned int &id, double &x, double &y);

    void moveLast(double &x, double &y);

    int turnLast();

    void getLastPosition(double &x, double &y);

    bool lastIsGirder();
};


#endif //WORMS_MAPMODEL_H

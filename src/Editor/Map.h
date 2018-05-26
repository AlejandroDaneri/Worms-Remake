
#ifndef WORMS_MAPMODEL_H
#define WORMS_MAPMODEL_H


#include <utility>
#include <vector>
#include "MapObject.h"

class Map {
    std::vector<std::pair<int, MapObject>> objects;

public:
    void undo();

    void clean();

    void add(unsigned int id, const double &x, const double &y,
             const int &angle = 0);

    void moveLast(double &x, double &y);

    int turnCCWLast();

    bool lastIsGirder();

    void getObjects(std::vector<std::vector<double>> &worms,
                    std::vector<std::vector<double>> &girders) const;

    int turnCWLast();
};


#endif //WORMS_MAPMODEL_H

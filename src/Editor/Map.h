
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

    void add(unsigned int &id, double &x, double &y);

    void moveLast(double &x, double &y);

    int turnLast();

    bool lastIsGirder();

    void load_signal();

    void getObjects(std::vector<std::vector<double>> &worms,
                    std::vector<std::vector<double>> &girders) const;

    const std::vector<std::pair<int, MapObject>> &getObjects() const;
};


#endif //WORMS_MAPMODEL_H

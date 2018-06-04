
#ifndef WORMS_MAPMODEL_H
#define WORMS_MAPMODEL_H


#include <utility>
#include <vector>
#include "MapObject.h"

class Map {
    std::vector<std::pair<int, MapObject>> contained_objects;

public:
    void erase(const int &index);

    void clean();

    void add(const unsigned int &id, const double &x, const double &y,
             const int &angle = 0);


    void getObjects(std::vector<std::vector<double>> &worms,
                    std::vector<std::vector<double>> &girders) const;

    void move(const int &index, const double &x, const double &y);

    const bool isGirder(int &index) const;

    const int getItemID(const int &index) const;

    const int
    turn(const unsigned int &index, unsigned int &id, const int &rotation);
};


#endif //WORMS_MAPMODEL_H

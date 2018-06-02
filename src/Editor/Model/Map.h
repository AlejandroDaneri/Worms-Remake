
#ifndef WORMS_MAPMODEL_H
#define WORMS_MAPMODEL_H


#include <utility>
#include <vector>
#include "Modelo/MapObject.h"

class Map {
    std::vector<std::pair<int, MapObject>> objects;

public:
    void erase(int index);

    void clean();

    void add(unsigned int id, const double &x, const double &y,
             const int &angle = 0);


    void getObjects(std::vector<std::vector<double>> &worms,
                    std::vector<std::vector<double>> &girders) const;


    const int turnCWLast(const unsigned int &index, unsigned int &id);

    const int turnCCWLast(const unsigned int &index, unsigned int &id);

    void move(const int &index, const double &x, const double &y);

    const bool isGirder(int &index) const;

    const int getItemID(const int &index) const;
};


#endif //WORMS_MAPMODEL_H

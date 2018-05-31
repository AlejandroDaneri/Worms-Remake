
#ifndef WORMS_MAPMODEL_H
#define WORMS_MAPMODEL_H


#include <utility>
#include <vector>
#include "MapObject.h"

class Map {
    std::vector<std::pair<int, MapObject>> objects;

public:
    void erase(int index);

    void clean();

    void add(unsigned int id, const double &x, const double &y,
             const int &angle = 0);


    void getObjects(std::vector<std::vector<double>> &worms,
                    std::vector<std::vector<double>> &girders) const;


    int turnCWLast(unsigned int index, unsigned int &id);

    int turnCCWLast(unsigned int index, unsigned int &id);

    void move(int index, double &x, double &y);

    bool isGirder(int &index);

    int getItemID(const int &index);
};


#endif //WORMS_MAPMODEL_H

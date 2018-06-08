
#ifndef WORMS_MAPMODEL_H
#define WORMS_MAPMODEL_H


#include <utility>
#include <vector>
#include "MapObject.h"

// Clase que se encarga de modelar el mapa
class Map {
    std::vector<std::pair<int, MapObject>> contained_objects;

public:
    // Borra el objeto que se encuentra en la posicion index del vector
    void erase(const int &index);

    // Borra todos los objetos contenidos en el mapa
    void clean();

    // Agregar un objeto en la posicion (x,y)
    void add(const unsigned int &id, const double &x, const double &y,
             const int &angle = 0);

    // Obtiene todos los objetos contenidos en el mapa separados por tipo
    void getObjects(std::vector<std::vector<double>> &worms,
                    std::vector<std::vector<double>> &girders) const;

    // Mueve el objeto en la posicion index del vector hacia la posicion
    // (x,y) del mapa
    void move(const int &index, const double &x, const double &y);

    // Devuelve verdadero si el objeto en la posicion index es una viga
    const bool isGirder(int &index) const;

    // Obtiene el tipo del objeto en la posicion index del vector
    const int getItemID(const int &index) const;

    // Gira el objeto en la posicion index del vector en un angulo indicado
    const int
    turn(const unsigned int &index, unsigned int &id, const int &rotation);
};


#endif //WORMS_MAPMODEL_H

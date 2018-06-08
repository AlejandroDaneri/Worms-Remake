
#ifndef WORMS_OBJECTMODEL_H
#define WORMS_OBJECTMODEL_H

#include <Position.h>

// Clase que modela un objeto contenido en el mapa
class MapObject {
    Position position;
    int angle;
public:
    MapObject(const float &x, const float &y, const int &angle = 0);

    // Actualiza la posicion en la que se encuentra el objeto
    void updatePosition(const float &x, const float &y);

    // Obtiene la posicion en la que se encuentra el objeto
    void getPosition(float &x, float &y) const;

    // Actualiza el angulo en la que se encuentra el objeto
    const int getAngle() const;

    // Gira el objeto la cantidad especificada
    int turn(const int &rotation);
};


#endif //WORMS_OBJECTMODEL_H

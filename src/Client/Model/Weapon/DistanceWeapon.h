#ifndef __CLIENTDISTANCEWEAPON_H__
#define __CLIENTDISTANCEWEAPON_H__

#include "Weapon.h"
#include <string>

/* Clase que se encarga de representar a las armas de distancia */
class DistanceWeapon : public Weapon {
public:
	/* Constructor */
	DistanceWeapon(std::string name, int ammo, bool time = false);

	/* Destructor */
	~DistanceWeapon();

	/* Constructor por movimiento */
	DistanceWeapon(DistanceWeapon&& other);


	/* Devuelve true si el arma tiene potencia variable */
	bool hasVariablePower() const override;
};

#endif

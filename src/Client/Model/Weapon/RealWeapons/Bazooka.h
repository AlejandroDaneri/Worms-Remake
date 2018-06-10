#ifndef __CLIENTBAZOOKA_H__
#define __CLIENTBAZOOKA_H__

#include "DistanceWeapon.h"

/* Clase que representa al arma Bazooka */
class Bazooka : public DistanceWeapon {
public:
	/* Constructor */
	explicit Bazooka(int ammo);

	/* Destructor */
	~Bazooka();

	/* Constructor por movimiento */
	Bazooka(Bazooka&& other);
};

#endif

#ifndef __CLIENTMORTAR_H__
#define __CLIENTMORTAR_H__

#include "DistanceWeapon.h"

/* Clase que representa al arma Mortero */
class Mortar : public DistanceWeapon {
public:
	/* Constructor */
	explicit Mortar(int ammo);

	/* Destructor */
	~Mortar();

	/* Constructor por movimiento */
	Mortar(Mortar&& other);
};

#endif

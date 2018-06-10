#ifndef __CLIENTTELEPORTATION_H__
#define __CLIENTTELEPORTATION_H__

#include "SelfDirectedWeapon.h"

/* Clase que representa al arma Teletransportador */
class Teleportation : public SelfDirectedWeapon {
public:
	/* Constructor */
	explicit Teleportation(int ammo);

	/* Destructor */
	~Teleportation();

	/* Constructor por movimiento */
	Teleportation(Teleportation&& other);
};

#endif

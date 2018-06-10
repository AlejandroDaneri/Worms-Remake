#ifndef __CLIENTREDGRENADE_H__
#define __CLIENTREDGRENADE_H__

#include "DistanceWeapon.h"

/* Clase que representa al arma Granada roja */
class RedGrenade : public DistanceWeapon {
public:
	/* Constructor */
	explicit RedGrenade(int ammo);

	/* Destructor */
	~RedGrenade();

	/* Constructor por movimiento */
	RedGrenade(RedGrenade&& other);
};

#endif

#ifndef __CLIENTGREENGRENADE_H__
#define __CLIENTGREENGRENADE_H__

#include "DistanceWeapon.h"

/* Clase que representa al arma Granada verde */
class GreenGrenade: public DistanceWeapon {
	public:
        /* Constructor */
		GreenGrenade(int ammo);

		/* Destructor */
		~GreenGrenade();

		/* Constructor por movimiento */
		GreenGrenade(GreenGrenade&& other);
};

#endif

#ifndef __CLIENTHOLYGRENADE_H__
#define __CLIENTHOLYGRENADE_H__

#include "DistanceWeapon.h"

/* Clase que representa al arma Granada santa */
class HolyGrenade: public DistanceWeapon {
	public:
        /* Constructor */
		HolyGrenade(int ammo);

		/* Destructor */
		~HolyGrenade();

		/* Constructor por movimiento */
		HolyGrenade(HolyGrenade&& other);
};

#endif

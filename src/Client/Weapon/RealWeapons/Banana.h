#ifndef __CLIENTBANANA_H__
#define __CLIENTBANANA_H__

#include "DistanceWeapon.h"

/* Clase que representa al arma Banana */
class Banana: public DistanceWeapon {
	public:
        /* Constructor */
		Banana(int ammo);

		/* Destructor */
		~Banana();

		/* Constructor por movimiento */
		Banana(Banana&& other);
};

#endif

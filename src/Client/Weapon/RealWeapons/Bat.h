#ifndef __CLIENTBAT_H__
#define __CLIENTBAT_H__

#include "MeleeWeapon.h"

/* Clase que representa al arma Bat de baseball */
class Bat: public MeleeWeapon {
	public:
        /* Constructor */
		Bat(int ammo);

		/* Destructor */
		~Bat();

		/* Constructor por movimiento */
		Bat(Bat&& other);
};

#endif

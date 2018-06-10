#ifndef __CLIENTDYNAMITE_H__
#define __CLIENTDYNAMITE_H__

#include "MeleeWeapon.h"

/* Clase que representa al arma Dinamita */
class Dynamite : public MeleeWeapon {
public:
	/* Constructor */
	explicit Dynamite(int ammo);

	/* Destructor */
	~Dynamite();

	/* Constructor por movimiento */
	Dynamite(Dynamite&& other);
};

#endif
